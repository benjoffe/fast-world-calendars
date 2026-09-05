#pragma once
#include <stdint.h>
#include <ostream>
#include <iomanip>

struct TIME_S {
    uint32_t hour, min, sec;
};

struct TIME_SUBUNIT {
    uint32_t hour, min, sec, sub;
};

inline bool operator==(const TIME_S& a, const TIME_S& b) {
    return a.hour == b.hour && a.min == b.min && a.sec == b.sec;
}
inline bool operator==(const TIME_SUBUNIT& a, const TIME_SUBUNIT& b) {
    return a.hour == b.hour && a.min == b.min && a.sec == b.sec && a.sub == b.sub;
}

inline std::ostream& operator<<(std::ostream& os, const TIME_S& t) {
    auto flags = os.flags();
    auto fill = os.fill();
    os << std::setfill('0')
       << std::setw(2) << t.hour << ":"
       << std::setw(2) << t.min << ":"
       << std::setw(2) << t.sec;
    os.flags(flags);
    os.fill(fill);
    return os;
}
inline std::ostream& operator<<(std::ostream& os, const TIME_SUBUNIT& t) {
    auto flags = os.flags();
    auto fill = os.fill();
    os << std::setfill('0')
       << std::setw(2) << t.hour << ":"
       << std::setw(2) << t.min << ":"
       << std::setw(2) << t.sec << "."
       << std::left << std::setw(9) << t.sub;
    os.flags(flags);
    os.fill(fill);
    return os;
}
