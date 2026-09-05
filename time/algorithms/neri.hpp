#pragma once
#include "time/_common.hpp"

// Reimplementation of Cassio Neri's time-of-day algorithm:
// https://github.com/cassioneri/calendar/blob/995f9b0b6badf4aec851f4e72cf57dde01f28287/benchmarks/to_time.cpp#L33

// Accurate from 0 to 97612918 (27114:41:58)
inline TIME_S time_neri(uint32_t t) {
    
    uint64_t prd  = 71582789ll * t;
    uint32_t mins = prd >> 32;              // secs / 60
    uint32_t ss = uint32_t(prd) / 71582789; // secs % 60
  
    uint64_t prd2 = 71582789ll * mins;
    uint32_t hh = prd2 >> 32;                // mins / 60
    uint32_t mm = uint32_t(prd2) / 71582789; // mins % 60
  
    return { hh, mm, ss };
}

// Accurate from 0 to 97612918 (27114:41:58)
inline TIME_S time_neri_fp(uint32_t t) {
    
    uint64_t prd  = 71582789ll * t;
    uint32_t mins = prd >> 32;              // secs / 60
    uint32_t ss = (uint64_t) uint32_t(prd) * 4026531799 >> 58; // secs % 60
  
    uint64_t prd2 = 71582789ll * mins;
    uint32_t hh = prd2 >> 32;                // mins / 60
    uint32_t mm = (uint64_t) uint32_t(prd2) * 4026531799 >> 58; // mins % 60
  
    return { hh, mm, ss };
}