// MIT License

// Copyright (c) 2026 - Ben Joffe <https://www.benjoffe.com/>

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once
#include "time/_common.hpp"
#include "util/_portable_uint128.hpp"


// Full range
inline TIME_S time_benjoffe_v1(uint32_t time) {
    uint32_t tmin = time / 60;
    uint32_t hour = time / 3600;

    uint32_t second = time - tmin * 60;
    uint32_t minute = tmin - hour * 60;

    return { hour, minute, second };
}

// accurate from 0 to 2257198 (626:59:58)
inline TIME_S time_benjoffe_v1_fp(uint32_t time) {
    uint32_t tmin = (uint64_t) time * 71582789 >> 32; // "total min": t / 60
    uint32_t hour = (uint64_t) time * 1193047 >> 32;  // hours: t / 3600

    uint32_t second = time - tmin * 60;
    uint32_t minute = tmin - hour * 60;

    return { hour, minute, second };
}

// accurate from 0 to 2255818 (626:36:58)
inline TIME_S time_benjoffe_v2(uint32_t time) {
    uint64_t hprd = uint64_t(time) * 1193047;
    uint32_t mlow = time * 71582789;
    uint32_t hour = hprd >> 32;

    uint32_t hlow = uint32_t(hprd);
    uint32_t minute = uint64_t(hlow) * 60 >> 32;
    uint32_t second = uint64_t(mlow) * 60 >> 32;

    return { hour, minute, second };
}

inline TIME_S time_benjoffe_v2_64(uint32_t time) {
    uint64_t M_MUL = ((1ull << 32) / 60 + 1) << 32;
    uint64_t H_MUL = ((1ull << 32) / 3600 + 1) << 32;

    uint128_t hprd = uint128_t(time) * H_MUL;
    uint64_t mlow = time * M_MUL;
    uint32_t hour = hprd >> 64;

    uint64_t hlow = uint64_t(hprd);
    uint32_t minute = uint128_t(hlow) * 60 >> 64;
    uint32_t second = uint128_t(mlow) * 60 >> 64;

    return { hour, minute, second };
}

// accurate from 0 to 2257198 (626:59:58)
inline TIME_S time_benjoffe_v3(uint32_t time) {
    uint32_t tmin = uint64_t(time) * 71582789 >> 32; // = time / 60 - fails at 97612919 (1129 days)
    uint32_t hour = uint64_t(time) * 1193047 >> 32; // = time / 3600 - fails at 2257199 (26 days)

    uint32_t second = (time + (tmin << 2)) & 63; // = time - tmin * 60
    uint32_t minute = (tmin + (hour << 2)) & 63; // = time - hour * 60

    return { hour, minute, second };
}

inline TIME_S time_benjoffe_v3b(uint32_t time) {
    uint64_t hprd = uint64_t(time) * 1193047;
    uint64_t mprd = uint64_t(time) * 71582789;
    uint32_t hour = hprd >> 32;

    uint32_t hlow = uint32_t(hprd);
    uint32_t mlow = uint32_t(mprd);
    uint32_t minute = uint64_t(hlow) * 60 >> 32;
    uint32_t second = (mlow >> 26) - (mlow >> 30);

    return { hour, minute, second };
}

inline TIME_S time_benjoffe_v3c(uint32_t time) {
    uint64_t hprd = uint64_t(time) * 1193047;
    uint64_t mprd = uint64_t(time) * 71582789;
    
    uint32_t mlow = uint32_t(mprd);    

    uint32_t tmin = mprd >> 32;
    uint32_t hour = hprd >> 32;

    uint32_t minute = (tmin + (hour << 2)) & 63;
    uint32_t second = (mlow >> 26) - (mlow >> 30);

    return { hour, minute, second };
}

inline TIME_S time_benjoffe_v3_64(uint32_t time) {
    uint64_t M_MUL = ((1ull << 32) / 60 + 1) << 32;
    uint64_t H_MUL = ((1ull << 32) / 3600 + 1) << 32;

    uint64_t tmin = uint128_t(time) * M_MUL >> 64; // = time / 60 - fails at 97612919 (1129 days)
    uint32_t hour = uint128_t(time) * H_MUL >> 64; // = time / 3600 - fails at 2257199 (26 days)

    uint32_t second = (time + (tmin << 2)) & 63; // = time - tmin * 60
    uint32_t minute = (tmin + (hour << 2)) & 63; // = time - hour * 60

    return { hour, minute, second };
}

inline TIME_S time_benjoffe_v3_64b(uint32_t time) {
    uint64_t M_MUL = ((1ull << 32) / 60 + 1) << 32;
    uint64_t H_MUL = ((1ull << 32) / 3600 + 1) << 32;

    uint128_t mprd = uint128_t(time) * M_MUL;
    uint32_t hour = uint128_t(time) * H_MUL >> 64; // = time / 3600 - fails at 2257199 (26 days)

    uint64_t tmin = mprd >> 64; // = time / 60 - fails at 97612919 (1129 days)
    uint64_t mlow = uint64_t(mprd);    
    
    uint32_t second = (mlow >> 58) - (mlow >> 62);
    uint32_t minute = (tmin + (hour << 2)) & 63; // = time - hour * 60

    return { hour, minute, second };
}

// accurate from 0 to 115199 (31:59:59)
inline TIME_S time_benjoffe_v4(uint32_t time) {
    uint32_t const hour = time * 37283 >> 27; // = time / 3600
    uint32_t const tsec = time - hour * 3600; // = time % 3600
    uint32_t const mins = tsec * 2185 >> 17;  // = tsec / 60
    uint32_t const secs = tsec - mins * 60;   // = tsec % 60
    return { hour, mins, secs };
}


/**************************************************/
/**  Time Functions With LEAP Second Adjustment  **/
/**************************************************/


inline TIME_S time_benjoffe_leap0(uint32_t time) {
    uint32_t const is_leap = (time == 86400);
    TIME_S hms = time_benjoffe_v2(time - is_leap);
    return { hms.hour, hms.min, hms.sec + is_leap };
}

inline TIME_S time_benjoffe_leap1(uint32_t time) {

    uint32_t tinc = time + 1;
    uint32_t tmin = (uint64_t(tinc) * 143163919) >> 33;
    uint32_t hour = (uint64_t(tinc) * 2386065) >> 33;

    uint32_t second = time - tmin * 60;
    uint32_t minute = tmin - hour * 60;

    return { hour, minute, second };
}

// Note: this does not appear in the blog.
// It is slightly slower than leap1, and requires 64-bit addition.
inline TIME_S time_benjoffe_leap2(uint32_t time) {

    uint32_t tmin = (uint64_t(time) * 71582788 + 0x59F0ll) >> 32;
    uint32_t hour = (uint64_t(time) * 1193046  + 0x9C00ll) >> 32;

    uint32_t second = time - tmin * 60;
    uint32_t minute = tmin - hour * 60;

    return { hour, minute, second };
}

/********************************************/
/**  Time Functions Including DECISECONDS  **/
/********************************************/

inline TIME_SUBUNIT time_benjoffe_ds1(uint32_t time) {

    uint32_t tmin = uint64_t(time) * 7158279   >> 32; // = time / 600;   ceil(2^32 / 600)
    uint32_t hour = uint64_t(time) * 477219    >> 34; // = time / 36000; ceil(2^34 / 36000)
    uint32_t secs = uint64_t(time) * 429496730 >> 32; // = time / 10;    ceil(2^32 / 10)

    uint32_t second = secs - tmin * 60;
    uint32_t minute = tmin - hour * 60;
    uint32_t centi  = time - secs * 10;

    return { hour, minute, second, centi };
}

/*********************************************/
/**  Time Functions Including CENTISECONDS  **/
/*********************************************/

inline TIME_SUBUNIT time_benjoffe_cs1(uint32_t time) {

    uint32_t tmin = uint64_t(time) * 11453247 >> 36; // = time / 6000;   ceil(2^40 / 6000)
    uint32_t hour = uint64_t(time) * 3054199 >> 40;  // = time / 360000; ceil(2^40 / 360000)
    uint32_t secs = uint64_t(time) * 42949673 >> 32; // = time / 1000;   ceil(2^32 / 100)

    uint32_t second = secs - tmin * 60;
    uint32_t minute = tmin - hour * 60;
    uint32_t milli  = time - secs * 100;

    return { hour, minute, second, milli };
}

inline TIME_SUBUNIT time_benjoffe_cs2(uint32_t t_centi) {

    uint64_t wide = t_centi * 42949673ll;
    uint64_t time = wide >> 32;
    uint32_t milli = uint32_t(wide) * 100ll >> 32;

    uint64_t prd0  = 1193047ll * time;
    uint64_t prd1  = 71582789ll * time;
        
    uint32_t hour   = prd0 >> 32;
    uint32_t minute = uint32_t(prd0) * 60ll >> 32;
    uint32_t second = uint32_t(prd1) * 60ll >> 32;

    return { hour, minute, second, milli };
}

/*********************************************/
/**  Time Functions Including MILLISECONDS  **/
/*********************************************/

inline TIME_SUBUNIT time_benjoffe_ms1(uint32_t t_milli) {

    uint64_t time = t_milli / 1000;
    uint32_t milli = t_milli % 1000;

    uint32_t tmin = time * 71582789 >> 32; // = time / 60
    uint32_t hour = time *  1193047 >> 32; // = time / 3600

    uint32_t second = (time + (tmin << 2)) & 63; // = time - tmin * 60
    uint32_t minute = (tmin + (hour << 2)) & 63; // = time - hour * 60

    return { hour, minute, second, milli };
}

inline TIME_SUBUNIT time_benjoffe_ms2(uint32_t t_milli) {

    uint32_t time = uint64_t(t_milli) * 274877907 >> 38;  // = time / 1000;    ceil(2^36 / 1000)
    uint32_t tmin = uint64_t(t_milli) * 1172812403 >> 46; // = time / 60000;   ceil(2^38 / 60000)
    uint32_t hour = uint64_t(t_milli) * 2501999793 >> 53; // = time / 3600000; ceil(2^46 / 3600000)

    uint32_t second = time - tmin * 60;
    uint32_t minute = tmin - hour * 60;
    uint32_t milli = t_milli - time * 1000;

    return { hour, minute, second, milli };
}

/********************************************/
/**  Time Functions Including NANOSECONDS  **/
/********************************************/

inline TIME_SUBUNIT time_benjoffe_ns1(uint64_t t_nano) {

    uint32_t time = t_nano / 1'000'000'000ull;
    uint32_t nano = t_nano % 1'000'000'000ull;

    uint64_t prd0  = 1193047ll * time;
    uint64_t prd1  = 71582789ll * time;
        
    uint32_t hour   = prd0 >> 32;
    uint32_t minute = uint32_t(prd0) * 60ll >> 32;
    uint32_t second = uint32_t(prd1) * 60ll >> 32;

    return { hour, minute, second, nano };
}

inline TIME_SUBUNIT time_benjoffe_ns2(uint64_t t_nano) {

    uint32_t tmin = t_nano / (60 * 1'000'000'000ULL);
    uint32_t hour = t_nano / (3600 * 1'000'000'000ULL);
    uint32_t time = t_nano / 1'000'000'000ULL;

    uint32_t second = time - tmin * 60;
    uint32_t minute = tmin - hour * 60;
    uint32_t nano = t_nano - time * 1'000'000'000;

    return { hour, minute, second, nano };
}

inline TIME_SUBUNIT time_benjoffe_ns3(uint64_t t_nano) {

    // ceil(2 ^ 64 / (60 * 1000000000 >> 11))   = 629,648,864,383
    // ceil(2 ^ 64 / (3600 * 1000000000 >> 13)) = 41,976,590,959
    // ceil(2 ^ 64 / (1000000000 >> 9))         = 9,444,732,965,740

    uint64_t S = uint64_t(-1) / (1000000000ull >> 9) + 1;
    uint64_t M = uint64_t(-1) / (60ull * 1000000000 >> 11) + 1;
    uint64_t H = uint64_t(-1) / (3600ull * 1000000000 >> 13) + 1;

    uint32_t time = uint128_t(t_nano >> 9) * S >> 64;
    uint32_t tmin = uint128_t(t_nano >> 11) * M >> 64;
    uint32_t hour = uint128_t(t_nano >> 13) * H >> 64;

    uint32_t second = time - tmin * 60;
    uint32_t minute = tmin - hour * 60;
    uint32_t nano = t_nano - time * 1'000'000'000;

    return { hour, minute, second, nano };
}

inline TIME_SUBUNIT time_benjoffe_ns4(uint64_t t_nano) {
    
    // 10^9/2^9 = 1953125
    uint64_t low = t_nano >> 9;
    uint64_t M = uint64_t(-1) / (1'000'000'000 >> 9) + 1; // 9444732965740 (44 bit number)
    uint128_t wide = uint128_t(low) * M;
    uint64_t time = wide >> 64;
    uint32_t nano = t_nano - time * 1'000'000'000ULL;

    uint64_t prd0  = 1193047ll * time;
    uint64_t prd1  = 71582789ll * time;
        
    uint32_t hour   = prd0 >> 32;
    uint32_t minute = uint32_t(prd0) * 60ll >> 32;
    uint32_t second = uint32_t(prd1) * 60ll >> 32;

    return { hour, minute, second, nano };
}

inline TIME_SUBUNIT time_benjoffe_ns5(uint64_t t_nano) {
    
    uint64_t low = t_nano >> 9;
    uint32_t time = (low * 2199 + (low * 99881871 >> 32)) >> 32;
    uint32_t nano = t_nano - time * 1'000'000'000ULL;

    uint64_t prd0  = 1193047ll * time;
    uint64_t prd1  = 71582789ll * time;
        
    uint32_t hour   = prd0 >> 32;
    uint32_t minute = uint32_t(prd0) * 60ll >> 32;
    uint32_t second = uint32_t(prd1) * 60ll >> 32;

    return { hour, minute, second, nano };
}

inline TIME_SUBUNIT time_benjoffe_ns6(uint64_t t_nano) {
    uint64_t low = t_nano >> 9;
    uint32_t time = (low * 36028797 + ((low * 39) >> 11)) >> 46;
    uint32_t nano = t_nano - time * 1'000'000'000ULL;

    uint64_t prd0  = 1193047ll * time;
    uint64_t prd1  = 71582789ll * time;
        
    uint32_t hour   = prd0 >> 32;
    uint32_t minute = uint32_t(prd0) * 60ll >> 32;
    uint32_t second = uint32_t(prd1) * 60ll >> 32;

    return { hour, minute, second, nano };
}