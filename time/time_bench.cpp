#include <benchmark/benchmark.h>

#include <chrono>
#include <cstdio>
#include <cstring>
#include <random>
#include <vector>

#include "time/algorithms/benjoffe.hpp"
#include "time/algorithms/consroe.hpp"
#include "time/algorithms/neri.hpp"
#include "time/algorithms/traditional.hpp"

#ifdef __clang__
#define NOVECTOR _Pragma("clang loop vectorize(disable)")
#define TRYVECTOR _Pragma("clang loop vectorize(enable)")
#else
#define NOVECTOR _Pragma("GCC novector")
#define TRYVECTOR _Pragma("GCC ivdep")
#endif

static size_t COUNT = 1 << 16;
static std::vector<uint32_t> times;
static std::vector<uint32_t> times_ms;
static std::vector<uint64_t> times_ns;
static bool latency_mode = false;
static bool vector_mode  = false;

// Scratch output arrays: results are written here instead of through a
// per-element DoNotOptimize, so the loop isn't serialized by a memory
// barrier on every iteration -- needed for vector_mode to stay vectorizable,
// and for scalar (throughput) mode to let independent iterations actually
// overlap on the out-of-order pipeline instead of being fenced apart.
static std::vector<TIME_S>       results_s;
static std::vector<TIME_SUBUNIT> results_subunit;
static std::vector<uint32_t>     results_u32;

static void init_times() {
    std::mt19937 rng(0xDEADBEEF);
    std::uniform_int_distribution<uint32_t> dist(0, 86399);
    times.resize(COUNT);
    for (auto& t : times) t = dist(rng);
    if (latency_mode) {
        // add one leap in the middle:
        times[COUNT/2] = 86400; // leap
    }
}

static void init_times_ms() {
    std::mt19937 rng(0xDEADBEEF);
    std::uniform_int_distribution<uint32_t> dist(0, 86399'000);
    times_ms.resize(COUNT);
    for (auto& t : times_ms) t = dist(rng);
}

static void init_times_ns() {
    std::mt19937_64 rng(0xDEADBEEF);
    std::uniform_int_distribution<uint64_t> dist(0, 86399ULL * 1'000'000'000ULL + 999'999'999ULL);
    times_ns.resize(COUNT);
    for (auto& t : times_ns) t = dist(rng);
}

static void init_results() {
    results_s.resize(COUNT);
    results_subunit.resize(COUNT);
    results_u32.resize(COUNT);
}

// Vector- and scalar-mode loops live in their own noinline functions: LLVM's
// loop vectorizer fails to establish a trip count / array bounds for these
// loops when they're embedded directly in the large latency/vector/scalar
// branch inside the benchmark function (alongside Google Benchmark's own
// state iteration) -- pulling each loop out into an isolated function
// restores its ability to analyze (and, for vecloop, vectorize) it. Both
// write into an output array rather than DoNotOptimize-ing each element, so
// the loop isn't serialized by a memory barrier every iteration -- required
// for vecloop to stay vectorizable, and for scalarloop to let independent
// iterations actually overlap on the out-of-order pipeline the way a real
// caller's use of these functions would.
#define ARRAYLOOP(name, suffix, pragma, expr, in_vec, out_vec, T_in)            \
__attribute__((noinline)) static void name##_##suffix() {                       \
    const T_in*    in  = in_vec.data();                                         \
    auto*          out = out_vec.data();                                        \
    const size_t   n   = in_vec.size();                                         \
pragma                                                                           \
    for (size_t i = 0; i < n; ++i) {                                            \
        T_in t = in[i];                                                         \
        out[i] = expr;                                                          \
    }                                                                           \
    benchmark::DoNotOptimize(out);                                              \
}

#define VECLOOP(name, expr, in_vec, out_vec, T_in) \
    ARRAYLOOP(name, vecloop, TRYVECTOR, expr, in_vec, out_vec, T_in)

// Mirrors BENCH's scalar/latency/vector split so the baseline is a floor
// *for whichever mode it's being compared against* -- a plain always-scalar
// "acc ^= t" would report a throughput number even under -latency/-vector,
// making it a meaningless floor there (missing the forced t^=carry
// dependency injection and DoNotOptimize barrier that every real algorithm's
// latency loop pays for, and never actually vectorizing under -vector).
__attribute__((noinline)) static void bench_baseline_scalarloop() {
    const uint32_t* in  = times.data();
    uint32_t*       out = results_u32.data();
    const size_t    n   = times.size();
NOVECTOR
    for (size_t i = 0; i < n; ++i)
        out[i] = in[i];
    benchmark::DoNotOptimize(out);
}

__attribute__((noinline)) static void bench_baseline_latencyloop() {
    uint32_t carry = 0;
NOVECTOR
    for (uint32_t t : times) {
        t ^= carry;
        carry ^= t;
        benchmark::DoNotOptimize(carry);
    }
}

__attribute__((noinline)) static void bench_baseline_vecloop() {
    const uint32_t* in = times.data();
    const size_t    n  = times.size();
    uint32_t acc = 0;
TRYVECTOR
    for (size_t i = 0; i < n; ++i)
        acc ^= in[i];
    benchmark::DoNotOptimize(acc);
}

static void bench_baseline(benchmark::State& state) {
    auto t0 = std::chrono::steady_clock::now();
    for (auto _ : state) {
        if (latency_mode)      bench_baseline_latencyloop();
        else if (vector_mode)  bench_baseline_vecloop();
        else                    bench_baseline_scalarloop();
    }
    double ns = std::chrono::duration<double, std::nano>(
        std::chrono::steady_clock::now() - t0).count();
    state.counters["ns/t"] = ns / (double(state.iterations()) * double(COUNT));
}
BENCHMARK(bench_baseline);

// Scalar and latency loops get the same isolation treatment as VECLOOP
// above, and for the same reason: pulled out of the huge benchmark
// function (which otherwise inlines Google Benchmark's own assert()-guarded
// iteration bookkeeping right next to the algorithm call), each loop body
// is small and self-contained again, which is what lets clang correctly
// strength-reduce a compile-time-constant division into a multiply-shift.
// Isolating the whole per-state-iteration loop (rather than putting a
// noinline boundary around each element) keeps the added call overhead to
// one function call per COUNT elements, not one per element -- otherwise
// the fixed call/return cost dominates the very sub-nanosecond differences
// these benchmarks exist to show.
#define SCALARLOOP(name, expr, in_vec, out_vec, T_in) \
    ARRAYLOOP(name, scalarloop, NOVECTOR, expr, in_vec, out_vec, T_in)

// Each input = array value + previous result, forcing a serial dependency
// chain that measures per-call latency rather than throughput.
#define LATENCYLOOP(name, expr, in_vec, T_in, carry_expr, extra_stmt)           \
__attribute__((noinline)) static void name##_latencyloop() {                    \
    uint32_t carry = 0;                                                         \
NOVECTOR                                                                         \
    for (T_in t : in_vec) {                                                     \
        t ^= carry;                                                             \
        auto r = expr;                                                          \
        extra_stmt                                                              \
        carry ^= carry_expr;                                                    \
        benchmark::DoNotOptimize(carry);                                        \
    }                                                                           \
}

#define BENCH(name, expr)                                                        \
VECLOOP(name, expr, times, results_s, uint32_t)                                 \
SCALARLOOP(name, expr, times, results_s, uint32_t)                             \
LATENCYLOOP(name, expr, times, uint32_t, r.hour ^ r.min ^ r.sec, )              \
static void name(benchmark::State& state) {                                      \
    auto t0 = std::chrono::steady_clock::now();                                  \
    for (auto _ : state) {                                                       \
        if (latency_mode)      name##_latencyloop();                            \
        else if (vector_mode)  name##_vecloop();                                \
        else                    name##_scalarloop();                            \
    }                                                                            \
    double ns = std::chrono::duration<double, std::nano>(                        \
        std::chrono::steady_clock::now() - t0).count();                          \
    state.counters["ns/t"] = ns / (double(state.iterations()) * double(COUNT));  \
}                                                                                \
BENCHMARK(name);

// BENCH_MS/BENCH_CS/BENCH_NS were identical in shape (only the input vector
// and its element type differed) -- merged into one implementation, with
// BENCH_SUBSEC/BENCH_NS as thin call-site aliases so existing invocations
// don't need to change.
#define BENCH_SUBSEC_IMPL(name, expr, in_vec, T_in)                             \
VECLOOP(name, expr, in_vec, results_subunit, T_in)                              \
SCALARLOOP(name, expr, in_vec, results_subunit, T_in)                          \
LATENCYLOOP(name, expr, in_vec, T_in, r.hour ^ r.min ^ r.sec ^ r.sub, )         \
static void name(benchmark::State& state) {                                      \
    auto t0 = std::chrono::steady_clock::now();                                  \
    for (auto _ : state) {                                                       \
        if (latency_mode)      name##_latencyloop();                            \
        else if (vector_mode)  name##_vecloop();                                \
        else                    name##_scalarloop();                            \
    }                                                                            \
    double ns = std::chrono::duration<double, std::nano>(                        \
        std::chrono::steady_clock::now() - t0).count();                          \
    state.counters["ns/t"] = ns / (double(state.iterations()) * double(COUNT));  \
}                                                                                \
BENCHMARK(name);

#define BENCH_SUBSEC(name, expr) BENCH_SUBSEC_IMPL(name, expr, times_ms, uint32_t)
#define BENCH_NS(name, expr)     BENCH_SUBSEC_IMPL(name, expr, times_ns, uint64_t)

BENCH(bench_benjoffe_v1,     time_benjoffe_v1(t));
BENCH(bench_benjoffe_v1_fp,  time_benjoffe_v1_fp(t));
BENCH(bench_benjoffe_v2,     time_benjoffe_v2(t));
BENCH(bench_benjoffe_v2_64,  time_benjoffe_v2_64(t));
BENCH(bench_benjoffe_v3,     time_benjoffe_v3(t));
BENCH(bench_benjoffe_v3b,    time_benjoffe_v3b(t));
BENCH(bench_benjoffe_v3c,    time_benjoffe_v3c(t));
BENCH(bench_benjoffe_v3_64,  time_benjoffe_v3_64(t));
BENCH(bench_benjoffe_v3_64b,  time_benjoffe_v3_64b(t));
BENCH(bench_benjoffe_v4,     time_benjoffe_v4(t));

BENCH(bench_traditional_leap1,     time_traditional_leap1(t));
BENCH(bench_traditional_leap2,     time_traditional_leap2(t));
BENCH(bench_benjoffe_leap0,  time_benjoffe_leap0(t));
BENCH(bench_benjoffe_leap1,  time_benjoffe_leap1(t));
BENCH(bench_benjoffe_leap2,  time_benjoffe_leap2(t));

BENCH(bench_traditional1,    time_traditional1(t));
BENCH(bench_traditional1_fp, time_traditional1_fp(t));
BENCH(bench_traditional2,    time_traditional2(t));
BENCH(bench_traditional3,    time_traditional3(t));
BENCH(bench_neri,            time_neri(t));
BENCH(bench_neri_fp,         time_neri_fp(t));
BENCH(bench_consroe_1,       time_consroe_1(t));
BENCH(bench_consroe_2,       time_consroe_2(t));

BENCH_SUBSEC(bench_traditional_ds1, time_traditional_ds1(t));
BENCH_SUBSEC(bench_traditional_ds2, time_traditional_ds2(t));
BENCH_SUBSEC(bench_benjoffe_ds1,    time_benjoffe_ds1(t));

BENCH_SUBSEC(bench_traditional_cs1, time_traditional_cs1(t));
BENCH_SUBSEC(bench_traditional_cs2, time_traditional_cs2(t));
BENCH_SUBSEC(bench_benjoffe_cs1,    time_benjoffe_cs1(t));
BENCH_SUBSEC(bench_benjoffe_cs2,    time_benjoffe_cs2(t));

BENCH_SUBSEC(bench_traditional_ms1,     time_traditional_ms1(t));
BENCH_SUBSEC(bench_traditional_ms2,     time_traditional_ms2(t));
BENCH_SUBSEC(bench_benjoffe_ms1,  time_benjoffe_ms1(t));
BENCH_SUBSEC(bench_benjoffe_ms2, time_benjoffe_ms2(t));

BENCH_NS(bench_traditional_ns1,     time_traditional_ns1(t));
BENCH_NS(bench_traditional_ns2,     time_traditional_ns2(t));
BENCH_NS(bench_benjoffe_ns1, time_benjoffe_ns1(t));
BENCH_NS(bench_benjoffe_ns2, time_benjoffe_ns2(t));
BENCH_NS(bench_benjoffe_ns3, time_benjoffe_ns3(t));
BENCH_NS(bench_benjoffe_ns4, time_benjoffe_ns4(t));
BENCH_NS(bench_benjoffe_ns5, time_benjoffe_ns5(t));
BENCH_NS(bench_benjoffe_ns6, time_benjoffe_ns6(t));

int main(int argc, char** argv) {
    std::vector<char*> bm_argv;
    bm_argv.push_back(argv[0]);

    auto parse_val = [&](int& i, const char* key) -> const char* {
        size_t klen = std::strlen(key);
        if (std::strncmp(argv[i], key, klen) == 0) {
            if (argv[i][klen] == '=') return argv[i] + klen + 1;
            if (argv[i][klen] == '\0' && i + 1 < argc) return argv[++i];
        }
        return nullptr;
    };

    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "-latency") == 0)
            latency_mode = true;
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
        std::fprintf(stderr, "\x1b[31m-latency and -vector are mutually exclusive "
                              "(each BENCH function only has one carry chain / "
                              "one vecloop; there's no combined latency+vector path)\x1b[0m\n");
        return 1;
    }

    init_times();
    init_times_ms();
    init_times_ns();
    init_results();

    int bm_argc = int(bm_argv.size());
    benchmark::Initialize(&bm_argc, bm_argv.data());
    if (benchmark::ReportUnrecognizedArguments(bm_argc, bm_argv.data())) return 1;
    benchmark::RunSpecifiedBenchmarks();
    benchmark::Shutdown();
    return 0;
}
