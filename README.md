# fast-world-calendars — weekday

Fast C++ implementations of weekday calculation from a Rata-Die (days since 1 Jan 1970).

This repo serves are reference material for the blog post at https://www.benjoffe.com/fast-day-of-week

## Algorithms

Standard functions return `0=Sun … 6=Sat`.

Functions with the term "iso" included return `1=Mon … 7=Sun`

## Build

Requires: CMake ≥ 3.14, C++20 compiler, internet access on first build (fetches Google Benchmark).

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j && ./build/bin/weekday_bench
```

## Build on GCC

```sh
cmake -S . -B build-gcc -DCMAKE_C_COMPILER=gcc-15 -DCMAKE_CXX_COMPILER=g++-15
cmake --build build-gcc -j && ./build-gcc/bin/weekday_bench
```

## Test

Verifies correctness over the full valid range of each algorithm, compared against the naive reference:

```sh
./build/bin/weekday_test
```

## Benchmark

```sh
./build/bin/weekday_bench
```

Three modes expose different aspects of performance:

| Flag | Measures |
|---|---|
| *(none)* | Throughput — independent calls, CPU free to pipeline |
| `-latency` | Latency — serial dependency chain, each result feeds the next input |
| `-batch` | Batch throughput — 3 calls per load, prevents fast algorithms appearing memory-bound |

Additional flags: `-count N` (array size, default 65536), `-repeat N` (benchmark repetitions).

## Attribution

The Hinnant and Neri benchmarks are independent reimplementations of their published algorithms — see the respective header files for sources.

## License

MIT — Copyright 2026 Ben Joffe — see [LICENSE](LICENSE).
