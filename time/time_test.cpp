#include <stdint.h>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <string>
#include <limits>
#include <chrono>
#include <cmath>
#include <iomanip>

#include "time/algorithms/benjoffe.hpp"
#include "time/algorithms/neri.hpp"
#include "time/algorithms/traditional.hpp"

static constexpr const char* RESET = "\033[0m";
static constexpr const char* AMBER = "\033[38;5;216m";
static constexpr const char* RED   = "\033[38;5;203m";

static std::string pad_right(std::string s, int w) {
    while ((int)s.size() < w) s = s + " ";
    return s;
}
static std::string pad_left(std::string s, int w) {
    while ((int)s.size() < w) s = " " + s;
    return s;
}

template <typename V>
static std::string ostr(const V& v) {
    std::ostringstream o;
    o << v;
    return o.str();
}

// TIME_SUBUNIT's own operator<< always prints 9 (nanosecond) sub-digits;
// these format with exactly the number of digits the domain actually has
// (1 for deci-, 2 for centi-, 3 for milliseconds, ...). `digits` is unused
// for TIME_S, which has no fractional part.
static std::string fmt_time(const TIME_S& v, int) { return ostr(v); }
static std::string fmt_time(const TIME_SUBUNIT& v, int digits) {
    std::ostringstream o;
    o << std::setfill('0')
      << std::setw(2) << v.hour << ":"
      << std::setw(2) << v.min << ":"
      << std::setw(2) << v.sec << "."
      << std::setw(digits) << v.sub;
    return o.str();
}

static constexpr int W_ALGO = 22, W_RANGE = 42, W_RETURN = 26;

static void table_sep() {
    std::cout << AMBER << "+" << std::string(W_ALGO + 2, '-')
              << "+" << std::string(W_RANGE + 2, '-')
              << "+" << std::string(W_RETURN + 2, '-')
              << "+" << RESET << "\n";
}
static void table_header() {
    table_sep();
    std::cout << AMBER
              << "| " << pad_right("ALGORITHM", W_ALGO)
              << " | " << pad_right("MAX INPUT   (period: 24hr is sufficient)", W_RANGE)
              << " | " << pad_left("MAX RETURN VALUE", W_RETURN)
              << " |" << RESET << "\n";
    table_sep();
}

// color == nullptr while ticking (plain, no highlight).
static void print_row(const std::string& algo, const std::string& range,
                      const std::string& ret, const char* color) {
    const char* col = color ? color : RESET;
    std::cout << col
              << "| " << pad_right(algo, W_ALGO)
              << " | " << pad_right(range, W_RANGE)
              << " | " << pad_left(ret, W_RETURN)
              << " |" << RESET << "\n";
}

// Rounds `units` (in T's own domain unit) to whichever of hours/days/years
// reads best, given `day` = how many of those units make up 24h. A "+" marks
// a rounded-down value, i.e. the algorithm is valid for *at least* this long.
static std::string format_duration(uint64_t units, uint64_t day) {
    const double hours = double(units) * 24.0 / double(day);
    const double days_v  = hours / 24.0;
    const double years_v = days_v / 365.0;

    double val; const char* unit;
    if (days_v >= 365.0)    { val = years_v; unit = "year"; }
    else if (hours >= 48.0) { val = days_v;  unit = "day";  }
    else                    { val = hours;   unit = "hour"; }

    const double whole = std::floor(val + 1e-9);
    const bool exact = (val - whole) < 1e-6;
    const long long n = (long long)whole;

    std::string s = "(" + std::to_string(n) + " " + unit + (n == 1 ? "" : "s");
    if (!exact) s += "+";
    s += ")";
    return s;
}

// "X" left-aligned, with a parenthesized annotation right-aligned in the
// same cell.
static std::string range_cell(uint64_t x, const std::string& note, int width) {
    std::string left = std::to_string(x);
    int pad = width - (int)left.size() - (int)note.size();
    if (pad < 1) pad = 1;
    return left + std::string(pad, ' ') + note;
}

// Deduces the domain type T that a test function operates on, straight from
// its own signature (Ret(*)(T)) — that's what "just works" without a
// separate min/max argument: T's own [0, TMAX] *is* the domain.
template <typename Ret, typename Arg>
static Arg deduce_domain(Ret(*)(Arg));

// Sweeps the whole domain of `test`'s argument type, from 0 to TMAX. With
// step == 1 every value is checked; with step > 1 only the two values at
// each step boundary (t % step == 0 and 1) are checked, since that's where a
// fast approximate algorithm's rounding errors show up. The sweep ends when
// it lands exactly on TMAX and steps once more, wrapping back to 0 — that
// wrap (not a separate counter, which would overflow for 64-bit domains) is
// what marks "done".
//
// day: how many units of T make up 24 hours. A mismatch found at or beyond
// that point isn't a real failure — these algorithms are only promised to be
// correct for at least a day, and are free to drift once the domain runs
// past what a clock ever needs; the row still reports exactly how far it got.
//
// frac_digits: how many digits ref's sub-second field actually holds (0 for
// TIME_S, which has none).
template <typename Fref, typename Ftest>
static bool run_search(const char* label, Fref ref, Ftest test, uint32_t step, uint64_t day,
                       int frac_digits = 0) {
    using T = decltype(deduce_domain(test));
    constexpr T TMAX = std::numeric_limits<T>::max();
    constexpr int BITS = int(sizeof(T) * 8);
    constexpr uint32_t PRINT_FREQ = 1 << 20;

    print_row(label, "0..0", "", nullptr);
    std::cout << "\033[1A\r" << std::flush;

    T t = 0, last_ok = 0;
    uint32_t ticks = 0;
    for (;;) {
        T v = t; asm volatile("" : "+r"(v));
        auto r = ref(v);
        auto g = test(v);
        if (!(r == g)) {
            // step > 1 only checks values right around each step boundary, so a
            // mismatch found straight after a skip could really have started
            // anywhere inside the chunk that got jumped over (and usually did,
            // a bit earlier). Walk that chunk one value at a time to pin down
            // the true first failure before reporting it.
            if (step > 1 && t > T(last_ok + 1)) {
                for (T v2 = T(last_ok + 1); v2 != t; v2 = T(v2 + 1)) {
                    auto r2 = ref(v2);
                    auto g2 = test(v2);
                    if (!(r2 == g2)) { t = v2; r = r2; g = g2; break; }
                    last_ok = v2;
                }
            }

            const bool ok = uint64_t(last_ok) >= day;
            // +1: the range 0..last_ok is inclusive of 0, so it covers
            // last_ok + 1 units of time, not last_ok.
            print_row(label, range_cell(uint64_t(last_ok), format_duration(uint64_t(last_ok) + 1, day), W_RANGE),
                      fmt_time(ref(last_ok), frac_digits), ok ? AMBER : RED);
            if (!ok) {
                std::cout << RED << "  expected " << fmt_time(r, frac_digits)
                          << ", got " << fmt_time(g, frac_digits)
                          << " at t=" << uint64_t(t) << RESET << "\n";
                return false;
            }
            return true;
        }
        last_ok = t;

        const T prev = t;
        if (step > 1 && t % step == 1) {
            const T remaining = TMAX - t;
            const T skip = T(step - 2);
            t = (skip > remaining) ? TMAX : T(t + skip);
        } else {
            t = T(t + 1);   // wraps to 0 when prev == TMAX
        }
        if (t == 0 && prev == TMAX) {
            print_row(label, range_cell(uint64_t(prev), "(100% " + std::to_string(BITS) + "-Bit)", W_RANGE),
                      fmt_time(ref(prev), frac_digits), AMBER);
            return true;
        }

        if ((++ticks & (PRINT_FREQ - 1)) == 0) {
            print_row(label, std::to_string(uint64_t(t)), fmt_time(g, frac_digits), nullptr);
            std::cout << "\033[1A\r" << std::flush;
        }
    }
}

static TIME_S time_ref(uint32_t t) {
    return {
        t / 3600,
        (t % 3600) / 60,
        t % 60
    };
}

static TIME_S time_ref_leap(uint32_t t) {
    if (t == 86400) {
        return { 23, 59, 60 };
    }
    if (t == 86401) {
        // Give an obviously invalid value for end-of-day + 1
        // because going beyond 23:59:60 is not defined for
        // our purposes
        return { 0, 0, 0};
    }
    return {
        t / 3600,
        (t % 3600) / 60,
        t % 60
    };
}

static constexpr uint32_t pow10(int n) { return n <= 0 ? 1u : 10u * pow10(n - 1); }

// Reference conversion for t counted in units of 1/10^DECIMALS of a second
// (DECIMALS=1 -> deciseconds, 2 -> centiseconds, 3 -> milliseconds, ...).
template <int DECIMALS>
static TIME_SUBUNIT time_ref_frac(uint32_t t) {
    constexpr uint32_t SCALE = pow10(DECIMALS);
    return {
        t / (3600 * SCALE),
        (t % (3600 * SCALE)) / (60 * SCALE),
        (t % (60 * SCALE)) / SCALE,
        t % SCALE
    };
}

static TIME_SUBUNIT time_ref_ds(uint32_t t) { return time_ref_frac<1>(t); }
static TIME_SUBUNIT time_ref_cs(uint32_t t) { return time_ref_frac<2>(t); }
static TIME_SUBUNIT time_ref_ms(uint32_t t) { return time_ref_frac<3>(t); }

static TIME_SUBUNIT time_ref_ns(uint64_t t) {
    auto total_sec = t / 1'000'000'000ULL;
    auto nano = uint32_t(t % 1'000'000'000ULL);
    auto hour = uint32_t(total_sec / 3600);
    auto rem  = total_sec % 3600;
    auto min  = uint32_t(rem / 60);
    auto sec  = uint32_t(rem % 60);
    return { hour, min, sec, nano };
}

int main() {
    auto t_start = std::chrono::steady_clock::now();

    std::cout << "\nEach algorithm's own argument type defines its domain (e.g. uint32_t\n"
              << "sweeps 0..2^32-1); MAX INPUT is how far it stayed correct before a\n"
              << "mismatch, or 100% N-Bit if it holds for the whole domain. A mismatch\n"
              << "found before 24h of domain is a real FAIL (shown in red, with detail);\n"
              << "one found at or beyond 24h is not -- these algorithms only need to be\n"
              << "correct for at least a day.\n\n";

    table_header();

    // 24h expressed in each domain's own unit.
    constexpr uint64_t DAY_SEC   = 86'400ull;
    constexpr uint64_t DAY_DECI  = 864'000ull;
    constexpr uint64_t DAY_CENTI = 8'640'000ull;
    constexpr uint64_t DAY_MILLI = 86'400'000ull;
    constexpr uint64_t DAY_NANO  = 86'400'000'000'000ull;

    run_search("time_neri",            time_ref,    time_neri,            1u, DAY_SEC);
    run_search("time_neri_fp",         time_ref,    time_neri_fp,         1u, DAY_SEC);
    
    run_search("time_traditional1",    time_ref,    time_traditional1,    1u, DAY_SEC);
    run_search("time_traditional1_fp", time_ref,    time_traditional1_fp, 1u, DAY_SEC);
    run_search("time_traditional2",    time_ref,    time_traditional2,    1u, DAY_SEC);
    run_search("time_traditional3",    time_ref,    time_traditional3,    1u, DAY_SEC);

    run_search("time_benjoffe_v1",     time_ref,    time_benjoffe_v1,     1u, DAY_SEC);
    run_search("time_benjoffe_v1_fp",  time_ref,    time_benjoffe_v1_fp,  1u, DAY_SEC);
    run_search("time_benjoffe_v2",     time_ref,    time_benjoffe_v2,     1u, DAY_SEC);
    run_search("time_benjoffe_v2_64",  time_ref,    time_benjoffe_v2_64,  1u, DAY_SEC);
    run_search("time_benjoffe_v3",     time_ref,    time_benjoffe_v3,     1u, DAY_SEC);
    run_search("time_benjoffe_v3b",     time_ref,    time_benjoffe_v3b,     1u, DAY_SEC);
    run_search("time_benjoffe_v3c",     time_ref,    time_benjoffe_v3c,     1u, DAY_SEC);
    run_search("time_benjoffe_v3_64",  time_ref,    time_benjoffe_v3_64,  1u, DAY_SEC);
    run_search("time_benjoffe_v3_64b",     time_ref, time_benjoffe_v3_64b, 1u, DAY_SEC);
    run_search("time_benjoffe_v4",     time_ref,    time_benjoffe_v4,     1u, DAY_SEC);

    run_search("time_traditional_leap1", time_ref_leap, time_traditional_leap1, 1u, DAY_SEC);
    run_search("time_traditional_leap2", time_ref_leap, time_traditional_leap2, 1u, DAY_SEC);
    run_search("time_benjoffe_leap0",    time_ref_leap, time_benjoffe_leap0,    1u, DAY_SEC);
    run_search("time_benjoffe_leap1",    time_ref_leap, time_benjoffe_leap1,    1u, DAY_SEC);
    run_search("time_benjoffe_leap2",    time_ref_leap, time_benjoffe_leap2,    1u, DAY_SEC);

    // Deci-seconds
    run_search("time_traditional_ds1", time_ref_ds, time_traditional_ds1, 1u, DAY_DECI, 1);
    run_search("time_traditional_ds2", time_ref_ds, time_traditional_ds2, 1u, DAY_DECI, 1);
    run_search("time_benjoffe_ds1",    time_ref_ds, time_benjoffe_ds1,    1u, DAY_DECI, 1);

    // Centiseconds
    run_search("time_traditional_cs1", time_ref_cs, time_traditional_cs1, 1u, DAY_CENTI, 2);
    run_search("time_traditional_cs2", time_ref_cs, time_traditional_cs2, 1u, DAY_CENTI, 2);
    run_search("time_benjoffe_cs1",    time_ref_cs, time_benjoffe_cs1,    1u, DAY_CENTI, 2);
    run_search("time_benjoffe_cs2",    time_ref_cs, time_benjoffe_cs2,    1u, DAY_CENTI, 2);

    // Milliseconds
    run_search("time_traditional_ms1", time_ref_ms, time_traditional_ms1, 1u, DAY_MILLI, 3);
    run_search("time_traditional_ms2", time_ref_ms, time_traditional_ms2, 1u, DAY_MILLI, 3);
    run_search("time_benjoffe_ms1",    time_ref_ms, time_benjoffe_ms1,    1u, DAY_MILLI, 3);
    run_search("time_benjoffe_ms2",    time_ref_ms, time_benjoffe_ms2,    1u, DAY_MILLI, 3);

    // Nanoseconds — full uint64_t domain, step-boundary checked only.
    run_search("time_benjoffe_ns1",    time_ref_ns, time_benjoffe_ns1,   1'000'000'000u, DAY_NANO, 9);
    run_search("time_benjoffe_ns2",    time_ref_ns, time_benjoffe_ns2,   1'000'000'000u, DAY_NANO, 9);
    run_search("time_benjoffe_ns3",    time_ref_ns, time_benjoffe_ns3,   1'000'000'000u, DAY_NANO, 9);
    run_search("time_benjoffe_ns4",    time_ref_ns, time_benjoffe_ns4,   1'000'000'000u, DAY_NANO, 9);
    run_search("time_benjoffe_ns5",    time_ref_ns, time_benjoffe_ns5,   1'000'000'000u, DAY_NANO, 9);
    run_search("time_benjoffe_ns6",    time_ref_ns, time_benjoffe_ns6,   1'000'000'000u, DAY_NANO, 9);

    table_sep();

    double secs = std::chrono::duration<double>(std::chrono::steady_clock::now() - t_start).count();
    std::cout << RESET << "\nCompleted in "
              << std::fixed << std::setprecision(1) << secs << "s\n";

    return 0;
}
