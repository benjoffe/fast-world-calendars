#pragma once
#include <stdint.h>

// 0 (Sunday) to 6 (Saturday)
inline uint32_t weekday_naive(int32_t d) {
    return ((d % 7) + 11) % 7;
}

// 1 (Monday) to 7 (Sunday)
inline uint32_t weekday_naive_iso(int32_t d) {
    return (((d % 7) + 10) % 7) + 1;
}

inline uint32_t weekday_compiled_naive(int32_t rd) {
    int32_t  a = (int64_t)rd * -1840700269 >> 32;
    uint32_t b = ((a + rd) >> 2) - (rd >> 31);
    uint32_t c = rd - b * 8 + b + 11;
    uint64_t d = (uint64_t)c * 613566757 >> 32;
    uint32_t f = (((c - d) >> 1) + d) >> 2;    
    return c - f * 8 + f;
}

// helper function for next method
inline int32_t _signed_add(int32_t a, int32_t b) {
    return int32_t(uint32_t(a) + uint32_t(b));
}

inline uint32_t weekday_compiled_rust(int32_t rd) {
    int32_t a = (int64_t(_signed_add(rd, 4)) * -1840700269) >> 32;
    int32_t b = _signed_add(_signed_add(rd, 4), a);
    int32_t c = (b >> 2) + (uint32_t(b) >> 31);
    int32_t d = rd - c * 7;
    int32_t e = d + 4;
    return e >= 0 ? e : d + 11;
}