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


// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd POS_MOD 7
// Range: Full signed 8-bit (-128..127)
// Output: [0..6]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=8
inline uint8_t get_weekday_8(int8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 3;
    const uint8_t a = uint8_t(rd) * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) POS_MOD 7
// Range: Full signed 8-bit (-128..127)
// Output: [0..6]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=8e1
inline uint8_t get_weekday_8e1(int8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 39;
    const uint8_t a = uint8_t(rd) * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) POS_MOD 7
// Range: Full signed 8-bit (-128..127)
// Output: [0..6]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=8e2
inline uint8_t get_weekday_8e2(int8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 76;
    const uint8_t a = uint8_t(rd) * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) POS_MOD 7
// Range: Full signed 8-bit (-128..127)
// Output: [0..6]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=8e3
inline uint8_t get_weekday_8e3(int8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 113;
    const uint8_t a = uint8_t(rd) * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 4
// Compute: Day of week: (rd + 4) POS_MOD 7
// Range: Full signed 8-bit (-128..127)
// Output: [0..6]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=8unix
inline uint8_t get_weekday_8unix(int8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 149;
    const uint8_t a = uint8_t(rd) * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) POS_MOD 7
// Range: Full signed 8-bit (-128..127)
// Output: [0..6]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=8e5
inline uint8_t get_weekday_8e5(int8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 186;
    const uint8_t a = uint8_t(rd) * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) POS_MOD 7
// Range: Full signed 8-bit (-128..127)
// Output: [0..6]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=8e6
inline uint8_t get_weekday_8e6(int8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 222;
    const uint8_t a = uint8_t(rd) * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd MOD 7
// Range: Full unsigned 8-bit (0..255)
// Output: [0..6]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u8
inline uint8_t get_weekday_u8(uint8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 3;
    const uint8_t a = rd * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) MOD 7
// Range: Full unsigned 8-bit (0..255)
// Output: [0..6]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u8e1
inline uint8_t get_weekday_u8e1(uint8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 40;
    const uint8_t a = rd * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) MOD 7
// Range: Full unsigned 8-bit (0..255)
// Output: [0..6]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u8e2
inline uint8_t get_weekday_u8e2(uint8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 76;
    const uint8_t a = rd * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) MOD 7
// Range: Full unsigned 8-bit (0..255)
// Output: [0..6]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u8e3
inline uint8_t get_weekday_u8e3(uint8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 113;
    const uint8_t a = rd * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 4
// Compute: Day of week: (rd + 4) MOD 7
// Range: Full unsigned 8-bit (0..255)
// Output: [0..6]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u8unix
inline uint8_t get_weekday_u8unix(uint8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 150;
    const uint8_t a = rd * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) MOD 7
// Range: Full unsigned 8-bit (0..255)
// Output: [0..6]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u8e5
inline uint8_t get_weekday_u8e5(uint8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 186;
    const uint8_t a = rd * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) MOD 7
// Range: Full unsigned 8-bit (0..255)
// Output: [0..6]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u8e6
inline uint8_t get_weekday_u8e6(uint8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 223;
    const uint8_t a = rd * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) POS_MOD 7) + 1
// Range: Full signed 8-bit (-128..127)
// Output: [1..7]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=8iso7
inline uint8_t get_weekday_8iso7(int8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 254;
    const uint8_t a = uint8_t(rd) * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd POS_MOD 7) + 1
// Range: Full signed 8-bit (-128..127)
// Output: [1..7]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=8iso1
inline uint8_t get_weekday_8iso1(int8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 35;
    const uint8_t a = uint8_t(rd) * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) POS_MOD 7) + 1
// Range: Full signed 8-bit (-128..127)
// Output: [1..7]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=8iso2
inline uint8_t get_weekday_8iso2(int8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 71;
    const uint8_t a = uint8_t(rd) * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) POS_MOD 7) + 1
// Range: Full signed 8-bit (-128..127)
// Output: [1..7]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=8iso3
inline uint8_t get_weekday_8iso3(int8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 108;
    const uint8_t a = uint8_t(rd) * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 4
// Compute: Day of week: ((rd + 3) POS_MOD 7) + 1
// Range: Full signed 8-bit (-128..127)
// Output: [1..7]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=8iso
inline uint8_t get_weekday_8iso(int8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 145;
    const uint8_t a = uint8_t(rd) * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) POS_MOD 7) + 1
// Range: Full signed 8-bit (-128..127)
// Output: [1..7]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=8iso5
inline uint8_t get_weekday_8iso5(int8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 181;
    const uint8_t a = uint8_t(rd) * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) POS_MOD 7) + 1
// Range: Full signed 8-bit (-128..127)
// Output: [1..7]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=8iso6
inline uint8_t get_weekday_8iso6(int8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 218;
    const uint8_t a = uint8_t(rd) * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) MOD 7) + 1
// Range: Full unsigned 8-bit (0..255)
// Output: [1..7]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u8iso7
inline uint8_t get_weekday_u8iso7(uint8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 255;
    const uint8_t a = rd * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd MOD 7) + 1
// Range: Full unsigned 8-bit (0..255)
// Output: [1..7]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u8iso1
inline uint8_t get_weekday_u8iso1(uint8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 35;
    const uint8_t a = rd * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) MOD 7) + 1
// Range: Full unsigned 8-bit (0..255)
// Output: [1..7]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u8iso2
inline uint8_t get_weekday_u8iso2(uint8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 72;
    const uint8_t a = rd * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) MOD 7) + 1
// Range: Full unsigned 8-bit (0..255)
// Output: [1..7]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u8iso3
inline uint8_t get_weekday_u8iso3(uint8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 108;
    const uint8_t a = rd * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 4
// Compute: Day of week: ((rd + 3) MOD 7) + 1
// Range: Full unsigned 8-bit (0..255)
// Output: [1..7]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u8iso
inline uint8_t get_weekday_u8iso(uint8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 145;
    const uint8_t a = rd * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) MOD 7) + 1
// Range: Full unsigned 8-bit (0..255)
// Output: [1..7]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u8iso5
inline uint8_t get_weekday_u8iso5(uint8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 182;
    const uint8_t a = rd * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) MOD 7) + 1
// Range: Full unsigned 8-bit (0..255)
// Output: [1..7]
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u8iso6
inline uint8_t get_weekday_u8iso6(uint8_t rd) {
    const uint8_t M = 256 / 7;  // 36
    const uint8_t Z = 218;
    const uint8_t a = rd * M + Z;
    const uint8_t b = (rd >> 1) + (rd >> 4);
    return uint8_t(a + b) >> 5; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd POS_MOD 7
// Range: Full signed 16-bit
// Output: [0..6]
// Years: -89.7 → 89.7
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=16
inline uint8_t get_weekday_16(int16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0x0200;     // 512
    const uint16_t a = uint16_t(rd) * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) POS_MOD 7
// Range: Full signed 16-bit
// Output: [0..6]
// Years: -89.7 → 89.7
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=16e1
inline uint8_t get_weekday_16e1(int16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0x2800;     // 10240
    const uint16_t a = uint16_t(rd) * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) POS_MOD 7
// Range: Full signed 16-bit
// Output: [0..6]
// Years: -89.7 → 89.7
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=16e2
inline uint8_t get_weekday_16e2(int16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0x4C00;     // 19456
    const uint16_t a = uint16_t(rd) * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) POS_MOD 7
// Range: Full signed 16-bit
// Output: [0..6]
// Years: -89.7 → 89.7
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=16e3
inline uint8_t get_weekday_16e3(int16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0x7000;     // 28672
    const uint16_t a = uint16_t(rd) * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: (rd + 4) POS_MOD 7
// Range: Full signed 16-bit
// Output: [0..6]
// Min Date: 1,880-04-14 (Wed: 3)
// Max Date:  2,059-09-18 (Thu: 4)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=16unix
inline uint8_t get_weekday_16unix(int16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0x9400;     // 37888
    const uint16_t a = uint16_t(rd) * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) POS_MOD 7
// Range: Full signed 16-bit
// Output: [0..6]
// Years: -89.7 → 89.7
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=16e5
inline uint8_t get_weekday_16e5(int16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0xBA00;     // 47616
    const uint16_t a = uint16_t(rd) * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) POS_MOD 7
// Range: Full signed 16-bit
// Output: [0..6]
// Years: -89.7 → 89.7
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=16e6
inline uint8_t get_weekday_16e6(int16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0xDE00;     // 56832
    const uint16_t a = uint16_t(rd) * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd MOD 7
// Range: Full unsigned 16-bit
// Output: [0..6]
// Years: 179.4
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u16
inline uint8_t get_weekday_u16(uint16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0x0200;     // 512
    const uint16_t a = rd * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) MOD 7
// Range: Full unsigned 16-bit
// Output: [0..6]
// Years: 179.4
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u16e1
inline uint8_t get_weekday_u16e1(uint16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0x2800;     // 10240
    const uint16_t a = rd * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) MOD 7
// Range: Full unsigned 16-bit
// Output: [0..6]
// Years: 179.4
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u16e2
inline uint8_t get_weekday_u16e2(uint16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0x4C00;     // 19456
    const uint16_t a = rd * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) MOD 7
// Range: Full unsigned 16-bit
// Output: [0..6]
// Years: 179.4
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u16e3
inline uint8_t get_weekday_u16e3(uint16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0x7000;     // 28672
    const uint16_t a = rd * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: (rd + 4) MOD 7
// Range: Full unsigned 16-bit
// Output: [0..6]
// Min Date: 1,970-01-01 (Thu: 4)
// Max Date: 2,149-06-06 (Fri: 5)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u16unix
inline uint8_t get_weekday_u16unix(uint16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0x9400;     // 37888
    const uint16_t a = rd * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) MOD 7
// Range: Full unsigned 16-bit
// Output: [0..6]
// Years: 179.4
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u16e5
inline uint8_t get_weekday_u16e5(uint16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0xBA00;     // 47616
    const uint16_t a = rd * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) MOD 7
// Range: Full unsigned 16-bit
// Output: [0..6]
// Years: 179.4
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u16e6
inline uint8_t get_weekday_u16e6(uint16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0xDE00;     // 56832
    const uint16_t a = rd * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) POS_MOD 7) + 1
// Range: Full signed 16-bit
// Output: [1..7]
// Years: -89.7 → 89.7
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=16iso7
inline uint8_t get_weekday_16iso7(int16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0xFF00;     // 65280
    const uint16_t a = uint16_t(rd) * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd POS_MOD 7) + 1
// Range: Full signed 16-bit
// Output: [1..7]
// Years: -89.7 → 89.7
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=16iso1
inline uint8_t get_weekday_16iso1(int16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0x2200;     // 8704
    const uint16_t a = uint16_t(rd) * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) POS_MOD 7) + 1
// Range: Full signed 16-bit
// Output: [1..7]
// Years: -89.7 → 89.7
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=16iso2
inline uint8_t get_weekday_16iso2(int16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0x4800;     // 18432
    const uint16_t a = uint16_t(rd) * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) POS_MOD 7) + 1
// Range: Full signed 16-bit
// Output: [1..7]
// Years: -89.7 → 89.7
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=16iso3
inline uint8_t get_weekday_16iso3(int16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0x6C00;     // 27648
    const uint16_t a = uint16_t(rd) * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: ((rd + 3) POS_MOD 7) + 1
// Range: Full signed 16-bit
// Output: [1..7]
// Min Date: 1,880-04-14 (Wed: 3)
// Max Date:  2,059-09-18 (Thu: 4)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=16iso
inline uint8_t get_weekday_16iso(int16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0x9000;     // 36864
    const uint16_t a = uint16_t(rd) * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) POS_MOD 7) + 1
// Range: Full signed 16-bit
// Output: [1..7]
// Years: -89.7 → 89.7
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=16iso5
inline uint8_t get_weekday_16iso5(int16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0xB400;     // 46080
    const uint16_t a = uint16_t(rd) * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) POS_MOD 7) + 1
// Range: Full signed 16-bit
// Output: [1..7]
// Years: -89.7 → 89.7
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=16iso6
inline uint8_t get_weekday_16iso6(int16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0xDA00;     // 55808
    const uint16_t a = uint16_t(rd) * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) MOD 7) + 1
// Range: Full unsigned 16-bit
// Output: [1..7]
// Years: 179.4
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u16iso7
inline uint8_t get_weekday_u16iso7(uint16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0xFF00;     // 65280
    const uint16_t a = rd * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd MOD 7) + 1
// Range: Full unsigned 16-bit
// Output: [1..7]
// Years: 179.4
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u16iso1
inline uint8_t get_weekday_u16iso1(uint16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0x2200;     // 8704
    const uint16_t a = rd * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) MOD 7) + 1
// Range: Full unsigned 16-bit
// Output: [1..7]
// Years: 179.4
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u16iso2
inline uint8_t get_weekday_u16iso2(uint16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0x4800;     // 18432
    const uint16_t a = rd * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) MOD 7) + 1
// Range: Full unsigned 16-bit
// Output: [1..7]
// Years: 179.4
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u16iso3
inline uint8_t get_weekday_u16iso3(uint16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0x6C00;     // 27648
    const uint16_t a = rd * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: ((rd + 3) MOD 7) + 1
// Range: Full unsigned 16-bit
// Output: [1..7]
// Min Date: 1,970-01-01 (Thu: 4)
// Max Date: 2,149-06-06 (Fri: 5)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u16iso
inline uint8_t get_weekday_u16iso(uint16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0x9000;     // 36864
    const uint16_t a = rd * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) MOD 7) + 1
// Range: Full unsigned 16-bit
// Output: [1..7]
// Years: 179.4
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u16iso5
inline uint8_t get_weekday_u16iso5(uint16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0xB400;     // 46080
    const uint16_t a = rd * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) MOD 7) + 1
// Range: Full unsigned 16-bit
// Output: [1..7]
// Years: 179.4
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u16iso6
inline uint8_t get_weekday_u16iso6(uint16_t rd) {
    const uint16_t M = 65536 / 7;  // 9362
    const uint16_t Z = 0xDA00;     // 55808
    const uint16_t a = rd * M + Z;
    const uint16_t b = (rd >> 2) + (rd >> 5);
    return uint16_t(a + b) >> 13; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd POS_MOD 7
// Input: -89,456,646 to 89,500,332
// Output: [0..6]
// Years: -244,924 → 245,043.6
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32_narrow
inline uint8_t get_weekday_32_narrow(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0x02490000;        // 38,338,560
    const uint32_t a = uint32_t(rd) * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) POS_MOD 7
// Input: -89,412,953 to 89,544,025
// Output: [0..6]
// Years: -244,804.4 → 245,163.2
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e1_narrow
inline uint8_t get_weekday_32e1_narrow(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0x26DB0000;        // 651,886,592
    const uint32_t a = uint32_t(rd) * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) POS_MOD 7
// Input: -89,522,182 to 89,434,796
// Output: [0..6]
// Years: -245,103.4 → 244,864.2
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e2_narrow
inline uint8_t get_weekday_32e2_narrow(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0x4B6E0000;        // 1,265,500,160
    const uint32_t a = uint32_t(rd) * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) POS_MOD 7
// Input: -89,478,489 to 89,478,489
// Output: [0..6]
// Years: -244,983.8 → 244,983.8
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e3_narrow
inline uint8_t get_weekday_32e3_narrow(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0x70000000;        // 1,879,048,192
    const uint32_t a = uint32_t(rd) * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: (rd + 4) POS_MOD 7
// Input: -89,434,796 to 89,522,175
// Output: [0..6]
// Min Date: -242,895-11-06 (Mon: 1)
// Max Date:  247,073-05-23 (Fri: 5)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32unix_narrow
inline uint8_t get_weekday_32unix_narrow(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0x94920000;        // 2,492,596,224
    const uint32_t a = uint32_t(rd) * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) POS_MOD 7
// Input: -89,544,025 to 89,412,953
// Output: [0..6]
// Years: -245,163.2 → 244,804.4
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e5_narrow
inline uint8_t get_weekday_32e5_narrow(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0xB9250000;        // 3,106,209,792
    const uint32_t a = uint32_t(rd) * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) POS_MOD 7
// Input: -89,500,332 to 89,456,639
// Output: [0..6]
// Years: -245,043.6 → 244,924
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e6_narrow
inline uint8_t get_weekday_32e6_narrow(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0xDDB70000;        // 3,719,757,824
    const uint32_t a = uint32_t(rd) * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd MOD 7
// Input: 0 to 178,956,972
// Output: [0..6]
// Years: 489,967.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32_narrow
inline uint8_t get_weekday_u32_narrow(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    return (rd * M) >> 29;  // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) MOD 7
// Input: 0 to 178,956,978
// Output: [0..6]
// Years: 489,967.6
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e1_narrow
inline uint8_t get_weekday_u32e1_narrow(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    return ((rd - 6) * M) >> 29;  // top 3 bits, subtraction intentional
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) MOD 7
// Input: 0 to 178,956,977
// Output: [0..6]
// Years: 489,967.6
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e2_narrow
inline uint8_t get_weekday_u32e2_narrow(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    return ((rd - 5) * M) >> 29;  // top 3 bits, subtraction intentional
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) MOD 7
// Input: 0 to 178,956,976
// Output: [0..6]
// Years: 489,967.6
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e3_narrow
inline uint8_t get_weekday_u32e3_narrow(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    return ((rd - 4) * M) >> 29;  // top 3 bits, subtraction intentional
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: (rd + 4) MOD 7
// Input: 0 to 178,956,975
// Output: [0..6]
// Min Date: 1,970-01-01 (Thu: 4)
// Max Date: 491,937-07-23 (Fri: 5)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32unix_narrow
inline uint8_t get_weekday_u32unix_narrow(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    return ((rd - 3) * M) >> 29;  // top 3 bits, subtraction intentional
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) MOD 7
// Input: 0 to 178,956,974
// Output: [0..6]
// Years: 489,967.6
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e5_narrow
inline uint8_t get_weekday_u32e5_narrow(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    return ((rd - 2) * M) >> 29;  // top 3 bits, subtraction intentional
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) MOD 7
// Input: 0 to 178,956,973
// Output: [0..6]
// Years: 489,967.6
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e6_narrow
inline uint8_t get_weekday_u32e6_narrow(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    return ((rd - 1) * M) >> 29;  // top 3 bits, subtraction intentional
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) POS_MOD 7) + 1
// Input: -89,500,332 to 89,456,639
// Output: [1..7]
// Years: -245,043.6 → 244,924
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso7_narrow
inline uint8_t get_weekday_32iso7_narrow(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0xFDB70000;        // 4,256,628,736
    const uint32_t a = uint32_t(rd) * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd POS_MOD 7) + 1
// Input: -89,456,646 to 89,500,332
// Output: [1..7]
// Years: -244,924 → 245,043.6
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso1_narrow
inline uint8_t get_weekday_32iso1_narrow(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0x22490000;        // 575,209,472
    const uint32_t a = uint32_t(rd) * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) POS_MOD 7) + 1
// Input: -89,412,953 to 89,544,025
// Output: [1..7]
// Years: -244,804.4 → 245,163.2
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso2_narrow
inline uint8_t get_weekday_32iso2_narrow(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0x46DB0000;        // 1,188,757,504
    const uint32_t a = uint32_t(rd) * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) POS_MOD 7) + 1
// Input: -89,522,182 to 89,434,796
// Output: [1..7]
// Years: -245,103.4 → 244,864.2
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso3_narrow
inline uint8_t get_weekday_32iso3_narrow(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0x6B6E0000;        // 1,802,371,072
    const uint32_t a = uint32_t(rd) * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: ((rd + 3) POS_MOD 7) + 1
// Input: -89,478,489 to 89,478,489
// Output: [1..7]
// Min Date: -243,014-03-21 (Tue: 2)
// Max Date:  246,953-10-13 (Sat: 6)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso_narrow
inline uint8_t get_weekday_32iso_narrow(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0x90000000;        // 2,415,919,104
    const uint32_t a = uint32_t(rd) * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) POS_MOD 7) + 1
// Input: -89,434,796 to 89,522,175
// Output: [1..7]
// Years: -244,864.2 → 245,103.4
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso5_narrow
inline uint8_t get_weekday_32iso5_narrow(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0xB4920000;        // 3,029,467,136
    const uint32_t a = uint32_t(rd) * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) POS_MOD 7) + 1
// Input: -89,544,025 to 89,412,953
// Output: [1..7]
// Years: -245,163.2 → 244,804.4
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso6_narrow
inline uint8_t get_weekday_32iso6_narrow(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0xD9250000;        // 3,643,080,704
    const uint32_t a = uint32_t(rd) * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) MOD 7) + 1
// Input: 0 to 178,913,279
// Output: [1..7]
// Years: 489,847.9
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso7_narrow
inline uint8_t get_weekday_u32iso7_narrow(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0xFB6E0000;        // 4,218,290,176
    const uint32_t a = rd * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd MOD 7) + 1
// Input: 0 to 178,956,972
// Output: [1..7]
// Years: 489,967.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso1_narrow
inline uint8_t get_weekday_u32iso1_narrow(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0x20000000;        // 536,870,912
    const uint32_t a = rd * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) MOD 7) + 1
// Input: 0 to 178,847,743
// Output: [1..7]
// Years: 489,668.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso2_narrow
inline uint8_t get_weekday_u32iso2_narrow(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0x44930000;        // 1,150,484,480
    const uint32_t a = rd * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) MOD 7) + 1
// Input: 0 to 178,891,436
// Output: [1..7]
// Years: 489,788.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso3_narrow
inline uint8_t get_weekday_u32iso3_narrow(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0x69250000;        // 1,764,032,512
    const uint32_t a = rd * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: ((rd + 3) MOD 7) + 1
// Input: 0 to 178,935,129
// Output: [1..7]
// Min Date: 1,970-01-01 (Thu: 4)
// Max Date: 491,877-09-29 (Sat: 6)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso_narrow
inline uint8_t get_weekday_u32iso_narrow(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0x8DB70000;        // 2,377,580,544
    const uint32_t a = rd * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) MOD 7) + 1
// Input: 0 to 178,825,900
// Output: [1..7]
// Years: 489,608.7
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso5_narrow
inline uint8_t get_weekday_u32iso5_narrow(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0xB24A0000;        // 2,991,194,112
    const uint32_t a = rd * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) MOD 7) + 1
// Input: 0 to 178,869,593
// Output: [1..7]
// Years: 489,728.3
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso6_narrow
inline uint8_t get_weekday_u32iso6_narrow(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t Z = 0xD6DC0000;        // 3,604,742,144
    const uint32_t a = rd * M + Z;
    return a >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd POS_MOD 7
// Input: -537,001,983 to 536,739,846
// Output: [0..6]
// Years: -1,470,261.5 → 1,469,543.8
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32_medium
inline uint8_t get_weekday_32_medium(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x02490000;        // 38,338,560
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) POS_MOD 7
// Input: -537,264,127 to 536,477,702
// Output: [0..6]
// Years: -1,470,979.2 → 1,468,826.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e1_medium
inline uint8_t get_weekday_32e1_medium(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x26DB0000;        // 651,886,592
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) POS_MOD 7
// Input: -536,608,767 to 537,133,062
// Output: [0..6]
// Years: -1,469,184.9 → 1,470,620.4
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e2_medium
inline uint8_t get_weekday_32e2_medium(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x4B6E0000;        // 1,265,500,160
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) POS_MOD 7
// Input: -536,870,911 to 536,870,918
// Output: [0..6]
// Years: -1,469,902.6 → 1,469,902.6
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e3_medium
inline uint8_t get_weekday_32e3_medium(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x70000000;        // 1,879,048,192
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: (rd + 4) POS_MOD 7
// Input: -537,133,055 to 536,608,774
// Output: [0..6]
// Min Date: -1,468,651-08-24 (Sun: 0)
// Max Date:  1,471,154-12-04 (Sat: 6)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32unix_medium
inline uint8_t get_weekday_32unix_medium(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x94920000;        // 2,492,596,224
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) POS_MOD 7
// Input: -536,477,695 to 537,264,134
// Output: [0..6]
// Years: -1,468,826 → 1,470,979.2
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e5_medium
inline uint8_t get_weekday_32e5_medium(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xB9250000;        // 3,106,209,792
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) POS_MOD 7
// Input: -536,739,839 to 537,001,990
// Output: [0..6]
// Years: -1,469,543.8 → 1,470,261.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e6_medium
inline uint8_t get_weekday_32e6_medium(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xDDB70000;        // 3,719,757,824
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd MOD 7
// Input: 0 to 1,073,479,686
// Output: [0..6]
// Years: 2,939,087.6
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32_medium
inline uint8_t get_weekday_u32_medium(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x04920000;        // 76,677,120
    const uint32_t a = rd * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) MOD 7
// Input: 0 to 1,073,217,542
// Output: [0..6]
// Years: 2,938,369.8
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e1_medium
inline uint8_t get_weekday_u32e1_medium(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x29240000;        // 690,225,152
    const uint32_t a = rd * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) MOD 7
// Input: 0 to 1,072,955,398
// Output: [0..6]
// Years: 2,937,652.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e2_medium
inline uint8_t get_weekday_u32e2_medium(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x4DB60000;        // 1,303,773,184
    const uint32_t a = rd * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) MOD 7
// Input: 0 to 1,073,610,758
// Output: [0..6]
// Years: 2,939,446.4
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e3_medium
inline uint8_t get_weekday_u32e3_medium(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x72490000;        // 1,917,386,752
    const uint32_t a = rd * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: (rd + 4) MOD 7
// Input: 0 to 1,073,348,614
// Output: [0..6]
// Min Date: 1,970-01-01 (Thu: 4)
// Max Date: 2,940,698-09-10 (Sat: 6)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32unix_medium
inline uint8_t get_weekday_u32unix_medium(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x96DB0000;        // 2,530,934,784
    const uint32_t a = rd * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) MOD 7
// Input: 0 to 1,073,086,470
// Output: [0..6]
// Years: 2,938,011
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e5_medium
inline uint8_t get_weekday_u32e5_medium(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xBB6D0000;        // 3,144,482,816
    const uint32_t a = rd * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) MOD 7
// Input: 0 to 1,073,741,816
// Output: [0..6]
// Years: 2,939,805.2
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e6_medium
inline uint8_t get_weekday_u32e6_medium(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xDFFFFFFF;        // 3,758,096,383
    const uint32_t a = rd * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) POS_MOD 7) + 1
// Input: -536,739,839 to 537,001,990
// Output: [1..7]
// Years: -1,469,543.8 → 1,470,261.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso7_medium
inline uint8_t get_weekday_32iso7_medium(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xFDB70000;        // 4,256,628,736
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd POS_MOD 7) + 1
// Input: -537,001,983 to 536,739,846
// Output: [1..7]
// Years: -1,470,261.5 → 1,469,543.8
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso1_medium
inline uint8_t get_weekday_32iso1_medium(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x22490000;        // 575,209,472
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) POS_MOD 7) + 1
// Input: -537,264,127 to 536,477,702
// Output: [1..7]
// Years: -1,470,979.2 → 1,468,826.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso2_medium
inline uint8_t get_weekday_32iso2_medium(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x46DB0000;        // 1,188,757,504
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) POS_MOD 7) + 1
// Input: -537,526,271 to 536,215,558
// Output: [1..7]
// Years: -1,471,696.9 → 1,468,108.3
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso3_medium
inline uint8_t get_weekday_32iso3_medium(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x6B6D0000;        // 1,802,305,536
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: ((rd + 3) POS_MOD 7) + 1
// Input: -536,870,911 to 536,870,918
// Output: [1..7]
// Min Date: -1,467,933-05-16 (Mon: 1)
// Max Date:  1,471,872-08-25 (Sun: 7)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso_medium
inline uint8_t get_weekday_32iso_medium(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x90000000;        // 2,415,919,104
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) POS_MOD 7) + 1
// Input: -537,133,055 to 536,608,774
// Output: [1..7]
// Years: -1,470,620.4 → 1,469,184.9
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso5_medium
inline uint8_t get_weekday_32iso5_medium(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xB4920000;        // 3,029,467,136
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) POS_MOD 7) + 1
// Input: -536,477,695 to 537,264,134
// Output: [1..7]
// Years: -1,468,826 → 1,470,979.2
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso6_medium
inline uint8_t get_weekday_32iso6_medium(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xD9250000;        // 3,643,080,704
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) MOD 7) + 1
// Input: 0 to 1,073,741,816
// Output: [1..7]
// Years: 2,939,805.2
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso7_medium
inline uint8_t get_weekday_u32iso7_medium(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xFFFFFFFF;        // 4,294,967,295
    const uint32_t a = rd * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd MOD 7) + 1
// Input: 0 to 1,073,479,686
// Output: [1..7]
// Years: 2,939,087.6
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso1_medium
inline uint8_t get_weekday_u32iso1_medium(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x24920000;        // 613,548,032
    const uint32_t a = rd * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) MOD 7) + 1
// Input: 0 to 1,073,217,542
// Output: [1..7]
// Years: 2,938,369.8
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso2_medium
inline uint8_t get_weekday_u32iso2_medium(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x49240000;        // 1,227,096,064
    const uint32_t a = rd * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) MOD 7) + 1
// Input: 0 to 1,072,955,398
// Output: [1..7]
// Years: 2,937,652.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso3_medium
inline uint8_t get_weekday_u32iso3_medium(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x6DB60000;        // 1,840,644,096
    const uint32_t a = rd * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: ((rd + 3) MOD 7) + 1
// Input: 0 to 1,073,610,758
// Output: [1..7]
// Min Date: 1,970-01-01 (Thu: 4)
// Max Date: 2,941,416-06-02 (Sun: 7)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso_medium
inline uint8_t get_weekday_u32iso_medium(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x92490000;        // 2,454,257,664
    const uint32_t a = rd * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) MOD 7) + 1
// Input: 0 to 1,073,348,614
// Output: [1..7]
// Years: 2,938,728.7
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso5_medium
inline uint8_t get_weekday_u32iso5_medium(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xB6DB0000;        // 3,067,805,696
    const uint32_t a = rd * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) MOD 7) + 1
// Input: 0 to 1,073,086,470
// Output: [1..7]
// Years: 2,938,011
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso6_medium
inline uint8_t get_weekday_u32iso6_medium(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xDB6D0000;        // 3,681,353,728
    const uint32_t a = rd * M + Z;
    const uint32_t b = rd >> 1;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32
inline uint8_t get_weekday_32(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x03000000;        // 50,331,648
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e1
inline uint8_t get_weekday_32e1(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x27000000;        // 654,311,424
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e2
inline uint8_t get_weekday_32e2(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x4C000000;        // 1,275,068,416
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e3
inline uint8_t get_weekday_32e3(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x70000000;        // 1,879,048,192
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: (rd + 4) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Min Date: -5,877,641-06-23 (Tue: 2)
// Max Date:  5,881,580-07-11 (Fri: 5)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32unix
inline uint8_t get_weekday_32unix(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x95000000;        // 2,499,805,184
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e5
inline uint8_t get_weekday_32e5(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xBA000000;        // 3,120,562,176
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e6
inline uint8_t get_weekday_32e6(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xDE000000;        // 3,724,541,952
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32
inline uint8_t get_weekday_u32(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x03000000;        // 50,331,648
    const uint32_t a = rd * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e1
inline uint8_t get_weekday_u32e1(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x27000000;        // 654,311,424
    const uint32_t a = rd * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e2
inline uint8_t get_weekday_u32e2(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x4C000000;        // 1,275,068,416
    const uint32_t a = rd * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e3
inline uint8_t get_weekday_u32e3(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x71000000;        // 1,895,825,408
    const uint32_t a = rd * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: (rd + 4) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Min Date: 1,970-01-01 (Thu: 4)
// Max Date: 11,761,191-01-20 (Sun: 0)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32unix
inline uint8_t get_weekday_u32unix(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x95000000;        // 2,499,805,184
    const uint32_t a = rd * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e5
inline uint8_t get_weekday_u32e5(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xBA000000;        // 3,120,562,176
    const uint32_t a = rd * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e6
inline uint8_t get_weekday_u32e6(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xDE000000;        // 3,724,541,952
    const uint32_t a = rd * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso7
inline uint8_t get_weekday_32iso7(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xFE000000;        // 4,261,412,864
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso1
inline uint8_t get_weekday_32iso1(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x23000000;        // 587,202,560
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso2
inline uint8_t get_weekday_32iso2(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x47000000;        // 1,191,182,336
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso3
inline uint8_t get_weekday_32iso3(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x6C000000;        // 1,811,939,328
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: ((rd + 3) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Min Date: -5,877,641-06-23 (Tue: 2)
// Max Date:  5,881,580-07-11 (Fri: 5)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso
inline uint8_t get_weekday_32iso(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x90000000;        // 2,415,919,104
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso5
inline uint8_t get_weekday_32iso5(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xB5000000;        // 3,036,676,096
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso6
inline uint8_t get_weekday_32iso6(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xDA000000;        // 3,657,433,088
    const uint32_t a = uint32_t(rd) * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso7
inline uint8_t get_weekday_u32iso7(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xFE000000;        // 4,261,412,864
    const uint32_t a = rd * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso1
inline uint8_t get_weekday_u32iso1(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x23000000;        // 587,202,560
    const uint32_t a = rd * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso2
inline uint8_t get_weekday_u32iso2(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x47000000;        // 1,191,182,336
    const uint32_t a = rd * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso3
inline uint8_t get_weekday_u32iso3(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x6C000000;        // 1,811,939,328
    const uint32_t a = rd * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: ((rd + 3) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Min Date: 1,970-01-01 (Thu: 4)
// Max Date: 11,761,191-01-20 (Sun: 7)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso
inline uint8_t get_weekday_u32iso(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x91000000;        // 2,432,696,320
    const uint32_t a = rd * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso5
inline uint8_t get_weekday_u32iso5(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xB5000000;        // 3,036,676,096
    const uint32_t a = rd * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso6
inline uint8_t get_weekday_u32iso6(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xDA000000;        // 3,657,433,088
    const uint32_t a = rd * M + Z;
    const uint32_t b = (rd >> 1) + (rd >> 4);
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32_v2
inline uint8_t get_weekday_32_v2(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const int32_t  N = ((4 << 16) / 7) << 16;  // -1,840,709,632
    const uint32_t Z = 0x2000;        // 8,192
    const uint32_t a = uint32_t(rd) * M + Z;
    const int32_t  b = (int64_t(rd) * N) >> 32;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e1_v2
inline uint8_t get_weekday_32e1_v2(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const int32_t  N = ((4 << 16) / 7) << 16;  // -1,840,709,632
    const uint32_t Z = 0x28000000;        // 671,088,640
    const uint32_t a = uint32_t(rd) * M + Z;
    const int32_t  b = (int64_t(rd) * N) >> 32;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e2_v2
inline uint8_t get_weekday_32e2_v2(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const int32_t  N = ((4 << 16) / 7) << 16;  // -1,840,709,632
    const uint32_t Z = 0x4C000000;        // 1,275,068,416
    const uint32_t a = uint32_t(rd) * M + Z;
    const int32_t  b = (int64_t(rd) * N) >> 32;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e3_v2
inline uint8_t get_weekday_32e3_v2(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const int32_t  N = ((4 << 16) / 7) << 16;  // -1,840,709,632
    const uint32_t Z = 0x70000000;        // 1,879,048,192
    const uint32_t a = uint32_t(rd) * M + Z;
    const int32_t  b = (int64_t(rd) * N) >> 32;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: (rd + 4) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Min Date: -5,877,641-06-23 (Tue: 2)
// Max Date:  5,881,580-07-11 (Fri: 5)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32unix_v2
inline uint8_t get_weekday_32unix_v2(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const int32_t  N = int32_t(M * 4);  // -1,840,700,268
    const uint32_t a = uint32_t(rd) * M + N;
    const int32_t  b = (int64_t(rd) * N) >> 32;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e5_v2
inline uint8_t get_weekday_32e5_v2(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const int32_t  N = ((4 << 16) / 7) << 16;  // -1,840,709,632
    const uint32_t Z = 0xB8000000;        // 3,087,007,744
    const uint32_t a = uint32_t(rd) * M + Z;
    const int32_t  b = (int64_t(rd) * N) >> 32;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e6_v2
inline uint8_t get_weekday_32e6_v2(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const int32_t  N = ((4 << 16) / 7) << 16;  // -1,840,709,632
    const uint32_t Z = 0xDC000000;        // 3,690,987,520
    const uint32_t a = uint32_t(rd) * M + Z;
    const int32_t  b = (int64_t(rd) * N) >> 32;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32_v2
inline uint8_t get_weekday_u32_v2(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t N = ((3 << 16) / 7) << 16;  // 1,840,644,096
    const uint32_t a = rd * M;
    const uint32_t b = (uint64_t(rd) * N) >> 32;
    return uint32_t(a - b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e1_v2
inline uint8_t get_weekday_u32e1_v2(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t N = ((3 << 16) / 7) << 16;  // 1,840,644,096
    const uint32_t Z = 0x28000000;        // 671,088,640
    const uint32_t a = rd * M + Z;
    const uint32_t b = (uint64_t(rd) * N) >> 32;
    return uint32_t(a - b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e2_v2
inline uint8_t get_weekday_u32e2_v2(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t N = ((3 << 16) / 7) << 16;  // 1,840,644,096
    const uint32_t Z = 0x4C000000;        // 1,275,068,416
    const uint32_t a = rd * M + Z;
    const uint32_t b = (uint64_t(rd) * N) >> 32;
    return uint32_t(a - b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e3_v2
inline uint8_t get_weekday_u32e3_v2(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t N = ((3 << 16) / 7) << 16;  // 1,840,644,096
    const uint32_t Z = 0x70000000;        // 1,879,048,192
    const uint32_t a = rd * M + Z;
    const uint32_t b = (uint64_t(rd) * N) >> 32;
    return uint32_t(a - b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: (rd + 4) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Min Date: 1,970-01-01 (Thu: 4)
// Max Date: 11,761,191-01-20 (Sun: 0)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32unix_v2
inline uint8_t get_weekday_u32unix_v2(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t N = ((3 << 16) / 7) << 16;  // 1,840,644,096
    const uint32_t Z = 0x93000000;        // 2,466,250,752
    const uint32_t a = rd * M + Z;
    const uint32_t b = (uint64_t(rd) * N) >> 32;
    return uint32_t(a - b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e5_v2
inline uint8_t get_weekday_u32e5_v2(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t N = ((3 << 16) / 7) << 16;  // 1,840,644,096
    const uint32_t Z = 0xB8000000;        // 3,087,007,744
    const uint32_t a = rd * M + Z;
    const uint32_t b = (uint64_t(rd) * N) >> 32;
    return uint32_t(a - b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e6_v2
inline uint8_t get_weekday_u32e6_v2(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t N = ((3 << 16) / 7) << 16;  // 1,840,644,096
    const uint32_t Z = 0xDC000000;        // 3,690,987,520
    const uint32_t a = rd * M + Z;
    const uint32_t b = (uint64_t(rd) * N) >> 32;
    return uint32_t(a - b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso7_v2
inline uint8_t get_weekday_32iso7_v2(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const int32_t  N = ((4 << 16) / 7) << 16;  // -1,840,709,632
    const uint32_t Z = 0xFC000000;        // 4,227,858,432
    const uint32_t a = uint32_t(rd) * M + Z;
    const int32_t  b = (int64_t(rd) * N) >> 32;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso1_v2
inline uint8_t get_weekday_32iso1_v2(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const int32_t  N = ((4 << 16) / 7) << 16;  // -1,840,709,632
    const uint32_t Z = 0x24000000;        // 603,979,776
    const uint32_t a = uint32_t(rd) * M + Z;
    const int32_t  b = (int64_t(rd) * N) >> 32;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso2_v2
inline uint8_t get_weekday_32iso2_v2(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const int32_t  N = ((4 << 16) / 7) << 16;  // -1,840,709,632
    const uint32_t Z = 0x48000000;        // 1,207,959,552
    const uint32_t a = uint32_t(rd) * M + Z;
    const int32_t  b = (int64_t(rd) * N) >> 32;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso3_v2
inline uint8_t get_weekday_32iso3_v2(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const int32_t  N = ((4 << 16) / 7) << 16;  // -1,840,709,632
    const uint32_t Z = 0x6C000000;        // 1,811,939,328
    const uint32_t a = uint32_t(rd) * M + Z;
    const int32_t  b = (int64_t(rd) * N) >> 32;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: ((rd + 3) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Min Date: -5,877,641-06-23 (Tue: 2)
// Max Date:  5,881,580-07-11 (Fri: 5)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso_v2
inline uint8_t get_weekday_32iso_v2(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const int32_t  N = ((4 << 16) / 7) << 16;  // -1,840,709,632
    const uint32_t Z = 0x90000000;        // 2,415,919,104
    const uint32_t a = uint32_t(rd) * M + Z;
    const int32_t  b = (int64_t(rd) * N) >> 32;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso5_v2
inline uint8_t get_weekday_32iso5_v2(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const int32_t  N = ((4 << 16) / 7) << 16;  // -1,840,709,632
    const uint32_t Z = 0xB4000000;        // 3,019,898,880
    const uint32_t a = uint32_t(rd) * M + Z;
    const int32_t  b = (int64_t(rd) * N) >> 32;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso6_v2
inline uint8_t get_weekday_32iso6_v2(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const int32_t  N = ((4 << 16) / 7) << 16;  // -1,840,709,632
    const uint32_t Z = 0xD8000000;        // 3,623,878,656
    const uint32_t a = uint32_t(rd) * M + Z;
    const int32_t  b = (int64_t(rd) * N) >> 32;
    return uint32_t(a + b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso7_v2
inline uint8_t get_weekday_u32iso7_v2(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t N = ((3 << 16) / 7) << 16;  // 1,840,644,096
    const uint32_t Z = 0xFC000000;        // 4,227,858,432
    const uint32_t a = rd * M + Z;
    const uint32_t b = (uint64_t(rd) * N) >> 32;
    return uint32_t(a - b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso1_v2
inline uint8_t get_weekday_u32iso1_v2(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t N = ((3 << 16) / 7) << 16;  // 1,840,644,096
    const uint32_t Z = 0x24000000;        // 603,979,776
    const uint32_t a = rd * M + Z;
    const uint32_t b = (uint64_t(rd) * N) >> 32;
    return uint32_t(a - b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso2_v2
inline uint8_t get_weekday_u32iso2_v2(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t N = ((3 << 16) / 7) << 16;  // 1,840,644,096
    const uint32_t Z = 0x48000000;        // 1,207,959,552
    const uint32_t a = rd * M + Z;
    const uint32_t b = (uint64_t(rd) * N) >> 32;
    return uint32_t(a - b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso3_v2
inline uint8_t get_weekday_u32iso3_v2(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t N = ((3 << 16) / 7) << 16;  // 1,840,644,096
    const uint32_t Z = 0x6C000000;        // 1,811,939,328
    const uint32_t a = rd * M + Z;
    const uint32_t b = (uint64_t(rd) * N) >> 32;
    return uint32_t(a - b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: ((rd + 3) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Min Date: 1,970-01-01 (Thu: 4)
// Max Date: 11,761,191-01-20 (Sun: 7)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso_v2
inline uint8_t get_weekday_u32iso_v2(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t N = ((3 << 16) / 7) << 16;  // 1,840,644,096
    const uint32_t Z = 0x90000000;        // 2,415,919,104
    const uint32_t a = rd * M + Z;
    const uint32_t b = (uint64_t(rd) * N) >> 32;
    return uint32_t(a - b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso5_v2
inline uint8_t get_weekday_u32iso5_v2(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t N = ((3 << 16) / 7) << 16;  // 1,840,644,096
    const uint32_t Z = 0xB4000000;        // 3,019,898,880
    const uint32_t a = rd * M + Z;
    const uint32_t b = (uint64_t(rd) * N) >> 32;
    return uint32_t(a - b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso6_v2
inline uint8_t get_weekday_u32iso6_v2(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7 + 1;  // 613,566,757
    const uint32_t N = ((3 << 16) / 7) << 16;  // 1,840,644,096
    const uint32_t Z = 0xD8000000;        // 3,623,878,656
    const uint32_t a = rd * M + Z;
    const uint32_t b = (uint64_t(rd) * N) >> 32;
    return uint32_t(a - b) >> 29; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32_v3
inline uint8_t get_weekday_32_v3(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + 4) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e1_v3
inline uint8_t get_weekday_32e1_v3(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x27000000;     // 654,311,424
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e2_v3
inline uint8_t get_weekday_32e2_v3(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x4C000000;     // 1,275,068,416
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e3_v3
inline uint8_t get_weekday_32e3_v3(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x70000000;     // 1,879,048,192
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: (rd + 4) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Min Date: -5,877,641-06-23 (Tue: 2)
// Max Date:  5,881,580-07-11 (Fri: 5)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32unix_v3
inline uint8_t get_weekday_32unix_v3(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x95000000;     // 2,499,805,184
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e5_v3
inline uint8_t get_weekday_32e5_v3(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xBA000000;     // 3,120,562,176
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e6_v3
inline uint8_t get_weekday_32e6_v3(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xDE000000;     // 3,724,541,952
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32_v3
inline uint8_t get_weekday_u32_v3(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + 4) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e1_v3
inline uint8_t get_weekday_u32e1_v3(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x27000000;     // 654,311,424
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e2_v3
inline uint8_t get_weekday_u32e2_v3(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x4C000000;     // 1,275,068,416
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e3_v3
inline uint8_t get_weekday_u32e3_v3(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x70000000;     // 1,879,048,192
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: (rd + 4) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Min Date: 1,970-01-01 (Thu: 4)
// Max Date: 11,761,191-01-20 (Sun: 0)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32unix_v3
inline uint8_t get_weekday_u32unix_v3(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x95000000;     // 2,499,805,184
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e5_v3
inline uint8_t get_weekday_u32e5_v3(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xBA000000;     // 3,120,562,176
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e6_v3
inline uint8_t get_weekday_u32e6_v3(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xDE000000;     // 3,724,541,952
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso7_v3
inline uint8_t get_weekday_32iso7_v3(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xFE000000;     // 4,261,412,864
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso1_v3
inline uint8_t get_weekday_32iso1_v3(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x23000000;     // 587,202,560
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso2_v3
inline uint8_t get_weekday_32iso2_v3(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x47000000;     // 1,191,182,336
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso3_v3
inline uint8_t get_weekday_32iso3_v3(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x6C000000;     // 1,811,939,328
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: ((rd + 3) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Min Date: -5,877,641-06-23 (Tue: 2)
// Max Date:  5,881,580-07-11 (Fri: 5)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso_v3
inline uint8_t get_weekday_32iso_v3(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x90000000;     // 2,415,919,104
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso5_v3
inline uint8_t get_weekday_32iso5_v3(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xB5000000;     // 3,036,676,096
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso6_v3
inline uint8_t get_weekday_32iso6_v3(int32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xDA000000;     // 3,657,433,088
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso7_v3
inline uint8_t get_weekday_u32iso7_v3(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xFE000000;     // 4,261,412,864
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso1_v3
inline uint8_t get_weekday_u32iso1_v3(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x23000000;     // 587,202,560
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso2_v3
inline uint8_t get_weekday_u32iso2_v3(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x47000000;     // 1,191,182,336
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso3_v3
inline uint8_t get_weekday_u32iso3_v3(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x6C000000;     // 1,811,939,328
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: ((rd + 3) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Min Date: 1,970-01-01 (Thu: 4)
// Max Date: 11,761,191-01-20 (Sun: 7)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso_v3
inline uint8_t get_weekday_u32iso_v3(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0x90000000;     // 2,415,919,104
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso5_v3
inline uint8_t get_weekday_u32iso5_v3(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xB5000000;     // 3,036,676,096
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso6_v3
inline uint8_t get_weekday_u32iso6_v3(uint32_t rd) {
    const uint32_t M = (1ull << 32) / 7;  // 613,566,756
    const uint32_t Z = 0xDA000000;     // 3,657,433,088
    const uint64_t w = uint64_t(rd) * M;
    const uint32_t a = uint32_t(w >> 32);
    const uint32_t b = uint32_t(w);
    return (b + (a << 2) + Z) >> 29;
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32_widen
inline uint8_t get_weekday_32_widen(int32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0x0200ull << 48;        // 144,115,188,075,855,872
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e1_widen
inline uint8_t get_weekday_32e1_widen(int32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0x2800ull << 48;        // 2,882,303,761,517,117,440
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e2_widen
inline uint8_t get_weekday_32e2_widen(int32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0x4C00ull << 48;        // 5,476,377,146,882,523,136
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e3_widen
inline uint8_t get_weekday_32e3_widen(int32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0x7000ull << 48;        // 8,070,450,532,247,928,832
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: (rd + 4) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Min Date: -5,877,641-06-23 (Tue: 2)
// Max Date:  5,881,580-07-11 (Fri: 5)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32unix_widen
inline uint8_t get_weekday_32unix_widen(int32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0x9400ull << 48;        // 10,664,523,917,613,334,528
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e5_widen
inline uint8_t get_weekday_32e5_widen(int32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0xBA00ull << 48;        // 13,402,712,491,054,596,096
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) POS_MOD 7
// Range: Full signed 32-bit
// Output: [0..6]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32e6_widen
inline uint8_t get_weekday_32e6_widen(int32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0xDD00ull << 48;        // 15,924,728,282,382,073,856
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32_widen
inline uint8_t get_weekday_u32_widen(uint32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    return (uint64_t(rd) * M) >> 61;  // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e1_widen
inline uint8_t get_weekday_u32e1_widen(uint32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    return ((uint64_t(rd) + 1) * M) >> 61;  // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e2_widen
inline uint8_t get_weekday_u32e2_widen(uint32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    return ((uint64_t(rd) + 2) * M) >> 61;  // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e3_widen
inline uint8_t get_weekday_u32e3_widen(uint32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    return ((uint64_t(rd) + 3) * M) >> 61;  // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: (rd + 4) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Min Date: 1,970-01-01 (Thu: 4)
// Max Date: 11,761,191-01-20 (Sun: 0)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32unix_widen
inline uint8_t get_weekday_u32unix_widen(uint32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    return ((uint64_t(rd) + 4) * M) >> 61;  // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e5_widen
inline uint8_t get_weekday_u32e5_widen(uint32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    return ((uint64_t(rd) + 5) * M) >> 61;  // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) MOD 7
// Range: Full unsigned 32-bit
// Output: [0..6]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32e6_widen
inline uint8_t get_weekday_u32e6_widen(uint32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    return ((uint64_t(rd) + 6) * M) >> 61;  // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso7_widen
inline uint8_t get_weekday_32iso7_widen(int32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0xFF00ull << 48;        // 18,374,686,479,671,623,680
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso1_widen
inline uint8_t get_weekday_32iso1_widen(int32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0x2200ull << 48;        // 2,449,958,197,289,549,824
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso2_widen
inline uint8_t get_weekday_32iso2_widen(int32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0x4800ull << 48;        // 5,188,146,770,730,811,392
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso3_widen
inline uint8_t get_weekday_32iso3_widen(int32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0x6C00ull << 48;        // 7,782,220,156,096,217,088
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: ((rd + 3) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Min Date: -5,877,641-06-23 (Tue: 2)
// Max Date:  5,881,580-07-11 (Fri: 5)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso_widen
inline uint8_t get_weekday_32iso_widen(int32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0x9000ull << 48;        // 10,376,293,541,461,622,784
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso5_widen
inline uint8_t get_weekday_32iso5_widen(int32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0xB400ull << 48;        // 12,970,366,926,827,028,480
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) POS_MOD 7) + 1
// Range: Full signed 32-bit
// Output: [1..7]
// Years: -5,879,610.5 → 5,879,610.5
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=32iso6_widen
inline uint8_t get_weekday_32iso6_widen(int32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0xDA00ull << 48;        // 15,708,555,500,268,290,048
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso7_widen
inline uint8_t get_weekday_u32iso7_widen(uint32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0xFF00ull << 48;        // 18,374,686,479,671,623,680
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso1_widen
inline uint8_t get_weekday_u32iso1_widen(uint32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0x2200ull << 48;        // 2,449,958,197,289,549,824
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso2_widen
inline uint8_t get_weekday_u32iso2_widen(uint32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0x4800ull << 48;        // 5,188,146,770,730,811,392
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso3_widen
inline uint8_t get_weekday_u32iso3_widen(uint32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0x6C00ull << 48;        // 7,782,220,156,096,217,088
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: ((rd + 3) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Min Date: 1,970-01-01 (Thu: 4)
// Max Date: 11,761,191-01-20 (Sun: 7)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso_widen
inline uint8_t get_weekday_u32iso_widen(uint32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0x9000ull << 48;        // 10,376,293,541,461,622,784
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso5_widen
inline uint8_t get_weekday_u32iso5_widen(uint32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0xB400ull << 48;        // 12,970,366,926,827,028,480
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) MOD 7) + 1
// Range: Full unsigned 32-bit
// Output: [1..7]
// Years: 11,759,221.1
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u32iso6_widen
inline uint8_t get_weekday_u32iso6_widen(uint32_t rd) {
    const uint64_t M = ((1ull << 40) / 7 + 1) << 24;
    const uint64_t Z = 0xDA00ull << 48;        // 15,708,555,500,268,290,048
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd POS_MOD 7
// Range: Full signed 64-bit
// Output: [0..6]
// Years: -25,252,734,927,766,554 → 25,252,734,927,766,554
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64
inline uint8_t get_weekday_64(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x0200ull << 48;        // 144,115,188,075,855,872
    const uint64_t a = uint64_t(rd) * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) POS_MOD 7
// Range: Full signed 64-bit
// Output: [0..6]
// Years: -25,252,734,927,766,554 → 25,252,734,927,766,554
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64e1
inline uint8_t get_weekday_64e1(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x2800ull << 48;        // 2,882,303,761,517,117,440
    const uint64_t a = uint64_t(rd) * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) POS_MOD 7
// Range: Full signed 64-bit
// Output: [0..6]
// Years: -25,252,734,927,766,554 → 25,252,734,927,766,554
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64e2
inline uint8_t get_weekday_64e2(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x4C00ull << 48;        // 5,476,377,146,882,523,136
    const uint64_t a = uint64_t(rd) * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) POS_MOD 7
// Range: Full signed 64-bit
// Output: [0..6]
// Years: -25,252,734,927,766,554 → 25,252,734,927,766,554
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64e3
inline uint8_t get_weekday_64e3(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x7000ull << 48;        // 8,070,450,532,247,928,832
    const uint64_t a = uint64_t(rd) * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: (rd + 4) POS_MOD 7
// Range: Full signed 64-bit
// Output: [0..6]
// Min Date: -25,252,734,927,764,585-06-07 (Wed: 3)
// Max Date:  25,252,734,927,768,524-07-27 (Thu: 4)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64unix
inline uint8_t get_weekday_64unix(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x9400ull << 48;        // 10,664,523,917,613,334,528
    const uint64_t a = uint64_t(rd) * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) POS_MOD 7
// Range: Full signed 64-bit
// Output: [0..6]
// Years: -25,252,734,927,766,554 → 25,252,734,927,766,554
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64e5
inline uint8_t get_weekday_64e5(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0xBA00ull << 48;        // 13,402,712,491,054,596,096
    const uint64_t a = uint64_t(rd) * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) POS_MOD 7
// Range: Full signed 64-bit
// Output: [0..6]
// Years: -25,252,734,927,766,554 → 25,252,734,927,766,554
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64e6
inline uint8_t get_weekday_64e6(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0xDD00ull << 48;        // 15,924,728,282,382,073,856
    const uint64_t a = uint64_t(rd) * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd MOD 7
// Range: Full unsigned 64-bit
// Output: [0..6]
// Years: 50,505,469,855,533,109
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64
inline uint8_t get_weekday_u64(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x0200ull << 48;        // 144,115,188,075,855,872
    const uint64_t a = rd * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) MOD 7
// Range: Full unsigned 64-bit
// Output: [0..6]
// Years: 50,505,469,855,533,109
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64e1
inline uint8_t get_weekday_u64e1(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x2800ull << 48;        // 2,882,303,761,517,117,440
    const uint64_t a = rd * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) MOD 7
// Range: Full unsigned 64-bit
// Output: [0..6]
// Years: 50,505,469,855,533,109
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64e2
inline uint8_t get_weekday_u64e2(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x4C00ull << 48;        // 5,476,377,146,882,523,136
    const uint64_t a = rd * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) MOD 7
// Range: Full unsigned 64-bit
// Output: [0..6]
// Years: 50,505,469,855,533,109
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64e3
inline uint8_t get_weekday_u64e3(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x7000ull << 48;        // 8,070,450,532,247,928,832
    const uint64_t a = rd * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: (rd + 4) MOD 7
// Range: Full unsigned 64-bit
// Output: [0..6]
// Min Date: 1,970-01-01 (Thu: 4)
// Max Date: 50,505,469,855,535,079-02-21 (Fri: 5)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64unix
inline uint8_t get_weekday_u64unix(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x9400ull << 48;        // 10,664,523,917,613,334,528
    const uint64_t a = rd * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) MOD 7
// Range: Full unsigned 64-bit
// Output: [0..6]
// Years: 50,505,469,855,533,109
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64e5
inline uint8_t get_weekday_u64e5(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0xBA00ull << 48;        // 13,402,712,491,054,596,096
    const uint64_t a = rd * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) MOD 7
// Range: Full unsigned 64-bit
// Output: [0..6]
// Years: 50,505,469,855,533,109
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64e6
inline uint8_t get_weekday_u64e6(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0xDD00ull << 48;        // 15,924,728,282,382,073,856
    const uint64_t a = rd * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) POS_MOD 7) + 1
// Range: Full signed 64-bit
// Output: [1..7]
// Years: -25,252,734,927,766,554 → 25,252,734,927,766,554
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64iso7
inline uint8_t get_weekday_64iso7(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0xFF00ull << 48;        // 18,374,686,479,671,623,680
    const uint64_t a = uint64_t(rd) * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd POS_MOD 7) + 1
// Range: Full signed 64-bit
// Output: [1..7]
// Years: -25,252,734,927,766,554 → 25,252,734,927,766,554
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64iso1
inline uint8_t get_weekday_64iso1(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x2200ull << 48;        // 2,449,958,197,289,549,824
    const uint64_t a = uint64_t(rd) * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) POS_MOD 7) + 1
// Range: Full signed 64-bit
// Output: [1..7]
// Years: -25,252,734,927,766,554 → 25,252,734,927,766,554
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64iso2
inline uint8_t get_weekday_64iso2(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x4800ull << 48;        // 5,188,146,770,730,811,392
    const uint64_t a = uint64_t(rd) * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) POS_MOD 7) + 1
// Range: Full signed 64-bit
// Output: [1..7]
// Years: -25,252,734,927,766,554 → 25,252,734,927,766,554
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64iso3
inline uint8_t get_weekday_64iso3(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x6C00ull << 48;        // 7,782,220,156,096,217,088
    const uint64_t a = uint64_t(rd) * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: ((rd + 3) POS_MOD 7) + 1
// Range: Full signed 64-bit
// Output: [1..7]
// Min Date: -25,252,734,927,764,585-06-07 (Wed: 3)
// Max Date:  25,252,734,927,768,524-07-27 (Thu: 4)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64iso
inline uint8_t get_weekday_64iso(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x9000ull << 48;        // 10,376,293,541,461,622,784
    const uint64_t a = uint64_t(rd) * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) POS_MOD 7) + 1
// Range: Full signed 64-bit
// Output: [1..7]
// Years: -25,252,734,927,766,554 → 25,252,734,927,766,554
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64iso5
inline uint8_t get_weekday_64iso5(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0xB400ull << 48;        // 12,970,366,926,827,028,480
    const uint64_t a = uint64_t(rd) * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) POS_MOD 7) + 1
// Range: Full signed 64-bit
// Output: [1..7]
// Years: -25,252,734,927,766,554 → 25,252,734,927,766,554
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64iso6
inline uint8_t get_weekday_64iso6(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0xDA00ull << 48;        // 15,708,555,500,268,290,048
    const uint64_t a = uint64_t(rd) * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) MOD 7) + 1
// Range: Full unsigned 64-bit
// Output: [1..7]
// Years: 50,505,469,855,533,109
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64iso7
inline uint8_t get_weekday_u64iso7(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0xFF00ull << 48;        // 18,374,686,479,671,623,680
    const uint64_t a = rd * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd MOD 7) + 1
// Range: Full unsigned 64-bit
// Output: [1..7]
// Years: 50,505,469,855,533,109
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64iso1
inline uint8_t get_weekday_u64iso1(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x2200ull << 48;        // 2,449,958,197,289,549,824
    const uint64_t a = rd * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) MOD 7) + 1
// Range: Full unsigned 64-bit
// Output: [1..7]
// Years: 50,505,469,855,533,109
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64iso2
inline uint8_t get_weekday_u64iso2(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x4800ull << 48;        // 5,188,146,770,730,811,392
    const uint64_t a = rd * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) MOD 7) + 1
// Range: Full unsigned 64-bit
// Output: [1..7]
// Years: 50,505,469,855,533,109
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64iso3
inline uint8_t get_weekday_u64iso3(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x6C00ull << 48;        // 7,782,220,156,096,217,088
    const uint64_t a = rd * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: ((rd + 3) MOD 7) + 1
// Range: Full unsigned 64-bit
// Output: [1..7]
// Min Date: 1,970-01-01 (Thu: 4)
// Max Date: 50,505,469,855,535,079-02-21 (Fri: 5)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64iso
inline uint8_t get_weekday_u64iso(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0x9000ull << 48;        // 10,376,293,541,461,622,784
    const uint64_t a = rd * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) MOD 7) + 1
// Range: Full unsigned 64-bit
// Output: [1..7]
// Years: 50,505,469,855,533,109
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64iso5
inline uint8_t get_weekday_u64iso5(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0xB400ull << 48;        // 12,970,366,926,827,028,480
    const uint64_t a = rd * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) MOD 7) + 1
// Range: Full unsigned 64-bit
// Output: [1..7]
// Years: 50,505,469,855,533,109
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64iso6
inline uint8_t get_weekday_u64iso6(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7;
    const uint64_t Z = 0xDA00ull << 48;        // 15,708,555,500,268,290,048
    const uint64_t a = rd * M + Z;
    const uint64_t b = (rd >> 2) + (rd >> 5);
    return uint64_t(a + b) >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd POS_MOD 7
// Input: -230,528,005,926,027,270 to 230,640,595,916,711,531
// Output: [0..6]
// Years: -631,164,242,731,958 → 631,472,503,656,369
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64_narrow
inline uint8_t get_weekday_64_narrow(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0x0249ull << 48;        // 164,662,861,375,733,760
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) POS_MOD 7
// Input: -230,415,415,935,343,002 to 230,753,185,907,395,792
// Output: [0..6]
// Years: -630,855,981,807,547 → 631,780,764,580,780
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64e1_narrow
inline uint8_t get_weekday_64e1_narrow(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0x26DBull << 48;        // 2,799,831,593,340,895,232
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) POS_MOD 7
// Input: -230,696,890,912,053,658 to 230,471,710,930,685,136
// Output: [0..6]
// Years: -631,626,634,118,575 → 631,010,112,269,752
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64e2_narrow
inline uint8_t get_weekday_64e2_narrow(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0x4B6Eull << 48;        // 5,435,281,800,282,767,360
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) POS_MOD 7
// Input: -230,584,300,921,369,397 to 230,584,300,921,369,397
// Output: [0..6]
// Years: -631,318,373,194,163 → 631,318,373,194,163
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64e3_narrow
inline uint8_t get_weekday_64e3_narrow(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0x7000ull << 48;        // 8,070,450,532,247,928,832
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: (rd + 4) POS_MOD 7
// Input: -230,471,710,930,685,136 to 230,696,890,912,053,658
// Output: [0..6]
// Min Date: -631,010,112,267,783-05-05 (Mon: 1)
// Max Date:  631,626,634,120,545-01-29 (Fri: 5)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64unix_narrow
inline uint8_t get_weekday_64unix_narrow(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0x9492ull << 48;        // 10,705,619,264,213,090,304
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) POS_MOD 7
// Input: -230,753,185,907,395,792 to 230,415,415,935,343,002
// Output: [0..6]
// Years: -631,780,764,580,780 → 630,855,981,807,547
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64e5_narrow
inline uint8_t get_weekday_64e5_narrow(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0xB925ull << 48;        // 13,341,069,471,154,962,432
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) POS_MOD 7
// Input: -230,640,595,916,711,531 to 230,528,005,926,027,263
// Output: [0..6]
// Years: -631,472,503,656,369 → 631,164,242,731,958
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64e6_narrow
inline uint8_t get_weekday_64e6_narrow(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0xDDB7ull << 48;        // 15,976,238,203,120,123,904
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 0
// Compute: Day of week: rd MOD 7
// Input: 0 to 461,168,601,842,738,795
// Output: [0..6]
// Years: 1,262,636,746,388,327
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64_narrow
inline uint8_t get_weekday_u64_narrow(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    return (rd * M) >> 61;  // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd + 1) MOD 7
// Input: 0 to 461,168,601,842,738,801
// Output: [0..6]
// Years: 1,262,636,746,388,327
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64e1_narrow
inline uint8_t get_weekday_u64e1_narrow(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    return ((rd - 6) * M) >> 61;  // top 3 bits, subtraction intentional
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: (rd + 2) MOD 7
// Input: 0 to 461,168,601,842,738,800
// Output: [0..6]
// Years: 1,262,636,746,388,327
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64e2_narrow
inline uint8_t get_weekday_u64e2_narrow(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    return ((rd - 5) * M) >> 61;  // top 3 bits, subtraction intentional
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: (rd + 3) MOD 7
// Input: 0 to 461,168,601,842,738,799
// Output: [0..6]
// Years: 1,262,636,746,388,327
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64e3_narrow
inline uint8_t get_weekday_u64e3_narrow(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    return ((rd - 4) * M) >> 61;  // top 3 bits, subtraction intentional
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: (rd + 4) MOD 7
// Input: 0 to 461,168,601,842,738,798
// Output: [0..6]
// Min Date: 1,970-01-01 (Thu: 4)
// Max Date: 1,262,636,746,390,297-10-01 (Fri: 5)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64unix_narrow
inline uint8_t get_weekday_u64unix_narrow(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    return ((rd - 3) * M) >> 61;  // top 3 bits, subtraction intentional
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: (rd + 5) MOD 7
// Input: 0 to 461,168,601,842,738,797
// Output: [0..6]
// Years: 1,262,636,746,388,327
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64e5_narrow
inline uint8_t get_weekday_u64e5_narrow(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    return ((rd - 2) * M) >> 61;  // top 3 bits, subtraction intentional
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: (rd + 6) MOD 7
// Input: 0 to 461,168,601,842,738,796
// Output: [0..6]
// Years: 1,262,636,746,388,327
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64e6_narrow
inline uint8_t get_weekday_u64e6_narrow(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    return ((rd - 1) * M) >> 61;  // top 3 bits, subtraction intentional
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) POS_MOD 7) + 1
// Input: -230,640,595,916,711,531 to 230,528,005,926,027,263
// Output: [1..7]
// Years: -631,472,503,656,369 → 631,164,242,731,958
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64iso7_narrow
inline uint8_t get_weekday_64iso7_narrow(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0xFDB7ull << 48;        // 18,282,081,212,333,817,856
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd POS_MOD 7) + 1
// Input: -230,528,005,926,027,270 to 230,640,595,916,711,531
// Output: [1..7]
// Years: -631,164,242,731,958 → 631,472,503,656,369
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64iso1_narrow
inline uint8_t get_weekday_64iso1_narrow(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0x2249ull << 48;        // 2,470,505,870,589,427,712
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) POS_MOD 7) + 1
// Input: -230,415,415,935,343,002 to 230,753,185,907,395,792
// Output: [1..7]
// Years: -630,855,981,807,547 → 631,780,764,580,780
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64iso2_narrow
inline uint8_t get_weekday_64iso2_narrow(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0x46DBull << 48;        // 5,105,674,602,554,589,184
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) POS_MOD 7) + 1
// Input: -230,696,890,912,053,658 to 230,471,710,930,685,136
// Output: [1..7]
// Years: -631,626,634,118,575 → 631,010,112,269,752
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64iso3_narrow
inline uint8_t get_weekday_64iso3_narrow(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0x6B6Eull << 48;        // 7,741,124,809,496,461,312
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: ((rd + 3) POS_MOD 7) + 1
// Input: -230,584,300,921,369,397 to 230,584,300,921,369,397
// Output: [1..7]
// Min Date: -631,318,373,192,194-02-18 (Tue: 2)
// Max Date:  631,318,373,196,133-11-14 (Sat: 6)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64iso_narrow
inline uint8_t get_weekday_64iso_narrow(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0x9000ull << 48;        // 10,376,293,541,461,622,784
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) POS_MOD 7) + 1
// Input: -230,471,710,930,685,136 to 230,696,890,912,053,658
// Output: [1..7]
// Years: -631,010,112,269,752 → 631,626,634,118,575
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64iso5_narrow
inline uint8_t get_weekday_64iso5_narrow(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0xB492ull << 48;        // 13,011,462,273,426,784,256
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) POS_MOD 7) + 1
// Input: -230,753,185,907,395,792 to 230,415,415,935,343,002
// Output: [1..7]
// Years: -631,780,764,580,780 → 630,855,981,807,547
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=64iso6_narrow
inline uint8_t get_weekday_64iso6_narrow(int64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0xD925ull << 48;        // 15,646,912,480,368,656,384
    const uint64_t a = uint64_t(rd) * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 7
// Compute: Day of week: ((rd + 6) MOD 7) + 1
// Input: 0 to 461,056,011,852,054,527
// Output: [1..7]
// Years: 1,262,328,485,463,916
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64iso7_narrow
inline uint8_t get_weekday_u64iso7_narrow(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0xFB6Eull << 48;        // 18,117,418,350,958,084,096
    const uint64_t a = rd * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 1
// Compute: Day of week: (rd MOD 7) + 1
// Input: 0 to 461,168,601,842,738,795
// Output: [1..7]
// Years: 1,262,636,746,388,327
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64iso1_narrow
inline uint8_t get_weekday_u64iso1_narrow(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0x2000ull << 48;        // 2,305,843,009,213,693,952
    const uint64_t a = rd * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 2
// Compute: Day of week: ((rd + 1) MOD 7) + 1
// Input: 0 to 460,887,126,866,028,139
// Output: [1..7]
// Years: 1,261,866,094,077,299
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64iso2_narrow
inline uint8_t get_weekday_u64iso2_narrow(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0x4493ull << 48;        // 4,941,293,216,155,566,080
    const uint64_t a = rd * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 3
// Compute: Day of week: ((rd + 2) MOD 7) + 1
// Input: 0 to 460,999,716,856,712,400
// Output: [1..7]
// Years: 1,262,174,355,001,710
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64iso3_narrow
inline uint8_t get_weekday_u64iso3_narrow(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0x6925ull << 48;        // 7,576,461,948,120,727,552
    const uint64_t a = rd * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), Unix epoch 1970-01-01: 4
// Compute: Day of week: ((rd + 3) MOD 7) + 1
// Input: 0 to 461,112,306,847,396,661
// Output: [1..7]
// Min Date: 1,970-01-01 (Thu: 4)
// Max Date: 1,262,482,615,928,092-02-16 (Sat: 6)
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64iso_narrow
inline uint8_t get_weekday_u64iso_narrow(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0x8DB7ull << 48;        // 10,211,630,680,085,889,024
    const uint64_t a = rd * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 5
// Compute: Day of week: ((rd + 4) MOD 7) + 1
// Input: 0 to 460,830,831,870,686,005
// Output: [1..7]
// Years: 1,261,711,963,615,094
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64iso5_narrow
inline uint8_t get_weekday_u64iso5_narrow(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0xB24Aull << 48;        // 12,847,080,887,027,761,152
    const uint64_t a = rd * M + Z;
    return a >> 61; // top 3 bits
}

// Given: rd = rata-die (day-count), where epoch: 6
// Compute: Day of week: ((rd + 5) MOD 7) + 1
// Input: 0 to 460,943,421,861,370,266
// Output: [1..7]
// Years: 1,262,020,224,539,505
// Optional Ref: https://www.benjoffe.com/fast-day-of-week#fn=u64iso6_narrow
inline uint8_t get_weekday_u64iso6_narrow(uint64_t rd) {
    const uint64_t M = uint64_t(-1) / 7 + 1;
    const uint64_t Z = 0xD6DCull << 48;        // 15,482,249,618,992,922,624
    const uint64_t a = rd * M + Z;
    return a >> 61; // top 3 bits
}
