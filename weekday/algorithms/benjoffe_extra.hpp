// Copyright 2026 Ben Joffe — MIT License
#pragma once
#include <stdint.h>


// Helper function
// lea<scale, disp>(base, index) = disp + base + index * scale, forced to LEA on Clang x86
// Note: does not force to LEA on GCC as GCC already does so.
template<uint32_t scale, uint32_t disp = 0>
inline uint32_t lea(uint32_t base, uint32_t index) noexcept {
    uint32_t r;
    static_assert(scale == 1 || scale == 2 || scale == 4 || scale == 8);
    #if (defined(__i386__) || defined(__x86_64__))
        __asm__("leal %c3(%1,%2,%c4),%0" : "=r"(r) : "r"(base), "r"(index), "n"((int32_t)disp), "n"(scale));
    #else
        r = disp + base + index * scale;
    #endif
    return r;
}

// Same as get_weekday_32unix
// Except using assembly to force the result of `b` to be blind to the compiler
// Helps avoid sub-par codegen.
// https://www.benjoffe.com/fast-day-of-week#fn=32unix
inline uint8_t get_weekday_32unix_forced_asm(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x95000000;        // 2,499,805,184
    const uint32_t a = uint32_t(rd) * M + Z;
    uint32_t b = (rd >> 1) + (rd >> 4);
    asm("" : "+r"(b));
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Same as get_weekday_32unix_v2
// Except using assembly to force the result of `b` to be blind to the compiler
// Helps avoid sub-par codegen.
// https://www.benjoffe.com/fast-day-of-week#fn=32unix_v2
inline uint8_t get_weekday_32unix_v2_forced_asm(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const int32_t  N = int32_t(M * 4);  // -1,840,700,268
    const uint32_t a = uint32_t(rd) * M + N;
    int32_t  b = (int64_t(rd) * N) >> 32;
    asm("" : "+r"(b));
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Same as get_weekday_32unix_v3
// Except using assembly to force usage of LEA for x86
// Helps avoid sub-par codegen.
// https://www.benjoffe.com/fast-day-of-week#fn=32unix_v3
inline uint8_t get_weekday_32unix_v3_forced_asm(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x95000000;     // 2,499,805,184
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return lea<4, Z>(b, a) >> 29;
}


// https//www.benjoffe.com/fast-day-of-week#generalisation
// Weekday algorithm.
// Presented only as material for the blog post (not fastest in its class).
// Modified version of Cassio Neri's formula.
// Unix formatted: [0..6] = [Sun..Sat]
// Valid over 100% of the 32-bit input range.
inline uint32_t get_weekday_1st_attempt(int32_t rd) {
    const uint32_t n = uint32_t(rd) + (rd >= 0 ? 4 : (9 << 28));
    const uint32_t q = (uint64_t) n * 2454267027 >> 34; // 2^34/7+1
    return (n + q) & 7;
}

