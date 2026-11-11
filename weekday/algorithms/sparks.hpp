#pragma once
#include <stdint.h>

// On 6 November 2026, David Sparks emailed me the following
// idea, which works full-range across 16-64 bit. It extends on
// the "Variant 1: Shifts" function, with potentially fewer
// steps on some targets.
// 
// David included the following commentary in the email:
//
// On x86, and some other platforms with small-shift-and-add, it's
// possible to use
//    const u32 b = (rd >> 4) * 9
// This is SHR+LEA, as opposed to SHR+SHR+ADD.  Unfortunately, on
// platforms without a shift-and-add primitive, it's back to three
// instructions without as much ILP.
// 
// It's very slightly less accurate in the lsbits, but all the
// algorithms 16 bits and up continue to work with this change.
// (8 bits breaks, since the lsbits are too close to the significant
// bits.)

inline uint8_t weekday_sparks16(int16_t rd) {
    const uint16_t M = 65536 / 7;
    const uint16_t Z = 0x9400;
    const uint16_t a = uint16_t(rd) * M + Z;
    const uint16_t b = (rd >> 5) * 9; // Approx: rs * 0.28125
    return uint16_t(a + b) >> 13;
}

inline uint8_t weekday_sparks32(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;
    const uint32_t Z = 0x94000000;
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = (rd >> 4) * 9; // Approx: rs * 0.5625
    return uint32_t(a + b) >> 29;
}

inline uint8_t weekday_sparks64(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x9400ull << 48;
    const uint64_t a = uint64_t(rd) * M + Z;
    const uint64_t b = (rd >> 5) * 9ll; // Approx: rs * 0.28125
    return uint64_t(a + b) >> 61;
}
