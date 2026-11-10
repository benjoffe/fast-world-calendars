# fast-world-calendars

Fast C++ implementations of calendar/clock conversions. Reference material for three blog posts:

- **weekday** — weekday from a Rata-Die (days since 1 Jan 1970): https://www.benjoffe.com/fast-day-of-week
- **time** — hours/minutes/seconds (and sub-second units) from a day-second count: https://www.benjoffe.com/fast-time-of-day
- **easter** — Gregorian Easter Sunday for a given year: https://www.benjoffe.com/fast-easter

## Algorithms

### weekday

Standard functions return `0=Sun … 6=Sat`.

Functions with the term "iso" included return `1=Mon … 7=Sun`.

### time

Functions return an `{hour, min, sec}` (or `{hour, min, sec, sub}` for deci/centi/milli/nanosecond variants) struct from a count of seconds (or sub-second units) since midnight. Variants with `_leap` handle a `23:59:60` leap second at `t=86400`.

### easter

Functions compute Gregorian Easter Sunday for a given year.
Return value: days since 22 March ∈ [0..34].
Note: the "Readable Easter Function" referenced in the blog post has a couple of small self-contained optimisations not stated on the website (fast day-of-week and fast mod 30).

## Build

Requires: CMake ≥ 3.14, C++20 compiler, internet access on first build (fetches Google Benchmark).

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/bin/weekday_bench
./build/bin/time_bench
./build/bin/easter_bench
```

## Build on GCC

```sh
cmake -S . -B build-gcc -DCMAKE_C_COMPILER=gcc-15 -DCMAKE_CXX_COMPILER=g++-15
cmake --build build-gcc -j
./build-gcc/bin/weekday_bench
./build-gcc/bin/time_bench
./build-gcc/bin/easter_bench
```

## Test

Verifies correctness over the full valid range of each algorithm, compared against the naive reference:

```sh
./build/bin/weekday_test
./build/bin/time_test
./build/bin/easter_test   # sweeps all 32-bit years; slow (minutes). Use -v to print mismatches
```

## Benchmark

```sh
./build/bin/weekday_bench
./build/bin/time_bench
./build/bin/easter_bench
```

Modes expose different aspects of performance:

| Flag | Measures |
|---|---|
| *(none)* | Throughput — independent calls, CPU free to pipeline |
| `-latency` | Latency — serial dependency chain, each result feeds the next input |
| `-batch` | Batch throughput — 3 calls per load, prevents fast algorithms appearing memory-bound (`weekday_bench` only) |
| `-vector` | Vector throughput — auto-vectorizable array loop, no per-element barrier |

Additional flags: `-count N` (array size, default 65536), `-repeat N` (benchmark repetitions).

## Attribution

The Hinnant and Neri benchmarks are independent reimplementations of their published algorithms — see the respective header files for sources.

## License

MIT — Copyright 2026 Ben Joffe — see [LICENSE](LICENSE).
