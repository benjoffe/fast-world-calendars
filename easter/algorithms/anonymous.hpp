#pragma once
#include <stdint.h>

// Anonymous Gregorian algorithm (Meeus/Jones/Butcher).
// Returns days since March 22 (the earliest possible Easter date):
//   0 = March 22, 9 = March 31, 10 = April 1, ..., 34 = April 25.
// Uses floor division / Euclidean modulo so negative years are handled
// consistently (extending the arithmetic beyond the calendar's real domain).
static inline uint32_t easter_anonymous(int32_t year) {
    auto fdiv = [](int32_t a, int32_t b) -> int32_t {
        int32_t q = a / b, r = a % b;
        if (r != 0 && ((r < 0) != (b < 0))) q -= 1;
        return q;
    };
    auto fmod = [](int32_t a, int32_t b) -> int32_t {
        int32_t r = a % b;
        if (r != 0 && ((r < 0) != (b < 0))) r += b;
        return r;
    };
    int32_t a = fmod(year, 19);
    int32_t b = fdiv(year, 100);
    int32_t c = fmod(year, 100);
    int32_t d = fdiv(b, 4);
    int32_t e = fmod(b, 4);
    int32_t f = fdiv(b + 8, 25);
    int32_t g = fdiv(b - f + 1, 3);
    int32_t h = fmod(19*a + b - d - g + 15, 30);
    int32_t i = fdiv(c, 4);
    int32_t k = fmod(c, 4);
    int32_t l = fmod(32 + 2*e + 2*i - h - k, 7);
    int32_t m = fdiv(a + 11*h + 22*l, 451);
    return h + l - 7*m;

    // Alternative for month, day:
    // int32_t n = h + l - 7*m + 114;
    // int32_t month = fdiv(n, 31);
    // int32_t day   = fmod(n, 31) + 1;
    // return uint32_t(month == 3 ? day - 22 : 9 + day);
}


static inline uint32_t easter_anonymous_unsigned(int32_t year) {
    const uint32_t y = (uint32_t) year;
    const uint32_t a = y % 19;
    const uint32_t b = y / 100;
    const uint32_t c = y % 100;
    const uint32_t d = b / 4;
    const uint32_t e = b % 4;
    const uint32_t f = (b + 8) / 25;
    const uint32_t g = (b - f + 1) / 3;
    const uint32_t h = (19 * a + b - d - g + 15) % 30;
    const uint32_t i = c / 4;
    const uint32_t k = c % 4;
    const uint32_t l = (32 + 2 * e + 2 * i - h - k) % 7;
    const uint32_t m = (a + 11 * h + 22 * l) / 451;

    return h + l - 7 * m;
}
