#pragma once
#include <stdint.h>
//#include <utility> // for std::pair

// Compute Gregorian Easter for a given year.
// Valid domain: -11,103,600 .. 16,663,835
// Returns days since March 22 (0 = March 22, ..., 34 = April 25).
static inline uint32_t easter_benjoffe(int32_t year) {
    uint32_t constexpr SHIFT = 400 * 19 * (25 * 30 * 2 - 39);
    uint32_t constexpr M1C = (1ull << 32) / 100 + 1;
    uint32_t constexpr M25 = (1ull << 32) * 8 / 25 + 1;
    uint64_t constexpr M19 = (1ull << 32) / 19 + 1 + (11ull << 32);
    uint32_t constexpr M30 = (1ull << 32) / 30 + 1;
    uint32_t constexpr M67 = (1ull << 32) * 6 / 7;

    uint32_t y = year + SHIFT;
    uint32_t c = (uint64_t) y * M1C >> 32;
    uint32_t a = (uint64_t) c * M25 >> 32;
    uint64_t b = (uint64_t) y * M19;
    uint32_t d = (uint32_t) b > 0x90000000;
    uint32_t e = b >> 32;
    uint32_t f = c - (c >> 2);
    uint32_t g = a - f + e;
    uint32_t h = (uint64_t) g * M30 >> 32;
    uint32_t i = (g + (h << 1)) & 31;
    uint32_t j = 31 - i - (d >= i);
    uint32_t k = y + (y >> 2) - f + j;
    uint32_t m = k * M67 >> 29;

    return j + m - 3;
    /*
    // Use below for testing month/day logic is correct:
    uint32_t v = j + m + 115;
    int32_t month = (v >> 5);
    int32_t day   = (v & 31) + (v >> 7);
    return uint32_t(month == 3 ? day - 22 : 9 + day);
    */
}

// Fast floor division by 30.
// (rounds towards negative infinity).
// Accurate over the full signed 32-bit range.
// Robison's N-bit multiply-add method.
// Cooperative divisor (`A` fits in bit-width).
// Optional ref:
// https://www.benjoffe.com/fast-floordiv#robison=i32_30
static inline int32_t robison_i32_floordiv_30(int32_t x) {
  int32_t A = ((1ll << 33) / 30); // 286331153
  int32_t B = A / 2; // 143165576
  return (int32_t) (((int64_t)x * A + B) >> 33);
}

static inline uint32_t mod30(int32_t x) {
    return x - 30 * robison_i32_floordiv_30(x);
}

// Returns: 7 - ((x + 3) mod 7)
static inline uint32_t nextSunday(int32_t x) {
    uint32_t const M67 = (1ull << 32) * 6 / 7;
    uint32_t const A = 0x92490000;
    return (x * M67 + A) >> 29;
}

static inline uint32_t getAdjustedEpoch(uint32_t y, uint32_t c, uint32_t a) {
    uint32_t m = y % 19;
    uint32_t t = mod30(int32_t(11 * m - a + c * 8 / 25));
    return 28 - t - ((m > 10) >= t);
}

/*
Alternative options for testing:
static inline uint32_t umod30(uint32_t x) {
    uint32_t const M30 = (1ull << 32) / 30 + 1;
    uint32_t h = (uint64_t) x * M30 >> 32;
    return(x + h * 2) % 32;
}

static inline uint32_t mul8on25(int32_t x) {
    uint32_t const M825 = (1ull << 32) * 8/25 + 1;
    return (uint64_t) x * M825 >> 32;
}

// Alternative getAdjustedEpoch for testing:
// Returns: { y * 11 + y / 19, y % 19 > 10 }
static inline std::pair<uint32_t, bool> mod19thresh(uint32_t y) {
    uint64_t const M = ((1ull << 32) / 19 + 1) + (11ll << 32);
    uint64_t const t = y * M;
    return { t >> 32, uint32_t(t) >= 0x90000000 };
}

static inline uint32_t getAdjustedEpoch(uint32_t y, uint32_t c, uint32_t a) {
    auto [yDiv19, thresh] = mod19thresh(y);
    uint32_t t = umod30(mul8on25(c) - a + yDiv19);
    return 27 - t + (thresh < t);
}
*/

// Compute Gregorian Easter for a given year.
// Valid domain: -73,803,600 .. 70,208,581
// Returns days since March 22 (0 = March 22, ..., 34 = April 25).
static inline uint32_t easter_benjoffe_readable(int32_t year) {
    uint32_t constexpr OFFSET = 400 * 19 * (25 * 30 * 13 - 39);
    uint32_t y = year + OFFSET;
    uint32_t c = y / 100;
    uint32_t a = c - c / 4;
    uint32_t e = getAdjustedEpoch(y, c, a);
    uint32_t w = nextSunday(y + y / 4 - a + e);
    return e + w;
}


// Correct for year in [1894, 2199].  Returns days since March 22.
// Found with Z3 Theorem Solver.
// Presumably much better ones can be found.
static inline uint32_t easter_benjoffe_narrow(int32_t year) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Q = 5392099833419275ull;
    const uint64_t R = 116588730010054835ull;

    uint32_t const yrs = year + 400;
    uint32_t const cen = yrs / 100;
    uint32_t const rd  = cen - yrs - yrs / 4 - cen / 4;
    uint32_t const z   = uint64_t(rd) * M >> 61;

    uint32_t const a   = (uint32_t)year - ((uint64_t)(uint32_t)year * 226050911ull >> 32) * 19u;
    uint32_t const sh  = a * 3;
    uint32_t const q   = (Q >> sh) & 7;
    uint32_t const r   = (R >> sh) & 7;
    uint32_t const i   = q + (r > z);

    return z + i * 7;
}