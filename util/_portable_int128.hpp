#pragma once
#include <cstdint>

// This is a minimal wrapper enabling __int128_t-style behaviour on
// compilers that do not have it, eg. MSVC and on some 32-bit targets.

// ============================================================================
//  CASE 1: GCC / Clang / LLVM with native __int128
// ============================================================================
#if defined(__SIZEOF_INT128__)

using int128_t = __int128_t;

// No operator overloads here — GCC/Clang already support them natively.

inline int64_t lo128(int128_t v) { return (int64_t)v; }
inline int64_t hi128(int128_t v) { return (int64_t)(v >> 64); }

#else


// ============================================================================
//  CASE 2: MSVC / 32-bit targets without native __int128 (e.g. armv6) —
//  implement int128_t manually
// ============================================================================
struct int128_t {
    uint64_t lo;
    int64_t  hi;

    int128_t() = default;
    constexpr int128_t(int64_t v) : lo((uint64_t)v), hi(v >> 63) {}
    constexpr int128_t(int64_t hi_, uint64_t lo_) : lo(lo_), hi(hi_) {}

    // Conversions are explicit: with four candidate widths, an implicit
    // conversion operator makes every comparison/arithmetic use ambiguous
    // (the compiler has no reason to prefer one width over another).
    explicit operator int64_t()  const { return (int64_t)lo; }
    explicit operator int32_t()  const { return (int32_t)lo; }
    explicit operator uint64_t() const { return lo; }
    explicit operator uint32_t() const { return (uint32_t)lo; }
    explicit operator double()   const {
        return (double)hi * 18446744073709551616.0 /* 2^64 */ + (double)lo;
    }
    explicit operator bool() const { return lo != 0 || hi != 0; }
};

inline int128_t operator-(const int128_t& v) {
    uint64_t lo = ~v.lo + 1;
    int64_t  hi = ~v.hi + (lo == 0 ? 1 : 0);
    return int128_t(hi, lo);
}

inline int128_t operator+(const int128_t& a, const int128_t& b) {
    uint64_t lo = a.lo + b.lo;
    int64_t  hi = a.hi + b.hi + (lo < a.lo ? 1 : 0);
    return int128_t(hi, lo);
}

inline int128_t operator-(const int128_t& a, const int128_t& b) {
    return a + (-b);
}

inline int128_t& operator+=(int128_t& a, const int128_t& b) {
    a = a + b;
    return a;
}

inline bool operator==(const int128_t& a, const int128_t& b) {
    return a.hi == b.hi && a.lo == b.lo;
}
inline bool operator!=(const int128_t& a, const int128_t& b) { return !(a == b); }
inline bool operator<(const int128_t& a, const int128_t& b) {
    return a.hi != b.hi ? a.hi < b.hi : a.lo < b.lo;
}
inline bool operator>(const int128_t& a, const int128_t& b)  { return b < a; }
inline bool operator<=(const int128_t& a, const int128_t& b) { return !(b < a); }
inline bool operator>=(const int128_t& a, const int128_t& b) { return !(a < b); }

// Left-shift (used to build magnitudes like `(int128_t)1 << 32`).
inline int128_t operator<<(const int128_t& v, int shift) {
    if (shift <= 0)  return v;
    uint64_t hi_u = (uint64_t)v.hi;
    if (shift < 64)  return int128_t((int64_t)((hi_u << shift) | (v.lo >> (64 - shift))), v.lo << shift);
    if (shift < 128) return int128_t((int64_t)(v.lo << (shift - 64)), 0ull);
    return int128_t(0, 0ull);
}

// Division by a small (32-bit magnitude) divisor — long division via
// 32-bit steps, same technique as _portable_uint128.hpp's operator/,
// with sign handled by working on magnitudes.
inline int128_t operator/(const int128_t& v, int32_t d) {
    const bool neg_v = v.hi < 0;
    const bool neg_d = d < 0;

    uint64_t lo = v.lo, hi = (uint64_t)v.hi;
    if (neg_v) { lo = ~lo + 1; hi = ~hi + (lo == 0 ? 1 : 0); }
    const uint32_t ud = neg_d ? (uint32_t)(-(int64_t)d) : (uint32_t)d;

    uint64_t q3 = (hi >> 32) / ud;
    uint64_t r  = (hi >> 32) % ud;
    uint64_t t  = (r << 32) | (hi & 0xFFFFFFFFu);
    uint64_t q2 = t / ud; r = t % ud;
             t  = (r << 32) | (lo >> 32);
    uint64_t q1 = t / ud; r = t % ud;
             t  = (r << 32) | (lo & 0xFFFFFFFFu);
    uint64_t q0 = t / ud;

    uint64_t r_lo = (q1 << 32) | q0;
    uint64_t r_hi = (q3 << 32) | q2;
    if (neg_v != neg_d) { r_lo = ~r_lo + 1; r_hi = ~r_hi + (r_lo == 0 ? 1 : 0); }
    return int128_t((int64_t)r_hi, r_lo);
}


// ============================================================================
//  Backend for signed 64×64 → 128 multiply
// ============================================================================
#if defined(_MSC_VER) && defined(_M_X64)

#include <intrin.h>

inline int128_t s128_mul64(int64_t a, int64_t b) {
    int128_t r;
    r.lo = _mul128(a, b, &r.hi);
    return r;
}

#elif defined(_MSC_VER) && defined(_M_ARM64)

#include <intrin.h>

inline int128_t s128_mul64(int64_t a, int64_t b) {
    int128_t r;
    r.hi = __mulh(a, b);
    r.lo = (uint64_t)((uint64_t)a * (uint64_t)b);
    return r;
}

#else

// Portable fallback: signed 64×64 → 128 using 32-bit multiplies
inline int128_t s128_mul64(int64_t a, int64_t b) {
    // Compute unsigned abs(a) * abs(b), then fix sign
    int neg = (a < 0) != (b < 0);
    uint64_t ua = a < 0 ? (uint64_t)(-(uint64_t)a) : (uint64_t)a;
    uint64_t ub = b < 0 ? (uint64_t)(-(uint64_t)b) : (uint64_t)b;

    uint32_t a_lo = (uint32_t)ua, a_hi = (uint32_t)(ua >> 32);
    uint32_t b_lo = (uint32_t)ub, b_hi = (uint32_t)(ub >> 32);

    uint64_t ll = (uint64_t)a_lo * b_lo;
    uint64_t lh = (uint64_t)a_lo * b_hi;
    uint64_t hl = (uint64_t)a_hi * b_lo;
    uint64_t hh = (uint64_t)a_hi * b_hi;

    uint64_t mid  = lh + (ll >> 32);
    uint64_t mid2 = (uint64_t)(uint32_t)mid + hl;

    uint64_t r_lo = ((uint64_t)(uint32_t)mid2 << 32) | (uint32_t)ll;
    uint64_t r_hi = hh + (mid >> 32) + (mid2 >> 32);

    if (neg) {
        r_lo = ~r_lo + 1;
        r_hi = ~r_hi + (r_lo == 0 ? 1 : 0);
    }

    int128_t r;
    r.lo = r_lo;
    r.hi = (int64_t)r_hi;
    return r;
}

#endif


inline int128_t operator*(int128_t a, int64_t b) {
    return s128_mul64((int64_t)a.lo, b);
}

inline int128_t operator*(int64_t a, int128_t b) {
    return s128_mul64(a, (int64_t)b.lo);
}

inline int128_t operator>>(const int128_t& v, int shift) {
    if (shift == 0)  return v;
    uint64_t hi = (uint64_t)v.hi;
    if (shift < 64)  return int128_t((int64_t)(hi >> shift), (v.lo >> shift) | (hi << (64 - shift)));
    if (shift == 64) return int128_t(0, hi);
    if (shift < 128) return int128_t(0, hi >> (shift - 64));
    return int128_t(0, 0);
}

inline uint64_t lo128(const int128_t& v) { return v.lo; }
inline uint64_t hi128(const int128_t& v) { return (uint64_t)v.hi; }


#endif // __SIZEOF_INT128__
