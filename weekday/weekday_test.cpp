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

#include "weekday/algorithms/basic.hpp"
#include "weekday/algorithms/benjoffe.hpp"
#include "weekday/algorithms/hinnant.hpp"
#include "weekday/algorithms/neri.hpp"

static const char* weekday_abbr(int32_t day) {
    static const char* names[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    return names[((day % 7) + 4 + 7) % 7];
}

static std::string iso_date(int32_t day) {
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
static constexpr const char* YELLOW = "\033[38;5;221m";
static constexpr const char* GREEN  = "\033[38;5;121m";
static constexpr const char* RED    = "\033[38;5;203m";
static constexpr const char* BLUE   = "\033[38;5;75m";

static void table_sep() {
    std::cout << AMBER << "+---------------------+-------------+------------+------------+--------+" << RESET << "\n";
}

static void table_header() {
    table_sep();
    std::cout << AMBER << "| ALGORITHM           |         MIN |        MAX |      YEARS |  RANGE |" << RESET << "\n";
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

static std::string fmt_years(int64_t days) {
    std::string s = std::to_string(std::abs(days) * 400 / 146097);
    for (int i = (int)s.size() - 3; i > 0; i -= 3) s.insert(i, ",");
    return pad_left(s, 10);
}

static void print_row(const char* label, int32_t mn, int32_t mx, bool done,
                      int32_t lo = 0, int32_t hi = 0) {
    int64_t span  = (int64_t)mx - mn + 1;
    int64_t total = (int64_t)INT32_MAX - INT32_MIN + 1;

    std::string name = std::string(label);
    while ((int)name.size() < 19) name += " ";

    const char* col = done ? AMBER : RESET;

    char buf[8];
    snprintf(buf, sizeof(buf), "%5.1f%%", std::floor(1000.0 * span / total) / 10.0);
    bool full    = (mn == lo && mx == hi);
    bool exceeds = (mn < lo || mx > hi);
    const char* range_col = done ? (exceeds ? BLUE : (full ? GREEN : RED)) : RESET;
    std::string range = std::string(RESET) + range_col + buf + RESET + col;

    std::cout << col
              << "| " << name
              << " | " << pad_left(std::to_string(mn), 11)
              << " | " << pad_left(std::to_string(mx), 10)
              << " | " << fmt_years(span)
              << " | " << range << " |"
              << RESET << "\n";
}

struct SearchResult { const char* label; int32_t found_lo, found_hi; };

template <typename Fref, typename Ftest>
SearchResult run_search(const char* label, Fref ref, Ftest test, int32_t lo, int32_t hi) {
    constexpr uint32_t PRINT_FREQ = 1 << 25;

    int32_t found_lo = 0, found_hi = -1;
    bool pass = true;

    print_row(label, found_lo, found_hi, false);
    std::cout << "\033[1A\r" << std::flush;

    for (int32_t dir : {1, -1}) {

        const int32_t start = dir > 0 ? 0 : -1;
        const int32_t limit = dir > 0 ? INT32_MAX : INT32_MIN;
        int32_t& found_end  = dir > 0 ? found_hi : found_lo;

        uint32_t counter = 0;
        for (int32_t y = start;; y += dir) {
            uint32_t expect = ref(y);
            uint32_t actual = test(y);
            if (expect != actual) {
                found_end = y - dir;
                if (y >= 0 ? (y < hi) : (y > lo)) {
                    print_row(label, found_lo, found_hi, true, lo, hi);
                    std::cout << std::flush << RED
                              << "*****  Fail at " << y
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
                print_row(label, found_lo, found_hi, false);
                std::cout << "\033[1A\r" << std::flush;
            }
        }
    }

    if (pass) {
        print_row(label, found_lo, found_hi, true, lo, hi);
    }
    return {label, found_lo, found_hi};
}

int main() {
    int32_t lo = std::numeric_limits<int32_t>::min();
    int32_t hi = std::numeric_limits<int32_t>::max();

    std::cout << "\n\n";

    std::cout << "Each algorithm will be tested sequentially for their range.\n"
              << "Range will be printed in a colour to mean:\n"
              << "* " << GREEN << "Green" << RESET << ": Range matches expectation\n"
              << "* " << BLUE  << "Blue"  << RESET << ":  Range exceeds expectation (eg. undefined behaviour)\n"
              << "* " << RED   << "Red"   << RESET << ":   Range is less than expected\n"
              << "After the process is completed, the ISO date of min/max for each\n"
              << "will be displayed.\n\n";

    auto t_start = std::chrono::steady_clock::now();

    // comparison (test) function:
    auto t_std = weekday_naive;
    auto t_iso = weekday_naive_iso;

    table_header();
    std::vector<SearchResult> r;

    // ISO Formatted Dates: 1 (Monday) .. 7 (Sunday)
    r.push_back(run_search("benjoffe_iso32_489k", t_iso,  weekday_benjoffe_iso32_489k, -89478489, 89478489));
    r.push_back(run_search("benjoffe_iso64",      t_iso,  weekday_benjoffe_iso64, lo, hi));
    
    // Standard Formatted Dates: 0 (Sunday) .. 6 (Saturday)
    r.push_back(run_search("benjoffe32_489k",     t_std, weekday_benjoffe32_489k,   -89128966, 89828012));
    r.push_back(run_search("benjoffe64_full32",   t_std, weekday_benjoffe64_full32, lo, hi));
    r.push_back(run_search("hinnant32",           t_std, weekday_hinnant32,         lo, hi - 4));
    r.push_back(run_search("neri32",              t_std, weekday_neri32,            lo, hi));
    r.push_back(run_search("neri64",              t_std, weekday_neri64,            lo, hi));
    r.push_back(run_search("naive",               t_std, weekday_naive,             lo, hi));
    r.push_back(run_search("compiled_naive",      t_std, weekday_compiled_naive,    lo, hi));
    r.push_back(run_search("compiled_rust",       t_std, weekday_compiled_rust,     lo, hi - 4));

    table_sep();

    std::cout << "\n" << YELLOW << "ISO date ranges:" << "\n";
    for (const auto& r : r) {
        std::cout << "* " << pad_right(r.label, 20)
                  << " " << pad_left(iso_date(r.found_lo), 16) << " (" << weekday_abbr(r.found_lo) << ")"
                  << " to " << pad_left(iso_date(r.found_hi), 16) << " (" << weekday_abbr(r.found_hi) << ")\n";
    }

    double secs = std::chrono::duration<double>(std::chrono::steady_clock::now() - t_start).count();
    std::cout << RESET << "\nCompleted in "
              << std::fixed << std::setprecision(1) << secs << "s"
              << "\n";

    return 0;
}
