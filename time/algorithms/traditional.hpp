#pragma once
#include "time/_common.hpp"

inline TIME_S time_traditional1(uint32_t time) {
    uint32_t const hour = time / 3600;
    uint32_t const tsec = time % 3600;
    uint32_t const mins = tsec / 60;
    uint32_t const secs = tsec % 60;
    return { hour, mins, secs };
}

// Same as time_traditional1, except with fixed-point math
// for 32-bit mul-shift divisions.
// Range: time = 0..97612918
// Max return-value: 27114:41:58
inline TIME_S time_traditional1_fp(uint32_t time) {
    uint32_t const hour = (uint64_t(time) * 1193047) >> 32; // time / 3600
    uint32_t const tsec = time - hour * 3600;
    uint32_t const mins = (uint64_t(tsec) * 71582789) >> 32; // time / 60
    uint32_t const secs = tsec - mins * 60;
    return { hour, mins, secs };
}

inline TIME_S time_traditional2(uint32_t time) {
    uint32_t const hour = time / 3600;
    uint32_t const mins = (time / 60) % 60;
    uint32_t const secs = time % 60;
    return { hour, mins, secs };
}

// Note: this one is not itemised in the blog post, as it's
// essentially the same as `time_traditional1` just in reverse,
// and it seems to be much less commonly found in the wild.
// It is used by .Net though.
inline TIME_S time_traditional3(uint32_t time) {
    uint32_t const tmin = time / 60;
    uint32_t const secs = time % 60;
    uint32_t const hour = tmin / 60;
    uint32_t const mins = tmin % 60;
    return { hour, mins, secs };
}

/********************************************/
/**  Time Functions Including DECISECONDS  **/
/********************************************/

inline TIME_SUBUNIT time_traditional_ds1(uint32_t time) {
    uint32_t const tsec = time / 10;
    uint32_t const cent = time % 10;
    uint32_t const hour = tsec / 3600;
    uint32_t const hsec = tsec % 3600;
    uint32_t const mins = hsec / 60;
    uint32_t const secs = hsec % 60;
    return { hour, mins, secs, cent };
}

inline TIME_SUBUNIT time_traditional_ds2(uint32_t time) {
    uint32_t const cent = time % 10;
    uint32_t const hour = time / (3600 * 10);
    uint32_t const mins = time / (60 * 10) % 60;
    uint32_t const secs = (time / 10) % 60;
    return { hour, mins, secs, cent };
}

/*********************************************/
/**  Time Functions Including CENTISECONDS  **/
/*********************************************/

inline TIME_SUBUNIT time_traditional_cs1(uint32_t time) {
    uint32_t const tsec = time / 100;
    uint32_t const cent = time % 100;
    uint32_t const hour = tsec / 3600;
    uint32_t const hsec = tsec % 3600;
    uint32_t const mins = hsec / 60;
    uint32_t const secs = hsec % 60;
    return { hour, mins, secs, cent };
}

inline TIME_SUBUNIT time_traditional_cs2(uint32_t time) {
    uint32_t const cent = time % 100;
    uint32_t const hour = time / (3600 * 100);
    uint32_t const mins = time / (60 * 100) % 60;
    uint32_t const secs = (time / 100) % 60;
    return { hour, mins, secs, cent };
}

/*********************************************/
/**  Time Functions Including MILLISECONDS  **/
/*********************************************/

inline TIME_SUBUNIT time_traditional_ms1(uint32_t time) {
    uint32_t const tsec = time / 1'000;
    uint32_t const mill = time % 1'000;
    uint32_t const hour = tsec / 3600;
    uint32_t const hrem = tsec % 3600;
    uint32_t const mins = hrem / 60;
    uint32_t const secs = hrem % 60;
    return { hour, mins, secs, mill };
}

inline TIME_SUBUNIT time_traditional_ms2(uint32_t time) {
    uint32_t const mill = time % 1000;
    uint32_t const hour = time / (3600 * 1000);
    uint32_t const mins = time / (60 * 1000) % 60;
    uint32_t const secs = (time / 1000) % 60;
    return { hour, mins, secs, mill };
}

/********************************************/
/**  Time Functions Including NANOSECONDS  **/
/********************************************/

inline TIME_SUBUNIT time_traditional_ns1(uint64_t time) {
    uint32_t const tsec = time / 1'000'000'000ull;
    uint32_t const nano = time % 1'000'000'000ull;
    uint32_t const hour = tsec / 3600;
    uint32_t const hrem = tsec % 3600;
    uint32_t const mins = hrem / 60;
    uint32_t const secs = hrem % 60;
    return { hour, mins, secs, nano };
}

inline TIME_SUBUNIT time_traditional_ns2(uint64_t time) {
    uint32_t const nano = time % 1'000'000'000ull;
    uint32_t const hour = time / (3600 * 1'000'000'000ull);
    uint32_t const mins = time / (60 * 1'000'000'000ull) % 60;
    uint32_t const secs = (time / 1'000'000'000ull) % 60;
    return { hour, mins, secs, nano };
}

/**************************************************/
/**  Time Functions With LEAP Second Adjustment  **/
/**************************************************/

inline TIME_S time_traditional_leap1(uint32_t time) {
    uint32_t const is_leap = (time == 86400);
    TIME_S hms = time_traditional1(time - is_leap);
    return { hms.hour, hms.min, hms.sec + is_leap };
}

inline TIME_S time_traditional_leap2(uint32_t time) {
    uint32_t const is_leap = (time == 86400);
    TIME_S hms = time_traditional2(time - is_leap);
    return { hms.hour, hms.min, hms.sec + is_leap };
}