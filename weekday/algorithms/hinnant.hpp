#pragma once
#include <stdint.h>

// Reimplementation of Howard Hinnant's weekday algorithm:
// https://howardhinnant.github.io/date_algorithms.html#weekday_from_days

inline uint32_t weekday_hinnant32(int32_t d) {
    return d >= -4 ? (d + 4) % 7 : (d + 5) % 7 + 6;
}
