// Copyright 2026 Ben Joffe — MIT License
#pragma once
#include <stdint.h>

/** Standard Formatted Dates: 0 (Sunday) .. 6 (Saturday) **/

// Valid range: -89128966 to 89828012
// -242,057-03-08 (Mon) to 247,910-09-30 (Fri)
// Note: compiler inlines: a * m = 0x9490_0000
inline uint32_t weekday_benjoffe32_489k(int32_t d) {
    static constexpr uint32_t M = 613566757; // ceil(2^32 / 7)
    static constexpr uint32_t A = 89128960; // 0x5500000 = 4 (mod 7)
    return uint32_t(d + A) * M >> 29;
}

// Valid range: full int32 (-2147483648 to 2147483647)
// -5,877,641-06-23 (Tue) to  5,881,580-07-11 (Fri)
// Note: compiler inlines a * m = 0x92A6_0000_0000_0000
inline uint32_t weekday_benjoffe64_full32(int32_t d) {
    static constexpr uint64_t M = 0x2492492493000000; // ceil(2^40/7) * 2^24
    static constexpr uint32_t A = 0x82000000; // 2181038080 = 4 (mod 7)
    return (uint64_t(d) + A) * M >> 61;
}

/** ISO Formatted Dates: 1 (Monday) .. 7 (Sunday) **/

// Valid range:  -89478489 to 89478489
// -243,014-03-21 (Tue) to 246,953-10-13 (Sat)
inline uint32_t weekday_benjoffe_iso32_489k(int32_t d) {
    static constexpr uint32_t M = 613566757;  // ceil(2^32 / 7)
    static constexpr uint32_t Z = 0x90000000; // rotate to 1..7
    return (uint32_t(d) * M + Z) >> 29;
}

// Valid range: full int32 (-2147483648 to 2147483647)
// -5,877,641-06-23 (Tue) to  5,881,580-07-11 (Fri)
inline uint32_t weekday_benjoffe_iso64(int32_t d) {
    static constexpr uint64_t M = 0x2492492493000000; // ceil(2^40/7) * 2^24
    static constexpr uint64_t Z = 0x9000000000000000; // rotate to 1..7
    return (uint64_t(d) * M + Z) >> 61;
}