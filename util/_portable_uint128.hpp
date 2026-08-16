#pragma once
#include <cstdint>

// This is a minimal wrapper enabling __uint128_t-style behaviour on
// compilers that do not have it, eg. MSVC and on some 32-bit targets.

// ============================================================================
//  CASE 1: GCC / Clang / LLVM with native unsigned __int128
// ============================================================================
#if defined(__SIZEOF_INT128__)

using uint128_t = __uint128_t;

// No operator overloads here — GCC/Clang already support them natively.

inline uint64_t lo128(uint128_t v) { return (uint64_t)v; }
inline uint64_t hi128(uint128_t v) { return (uint64_t)(v >> 64); }

#else


// ============================================================================
//  CASE 2: MSVC — implement uint128_t manually
// ============================================================================
struct uint128_t {
    uint64_t lo;
    uint64_t hi;

    uint128_t() = default;

    // unsigned
    constexpr uint128_t(uint64_t v) : lo(v), hi(0) {}
    constexpr uint128_t(uint32_t v) : lo(v), hi(0) {}

    // signed literal support (needed!)
    constexpr uint128_t(int v) : lo((uint64_t)(uint32_t)v), hi(0) {}
    constexpr uint128_t(int64_t v) : lo((uint64_t)v), hi(0) {}

    // explicit hi/lo constructor
    constexpr uint128_t(uint64_t hi_, uint64_t lo_) : lo(lo_), hi(hi_) {}

    constexpr explicit operator uint64_t() const { return lo; }
    constexpr explicit operator int64_t()  const { return (int64_t)lo; }
};


// ============================================================================
//  Backend for 64×64 → 128 multiply
// ============================================================================
#if defined(_MSC_VER) && defined(_M_X64)

#include <intrin.h>

inline uint128_t u128_mul64(uint64_t a, uint64_t b) {
    uint128_t r;
    r.lo = _umul128(a, b, &r.hi);
    return r;
}

#elif defined(_MSC_VER) && defined(_M_ARM64)

#include <intrin.h>

// ARM64 MSVC: hi via __umulh, lo via normal mul
inline uint128_t u128_mul64(uint64_t a, uint64_t b) {
    uint128_t r;
    r.hi = __umulh(a, b);
    r.lo = a * b;
    return r;
}

#else

// Portable fallback: 64×64 → 128 using 32-bit multiplies
inline uint128_t u128_mul64(uint64_t a, uint64_t b) {
    uint32_t a_lo = (uint32_t)a, a_hi = (uint32_t)(a >> 32);
    uint32_t b_lo = (uint32_t)b, b_hi = (uint32_t)(b >> 32);

    uint64_t ll = (uint64_t)a_lo * b_lo;
    uint64_t lh = (uint64_t)a_lo * b_hi;
    uint64_t hl = (uint64_t)a_hi * b_lo;
    uint64_t hh = (uint64_t)a_hi * b_hi;

    uint64_t mid  = lh + (ll >> 32);
    uint64_t mid2 = (uint64_t)(uint32_t)mid + hl;

    uint128_t r;
    r.lo = ((uint64_t)(uint32_t)mid2 << 32) | (uint32_t)ll;
    r.hi = hh + (mid >> 32) + (mid2 >> 32);
    return r;
}

#endif


inline uint128_t operator*(uint128_t a, uint64_t b) {
    uint128_t r = u128_mul64(a.lo, b);
    r.hi += a.hi * b;
    return r;
}

inline uint128_t operator*(uint64_t a, uint128_t b) {
    uint128_t r = u128_mul64(a, b.lo);
    r.hi += b.hi * a;
    return r;
}


// ============================================================================
//  Left-shift operator
// ============================================================================
inline constexpr uint128_t operator<<(const uint128_t& v, unsigned shift) {
    if (shift == 0)    return v;
    if (shift < 64)    return uint128_t((v.hi << shift) | (v.lo >> (64 - shift)), v.lo << shift);
    if (shift == 64)   return uint128_t(v.lo, 0ull);
    if (shift < 128)   return uint128_t(v.lo << (shift - 64), 0ull);
    return uint128_t(0ull, 0ull);
}

// ============================================================================
//  Right-shift operator: return 64-bit high part when >> 64
// ============================================================================
inline uint64_t operator>>(const uint128_t& v, unsigned shift) {
    if (shift == 0)     return v.lo;
    if (shift < 64)     return (v.lo >> shift) | (v.hi << (64 - shift));
    if (shift == 64)    return v.hi;
    if (shift < 128)    return v.hi >> (shift - 64);
    return 0;
}

// ============================================================================
//  Division by a 32-bit divisor (128-bit long division via 64-bit steps)
// ============================================================================
inline constexpr uint128_t operator/(const uint128_t& v, uint32_t d) {
    uint64_t q3 = (v.hi >> 32) / d;
    uint64_t r  = (v.hi >> 32) % d;
    uint64_t t  = (r << 32) | (v.hi & 0xFFFFFFFFu);
    uint64_t q2 = t / d; r = t % d;
             t  = (r << 32) | (v.lo >> 32);
    uint64_t q1 = t / d; r = t % d;
             t  = (r << 32) | (v.lo & 0xFFFFFFFFu);
    uint64_t q0 = t / d;
    return uint128_t((q3 << 32) | q2, (q1 << 32) | q0);
}

// ============================================================================
//  Addition with a 64-bit value
// ============================================================================
inline constexpr uint128_t operator+(const uint128_t& a, uint64_t b) {
    uint64_t lo = a.lo + b;
    uint64_t hi = a.hi + (lo < a.lo ? 1ull : 0ull);
    return uint128_t(hi, lo);
}

inline uint64_t lo128(const uint128_t& v) { return v.lo; }
inline uint64_t hi128(const uint128_t& v) { return v.hi; }


#endif // __SIZEOF_INT128__