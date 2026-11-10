#include <stdint.h>
#include <iostream>
#include <cstdio>
#include <string>
#include <limits>
#include <chrono>
#include <iomanip>

#include "easter/algorithms/anonymous.hpp"
#include "easter/algorithms/benjoffe.hpp"
#include "easter/algorithms/iantaylor.hpp"
#include "easter/algorithms/dirkloss.hpp"
#include "easter/algorithms/reingold_dershowitz.hpp"

static constexpr const char* RESET = "\033[0m";
static constexpr const char* AMBER = "\033[38;5;216m";

static std::string pad_right(std::string s, int w) {
    while ((int)s.size() < w) s += " ";
    return s;
}
static std::string pad_left(std::string s, int w) {
    while ((int)s.size() < w) s = " " + s;
    return s;
}

static constexpr int W_ALGO = 22, W_MIN = 16, W_MAX = 16;

static void table_sep() {
    std::cout << AMBER << "+" << std::string(W_ALGO + 2, '-')
              << "+" << std::string(W_MIN + 2, '-')
              << "+" << std::string(W_MAX + 2, '-')
              << "+" << RESET << "\n";
}
static void table_header() {
    table_sep();
    std::cout << AMBER
              << "| " << pad_right("ALGORITHM", W_ALGO)
              << " | " << pad_left("MIN_YEAR", W_MIN)
              << " | " << pad_left("MAX_YEAR", W_MAX)
              << " |" << RESET << "\n";
    table_sep();
}

static void print_row(const std::string& algo, const std::string& min_year,
                      const std::string& max_year, const char* color) {
    const char* col = color ? color : RESET;
    std::cout << col
              << "| " << pad_right(algo, W_ALGO)
              << " | " << pad_left(min_year, W_MIN)
              << " | " << pad_left(max_year, W_MAX)
              << " |" << RESET << "\n";
}

using Fn = uint32_t(*)(int32_t);

static bool g_verbose = false;

// Sweeps up from `start` to INT32_MAX, then down from start-1 to INT32_MIN,
// comparing test against ref. Each sweep stops at its first mismatch.
// Reports (MIN_YEAR, MAX_YEAR) — the extreme values where they still agreed.
static bool run_search(const char* label, Fn ref, Fn test, int32_t start = 0) {
    constexpr uint32_t PRINT_FREQ = 1 << 20;

    auto show = [&](const std::string& min_cell, const std::string& max_cell) {
        print_row(label, min_cell, max_cell, nullptr);
        std::cout << "\033[1A\r" << std::flush;
    };

    // Runs one sweep in direction `step`; returns the last agreeing year and
    // whether the whole range agreed. `ok` is false if nothing agreed.
    auto sweep = [&](int64_t from, int64_t to, int64_t step, auto&& progress,
                     int32_t& last_ok, bool& ok) {
        uint32_t ticks = 0;
        ok = false;
        for (int64_t t = from; step > 0 ? t <= to : t >= to; t += step) {
            int32_t v = int32_t(t);
            asm volatile("" : "+r"(v));
            if (ref(v) != test(v)) {
                if (g_verbose)
                    std::cout << "\033[2K\rLast ok " << (ok ? last_ok : int32_t(from - step)) << " - Next got: "
                              << test(v) << "; expected: " << ref(v) << "\n";
                return false;
            }
            last_ok = v;
            ok = true;
            if ((++ticks & (PRINT_FREQ - 1)) == 0)
                progress(v);
        }
        return true;
    };

    show("-", "-");

    int32_t max_ok = start;
    bool any_pos = false;
    bool pos_full = sweep(start, INT32_MAX, 1,
                          [&](int32_t v) { show("-", std::to_string(v)); },
                          max_ok, any_pos);

    std::string max_progress = any_pos ? std::to_string(max_ok) : "-";

    int32_t min_ok = start - 1;
    bool any_neg = false;
    bool neg_full = sweep(int64_t(start) - 1, INT32_MIN, -1,
                          [&](int32_t v) { show(std::to_string(v), max_progress); },
                          min_ok, any_neg);

    // Passing range is [min_ok, max_ok]; a side with no passes collapses onto start.
    std::string min_cell, max_cell;
    if (!any_pos && !any_neg) {
        min_cell = max_cell = "-";
    } else {
        min_cell = std::to_string(any_neg ? min_ok : start);
        max_cell = std::to_string(any_pos ? max_ok : start - 1);
    }

    print_row(label, min_cell, max_cell, AMBER);
    return pos_full && neg_full;
}

// Returns int32_t, so it needs adapting to Fn.
static uint32_t ref_reingold_dershowitz(int32_t y) { return easter_reingold_dershowitz(y); }

int main(int argc, char** argv) {
    for (int i = 1; i < argc; ++i)
        if (std::string(argv[i]) == "-v") g_verbose = true;

    auto t_start = std::chrono::steady_clock::now();

    std::cout << "\nSweeps the full 32-bit Gregorian year range exhaustively.\n"
              << "Output: days since March 22 (0=Mar 22, 34=Apr 25).\n"
              << "Each row shows the range over which the algorithm matches the Meeus reference.\n"
              << "Pass -v to print the first mismatch found in each sweep.\n\n";

    table_header();

    constexpr auto ref = easter_anonymous;

    run_search("benjoffe",             ref, easter_benjoffe);
    run_search("benjoffe_readable",    ref, easter_benjoffe_readable);
    run_search("benjoffe_narrow",      ref, easter_benjoffe_narrow, 1894);
    run_search("dirkloss",             ref, easter_dirkloss, 1583);
    run_search("reingold_dershowitz",  ref, ref_reingold_dershowitz);
    run_search("iantaylor",            ref, easter_iantaylor);
    run_search("anonymous_unsigned",   ref, easter_anonymous_unsigned);

    table_sep();

    double secs = std::chrono::duration<double>(std::chrono::steady_clock::now() - t_start).count();
    std::cout << AMBER << "done" << RESET
              << " in " << std::fixed << std::setprecision(1) << secs << "s\n";

    return 0;
}
