#include <benchmark/benchmark.h>

#include <chrono>
#include <cstdio>
#include <cstring>
#include <random>
#include <vector>

#include "easter/algorithms/anonymous.hpp"
#include "easter/algorithms/iantaylor.hpp"
#include "easter/algorithms/benjoffe.hpp"
#include "easter/algorithms/dirkloss.hpp"
#include "easter/algorithms/reingold_dershowitz.hpp"

#ifdef __clang__
#define NOVECTOR _Pragma("clang loop vectorize(disable)")
#define TRYVECTOR _Pragma("clang loop vectorize(enable)")
#else
#define NOVECTOR _Pragma("GCC novector")
#define TRYVECTOR _Pragma("GCC ivdep")
#endif

static size_t COUNT = 1 << 16;
static std::vector<uint32_t> years;
static bool latency_mode = false;
static bool batch_mode   = false;
static bool vector_mode  = false;

static void init_years() {
    std::mt19937 rng(0xDEADBEEF);
    std::uniform_int_distribution<uint32_t> dist(0, 65535);
    years.resize(COUNT);
    for (auto& y : years) y = dist(rng);
}

#define BENCH(name, expr)                                                        \
static void name(benchmark::State& state) {                                      \
    auto t0 = std::chrono::steady_clock::now();                                  \
    for (auto _ : state) {                                                       \
        uint32_t carry = 0;                                                      \
        if (latency_mode) {                                                      \
NOVECTOR                                                                         \
            for (uint32_t y : years) {                                           \
                y ^= carry;                                                      \
                uint32_t r = (expr);                                             \
                benchmark::DoNotOptimize(r);                                     \
                carry = r;                                                       \
            }                                                                    \
        } else if (batch_mode) {                                                 \
NOVECTOR                                                                         \
            for (uint32_t y_base : years) {                                      \
                { uint32_t y = y_base;     uint32_t r = (expr); benchmark::DoNotOptimize(r); } \
                { uint32_t y = y_base ^ 1; uint32_t r = (expr); benchmark::DoNotOptimize(r); } \
                { uint32_t y = y_base ^ 2; uint32_t r = (expr); benchmark::DoNotOptimize(r); } \
            }                                                                    \
        } else if (vector_mode) {                                                \
            uint32_t acc = 0;                                                    \
TRYVECTOR                                                                        \
            for (uint32_t y : years) {                                           \
                uint32_t r = (expr);                                             \
                acc ^= r;                                                        \
            }                                                                    \
            benchmark::DoNotOptimize(acc);                                       \
        } else {                                                                 \
NOVECTOR                                                                         \
            for (uint32_t y : years) {                                           \
                uint32_t r = (expr);                                             \
                benchmark::DoNotOptimize(r);                                     \
            }                                                                    \
        }                                                                        \
    }                                                                            \
    double ns = std::chrono::duration<double, std::nano>(                        \
        std::chrono::steady_clock::now() - t0).count();                          \
    double calls = double(state.iterations()) * double(COUNT) * (batch_mode ? 3.0 : 1.0); \
    state.counters["ns/y"] = ns / calls;                                         \
}                                                                                \
BENCHMARK(name);

BENCH(bench_baseline,                  y)
BENCH(bench_reingold_dershowitz,       easter_reingold_dershowitz(y))
BENCH(bench_benjoffe,                  easter_benjoffe(y))
BENCH(bench_benjoffe_readable,         easter_benjoffe_readable(y))
BENCH(bench_benjoffe_narrow,           easter_benjoffe_narrow(y))
BENCH(bench_iantaylor,                 easter_iantaylor(y))
BENCH(bench_dirkloss,                  easter_dirkloss(y))
BENCH(bench_anonymous,                 easter_anonymous(y))
BENCH(bench_anonymous_unsigned,        easter_anonymous_unsigned(y))

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
        else if (std::strcmp(argv[i], "-vector") == 0)
            vector_mode = true;
        else if (const char* v = parse_val(i, "-count"))
            COUNT = std::stoul(v);
        else if (const char* v = parse_val(i, "-repeat")) {
            static char buf[64];
            std::snprintf(buf, sizeof(buf), "--benchmark_repetitions=%s", v);
            bm_argv.push_back(buf);
        } else
            bm_argv.push_back(argv[i]);
    }

    if (latency_mode && vector_mode) {
        std::fprintf(stderr, "\x1b[31m-latency and -vector are mutually exclusive\x1b[0m\n");
        return 1;
    }

    init_years();

    int bm_argc = int(bm_argv.size());
    benchmark::Initialize(&bm_argc, bm_argv.data());
    if (benchmark::ReportUnrecognizedArguments(bm_argc, bm_argv.data())) return 1;
    benchmark::RunSpecifiedBenchmarks();
    benchmark::Shutdown();
    return 0;
}
