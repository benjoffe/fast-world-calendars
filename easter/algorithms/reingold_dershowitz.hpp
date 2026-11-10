#pragma once
#include <stdint.h>

// Reimplementation of the algorithm from
// Calendrical Calculations by Reingold and Dershowitz
// Note: the book contains many intermediary functions,
// this version is highly stripped down.
// Returns days since March 22 (0 = March 22, ..., 34 = April 25).
static inline int32_t easter_reingold_dershowitz(int32_t y) {

    int32_t c = y / 100 + 1;
    int32_t a = y % 19;

    int32_t s = (
        14 + 11 * a
        - c * 3 / 4
        + (5 + 8 * c) / 25
    ) % 30;

    uint32_t t = (s < 0 ? s + 30 : s);
    uint32_t e = t + (t == 0 || (t == 1 && a > 10));
    uint32_t d = 28 - e;
    uint32_t w = (y + y/4 - y/100 + y/400 + 3 + d) % 7;

    return d + 7 - w;
}