# fast-world-calendars — weekday

Fast C implementations of weekday calculation from a Rata-Die (days since 1 Jan 1970).

This will soon be used as reference material in a blog post at https://www.benjoffe.com/

## Algorithms

Standard functions return `0=Sun … 6=Sat`.

Functions with the term "iso" included return `1=Mon … 7=Sun`

## Build

Requires: CMake ≥ 3.14, C++26 compiler, internet access on first build (fetches Google Benchmark).

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
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

The latency result is the most meaningful for typical use, where the weekday is needed before the next computation can proceed.

Additional flags: `-count N` (array size, default 65536), `-repeat N` (benchmark repetitions).

## Attribution

The Hinnant and Neri benchmarks are independent reimplementations of their published algorithms — see the respective header files for sources.

## License

MIT — Copyright 2026 Ben Joffe — see [LICENSE](LICENSE).
