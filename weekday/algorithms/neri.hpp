#pragma once
#include <stdint.h>

// Reimplementation of Cassio Neri's weekday algorithms:
// Part 1: https://www.linkedin.com/posts/cassioneri_mathematics-algorithms-cpp-share-7270147856559161346-I1Q9/
// Part 2: https://www.linkedin.com/posts/cassioneri_mathematics-algorithms-cpp-share-7271627704217616387-JIwr/
// Part 3: https://www.linkedin.com/posts/cassioneri_mathematics-algorithms-cpp-share-7273093872149303298-cU9T/
// Part 4: https://www.linkedin.com/feed/update/urn:li:share:7274535815530057728/

inline uint32_t weekday_neri32(int32_t rd) {
    return (uint32_t(rd) + (rd >= 0 ? 4 : 0)) % 7;
}

inline uint32_t weekday_neri64(int32_t rd) {
    int64_t rd64 = (int64_t) rd;
    return (uint64_t(rd64) + (rd >= 0 ? 4 : -5)) % 7;
}