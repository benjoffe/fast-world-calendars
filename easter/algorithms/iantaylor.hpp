#pragma once
#include <stdint.h>

// Ian Taylor's 16-bit Gregorian Easter algorithm.
// Source: https://chilliant.blogspot.com/2010/12/computus-1.html
// Returns days since March 22 (0 = March 22, ..., 34 = April 25).
static inline uint32_t easter_iantaylor(int32_t year) {
    int32_t a = year % 19;
    int32_t b = year >> 2;
    int32_t c = (b / 25) + 1;
    int32_t d = (c * 3) >> 2;
    int32_t e = ((a * 19) - ((c * 8 + 5) / 25) + d + 15) % 30;
    e += (29578 - a - e * 32) >> 10;
    e -= ((year % 7) + b - d + e + 2) % 7;
    return e - 22;
}