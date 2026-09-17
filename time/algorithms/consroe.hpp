#pragma once
#include "time/_common.hpp"
#include "util/_portable_uint128.hpp"

// Modified from Andrew Consroe's post:
// https://aconz2.github.io/2026/09/09/muldiv.html
// Which specifies `time_bogo_1` and `time_bogo_2`.

// Same range as `time_bogo_1` but with a slightly different
// calculated multiplier rather than a pre-solved constant.
// Accurate to 1198378
// Maximum output: 332:52:58 (13.8 days)
inline TIME_S time_consroe_1(uint32_t time) {
    uint64_t const MUL_H = (1ull << 32) / 3600 + 1;
    uint64_t const MUL_M = (1ull << 25) / 60 + 1;
    uint64_t const MUL = (MUL_H << 32) + MUL_M;

    uint128_t prd = (uint128_t)time * MUL;
    uint64_t lo = prd;
    uint64_t hi = prd >> 64;

    uint64_t tmin = lo >> 25;

    uint32_t hour = hi;
    uint32_t minute = (tmin + 4 * hour) % 64;
    uint32_t second = (time + 4 * tmin) % 64;

    return { hour, minute, second };
}

// Similar idea to `time_bogo_2` (hour being the high 64 bits)
// Source function accurate for ~70 days, but this modified
// version has a different multiplier, yielding a larger range.
// Accurate to 41288398
// Maximum output: 11468:59:58 (477.8 days)
inline TIME_S time_consroe_2(uint32_t time) {
    uint64_t const MUL_H = (1ull << 33) / 3600 + 1;
    uint64_t const MUL_M = (1ull << 32) / 60 + 1;
    uint64_t const MUL = (MUL_H << 42) + MUL_M;

    uint128_t prd = (uint128_t)time * MUL;
    uint64_t lo = prd;
    uint64_t hi = prd >> 64;

    // You can reduce below to shift 31
    // and adjust MUL_M accordingly
    // to get one extra hour of range
    // but not worth it, shift 32 is
    // preferable on some platforms:
    uint64_t tmin = lo >> 32;

    uint32_t hour = hi >> 11;
    uint32_t minute = (tmin + 4 * hour) % 64;
    uint32_t second = (time + 4 * tmin) % 64;

    return { hour, minute, second };
}