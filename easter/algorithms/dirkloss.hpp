#pragma once
#include <stdint.h>

// Dirk Loss's ChatGPT generated Easter algorithm.
// Source: https://x.com/dloss/status/2090496142173692232
// https://chatgpt.com/share/6a873ce2-6d24-83eb-9fbe-1e4a1fd46c9f
// Returns days since March 22 (0 = March 22, ..., 34 = April 25).
static inline uint32_t easter_dirkloss(int32_t y_in) {
    uint32_t y = uint32_t(y_in);
    uint32_t C = (y * 5243u) >> 19;
    uint32_t P = y * 6899u;
    uint32_t q19 = P >> 17;
    uint32_t ha = ((P & 0x1ffffu) + 0xe000u) >> 17;
    uint32_t d = C - (C >> 2);
    uint32_t f = (41u * C + 65u) >> 7;
    uint32_t u = 19u*y - q19 + d - f + 15u;
    uint32_t p = u * 143165577u;
    uint32_t t = p >> 27;
    uint32_t hi = p >> 31;
    uint32_t bad = (t + 2u + ha) >> 5;
    uint32_t A = t - hi - bad;
    uint32_t z = y + (y >> 2) - d + A + 2u;
    uint32_t r7 = (z * 613566757u) >> 29;
    return A + 6u - r7;
}