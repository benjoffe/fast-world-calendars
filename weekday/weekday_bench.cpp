#include <benchmark/benchmark.h>

#include <chrono>
#include <cstdio>
#include <cstring>
#include <limits>
#include <random>
#include <vector>

#include "weekday/algorithms/basic.hpp"
#include "weekday/algorithms/hinnant.hpp"
#include "weekday/algorithms/neri.hpp"
#include "weekday/algorithms/benjoffe.hpp"
#include "weekday/algorithms/benjoffe_extra.hpp"

#ifdef __clang__
#define NOVECTOR _Pragma("clang loop vectorize(disable)")
#else
#define NOVECTOR _Pragma("GCC novector")
#endif

static size_t COUNT = 1 << 16;
static std::vector<int32_t> dates;
static bool latency_mode = false;
static bool batch_mode   = false;

static void init_dates() {
    std::mt19937 rng(0xDEADBEEF);
    std::uniform_int_distribution<int32_t> dist(
        std::numeric_limits<int32_t>::min(),
        std::numeric_limits<int32_t>::max());
    dates.resize(COUNT);
    for (auto& d : dates) d = dist(rng);
}

#define BENCH(name, expr)                                                        \
static void name(benchmark::State& state) {                                      \
    auto t0 = std::chrono::steady_clock::now();                                  \
    for (auto _ : state) {                                                       \
        int32_t carry = 0;                                                       \
        if (latency_mode) {                                                      \
            /* Each input = array value + previous result, forcing a serial      \
               dependency chain that measures per-call latency. */               \
NOVECTOR                                                                         \
            for (int32_t d : dates) {                                            \
                d ^= carry;                                                      \
                int32_t r = (expr);                                              \
                benchmark::DoNotOptimize(r);                                     \
                carry = r;                                                       \
            }                                                                    \
        } else if (batch_mode) {                                                 \
            /* 3 calls per load: prevents fast algorithms from appearing          \
               memory-bound when their compute is hidden by the load latency. */ \
NOVECTOR                                                                         \
            for (int32_t d_base : dates) {                                       \
                { int32_t d = d_base;     int32_t r = (expr); benchmark::DoNotOptimize(r); } \
                { int32_t d = d_base ^ 1; int32_t r = (expr); benchmark::DoNotOptimize(r); } \
                { int32_t d = d_base ^ 2; int32_t r = (expr); benchmark::DoNotOptimize(r); } \
            }                                                                    \
        } else {                                                                 \
NOVECTOR                                                                         \
            for (int32_t d : dates) {                                            \
                int32_t r = (expr);                                              \
                benchmark::DoNotOptimize(r);                                     \
            }                                                                    \
        }                                                                        \
    }                                                                            \
    double ns = std::chrono::duration<double, std::nano>(                        \
        std::chrono::steady_clock::now() - t0).count();                          \
    double calls = double(state.iterations()) * double(COUNT) * (batch_mode ? 3.0 : 1.0); \
    state.counters["ns/d"] = ns / calls;                                         \
}                                                                                \
BENCHMARK(name);

BENCH(bench_baseline,            d);

BENCH(bench_naive,                weekday_naive(d));
BENCH(bench_hinnant32,            weekday_hinnant32(d));
BENCH(bench_rust_compiled,        weekday_rust_compiled(d));
BENCH(bench_neri32,               weekday_neri32(d));
BENCH(bench_neri64,               weekday_neri64(d));

BENCH(bench_32unix_narrow,        get_weekday_32unix_narrow(d));
BENCH(bench_32unix_medium,        get_weekday_32unix_medium(d));
BENCH(bench_32unix_widen,         get_weekday_32unix_widen(d));
BENCH(bench_32unix,               get_weekday_32unix(d));
BENCH(bench_32unix_v2,            get_weekday_32unix_v2(d));
BENCH(bench_32unix_v3,            get_weekday_32unix_v3(d));
BENCH(bench_1st_attempt,          get_weekday_1st_attempt(d));

BENCH(bench_32unix_forced_asm,    get_weekday_32unix_forced_asm(d));
BENCH(bench_32unix_v2_forced_asm, get_weekday_32unix_v2_forced_asm(d));
BENCH(bench_32unix_v3_forced_asm, get_weekday_32unix_v3_forced_asm(d));

BENCH(bench_64unix,               get_weekday_64unix(d));
BENCH(bench_64unix_narrow,        get_weekday_64unix_narrow(d));
BENCH(bench_16unix,               get_weekday_16unix(d));
BENCH(bench_8unix,                get_weekday_8unix(d));


int main(int argc, char** argv) {
    std::vector<char*> bm_argv;
    bm_argv.push_back(argv[0]);

    auto parse_val = [&](int& i, const char* key) -> const char* {
        size_t klen = std::strlen(key);
        if (std::strncmp(argv[i], key, klen) == 0) {
            if (argv[i][klen] == '=' ) return argv[i] + klen + 1;
            if (argv[i][klen] == '\0' && i + 1 < argc) return argv[++i];
        }
        return nullptr;
    };

    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "-latency") == 0)
            latency_mode = true;
        else if (std::strcmp(argv[i], "-batch") == 0)
            batch_mode = true;
        else if (const char* v = parse_val(i, "-count"))
            COUNT = std::stoul(v);
        else if (const char* v = parse_val(i, "-repeat")) {
            static char buf[64];
            std::snprintf(buf, sizeof(buf), "--benchmark_repetitions=%s", v);
            bm_argv.push_back(buf);
        } else
            bm_argv.push_back(argv[i]);
    }

    init_dates();

    int bm_argc = int(bm_argv.size());
    benchmark::Initialize(&bm_argc, bm_argv.data());
    if (benchmark::ReportUnrecognizedArguments(bm_argc, bm_argv.data())) return 1;
    benchmark::RunSpecifiedBenchmarks();
    benchmark::Shutdown();
    return 0;
}
