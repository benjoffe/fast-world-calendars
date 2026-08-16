#pragma once
#include <stdint.h>

// Reimplementation of Cassio Neri's weekday algorithms:
// Part 1: https://www.linkedin.com/posts/cassioneri_mathematics-algorithms-cpp-share-7270147856559161346-I1Q9/
// Part 2: https://www.linkedin.com/posts/cassioneri_mathematics-algorithms-cpp-share-7271627704217616387-JIwr/
// Part 3: https://www.linkedin.com/posts/cassioneri_mathematics-algorithms-cpp-share-7273093872149303298-cU9T/
// Part 4: https://www.linkedin.com/feed/update/urn:li:share:7274535815530057728/

// Valid range: full int32
inline uint32_t weekday_neri32(int32_t rd) {
    return (uint32_t(rd) + (rd >= 0 ? 4 : 0)) % 7;
}

// Valid range: full int64
inline uint32_t weekday_neri64(int32_t rd) {
    int64_t rd64 = (int64_t) rd;
    return (uint64_t(rd64) + (rd >= 0 ? 4 : -5)) % 7;
}

// Implementation of Cassio Neri's full-range algorithm
// by hand-rolling the logic typically produced by a compiler.
inline uint32_t weekday_neri32_compiled(int32_t rd) {
    const uint32_t a = rd + (rd >= 0 ? 4 : 0);
    const uint32_t b = (uint64_t(a) * 613566757) >> 32;
    const uint32_t c = (((a - b) >> 1) + b) >> 2;
    return a - c * 7;
}