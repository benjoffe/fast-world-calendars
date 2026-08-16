#include <stdint.h>
#include <iostream>
#include <limits>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>
#include <chrono>
#include <type_traits>
#include <algorithm>

#include "util/_portable_int128.hpp"

#include "weekday/algorithms/basic.hpp"
#include "weekday/algorithms/hinnant.hpp"
#include "weekday/algorithms/neri.hpp"
#include "weekday/algorithms/benjoffe.hpp"
#include "weekday/algorithms/benjoffe_extra.hpp"

static const char* weekday_abbr(int64_t day) {
    static const char* names[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    return names[int(((day % 7) + 4 + 7) % 7)];
}

static std::string iso_date(int64_t day) {
    if (day < INT32_MIN || day > INT32_MAX) return "(out of range)";
    int64_t z   = int64_t(day) + 719468;
    int64_t era = (z >= 0 ? z : z - 146096) / 146097;
    int64_t doe = z - era * 146097;
    int64_t yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365;
    int64_t y   = yoe + era * 400;
    int64_t doy = doe - (365*yoe + yoe/4 - yoe/100);
    int64_t mp  = (5*doy + 2) / 153;
    int      d  = int(doy - (153*mp + 2)/5 + 1);
    int      m  = int(mp + (mp < 10 ? 3 : -9));
    y += (m <= 2);
    std::string ys = std::to_string(std::abs(y));
    for (int i = (int)ys.size() - 3; i > 0; i -= 3) ys.insert(i, ",");
    if (y < 0) ys = "-" + ys;
    char buf[32];
    snprintf(buf, sizeof(buf), "%s-%02d-%02d", ys.c_str(), m, d);
    return buf;
}

static constexpr const char* RESET  = "\033[0m";
static constexpr const char* AMBER  = "\033[38;5;216m";
static constexpr const char* AMBER_DIM = "\033[38;5;173m";   // same hue, darker
static constexpr const char* YELLOW = "\033[38;5;221m";
static constexpr const char* GREEN  = "\033[38;5;121m";
static constexpr const char* RED    = "\033[38;5;203m";
static constexpr const char* BLUE   = "\033[38;5;75m";

// Sampled blocks are bracketed by separator lines; these track state so two
// adjacent blocks share one separator and nothing doubles up with the
// header/footer separators.
static bool g_prev_sampled = false;
static bool g_after_sep    = true;

static void table_sep() {
    std::cout << AMBER << "+------------------------------+-------------+------------+------------+--------+" << RESET << "\n";
    g_after_sep = true;
}

static void table_header() {
    table_sep();
    std::cout << AMBER << "| ALGORITHM                    |         MIN |        MAX |      YEARS |  RANGE |" << RESET << "\n";
    table_sep();
}

static std::string pad_left(std::string s, int w) {
    while ((int)s.size() < w) s = " " + s;
    return s;
}
static std::string pad_right(std::string s, int w) {
    while ((int)s.size() < w) s = s + " ";
    return s;
}

static std::string fmt_years(int128_t days) {
    std::string s = "";
    if (days < 0) days = -days;
    if (days > 0 && days < 365) {
        s = " < 1";
    }
    else {
        s = std::to_string((long long)(days * 400 / 146097));
        for (int i = (int)s.size() - 3; i > 0; i -= 3) s.insert(i, ",");
    }
    return pad_left(s, 10);
}

// Values printed here are always within [-2^63, 2^64), so one of the two
// 64-bit to_strings always fits.
static std::string i128_str(int128_t v) {
    return v < 0 ? std::to_string((long long)v)
                 : std::to_string((unsigned long long)v);
}

static std::string commas(uint64_t v) {
    std::string s = std::to_string(v);
    for (int i = (int)s.size() - 3; i > 0; i -= 3) s.insert(i, ",");
    return s;
}

// One row of a sampled-mode block: the middle field spans the MIN/MAX/YEARS
// columns.  status is nullptr while ticking, "Pass"/"FAIL" once the region
// completes.  c1_col overrides the first column's colour when given.
static void print_sample_row(const std::string& c1, const std::string& c2,
                             const char* status, bool failed = false,
                             const char* c1_col = nullptr) {
    const char* col    = status ? AMBER : RESET;
    const char* st_col = status ? (failed ? RED : GREEN) : col;
    std::cout << col
              << "| " << (c1_col ? c1_col : col) << pad_right(c1, 28) << col
              << " | " << pad_right(c2, 37)
              << " | " << st_col << pad_right(status ? status : "", 6) << col
              << " |" << RESET << "\n";
    g_after_sep = false;
}

// mn/mx/lo/hi are bit patterns of the tested type read as int64_t; `total` is
// the type's modulus (2^N, as int128_t so 2^64 fits).  `empty` marks the
// nothing-tested-yet sentinel (0, -1), which for unsigned types is otherwise
// indistinguishable from a full 64-bit range.
static void print_row(const char* label, int64_t mn, int64_t mx, bool done,
                      int64_t lo = 0, int64_t hi = 0, bool uns = false,
                      int128_t total = (int128_t)1 << 32, bool empty = false) {
    // Unsigned view: negative bit patterns are the top of the unsigned range,
    // so shift them up by the modulus (a full uint32_t range becomes
    // 0..4294967295, uint8_t becomes 0..255).  lo/hi expectations are given in
    // the type's own domain too.
    int128_t mn_p = mn, mx_p = mx, lo_p = lo, hi_p = hi;
    if (uns) {
        if (mn_p < 0) mn_p += total;
        if (mx_p < 0) mx_p += total;
        if (lo_p < 0) lo_p += total;
        if (hi_p < 0) hi_p += total;
    }

    int128_t span;
    if (empty)                   span = 0;
    else if (uns && mx_p < mn_p) span = total - (mn_p - mx_p - 1);  // sweep wrapped past 0
    else                         span = mx_p - mn_p + 1;
    if (uns && span == total) { mn_p = 0; mx_p = total - 1; }

    std::string name = std::string(label);
    while ((int)name.size() < 28) name += " ";

    const char* col = done ? AMBER : RESET;

    char buf[8];
    snprintf(buf, sizeof(buf), "%5.1f%%", std::floor(1000.0 * double(span) / double(total)) / 10.0);
    bool full    = (mn_p == lo_p && mx_p == hi_p);
    bool exceeds = (mn_p < lo_p || mx_p > hi_p);
    const char* range_col = done ? (exceeds ? BLUE : (full ? GREEN : RED)) : RESET;
    std::string range = std::string(RESET) + range_col + buf + RESET + col;

    std::cout << col
              << "| " << name
              << " | " << pad_left(i128_str(mn_p), 11)
              << " | " << pad_left(i128_str(mx_p), 10)
              << " | " << fmt_years(span)
              << " | " << range << " |"
              << RESET << "\n";
    g_after_sep = false;
}

// ─── True-range seeker (self-contained diagnostic) ───────────────────────────
// Used only when a sampled test unexpectedly passes just outside its claimed
// range.  Gallops away from the boundary in 256-value chunks with doubling
// gaps, then binary-searches back (256-wide probes) to the exact boundary.
// Assumes failures are reasonably dense (>= ~1/256) past the true boundary and
// that chunk results are monotonic — fine as a diagnostic.  Delete once the
// algorithms are fully solved.

// fails(p): does position p fail?  start: a known-passing position.  Returns
// the last passing position at or above start (UINT64_MAX if nothing fails).
template <typename F>
static uint64_t seek_last_pass(F fails, uint64_t start) {
    auto chunk_fail = [&](uint64_t s, uint64_t& first) -> bool {
        const uint64_t e = (s > UINT64_MAX - 255) ? UINT64_MAX : s + 255;
        for (uint64_t p = s;; ++p) {
            if (fails(p)) { first = p; return true; }
            if (p == e) return false;
        }
    };

    if (start == UINT64_MAX) return start;

    uint64_t last_pass = start, cur = start + 1, jump = 0, first_fail = 0;
    for (;;) {
        if (chunk_fail(cur, first_fail)) break;
        last_pass = (cur > UINT64_MAX - 255) ? UINT64_MAX : cur + 255;
        if (last_pass == UINT64_MAX) return UINT64_MAX;
        uint64_t next = cur + 256 + jump;
        if (next < cur || next > UINT64_MAX - 255) next = UINT64_MAX - 255;
        cur = std::max(next, last_pass + 1);
        if (jump < (uint64_t(1) << 62)) jump = jump ? jump << 1 : 512;
    }

    // Binary search between a passing and a failing position.
    uint64_t blo = last_pass, bhi = first_fail;
    while (bhi - blo > 256) {
        const uint64_t mid = blo + (bhi - blo) / 2;
        uint64_t f = 0;
        if (chunk_fail(mid, f) && f < bhi) bhi = f;
        else                               blo = std::min(mid + 255, bhi - 1);
    }
    for (uint64_t p = blo + 1; p < bhi; ++p)
        if (fails(p)) return p - 1;
    return bhi - 1;
}

// Finds and prints the true MIN/MAX when values just outside the claimed
// bounds unexpectedly pass.  olo/ohi are the claimed bounds in the same
// ordinal space run_search uses (order-preserving uint64 mapping).
template <typename Fref, typename Ftest>
static void seek_true_range(Fref ref, Ftest test, bool uns,
                            uint64_t olo, uint64_t ohi,
                            bool max_leaks, bool min_leaks) {
    const uint64_t FLIP = uns ? 0 : (uint64_t(1) << 63);
    auto fails_at = [&](uint64_t o) {
        int64_t v = int64_t(o ^ FLIP);
        return ref(v) != test(v);
    };
    // Plain digits with a literal suffix, ready to paste into a test() call.
    auto fmt = [&](uint64_t o) -> std::string {
        int64_t v = int64_t(o ^ FLIP);
        return uns ? std::to_string(uint64_t(v)) + "ull"
                   : std::to_string(v) + "ll";
    };

    if (max_leaks)
        print_sample_row("", "True MAX: " + fmt(seek_last_pass(fails_at, ohi)), "");
    if (min_leaks) {
        auto fails_rev = [&](uint64_t p) { return fails_at(~p); };
        print_sample_row("", "True MIN: " + fmt(~seek_last_pass(fails_rev, ~olo)), "");
    }
}

struct SearchResult { const char* label; int64_t found_lo, found_hi; };

template <typename Fref, typename Ftest>
SearchResult run_search(const char* label, Fref ref, Ftest test, int64_t lo, int64_t hi,
                        bool uns = false,
                        int64_t lim_lo = INT32_MIN, int64_t lim_hi = INT32_MAX) {
    constexpr uint32_t PRINT_FREQ = 1 << 25;

    // Order-preserving map of the type's bit patterns into uint64 "ordinal"
    // space (identity for unsigned types), so range arithmetic can't overflow.
    const uint64_t FLIP = uns ? 0 : (uint64_t(1) << 63);
    auto to_ord   = [&](int64_t v) -> uint64_t { return uint64_t(v) ^ FLIP; };
    auto from_ord = [&](uint64_t o) -> int64_t { return int64_t(o ^ FLIP); };

    const uint64_t olo = to_ord(lo), ohi = to_ord(hi);
    const bool sampled = (ohi - olo) > (uint64_t(1) << 34);

    if (!sampled) {   // exhaustive sweeps never go beyond the 32-bit range
        lim_lo = std::max<int64_t>(lim_lo, INT32_MIN);
        lim_hi = std::min<int64_t>(lim_hi, INT32_MAX);
    }
    const int128_t total = (int128_t)lim_hi - lim_lo + 1;

    // Bracket sampled blocks with separator lines (adjacent blocks share one).
    if (!g_after_sep && (sampled || g_prev_sampled)) table_sep();
    g_prev_sampled = sampled;

    int64_t found_lo = 0, found_hi = -1;
    bool pass = true;

    if (sampled) {
        // Ranges wider than 2^34 can't be swept exhaustively.  Four regions,
        // a billion samples each, one output row per region: the bottom of
        // the range, the top (descending), around zero, then random probes.
        //const uint64_t N = 1000000000ull;
        const uint64_t N = 100000000ull;
        uint32_t counter = 0;
        int64_t  fail_v = 0;
        uint32_t fail_exp = 0, fail_got = 0;

        auto probe = [&](uint64_t o) -> bool {
            int64_t v = from_ord(o);
            uint32_t expect = ref(v);
            uint32_t actual = test(v);
            if (expect != actual) {
                fail_v = v; fail_exp = expect; fail_got = actual;
                pass = false;
                return false;
            }
            return true;
        };

        // Natural type bounds get a short token in the region text instead of
        // a MIN:/MAX: legend cell.
        const bool lo_nat = (lo == 0) || (!uns && lo == INT64_MIN);
        const bool hi_nat = (hi == INT64_MAX) || (uns && hi == -1);
        const std::string min_tok = !lo_nat ? "MIN" : (lo == 0 ? "0" : "-2^63");
        const std::string max_tok = !hi_nat ? "MAX" : (hi == INT64_MAX ? "2^63-1" : "2^64-1");

        std::string mn_s = uns ? std::to_string(uint64_t(lo)) : std::to_string(lo);
        std::string mx_s = uns ? std::to_string(uint64_t(hi)) : std::to_string(hi);
        if (mn_s[0] == '-' && mx_s[0] != '-') mx_s = " " + mx_s;   // align signs
        const std::string col1[4] = { label,
                                      hi_nat ? "" : "MAX: " + mx_s,
                                      lo_nat ? "" : "MIN: " + mn_s,
                                      "" };

        auto tick = [&](int row, const std::string& c2) {
            print_sample_row(col1[row], c2, nullptr, false,
                             (row == 1 || row == 2) ? AMBER_DIM : nullptr);
            std::cout << "\033[1A\r" << std::flush;
        };
        auto finish = [&](int row, const std::string& c2) {
            print_sample_row(col1[row], c2, pass ? "Pass" : "FAIL", !pass,
                             (row == 1 || row == 2) ? AMBER_DIM : nullptr);
        };

        if (pass) {   // -N/2 .. N/2-1, clamped to [lo, hi]
            const uint64_t oz  = to_ord(0);
            const uint64_t c_a = std::max(olo, oz >= N / 2 ? oz - N / 2 : 0);
            const uint64_t c_b = std::min(ohi, oz + (N / 2 - 1));
            auto val_s = [&](uint64_t o) -> std::string {
                int64_t v = from_ord(o);
                if (uns || v >= 0) return commas(uint64_t(v));
                return "-" + commas(uint64_t(-v));
            };
            auto text = [&](uint64_t o) { return "Test: " + val_s(c_a) + " ... " + val_s(o); };
            if (c_a > c_b) {
                finish(0, "Test: (outside range)");
            } else {
                tick(0, text(c_a));
                for (uint64_t o = c_a;; ++o) {
                    if (!probe(o)) { finish(0, text(o)); break; }
                    if (o == c_b)  { finish(0, text(c_b)); break; }
                    if (++counter == PRINT_FREQ) { counter = 0; tick(0, text(o)); }
                }
            }
        }

        if (pass) {   // MIN .. MIN + N-1
            auto text = [&](uint64_t k) {
                return lo == 0 ? "Test: 0 ... " + commas(k)
                               : "Test: " + min_tok + " ... " + min_tok + " + " + commas(k);
            };
            tick(1, text(0));
            for (uint64_t k = 0; k < N; ++k) {
                if (!probe(olo + k)) { finish(1, text(k)); break; }
                if (++counter == PRINT_FREQ) { counter = 0; tick(1, text(k)); }
            }
            if (pass) finish(1, text(N - 1));
        }

        if (pass) {   // MAX .. MAX - N+1, descending
            auto text = [&](uint64_t k) {
                return "Test: " + max_tok + " - " + commas(k) + " ... " + max_tok;
            };
            tick(2, text(0));
            for (uint64_t k = 0; k < N; ++k) {
                if (!probe(ohi - k)) { finish(2, text(k)); break; }
                if (++counter == PRINT_FREQ) { counter = 0; tick(2, text(k)); }
            }
            if (pass) finish(2, text(N - 1));
        }

        if (pass) {   // N random probes (splitmix64, deterministic)
            const uint64_t width = ohi - olo;
            auto text = [&](uint64_t i) { return "Test random count: " + commas(i); };
            tick(3, text(0));
            uint64_t s = 0;
            for (uint64_t i = 0; i < N; ++i) {
                s += 0x9E3779B97F4A7C15ull;
                uint64_t z = s;
                z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ull;
                z = (z ^ (z >> 27)) * 0x94D049BB133111EBull;
                z ^= z >> 31;
                uint64_t o = (width == UINT64_MAX) ? z : olo + z % (width + 1);
                if (!probe(o)) { finish(3, text(i)); break; }
                if (++counter == PRINT_FREQ) { counter = 0; tick(3, text(i)); }
            }
            if (pass) finish(3, text(N - 1));
        }

        // Values just outside the claimed range are expected to FAIL — skip
        // whichever side sits on the type's edge.  If one unexpectedly passes,
        // hunt down the true boundary.
        if (pass && (olo > 0 || ohi < UINT64_MAX)) {
            auto fails = [&](uint64_t o) {
                int64_t v = from_ord(o);
                return ref(v) != test(v);
            };
            const bool max_leaks = ohi < UINT64_MAX && !fails(ohi + 1);
            const bool min_leaks = olo > 0 && !fails(olo - 1);
            print_sample_row("", "Test fail outside range...",
                             (max_leaks || min_leaks) ? "FAIL" : "Pass",
                             max_leaks || min_leaks);
            if (max_leaks || min_leaks)
                seek_true_range(ref, test, uns, olo, ohi, max_leaks, min_leaks);
        }

        if (!pass) {
            std::cout << std::flush << RED
                      << "*****  Fail at "
                      << (uns ? std::to_string(uint64_t(fail_v)) : std::to_string(fail_v))
                      << ".  Expected: " << fail_exp
                      << ".  Got: " << fail_got
                      << ".  Exiting Test  *****. \n";
        } else {
            found_lo = lo; found_hi = hi;
        }
        return {label, found_lo, found_hi};
    }

    print_row(label, found_lo, found_hi, false, 0, 0, uns, total, true);
    std::cout << "\033[1A\r" << std::flush;

    for (int32_t dir : {1, -1}) {

        const int64_t start = dir > 0 ? 0 : -1;
        const int64_t limit = dir > 0 ? lim_hi : lim_lo;
        int64_t& found_end  = dir > 0 ? found_hi : found_lo;

        uint32_t counter = 0;
        for (int64_t y = start;; y += dir) {
            uint32_t expect = ref(y);
            uint32_t actual = test(y);
            if (expect != actual) {
                found_end = y - dir;
                // Was the failure inside the expected range?  For unsigned
                // types the descending phase and lo/hi live in the unsigned
                // domain, so convert y before comparing.
                int64_t u = (uns && y < 0) ? int64_t(y + total) : y;
                if (y >= 0 ? (u < hi) : (uns ? (u <= hi) : (u > lo))) {
                    // A partial top-end fragment from the unsigned descending
                    // phase is disjoint from [0, found_hi] — not a lower bound.
                    if (uns && found_lo < 0 && found_lo != lim_lo) found_lo = 0;
                    print_row(label, found_lo, found_hi, true, lo, hi, uns, total);
                    std::cout << std::flush << RED
                              << "*****  Fail at " << u
                              << ".  Expected: " << expect
                              << ".  Got: " << actual
                              << ".  Exiting Test  *****. \n";
                    pass = false;
                }
                break;
            }
            if (y == limit) {
                found_end = limit;
                break;
            }
            if (++counter == PRINT_FREQ) {
                counter = 0;
                found_end = y;
                print_row(label, found_lo, found_hi, false, 0, 0, uns, total);
                std::cout << "\033[1A\r" << std::flush;
            }
        }
    }

    // For unsigned types the descending phase covers the top of the range; if
    // it only partially passed, that fragment is disjoint from [0, found_hi],
    // so it is not a lower bound — report 0.  (found_lo == lim_lo means the
    // whole descending phase passed: the genuine full-range case.)
    if (uns && found_lo < 0 && found_lo != lim_lo) found_lo = 0;

    if (pass) {
        print_row(label, found_lo, found_hi, true, lo, hi, uns, total);
    }
    return {label, found_lo, found_hi};
}

// Inline-expression form of run_search: the reference is written directly as
// an expression in x, with T giving the type x is read as (int8_t, uint32_t,
// int64_t, ...).  T also bounds the search to the type's representable range
// (all 2^N bit patterns for an N-bit type).  A lo..hi range wider than 2^34
// is spot-checked (around zero, both ends, random probes) instead of swept, e.g.
//   test("umod7narrow_bj32_2_0", uint32_t, umod7narrow_bj32_2_0, (((x%7)+8)%7)+1, 0, 178956972);
// (Defined after run_search so it can't expand the test(y) call inside it.)
#define test(label, T, fn, expr, lo, hi) \
    r.push_back(run_search(label, [](T x) -> uint32_t { return uint32_t(expr); }, fn, lo, hi, \
        std::is_unsigned<T>::value, \
        (int64_t)std::numeric_limits<std::make_signed_t<T>>::min(), \
        (int64_t)std::numeric_limits<std::make_signed_t<T>>::max()))

int main() {
    int32_t min32 = std::numeric_limits<int32_t>::min();
    int32_t max32 = std::numeric_limits<int32_t>::max();

    std::cout << "\n\n";

    std::cout << "Each algorithm will be tested sequentially for their range.\n"
              << "Range will be printed in a colour to mean:\n"
              << "* " << GREEN << "Green" << RESET << ": Range matches expectation\n"
              << "* " << BLUE  << "Blue"  << RESET << ":  Range exceeds expectation (eg. undefined behaviour)\n"
              << "* " << RED   << "Red"   << RESET << ":   Range is less than expected\n"
              << "After the process is completed, the ISO date of min/max for each\n"
              << "will be displayed.\n\n";

    auto t_start = std::chrono::steady_clock::now();

    table_header();
    std::vector<SearchResult> r;

    // Step 1. Test the functions showin the blog post at
    // https://www.benjoffe.com/fast-day-of-week
    test("naive",          int32_t, weekday_naive,             ((x%7)+11)%7,     min32, max32);
    test("naive_iso",      int32_t, weekday_naive_iso,         (((x%7)+10)%7)+1, min32, max32);
    test("hinnant32",      int32_t, weekday_hinnant32,         ((x%7)+11)%7,     min32, max32 - 4);
    test("neri32",         int32_t, weekday_neri32,            ((x%7)+11)%7,     min32, max32);
    test("neri64",         int32_t, weekday_neri64,            ((x%7)+11)%7,     min32, max32);

    test("naive_compiled",  int32_t,  weekday_naive_compiled,  ((x%7)+11)%7,     min32, max32);
    test("rust_compiled",   int32_t,  weekday_rust_compiled,   ((x%7)+11)%7,     min32, max32 - 4);
    test("neri32_compiled", int32_t,  weekday_neri32_compiled, ((x%7)+11)%7,     -2147483648ll, 2147483647ll   );

    test("1st_attempt",          int32_t,  get_weekday_1st_attempt,          ((x%7)+11)%7,      -2147483648ll, 2147483647ll   );

    // Step 2. Test a few specific variants where we us assembly calls to force better codegen.
    test("32unix_forced_asm",    int32_t,  get_weekday_32unix_forced_asm,    ((x%7)+11)%7,      -2147483648ll, 2147483647ll   );
    test("32unix_v2_forced_asm", int32_t,  get_weekday_32unix_v2_forced_asm, ((x%7)+11)%7,      -2147483648ll, 2147483647ll   );
    test("32unix_v3_forced_asm", int32_t,  get_weekday_32unix_v3_forced_asm, ((x%7)+11)%7,      -2147483648ll, 2147483647ll   );

    // Step 3. Test all variants of the "Function Explorer".
    // The below test commands were copy/pasted directly from the export at
    // https://www.benjoffe.com/fast-day-of-week#fn
    test("8",              int8_t,   get_weekday_8,              ((x%7)+7)%7,      -128,          127            );
    test("8e1",            int8_t,   get_weekday_8e1,            ((x%7)+8)%7,      -128,          127            );
    test("8e2",            int8_t,   get_weekday_8e2,            ((x%7)+9)%7,      -128,          127            );
    test("8e3",            int8_t,   get_weekday_8e3,            ((x%7)+10)%7,     -128,          127            );
    test("8unix",          int8_t,   get_weekday_8unix,          ((x%7)+11)%7,     -128,          127            );
    test("8e5",            int8_t,   get_weekday_8e5,            ((x%7)+12)%7,     -128,          127            );
    test("8e6",            int8_t,   get_weekday_8e6,            ((x%7)+13)%7,     -128,          127            );
    test("u8",             uint8_t,  get_weekday_u8,             ((x%7)+7)%7,      0u,            255u           );
    test("u8e1",           uint8_t,  get_weekday_u8e1,           ((x%7)+8)%7,      0u,            255u           );
    test("u8e2",           uint8_t,  get_weekday_u8e2,           ((x%7)+9)%7,      0u,            255u           );
    test("u8e3",           uint8_t,  get_weekday_u8e3,           ((x%7)+10)%7,     0u,            255u           );
    test("u8unix",         uint8_t,  get_weekday_u8unix,         ((x%7)+11)%7,     0u,            255u           );
    test("u8e5",           uint8_t,  get_weekday_u8e5,           ((x%7)+12)%7,     0u,            255u           );
    test("u8e6",           uint8_t,  get_weekday_u8e6,           ((x%7)+13)%7,     0u,            255u           );
    test("8iso7",          int8_t,   get_weekday_8iso7,          (((x%7)+6)%7)+1,  -128,          127            );
    test("8iso1",          int8_t,   get_weekday_8iso1,          (((x%7)+7)%7)+1,  -128,          127            );
    test("8iso2",          int8_t,   get_weekday_8iso2,          (((x%7)+8)%7)+1,  -128,          127            );
    test("8iso3",          int8_t,   get_weekday_8iso3,          (((x%7)+9)%7)+1,  -128,          127            );
    test("8iso",           int8_t,   get_weekday_8iso,           (((x%7)+10)%7)+1, -128,          127            );
    test("8iso5",          int8_t,   get_weekday_8iso5,          (((x%7)+11)%7)+1, -128,          127            );
    test("8iso6",          int8_t,   get_weekday_8iso6,          (((x%7)+12)%7)+1, -128,          127            );
    test("u8iso7",         uint8_t,  get_weekday_u8iso7,         (((x%7)+6)%7)+1,  0u,            255u           );
    test("u8iso1",         uint8_t,  get_weekday_u8iso1,         (((x%7)+7)%7)+1,  0u,            255u           );
    test("u8iso2",         uint8_t,  get_weekday_u8iso2,         (((x%7)+8)%7)+1,  0u,            255u           );
    test("u8iso3",         uint8_t,  get_weekday_u8iso3,         (((x%7)+9)%7)+1,  0u,            255u           );
    test("u8iso",          uint8_t,  get_weekday_u8iso,          (((x%7)+10)%7)+1, 0u,            255u           );
    test("u8iso5",         uint8_t,  get_weekday_u8iso5,         (((x%7)+11)%7)+1, 0u,            255u           );
    test("u8iso6",         uint8_t,  get_weekday_u8iso6,         (((x%7)+12)%7)+1, 0u,            255u           );
    test("16",             int16_t,  get_weekday_16,             ((x%7)+7)%7,      -32768,        32767          );
    test("16e1",           int16_t,  get_weekday_16e1,           ((x%7)+8)%7,      -32768,        32767          );
    test("16e2",           int16_t,  get_weekday_16e2,           ((x%7)+9)%7,      -32768,        32767          );
    test("16e3",           int16_t,  get_weekday_16e3,           ((x%7)+10)%7,     -32768,        32767          );
    test("16unix",         int16_t,  get_weekday_16unix,         ((x%7)+11)%7,     -32768,        32767          );
    test("16e5",           int16_t,  get_weekday_16e5,           ((x%7)+12)%7,     -32768,        32767          );
    test("16e6",           int16_t,  get_weekday_16e6,           ((x%7)+13)%7,     -32768,        32767          );
    test("u16",            uint16_t, get_weekday_u16,            ((x%7)+7)%7,      0u,            65535u         );
    test("u16e1",          uint16_t, get_weekday_u16e1,          ((x%7)+8)%7,      0u,            65535u         );
    test("u16e2",          uint16_t, get_weekday_u16e2,          ((x%7)+9)%7,      0u,            65535u         );
    test("u16e3",          uint16_t, get_weekday_u16e3,          ((x%7)+10)%7,     0u,            65535u         );
    test("u16unix",        uint16_t, get_weekday_u16unix,        ((x%7)+11)%7,     0u,            65535u         );
    test("u16e5",          uint16_t, get_weekday_u16e5,          ((x%7)+12)%7,     0u,            65535u         );
    test("u16e6",          uint16_t, get_weekday_u16e6,          ((x%7)+13)%7,     0u,            65535u         );
    test("16iso7",         int16_t,  get_weekday_16iso7,         (((x%7)+6)%7)+1,  -32768,        32767          );
    test("16iso1",         int16_t,  get_weekday_16iso1,         (((x%7)+7)%7)+1,  -32768,        32767          );
    test("16iso2",         int16_t,  get_weekday_16iso2,         (((x%7)+8)%7)+1,  -32768,        32767          );
    test("16iso3",         int16_t,  get_weekday_16iso3,         (((x%7)+9)%7)+1,  -32768,        32767          );
    test("16iso",          int16_t,  get_weekday_16iso,          (((x%7)+10)%7)+1, -32768,        32767          );
    test("16iso5",         int16_t,  get_weekday_16iso5,         (((x%7)+11)%7)+1, -32768,        32767          );
    test("16iso6",         int16_t,  get_weekday_16iso6,         (((x%7)+12)%7)+1, -32768,        32767          );
    test("u16iso7",        uint16_t, get_weekday_u16iso7,        (((x%7)+6)%7)+1,  0u,            65535u         );
    test("u16iso1",        uint16_t, get_weekday_u16iso1,        (((x%7)+7)%7)+1,  0u,            65535u         );
    test("u16iso2",        uint16_t, get_weekday_u16iso2,        (((x%7)+8)%7)+1,  0u,            65535u         );
    test("u16iso3",        uint16_t, get_weekday_u16iso3,        (((x%7)+9)%7)+1,  0u,            65535u         );
    test("u16iso",         uint16_t, get_weekday_u16iso,         (((x%7)+10)%7)+1, 0u,            65535u         );
    test("u16iso5",        uint16_t, get_weekday_u16iso5,        (((x%7)+11)%7)+1, 0u,            65535u         );
    test("u16iso6",        uint16_t, get_weekday_u16iso6,        (((x%7)+12)%7)+1, 0u,            65535u         );
    test("32_narrow",      int32_t,  get_weekday_32_narrow,      ((x%7)+7)%7,      -89456646,     89500332       );
    test("32e1_narrow",    int32_t,  get_weekday_32e1_narrow,    ((x%7)+8)%7,      -89412953,     89544025       );
    test("32e2_narrow",    int32_t,  get_weekday_32e2_narrow,    ((x%7)+9)%7,      -89522182,     89434796       );
    test("32e3_narrow",    int32_t,  get_weekday_32e3_narrow,    ((x%7)+10)%7,     -89478489,     89478489       );
    test("32unix_narrow",  int32_t,  get_weekday_32unix_narrow,  ((x%7)+11)%7,     -89434796,     89522175       );
    test("32e5_narrow",    int32_t,  get_weekday_32e5_narrow,    ((x%7)+12)%7,     -89544025,     89412953       );
    test("32e6_narrow",    int32_t,  get_weekday_32e6_narrow,    ((x%7)+13)%7,     -89500332,     89456639       );
    test("u32_narrow",     uint32_t, get_weekday_u32_narrow,     ((x%7)+7)%7,      0u,            178956972u     );
    test("u32e1_narrow",   uint32_t, get_weekday_u32e1_narrow,   ((x%7)+8)%7,      0u,            178956978u     );
    test("u32e2_narrow",   uint32_t, get_weekday_u32e2_narrow,   ((x%7)+9)%7,      0u,            178956977u     );
    test("u32e3_narrow",   uint32_t, get_weekday_u32e3_narrow,   ((x%7)+10)%7,     0u,            178956976u     );
    test("u32unix_narrow", uint32_t, get_weekday_u32unix_narrow, ((x%7)+11)%7,     0u,            178956975u     );
    test("u32e5_narrow",   uint32_t, get_weekday_u32e5_narrow,   ((x%7)+12)%7,     0u,            178956974u     );
    test("u32e6_narrow",   uint32_t, get_weekday_u32e6_narrow,   ((x%7)+13)%7,     0u,            178956973u     );
    test("32iso7_narrow",  int32_t,  get_weekday_32iso7_narrow,  (((x%7)+6)%7)+1,  -89500332,     89456639       );
    test("32iso1_narrow",  int32_t,  get_weekday_32iso1_narrow,  (((x%7)+7)%7)+1,  -89456646,     89500332       );
    test("32iso2_narrow",  int32_t,  get_weekday_32iso2_narrow,  (((x%7)+8)%7)+1,  -89412953,     89544025       );
    test("32iso3_narrow",  int32_t,  get_weekday_32iso3_narrow,  (((x%7)+9)%7)+1,  -89522182,     89434796       );
    test("32iso_narrow",   int32_t,  get_weekday_32iso_narrow,   (((x%7)+10)%7)+1, -89478489,     89478489       );
    test("32iso5_narrow",  int32_t,  get_weekday_32iso5_narrow,  (((x%7)+11)%7)+1, -89434796,     89522175       );
    test("32iso6_narrow",  int32_t,  get_weekday_32iso6_narrow,  (((x%7)+12)%7)+1, -89544025,     89412953       );
    test("u32iso7_narrow", uint32_t, get_weekday_u32iso7_narrow, (((x%7)+6)%7)+1,  0u,            178913279u     );
    test("u32iso1_narrow", uint32_t, get_weekday_u32iso1_narrow, (((x%7)+7)%7)+1,  0u,            178956972u     );
    test("u32iso2_narrow", uint32_t, get_weekday_u32iso2_narrow, (((x%7)+8)%7)+1,  0u,            178847743u     );
    test("u32iso3_narrow", uint32_t, get_weekday_u32iso3_narrow, (((x%7)+9)%7)+1,  0u,            178891436u     );
    test("u32iso_narrow",  uint32_t, get_weekday_u32iso_narrow,  (((x%7)+10)%7)+1, 0u,            178935129u     );
    test("u32iso5_narrow", uint32_t, get_weekday_u32iso5_narrow, (((x%7)+11)%7)+1, 0u,            178825900u     );
    test("u32iso6_narrow", uint32_t, get_weekday_u32iso6_narrow, (((x%7)+12)%7)+1, 0u,            178869593u     );
    test("32_medium",      int32_t,  get_weekday_32_medium,      ((x%7)+7)%7,      -537001983,    536739846      );
    test("32e1_medium",    int32_t,  get_weekday_32e1_medium,    ((x%7)+8)%7,      -537264127,    536477702      );
    test("32e2_medium",    int32_t,  get_weekday_32e2_medium,    ((x%7)+9)%7,      -536608767,    537133062      );
    test("32e3_medium",    int32_t,  get_weekday_32e3_medium,    ((x%7)+10)%7,     -536870911,    536870918      );
    test("32unix_medium",  int32_t,  get_weekday_32unix_medium,  ((x%7)+11)%7,     -537133055,    536608774      );
    test("32e5_medium",    int32_t,  get_weekday_32e5_medium,    ((x%7)+12)%7,     -536477695,    537264134      );
    test("32e6_medium",    int32_t,  get_weekday_32e6_medium,    ((x%7)+13)%7,     -536739839,    537001990      );
    test("u32_medium",     uint32_t, get_weekday_u32_medium,     ((x%7)+7)%7,      0u,            1073479686u    );
    test("u32e1_medium",   uint32_t, get_weekday_u32e1_medium,   ((x%7)+8)%7,      0u,            1073217542u    );
    test("u32e2_medium",   uint32_t, get_weekday_u32e2_medium,   ((x%7)+9)%7,      0u,            1072955398u    );
    test("u32e3_medium",   uint32_t, get_weekday_u32e3_medium,   ((x%7)+10)%7,     0u,            1073610758u    );
    test("u32unix_medium", uint32_t, get_weekday_u32unix_medium, ((x%7)+11)%7,     0u,            1073348614u    );
    test("u32e5_medium",   uint32_t, get_weekday_u32e5_medium,   ((x%7)+12)%7,     0u,            1073086470u    );
    test("u32e6_medium",   uint32_t, get_weekday_u32e6_medium,   ((x%7)+13)%7,     0u,            1073741816u    );
    test("32iso7_medium",  int32_t,  get_weekday_32iso7_medium,  (((x%7)+6)%7)+1,  -536739839,    537001990      );
    test("32iso1_medium",  int32_t,  get_weekday_32iso1_medium,  (((x%7)+7)%7)+1,  -537001983,    536739846      );
    test("32iso2_medium",  int32_t,  get_weekday_32iso2_medium,  (((x%7)+8)%7)+1,  -537264127,    536477702      );
    test("32iso3_medium",  int32_t,  get_weekday_32iso3_medium,  (((x%7)+9)%7)+1,  -537526271,    536215558      );
    test("32iso_medium",   int32_t,  get_weekday_32iso_medium,   (((x%7)+10)%7)+1, -536870911,    536870918      );
    test("32iso5_medium",  int32_t,  get_weekday_32iso5_medium,  (((x%7)+11)%7)+1, -537133055,    536608774      );
    test("32iso6_medium",  int32_t,  get_weekday_32iso6_medium,  (((x%7)+12)%7)+1, -536477695,    537264134      );
    test("u32iso7_medium", uint32_t, get_weekday_u32iso7_medium, (((x%7)+6)%7)+1,  0u,            1073741816u    );
    test("u32iso1_medium", uint32_t, get_weekday_u32iso1_medium, (((x%7)+7)%7)+1,  0u,            1073479686u    );
    test("u32iso2_medium", uint32_t, get_weekday_u32iso2_medium, (((x%7)+8)%7)+1,  0u,            1073217542u    );
    test("u32iso3_medium", uint32_t, get_weekday_u32iso3_medium, (((x%7)+9)%7)+1,  0u,            1072955398u    );
    test("u32iso_medium",  uint32_t, get_weekday_u32iso_medium,  (((x%7)+10)%7)+1, 0u,            1073610758u    );
    test("u32iso5_medium", uint32_t, get_weekday_u32iso5_medium, (((x%7)+11)%7)+1, 0u,            1073348614u    );
    test("u32iso6_medium", uint32_t, get_weekday_u32iso6_medium, (((x%7)+12)%7)+1, 0u,            1073086470u    );
    test("32",             int32_t,  get_weekday_32,             ((x%7)+7)%7,      -2147483648ll, 2147483647ll   );
    test("32e1",           int32_t,  get_weekday_32e1,           ((x%7)+8)%7,      -2147483648ll, 2147483647ll   );
    test("32e2",           int32_t,  get_weekday_32e2,           ((x%7)+9)%7,      -2147483648ll, 2147483647ll   );
    test("32e3",           int32_t,  get_weekday_32e3,           ((x%7)+10)%7,     -2147483648ll, 2147483647ll   );
    test("32unix",         int32_t,  get_weekday_32unix,         ((x%7)+11)%7,     -2147483648ll, 2147483647ll   );
    test("32e5",           int32_t,  get_weekday_32e5,           ((x%7)+12)%7,     -2147483648ll, 2147483647ll   );
    test("32e6",           int32_t,  get_weekday_32e6,           ((x%7)+13)%7,     -2147483648ll, 2147483647ll   );
    test("u32",            uint32_t, get_weekday_u32,            ((x%7)+7)%7,      0u,            4294967295ull  );
    test("u32e1",          uint32_t, get_weekday_u32e1,          ((x%7)+8)%7,      0u,            4294967295ull  );
    test("u32e2",          uint32_t, get_weekday_u32e2,          ((x%7)+9)%7,      0u,            4294967295ull  );
    test("u32e3",          uint32_t, get_weekday_u32e3,          ((x%7)+10)%7,     0u,            4294967295ull  );
    test("u32unix",        uint32_t, get_weekday_u32unix,        ((x%7)+11)%7,     0u,            4294967295ull  );
    test("u32e5",          uint32_t, get_weekday_u32e5,          ((x%7)+12)%7,     0u,            4294967295ull  );
    test("u32e6",          uint32_t, get_weekday_u32e6,          ((x%7)+13)%7,     0u,            4294967295ull  );
    test("32iso7",         int32_t,  get_weekday_32iso7,         (((x%7)+6)%7)+1,  -2147483648ll, 2147483647ll   );
    test("32iso1",         int32_t,  get_weekday_32iso1,         (((x%7)+7)%7)+1,  -2147483648ll, 2147483647ll   );
    test("32iso2",         int32_t,  get_weekday_32iso2,         (((x%7)+8)%7)+1,  -2147483648ll, 2147483647ll   );
    test("32iso3",         int32_t,  get_weekday_32iso3,         (((x%7)+9)%7)+1,  -2147483648ll, 2147483647ll   );
    test("32iso",          int32_t,  get_weekday_32iso,          (((x%7)+10)%7)+1, -2147483648ll, 2147483647ll   );
    test("32iso5",         int32_t,  get_weekday_32iso5,         (((x%7)+11)%7)+1, -2147483648ll, 2147483647ll   );
    test("32iso6",         int32_t,  get_weekday_32iso6,         (((x%7)+12)%7)+1, -2147483648ll, 2147483647ll   );
    test("u32iso7",        uint32_t, get_weekday_u32iso7,        (((x%7)+6)%7)+1,  0u,            4294967295ull  );
    test("u32iso1",        uint32_t, get_weekday_u32iso1,        (((x%7)+7)%7)+1,  0u,            4294967295ull  );
    test("u32iso2",        uint32_t, get_weekday_u32iso2,        (((x%7)+8)%7)+1,  0u,            4294967295ull  );
    test("u32iso3",        uint32_t, get_weekday_u32iso3,        (((x%7)+9)%7)+1,  0u,            4294967295ull  );
    test("u32iso",         uint32_t, get_weekday_u32iso,         (((x%7)+10)%7)+1, 0u,            4294967295ull  );
    test("u32iso5",        uint32_t, get_weekday_u32iso5,        (((x%7)+11)%7)+1, 0u,            4294967295ull  );
    test("u32iso6",        uint32_t, get_weekday_u32iso6,        (((x%7)+12)%7)+1, 0u,            4294967295ull  );
    test("32_v2",          int32_t,  get_weekday_32_v2,          ((x%7)+7)%7,      -2147483648ll, 2147483647ll   );
    test("32e1_v2",        int32_t,  get_weekday_32e1_v2,        ((x%7)+8)%7,      -2147483648ll, 2147483647ll   );
    test("32e2_v2",        int32_t,  get_weekday_32e2_v2,        ((x%7)+9)%7,      -2147483648ll, 2147483647ll   );
    test("32e3_v2",        int32_t,  get_weekday_32e3_v2,        ((x%7)+10)%7,     -2147483648ll, 2147483647ll   );
    test("32unix_v2",      int32_t,  get_weekday_32unix_v2,      ((x%7)+11)%7,     -2147483648ll, 2147483647ll   );
    test("32e5_v2",        int32_t,  get_weekday_32e5_v2,        ((x%7)+12)%7,     -2147483648ll, 2147483647ll   );
    test("32e6_v2",        int32_t,  get_weekday_32e6_v2,        ((x%7)+13)%7,     -2147483648ll, 2147483647ll   );
    test("u32_v2",         uint32_t, get_weekday_u32_v2,         ((x%7)+7)%7,      0u,            4294967295ull  );
    test("u32e1_v2",       uint32_t, get_weekday_u32e1_v2,       ((x%7)+8)%7,      0u,            4294967295ull  );
    test("u32e2_v2",       uint32_t, get_weekday_u32e2_v2,       ((x%7)+9)%7,      0u,            4294967295ull  );
    test("u32e3_v2",       uint32_t, get_weekday_u32e3_v2,       ((x%7)+10)%7,     0u,            4294967295ull  );
    test("u32unix_v2",     uint32_t, get_weekday_u32unix_v2,     ((x%7)+11)%7,     0u,            4294967295ull  );
    test("u32e5_v2",       uint32_t, get_weekday_u32e5_v2,       ((x%7)+12)%7,     0u,            4294967295ull  );
    test("u32e6_v2",       uint32_t, get_weekday_u32e6_v2,       ((x%7)+13)%7,     0u,            4294967295ull  );
    test("32iso7_v2",      int32_t,  get_weekday_32iso7_v2,      (((x%7)+6)%7)+1,  -2147483648ll, 2147483647ll   );
    test("32iso1_v2",      int32_t,  get_weekday_32iso1_v2,      (((x%7)+7)%7)+1,  -2147483648ll, 2147483647ll   );
    test("32iso2_v2",      int32_t,  get_weekday_32iso2_v2,      (((x%7)+8)%7)+1,  -2147483648ll, 2147483647ll   );
    test("32iso3_v2",      int32_t,  get_weekday_32iso3_v2,      (((x%7)+9)%7)+1,  -2147483648ll, 2147483647ll   );
    test("32iso_v2",       int32_t,  get_weekday_32iso_v2,       (((x%7)+10)%7)+1, -2147483648ll, 2147483647ll   );
    test("32iso5_v2",      int32_t,  get_weekday_32iso5_v2,      (((x%7)+11)%7)+1, -2147483648ll, 2147483647ll   );
    test("32iso6_v2",      int32_t,  get_weekday_32iso6_v2,      (((x%7)+12)%7)+1, -2147483648ll, 2147483647ll   );
    test("u32iso7_v2",     uint32_t, get_weekday_u32iso7_v2,     (((x%7)+6)%7)+1,  0u,            4294967295ull  );
    test("u32iso1_v2",     uint32_t, get_weekday_u32iso1_v2,     (((x%7)+7)%7)+1,  0u,            4294967295ull  );
    test("u32iso2_v2",     uint32_t, get_weekday_u32iso2_v2,     (((x%7)+8)%7)+1,  0u,            4294967295ull  );
    test("u32iso3_v2",     uint32_t, get_weekday_u32iso3_v2,     (((x%7)+9)%7)+1,  0u,            4294967295ull  );
    test("u32iso_v2",      uint32_t, get_weekday_u32iso_v2,      (((x%7)+10)%7)+1, 0u,            4294967295ull  );
    test("u32iso5_v2",     uint32_t, get_weekday_u32iso5_v2,     (((x%7)+11)%7)+1, 0u,            4294967295ull  );
    test("u32iso6_v2",     uint32_t, get_weekday_u32iso6_v2,     (((x%7)+12)%7)+1, 0u,            4294967295ull  );
    test("32_v3",          int32_t,  get_weekday_32_v3,          ((x%7)+7)%7,      -2147483648ll, 2147483647ll   );
    test("32e1_v3",        int32_t,  get_weekday_32e1_v3,        ((x%7)+8)%7,      -2147483648ll, 2147483647ll   );
    test("32e2_v3",        int32_t,  get_weekday_32e2_v3,        ((x%7)+9)%7,      -2147483648ll, 2147483647ll   );
    test("32e3_v3",        int32_t,  get_weekday_32e3_v3,        ((x%7)+10)%7,     -2147483648ll, 2147483647ll   );
    test("32unix_v3",      int32_t,  get_weekday_32unix_v3,      ((x%7)+11)%7,     -2147483648ll, 2147483647ll   );
    test("32e5_v3",        int32_t,  get_weekday_32e5_v3,        ((x%7)+12)%7,     -2147483648ll, 2147483647ll   );
    test("32e6_v3",        int32_t,  get_weekday_32e6_v3,        ((x%7)+13)%7,     -2147483648ll, 2147483647ll   );
    test("u32_v3",         uint32_t, get_weekday_u32_v3,         ((x%7)+7)%7,      0u,            4294967295ull  );
    test("u32e1_v3",       uint32_t, get_weekday_u32e1_v3,       ((x%7)+8)%7,      0u,            4294967295ull  );
    test("u32e2_v3",       uint32_t, get_weekday_u32e2_v3,       ((x%7)+9)%7,      0u,            4294967295ull  );
    test("u32e3_v3",       uint32_t, get_weekday_u32e3_v3,       ((x%7)+10)%7,     0u,            4294967295ull  );
    test("u32unix_v3",     uint32_t, get_weekday_u32unix_v3,     ((x%7)+11)%7,     0u,            4294967295ull  );
    test("u32e5_v3",       uint32_t, get_weekday_u32e5_v3,       ((x%7)+12)%7,     0u,            4294967295ull  );
    test("u32e6_v3",       uint32_t, get_weekday_u32e6_v3,       ((x%7)+13)%7,     0u,            4294967295ull  );
    test("32iso7_v3",      int32_t,  get_weekday_32iso7_v3,      (((x%7)+6)%7)+1,  -2147483648ll, 2147483647ll   );
    test("32iso1_v3",      int32_t,  get_weekday_32iso1_v3,      (((x%7)+7)%7)+1,  -2147483648ll, 2147483647ll   );
    test("32iso2_v3",      int32_t,  get_weekday_32iso2_v3,      (((x%7)+8)%7)+1,  -2147483648ll, 2147483647ll   );
    test("32iso3_v3",      int32_t,  get_weekday_32iso3_v3,      (((x%7)+9)%7)+1,  -2147483648ll, 2147483647ll   );
    test("32iso_v3",       int32_t,  get_weekday_32iso_v3,       (((x%7)+10)%7)+1, -2147483648ll, 2147483647ll   );
    test("32iso5_v3",      int32_t,  get_weekday_32iso5_v3,      (((x%7)+11)%7)+1, -2147483648ll, 2147483647ll   );
    test("32iso6_v3",      int32_t,  get_weekday_32iso6_v3,      (((x%7)+12)%7)+1, -2147483648ll, 2147483647ll   );
    test("u32iso7_v3",     uint32_t, get_weekday_u32iso7_v3,     (((x%7)+6)%7)+1,  0u,            4294967295ull  );
    test("u32iso1_v3",     uint32_t, get_weekday_u32iso1_v3,     (((x%7)+7)%7)+1,  0u,            4294967295ull  );
    test("u32iso2_v3",     uint32_t, get_weekday_u32iso2_v3,     (((x%7)+8)%7)+1,  0u,            4294967295ull  );
    test("u32iso3_v3",     uint32_t, get_weekday_u32iso3_v3,     (((x%7)+9)%7)+1,  0u,            4294967295ull  );
    test("u32iso_v3",      uint32_t, get_weekday_u32iso_v3,      (((x%7)+10)%7)+1, 0u,            4294967295ull  );
    test("u32iso5_v3",     uint32_t, get_weekday_u32iso5_v3,     (((x%7)+11)%7)+1, 0u,            4294967295ull  );
    test("u32iso6_v3",     uint32_t, get_weekday_u32iso6_v3,     (((x%7)+12)%7)+1, 0u,            4294967295ull  );
    test("32_widen",       int32_t,  get_weekday_32_widen,       ((x%7)+7)%7,      -2147483648ll, 2147483647ll   );
    test("32e1_widen",     int32_t,  get_weekday_32e1_widen,     ((x%7)+8)%7,      -2147483648ll, 2147483647ll   );
    test("32e2_widen",     int32_t,  get_weekday_32e2_widen,     ((x%7)+9)%7,      -2147483648ll, 2147483647ll   );
    test("32e3_widen",     int32_t,  get_weekday_32e3_widen,     ((x%7)+10)%7,     -2147483648ll, 2147483647ll   );
    test("32unix_widen",   int32_t,  get_weekday_32unix_widen,   ((x%7)+11)%7,     -2147483648ll, 2147483647ll   );
    test("32e5_widen",     int32_t,  get_weekday_32e5_widen,     ((x%7)+12)%7,     -2147483648ll, 2147483647ll   );
    test("32e6_widen",     int32_t,  get_weekday_32e6_widen,     ((x%7)+13)%7,     -2147483648ll, 2147483647ll   );
    test("u32_widen",      uint32_t, get_weekday_u32_widen,      ((x%7)+7)%7,      0u,            4294967295ull  );
    test("u32e1_widen",    uint32_t, get_weekday_u32e1_widen,    ((x%7)+8)%7,      0u,            4294967295ull  );
    test("u32e2_widen",    uint32_t, get_weekday_u32e2_widen,    ((x%7)+9)%7,      0u,            4294967295ull  );
    test("u32e3_widen",    uint32_t, get_weekday_u32e3_widen,    ((x%7)+10)%7,     0u,            4294967295ull  );
    test("u32unix_widen",  uint32_t, get_weekday_u32unix_widen,  ((x%7)+11)%7,     0u,            4294967295ull  );
    test("u32e5_widen",    uint32_t, get_weekday_u32e5_widen,    ((x%7)+12)%7,     0u,            4294967295ull  );
    test("u32e6_widen",    uint32_t, get_weekday_u32e6_widen,    ((x%7)+13)%7,     0u,            4294967295ull  );
    test("32iso7_widen",   int32_t,  get_weekday_32iso7_widen,   (((x%7)+6)%7)+1,  -2147483648ll, 2147483647ll   );
    test("32iso1_widen",   int32_t,  get_weekday_32iso1_widen,   (((x%7)+7)%7)+1,  -2147483648ll, 2147483647ll   );
    test("32iso2_widen",   int32_t,  get_weekday_32iso2_widen,   (((x%7)+8)%7)+1,  -2147483648ll, 2147483647ll   );
    test("32iso3_widen",   int32_t,  get_weekday_32iso3_widen,   (((x%7)+9)%7)+1,  -2147483648ll, 2147483647ll   );
    test("32iso_widen",    int32_t,  get_weekday_32iso_widen,    (((x%7)+10)%7)+1, -2147483648ll, 2147483647ll   );
    test("32iso5_widen",   int32_t,  get_weekday_32iso5_widen,   (((x%7)+11)%7)+1, -2147483648ll, 2147483647ll   );
    test("32iso6_widen",   int32_t,  get_weekday_32iso6_widen,   (((x%7)+12)%7)+1, -2147483648ll, 2147483647ll   );
    test("u32iso7_widen",  uint32_t, get_weekday_u32iso7_widen,  (((x%7)+6)%7)+1,  0u,            4294967295ull  );
    test("u32iso1_widen",  uint32_t, get_weekday_u32iso1_widen,  (((x%7)+7)%7)+1,  0u,            4294967295ull  );
    test("u32iso2_widen",  uint32_t, get_weekday_u32iso2_widen,  (((x%7)+8)%7)+1,  0u,            4294967295ull  );
    test("u32iso3_widen",  uint32_t, get_weekday_u32iso3_widen,  (((x%7)+9)%7)+1,  0u,            4294967295ull  );
    test("u32iso_widen",   uint32_t, get_weekday_u32iso_widen,   (((x%7)+10)%7)+1, 0u,            4294967295ull  );
    test("u32iso5_widen",  uint32_t, get_weekday_u32iso5_widen,  (((x%7)+11)%7)+1, 0u,            4294967295ull  );
    test("u32iso6_widen",  uint32_t, get_weekday_u32iso6_widen,  (((x%7)+12)%7)+1, 0u,            4294967295ull  );
    test("64",             int64_t,  get_weekday_64,             ((x%7)+7)%7,      INT64_MIN,     INT64_MAX      );
    test("64e1",           int64_t,  get_weekday_64e1,           ((x%7)+8)%7,      INT64_MIN,     INT64_MAX      );
    test("64e2",           int64_t,  get_weekday_64e2,           ((x%7)+9)%7,      INT64_MIN,     INT64_MAX      );
    test("64e3",           int64_t,  get_weekday_64e3,           ((x%7)+10)%7,     INT64_MIN,     INT64_MAX      );
    test("64unix",         int64_t,  get_weekday_64unix,         ((x%7)+11)%7,     INT64_MIN,     INT64_MAX      );
    test("64e5",           int64_t,  get_weekday_64e5,           ((x%7)+12)%7,     INT64_MIN,     INT64_MAX      );
    test("64e6",           int64_t,  get_weekday_64e6,           ((x%7)+13)%7,     INT64_MIN,     INT64_MAX      );
    test("u64",            uint64_t, get_weekday_u64,            ((x%7)+7)%7,      0u,            18446744073709551615ull);
    test("u64e1",          uint64_t, get_weekday_u64e1,          ((x%7)+8)%7,      0u,            18446744073709551615ull);
    test("u64e2",          uint64_t, get_weekday_u64e2,          ((x%7)+9)%7,      0u,            18446744073709551615ull);
    test("u64e3",          uint64_t, get_weekday_u64e3,          ((x%7)+10)%7,     0u,            18446744073709551615ull);
    test("u64unix",        uint64_t, get_weekday_u64unix,        ((x%7)+11)%7,     0u,            18446744073709551615ull);
    test("u64e5",          uint64_t, get_weekday_u64e5,          ((x%7)+12)%7,     0u,            18446744073709551615ull);
    test("u64e6",          uint64_t, get_weekday_u64e6,          ((x%7)+13)%7,     0u,            18446744073709551615ull);
    test("64iso7",         int64_t,  get_weekday_64iso7,         (((x%7)+6)%7)+1,  INT64_MIN,     INT64_MAX      );
    test("64iso1",         int64_t,  get_weekday_64iso1,         (((x%7)+7)%7)+1,  INT64_MIN,     INT64_MAX      );
    test("64iso2",         int64_t,  get_weekday_64iso2,         (((x%7)+8)%7)+1,  INT64_MIN,     INT64_MAX      );
    test("64iso3",         int64_t,  get_weekday_64iso3,         (((x%7)+9)%7)+1,  INT64_MIN,     INT64_MAX      );
    test("64iso",          int64_t,  get_weekday_64iso,          (((x%7)+10)%7)+1, INT64_MIN,     INT64_MAX      );
    test("64iso5",         int64_t,  get_weekday_64iso5,         (((x%7)+11)%7)+1, INT64_MIN,     INT64_MAX      );
    test("64iso6",         int64_t,  get_weekday_64iso6,         (((x%7)+12)%7)+1, INT64_MIN,     INT64_MAX      );
    test("u64iso7",        uint64_t, get_weekday_u64iso7,        (((x%7)+6)%7)+1,  0u,            18446744073709551615ull);
    test("u64iso1",        uint64_t, get_weekday_u64iso1,        (((x%7)+7)%7)+1,  0u,            18446744073709551615ull);
    test("u64iso2",        uint64_t, get_weekday_u64iso2,        (((x%7)+8)%7)+1,  0u,            18446744073709551615ull);
    test("u64iso3",        uint64_t, get_weekday_u64iso3,        (((x%7)+9)%7)+1,  0u,            18446744073709551615ull);
    test("u64iso",         uint64_t, get_weekday_u64iso,         (((x%7)+10)%7)+1, 0u,            18446744073709551615ull);
    test("u64iso5",        uint64_t, get_weekday_u64iso5,        (((x%7)+11)%7)+1, 0u,            18446744073709551615ull);
    test("u64iso6",        uint64_t, get_weekday_u64iso6,        (((x%7)+12)%7)+1, 0u,            18446744073709551615ull);
    test("64_narrow",      int64_t,  get_weekday_64_narrow,      ((x%7)+7)%7,      -230528005926027270ll, 230640595916711531ll);
    test("64e1_narrow",    int64_t,  get_weekday_64e1_narrow,    ((x%7)+8)%7,      -230415415935343002ll, 230753185907395792ll);
    test("64e2_narrow",    int64_t,  get_weekday_64e2_narrow,    ((x%7)+9)%7,      -230696890912053658ll, 230471710930685136ll);
    test("64e3_narrow",    int64_t,  get_weekday_64e3_narrow,    ((x%7)+10)%7,     -230584300921369397ll, 230584300921369397ll);
    test("64unix_narrow",  int64_t,  get_weekday_64unix_narrow,  ((x%7)+11)%7,     -230471710930685136ll, 230696890912053658ll);
    test("64e5_narrow",    int64_t,  get_weekday_64e5_narrow,    ((x%7)+12)%7,     -230753185907395792ll, 230415415935343002ll);
    test("64e6_narrow",    int64_t,  get_weekday_64e6_narrow,    ((x%7)+13)%7,     -230640595916711531ll, 230528005926027263ll);
    test("u64_narrow",     uint64_t, get_weekday_u64_narrow,     ((x%7)+7)%7,      0u,            461168601842738795ull);
    test("u64e1_narrow",   uint64_t, get_weekday_u64e1_narrow,   ((x%7)+8)%7,      0u,            461168601842738801ull);
    test("u64e2_narrow",   uint64_t, get_weekday_u64e2_narrow,   ((x%7)+9)%7,      0u,            461168601842738800ull);
    test("u64e3_narrow",   uint64_t, get_weekday_u64e3_narrow,   ((x%7)+10)%7,     0u,            461168601842738799ull);
    test("u64unix_narrow", uint64_t, get_weekday_u64unix_narrow, ((x%7)+11)%7,     0u,            461168601842738798ull);
    test("u64e5_narrow",   uint64_t, get_weekday_u64e5_narrow,   ((x%7)+12)%7,     0u,            461168601842738797ull);
    test("u64e6_narrow",   uint64_t, get_weekday_u64e6_narrow,   ((x%7)+13)%7,     0u,            461168601842738796ull);
    test("64iso7_narrow",  int64_t,  get_weekday_64iso7_narrow,  (((x%7)+6)%7)+1,  -230640595916711531ll, 230528005926027263ll);
    test("64iso1_narrow",  int64_t,  get_weekday_64iso1_narrow,  (((x%7)+7)%7)+1,  -230528005926027270ll, 230640595916711531ll);
    test("64iso2_narrow",  int64_t,  get_weekday_64iso2_narrow,  (((x%7)+8)%7)+1,  -230415415935343002ll, 230753185907395792ll);
    test("64iso3_narrow",  int64_t,  get_weekday_64iso3_narrow,  (((x%7)+9)%7)+1,  -230696890912053658ll, 230471710930685136ll);
    test("64iso_narrow",   int64_t,  get_weekday_64iso_narrow,   (((x%7)+10)%7)+1, -230584300921369397ll, 230584300921369397ll);
    test("64iso5_narrow",  int64_t,  get_weekday_64iso5_narrow,  (((x%7)+11)%7)+1, -230471710930685136ll, 230696890912053658ll);
    test("64iso6_narrow",  int64_t,  get_weekday_64iso6_narrow,  (((x%7)+12)%7)+1, -230753185907395792ll, 230415415935343002ll);
    test("u64iso7_narrow", uint64_t, get_weekday_u64iso7_narrow, (((x%7)+6)%7)+1,  0u,            461056011852054527ull);
    test("u64iso1_narrow", uint64_t, get_weekday_u64iso1_narrow, (((x%7)+7)%7)+1,  0u,            461168601842738795ull);
    test("u64iso2_narrow", uint64_t, get_weekday_u64iso2_narrow, (((x%7)+8)%7)+1,  0u,            460887126866028139ull);
    test("u64iso3_narrow", uint64_t, get_weekday_u64iso3_narrow, (((x%7)+9)%7)+1,  0u,            460999716856712400ull);
    test("u64iso_narrow",  uint64_t, get_weekday_u64iso_narrow,  (((x%7)+10)%7)+1, 0u,            461112306847396661ull);
    test("u64iso5_narrow", uint64_t, get_weekday_u64iso5_narrow, (((x%7)+11)%7)+1, 0u,            460830831870686005ull);
    test("u64iso6_narrow", uint64_t, get_weekday_u64iso6_narrow, (((x%7)+12)%7)+1, 0u,            460943421861370266ull);

    table_sep();

    std::cout << "\n" << YELLOW << "ISO date ranges:" << "\n";
    for (const auto& r : r) {
        std::cout << "* " << pad_right(r.label, 22)
                  << " " << pad_left(iso_date(r.found_lo), 16) << " (" << weekday_abbr(r.found_lo) << ")"
                  << " to " << pad_left(iso_date(r.found_hi), 16) << " (" << weekday_abbr(r.found_hi) << ")\n";
    }

    double secs = std::chrono::duration<double>(std::chrono::steady_clock::now() - t_start).count();
    std::cout << RESET << "\nCompleted in "
              << std::fixed << std::setprecision(1) << secs << "s"
              << "\n";

    return 0;
}
