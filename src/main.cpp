// main.cpp — harness: generators, metrics (time / comparisons / aux memory),
// selftest, Ford–Johnson count validation, bench CLI.
#include "algos.h"

#include <cinttypes>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <random>
#include <string>

#ifndef SORTLAB_BUILD_ID
#define SORTLAB_BUILD_ID "dev"
#endif
#ifndef SORTLAB_TRACK_ALLOCATIONS
#define SORTLAB_TRACK_ALLOCATIONS 1
#endif

using u64 = uint64_t;

uint64_t lab::g_comps = 0;
uint64_t lab::g_merge_cost = 0;
size_t lab::g_small_merge = 96;
size_t lab::g_fj_run_thresh = 0;
size_t lab::g_fj_largest_block = 0;
size_t lab::g_fj_scratch_cap = 0;
uint64_t lab::g_gate_probe_comps = 0;
int lab::g_gate_choice = 0;

// ---------------------------------------------------------------------------
// auxiliary-memory tracking: every heap allocation in the process goes
// through these; the harness reads peak-minus-baseline around each sort call.
// ---------------------------------------------------------------------------
static size_t g_alloc_cur = 0;
static size_t g_alloc_peak = 0;

#if SORTLAB_TRACK_ALLOCATIONS
static void* tracked_alloc(size_t sz) {
    void* p = std::malloc(sz + 16);
    if (!p) std::abort();
    *(size_t*)p = sz;
    g_alloc_cur += sz;
    if (g_alloc_cur > g_alloc_peak) g_alloc_peak = g_alloc_cur;
    return (char*)p + 16;
}
static void tracked_free(void* p) {
    if (!p) return;
    char* q = (char*)p - 16;
    g_alloc_cur -= *(size_t*)q;
    std::free(q);
}
static void* tracked_alloc_nothrow(size_t sz) noexcept {
    void* p = std::malloc(sz + 16);
    if (!p) return nullptr;
    *(size_t*)p = sz;
    g_alloc_cur += sz;
    if (g_alloc_cur > g_alloc_peak) g_alloc_peak = g_alloc_cur;
    return (char*)p + 16;
}
void* operator new(size_t sz) { return tracked_alloc(sz); }
void* operator new[](size_t sz) { return tracked_alloc(sz); }
void* operator new(size_t sz, const std::nothrow_t&) noexcept { return tracked_alloc_nothrow(sz); }
void* operator new[](size_t sz, const std::nothrow_t&) noexcept { return tracked_alloc_nothrow(sz); }
void operator delete(void* p) noexcept { tracked_free(p); }
void operator delete[](void* p) noexcept { tracked_free(p); }
void operator delete(void* p, size_t) noexcept { tracked_free(p); }
void operator delete[](void* p, size_t) noexcept { tracked_free(p); }
void operator delete(void* p, const std::nothrow_t&) noexcept { tracked_free(p); }
void operator delete[](void* p, const std::nothrow_t&) noexcept { tracked_free(p); }
#endif

static uint64_t now_ns() {
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec;
}

// ---------------------------------------------------------------------------
// input distributions
// ---------------------------------------------------------------------------
static std::vector<u64> gen_dist(const std::string& d, size_t n, u64 seed) {
    std::mt19937_64 rng(seed ^ 0x9E3779B97F4A7C15ull);
    std::vector<u64> v(n);
    if (n == 0) return v;
    if (d == "random") {                       // random permutation of 0..n-1
        for (size_t i = 0; i < n; ++i) v[i] = i;
        std::shuffle(v.begin(), v.end(), rng);
    } else if (d == "uniform64") {
        for (size_t i = 0; i < n; ++i) v[i] = rng();
    } else if (d == "uniform32") {
        for (size_t i = 0; i < n; ++i) v[i] = rng() & 0xFFFFFFFFULL;
    } else if (d == "highbits32") {
        for (size_t i = 0; i < n; ++i) v[i] = (rng() & 0xFFFFFFFFULL) << 32;
    } else if (d.rfind("dup", 0) == 0) {   // K distinct values via rng() % K
        // For dyadic K this is bit-identical to the former rng() & (K-1)
        // masks, so committed dup2/dup16/dup256 rows reproduce exactly; the
        // modulo bias for other K is <= K/2^64.
        char* end = nullptr;
        unsigned long long k = std::strtoull(d.c_str() + 3, &end, 10);
        if (end == d.c_str() + 3 || *end != '\0' || k < 2 ||
            k > 1000000000ull) {
            std::fprintf(stderr, "unknown dist %s\n", d.c_str());
            std::exit(2);
        }
        for (size_t i = 0; i < n; ++i) v[i] = rng() % k;
    } else if (d == "equal") {
        for (size_t i = 0; i < n; ++i) v[i] = 42;
    } else if (d == "sorted") {
        for (size_t i = 0; i < n; ++i) v[i] = i;
    } else if (d == "reversed") {
        for (size_t i = 0; i < n; ++i) v[i] = n - 1 - i;
    } else if (d == "runs32" || d == "runs1024") {
        size_t L = (d == "runs32") ? 32 : 1024;
        for (size_t i = 0; i < n; ++i) v[i] = i;
        std::shuffle(v.begin(), v.end(), rng);
        for (size_t i = 0; i < n; i += L)
            std::sort(v.begin() + i, v.begin() + std::min(n, i + L));
    } else if (d == "nearly1") {               // sorted + n/100 transpositions
        for (size_t i = 0; i < n; ++i) v[i] = i;
        for (size_t s = 0; s < n / 100 + 1; ++s)
            std::swap(v[rng() % n], v[rng() % n]);
    } else if (d == "tail10") {                // 90% sorted, 10% random tail
        for (size_t i = 0; i < n; ++i) v[i] = i;
        for (size_t i = n - n / 10; i < n; ++i) v[i] = rng() % n;
    } else if (d == "saw13") {
        for (size_t i = 0; i < n; ++i) v[i] = i % 13;
    } else if (d == "organpipe") {
        for (size_t i = 0; i < n; ++i) v[i] = std::min(i, n - 1 - i);
    } else if (d.rfind("disp", 0) == 0) {      // rank + gaussian noise (sigma)
        double sigma = std::atof(d.c_str() + 4);
        std::normal_distribution<double> gau(0.0, sigma);
        std::vector<std::pair<double, u64>> tmp(n);
        for (size_t i = 0; i < n; ++i) tmp[i] = {(double)i + gau(rng), (u64)i};
        std::sort(tmp.begin(), tmp.end(),
                  [](const auto& x, const auto& y) { return x.first < y.first; });
        for (size_t i = 0; i < n; ++i) v[i] = tmp[i].second;
    } else if (d.rfind("outliers", 0) == 0) {
        char* end = nullptr;
        const unsigned long long requested = std::strtoull(d.c_str() + 8, &end, 10);
        if (end == d.c_str() + 8 || *end != '\0' || requested > 1000000000ull) {
            std::fprintf(stderr, "unknown dist %s\n", d.c_str());
            std::exit(2);
        }
        const size_t k = std::min<size_t>(n, static_cast<size_t>(requested));
        std::vector<unsigned char> marked(n, 0);
        std::vector<size_t> positions(n);
        for (size_t i = 0; i < n; ++i) positions[i] = i;
        std::shuffle(positions.begin(), positions.end(), rng);
        for (size_t i = 0; i < k; ++i) marked[positions[i]] = 1;
        std::vector<u64> exceptional(k);
        for (size_t i = 0; i < k; ++i) exceptional[i] = n - k + i;
        std::shuffle(exceptional.begin(), exceptional.end(), rng);
        size_t ordinary = 0, special = 0;
        for (size_t i = 0; i < n; ++i)
            v[i] = marked[i] ? exceptional[special++] : ordinary++;
    } else if (d.rfind("outpct", 0) == 0) {
        char* end = nullptr;
        const unsigned long long pct = std::strtoull(d.c_str() + 6, &end, 10);
        if (end == d.c_str() + 6 || *end != '\0' || pct == 0 || pct > 100) {
            std::fprintf(stderr, "unknown dist %s\n", d.c_str());
            std::exit(2);
        }
        const size_t percent = static_cast<size_t>(pct);
        const size_t k = (n / 100) * percent + ((n % 100) * percent) / 100;
        std::vector<unsigned char> marked(n, 0);
        std::vector<size_t> positions(n);
        for (size_t i = 0; i < n; ++i) positions[i] = i;
        std::shuffle(positions.begin(), positions.end(), rng);
        for (size_t i = 0; i < k; ++i) marked[positions[i]] = 1;
        std::vector<u64> exceptional(k);
        for (size_t i = 0; i < k; ++i) exceptional[i] = n - k + i;
        std::shuffle(exceptional.begin(), exceptional.end(), rng);
        size_t ordinary = 0, special = 0;
        for (size_t i = 0; i < n; ++i)
            v[i] = marked[i] ? exceptional[special++] : ordinary++;
    } else {
        std::fprintf(stderr, "unknown dist %s\n", d.c_str());
        std::exit(2);
    }
    return v;
}

// ---------------------------------------------------------------------------
// algorithm registry
// ---------------------------------------------------------------------------
enum Algo {
    A_STD_SORT, A_STD_STABLE, A_HEAP, A_QMO3, A_DUAL, A_BLQ, A_MTD,
    A_TIM, A_POW, A_POW_FIXED, A_POW_FJ, A_PINGPONG_POW, A_DIRECTIONAL,
    A_SHELL_LEARNED, A_SHELL_CIURA, A_SHELL_TOKUDA, A_SKELETON,
    A_HFJ8, A_HFJ12, A_HFJ16, A_HFJ21, A_HFJ32, A_HFJ42,
    A_HFJ56, A_HFJ62, A_HFJ64, A_HFJA62,
    A_HFJ85, A_HFJ123, A_HFJ128, A_HFJAUTO, A_HFJAUTO256, A_HFJAUTO512,
    A_HFJAUTO1024, A_HFJAUTO2048, A_HGATE, A_HLADDER, A_HRUNGATE,
    A_HBIN21, A_HBIN32, A_HBIN62, A_HBIN123, A_INV_BINSERT, A_HINV_GATE,
    A_WINDOW_HEAP, A_DELETION_BACKBONE, A_DELETION_BACKBONE_ROUTE,
    A_DELETION_BACKBONE_PRESERVE, A_DELETION_BACKBONE_ROTATE,
    A_HBACKBONE_GATE, A_HDESCENT_PORTFOLIO, A_HQUANTILE_BACKBONE,
    A_HGENERAL_PORTFOLIO, A_HGENERAL_PREFIX, A_HQUANTILE_CONCAT,
    A_HCERTIFIED_PORTFOLIO, A_PDQ, A_PDQ_BL,
#ifdef SORTLAB_HAVE_IPS4O
    A_IPS4O,
#endif
#ifdef SORTLAB_HAVE_X86_SIMD
    A_X86_SIMD,
#endif
    A_RADIX,
};
struct AlgoInfo {
    const char* name; Algo id; bool stable; bool comparison;
    bool native_numeric = false; // intrinsic comparisons bypass Counting<C>
};
static const AlgoInfo ALGOS[] = {
    {"std_sort",    A_STD_SORT,   false, true},
    {"std_stable",  A_STD_STABLE, true,  true},
    {"heapsort",    A_HEAP,       false, true},
    {"quick_mo3",   A_QMO3,       false, true},
    {"dual_pivot",  A_DUAL,       false, true},
    {"bl_quick",    A_BLQ,        false, true},
    {"merge_td",    A_MTD,        true,  true},
    {"timsort",     A_TIM,        true,  true},
    {"powersort",   A_POW,        true,  true},
    {"powersort_fixed", A_POW_FIXED, true, true},
    {"powersort_fj", A_POW_FJ,    false, true},
    {"pingpong_powersort", A_PINGPONG_POW, true, true},
    {"directional_mergesort", A_DIRECTIONAL, true, true},
    {"shell_learned", A_SHELL_LEARNED, false, true},
    {"shell_ciura", A_SHELL_CIURA, false, true},
    {"shell_tokuda", A_SHELL_TOKUDA, false, true},
    {"skeleton_sort", A_SKELETON, true, true},
    {"hybrid_fj8",  A_HFJ8,       false, true},
    {"hybrid_fj12", A_HFJ12,      false, true},
    {"hybrid_fj16", A_HFJ16,      false, true},
    {"hybrid_fj21", A_HFJ21,      false, true},
    {"hybrid_fj32", A_HFJ32,      false, true},
    {"hybrid_fj42", A_HFJ42,      false, true},
    {"hybrid_fj56", A_HFJ56,      false, true},
    {"hybrid_fj62", A_HFJ62,      false, true},
    {"hybrid_fj64", A_HFJ64,      false, true},
    {"hybrid_fja62", A_HFJA62,    false, true},
    {"hybrid_fj85",  A_HFJ85,     false, true},
    {"hybrid_fj123", A_HFJ123,    false, true},
    {"hybrid_fj128", A_HFJ128,    false, true},
    {"hybrid_fjauto", A_HFJAUTO,  false, true},
    {"hybrid_fjauto256", A_HFJAUTO256, false, true},
    {"hybrid_fjauto512", A_HFJAUTO512, false, true},
    {"hybrid_fjauto1024", A_HFJAUTO1024, false, true},
    {"hybrid_fjauto2048", A_HFJAUTO2048, false, true},
    {"hybrid_gate",  A_HGATE,     false, true},
    {"hybrid_ladder", A_HLADDER,   false, true},
    {"hybrid_run_gate", A_HRUNGATE, false, true},
    {"hybrid_bin21", A_HBIN21,    true,  true},
    {"hybrid_bin32", A_HBIN32,    true,  true},
    {"hybrid_bin62", A_HBIN62,    true,  true},
    {"hybrid_bin123", A_HBIN123,  true,  true},
    {"inversion_binsert", A_INV_BINSERT, true, true},
    {"hybrid_inversion_gate", A_HINV_GATE, false, true},
    {"adaptive_window_heap", A_WINDOW_HEAP, false, true},
    {"deletion_backbone_sort", A_DELETION_BACKBONE, false, true},
    {"deletion_backbone_route", A_DELETION_BACKBONE_ROUTE, false, true},
    {"deletion_backbone_preserve", A_DELETION_BACKBONE_PRESERVE, false, true},
    {"deletion_backbone_rotate", A_DELETION_BACKBONE_ROTATE, false, true},
    {"hybrid_backbone_gate", A_HBACKBONE_GATE, false, true},
    {"hybrid_descent_portfolio", A_HDESCENT_PORTFOLIO, false, true},
    {"hybrid_quantile_backbone", A_HQUANTILE_BACKBONE, false, true},
    {"hybrid_general_portfolio", A_HGENERAL_PORTFOLIO, false, true},
    {"hybrid_general_prefix", A_HGENERAL_PREFIX, false, true},
    {"hybrid_quantile_concat", A_HQUANTILE_CONCAT, false, true},
    {"hybrid_certified_portfolio", A_HCERTIFIED_PORTFOLIO, false, true},
    {"pdqsort_branchy", A_PDQ, false, true},
    {"pdqsort_branchless", A_PDQ_BL, false, true},
#ifdef SORTLAB_HAVE_IPS4O
    {"ips4o", A_IPS4O, false, true},
#endif
#ifdef SORTLAB_HAVE_X86_SIMD
    {"x86_simd", A_X86_SIMD, false, true, true},
#endif
    {"radix_lsd",   A_RADIX,      false, false},
};
static const AlgoInfo* find_algo(const std::string& name) {
    for (auto& ai : ALGOS) if (name == ai.name) return &ai;
    std::fprintf(stderr, "unknown algo %s\n", name.c_str());
    std::exit(2);
}

template <class Cmp>
static void run_algo(Algo id, u64* a, size_t n, Cmp cmp,
                     u64 seed = 0x534b454c45544f4eULL) {
    switch (id) {
        case A_STD_SORT:   std::sort(a, a + n, cmp); break;
        case A_STD_STABLE: std::stable_sort(a, a + n, cmp); break;
        case A_HEAP:       lab::heapsort(a, n, cmp); break;
        case A_QMO3:       lab::quick_mo3(a, n, cmp); break;
        case A_DUAL:       lab::dual_pivot(a, n, cmp); break;
        case A_BLQ:        lab::bl_quick(a, n, cmp); break;
        case A_MTD:        lab::merge_td(a, n, cmp); break;
        case A_TIM:        lab::timsort(a, n, cmp); break;
        case A_POW:        lab::powersort(a, n, cmp); break;
        case A_POW_FIXED:  lab::powersort_fixed(a, n, cmp); break;
        case A_POW_FJ:     lab::powersort_fj(a, n, cmp); break;
        case A_PINGPONG_POW: lab::pingpong_powersort(a, n, cmp); break;
        case A_DIRECTIONAL: lab::directional_mergesort(a, n, cmp); break;
        case A_SHELL_LEARNED: lab::shellsort_learned(a, n, cmp); break;
        case A_SHELL_CIURA: lab::shellsort_ciura(a, n, cmp); break;
        case A_SHELL_TOKUDA: lab::shellsort_tokuda(a, n, cmp); break;
        case A_SKELETON:    lab::skeleton_sort(a, n, cmp, seed); break;
        case A_HFJ8:       lab::hybrid_fj<8>(a, n, cmp); break;
        case A_HFJ12:      lab::hybrid_fj<12>(a, n, cmp); break;
        case A_HFJ16:      lab::hybrid_fj<16>(a, n, cmp); break;
        case A_HFJ21:      lab::hybrid_fj<21>(a, n, cmp); break;
        case A_HFJ32:      lab::hybrid_fj<32>(a, n, cmp); break;
        case A_HFJ42:      lab::hybrid_fj<42>(a, n, cmp); break;
        case A_HFJ56:      lab::hybrid_fj<56>(a, n, cmp); break;
        case A_HFJ62:      lab::hybrid_fj<62>(a, n, cmp); break;
        case A_HFJ64:      lab::hybrid_fj<64>(a, n, cmp); break;
        case A_HFJA62:     lab::hybrid_fj_adaptive<62>(a, n, cmp); break;
        case A_HFJ85:      lab::hybrid_fj<85>(a, n, cmp); break;
        case A_HFJ123:     lab::hybrid_fj<123>(a, n, cmp); break;
        case A_HFJ128:     lab::hybrid_fj<128>(a, n, cmp); break;
        case A_HFJAUTO:    lab::hybrid_fj_auto(a, n, cmp); break;
        case A_HFJAUTO256: lab::hybrid_fj_auto_capped<256>(a, n, cmp); break;
        case A_HFJAUTO512: lab::hybrid_fj_auto_capped<512>(a, n, cmp); break;
        case A_HFJAUTO1024: lab::hybrid_fj_auto_capped<1024>(a, n, cmp); break;
        case A_HFJAUTO2048: lab::hybrid_fj_auto_capped<2048>(a, n, cmp); break;
        case A_HGATE:      lab::hybrid_gate(a, n, cmp); break;
        case A_HLADDER:    lab::hybrid_ladder(a, n, cmp); break;
        case A_HRUNGATE:   lab::hybrid_run_gate(a, n, cmp); break;
        case A_HBIN21:     lab::hybrid_bin<21>(a, n, cmp); break;
        case A_HBIN32:     lab::hybrid_bin<32>(a, n, cmp); break;
        case A_HBIN62:     lab::hybrid_bin<62>(a, n, cmp); break;
        case A_HBIN123:    lab::hybrid_bin<123>(a, n, cmp); break;
        case A_INV_BINSERT: lab::inversion_binary_insertion_sort(a, n, cmp); break;
        case A_HINV_GATE: lab::hybrid_inversion_gate(a, n, cmp); break;
        case A_WINDOW_HEAP: lab::adaptive_window_heap_sort(a, n, cmp); break;
        case A_DELETION_BACKBONE: lab::deletion_backbone_sort(a, n, cmp); break;
        case A_DELETION_BACKBONE_ROUTE: lab::deletion_backbone_route(a, n, cmp); break;
        case A_DELETION_BACKBONE_PRESERVE: lab::deletion_backbone_preserve_sort(a, n, cmp); break;
        case A_DELETION_BACKBONE_ROTATE: lab::deletion_backbone_rotate_sort(a, n, cmp); break;
        case A_HBACKBONE_GATE: lab::hybrid_backbone_gate(a, n, cmp); break;
        case A_HDESCENT_PORTFOLIO: lab::hybrid_descent_portfolio(a, n, cmp); break;
        case A_HQUANTILE_BACKBONE: lab::hybrid_quantile_backbone(a, n, cmp); break;
        case A_HGENERAL_PORTFOLIO: lab::hybrid_general_portfolio(a, n, cmp); break;
        case A_HGENERAL_PREFIX: lab::hybrid_general_prefix(a, n, cmp); break;
        case A_HQUANTILE_CONCAT: lab::hybrid_quantile_concat(a, n, cmp); break;
        case A_HCERTIFIED_PORTFOLIO: lab::hybrid_certified_portfolio(a, n, cmp); break;
        case A_PDQ: if (n > 1) ::pdqsort(a, a + n, cmp); break;
        case A_PDQ_BL: if (n > 1) ::pdqsort_branchless(a, a + n, cmp); break;
#ifdef SORTLAB_HAVE_IPS4O
        case A_IPS4O: if (n > 1) ips4o::sort(a, a + n, cmp); break;
#endif
#ifdef SORTLAB_HAVE_X86_SIMD
        case A_X86_SIMD:
            if (n > 1) x86simdsortStatic::qsort(a, n);
            break;
#endif
        case A_RADIX:      lab::radix_sort_u64(a, n); break;
    }
}

// ---------------------------------------------------------------------------
// selftest
// ---------------------------------------------------------------------------
static bool selftest() {
    const char* dists[] = {"random", "uniform64", "uniform32", "highbits32",
                           "dup2", "dup6", "dup16", "equal",
                           "sorted", "reversed", "runs32", "nearly1", "saw13",
                           "organpipe", "disp16", "tail10", "outliers1",
                           "outliers8", "outliers64"};
    size_t sizes[] = {0, 1, 2, 3, 4, 5, 7, 8, 15, 16, 17, 21, 24, 25, 63, 64,
                      65, 100, 127, 257, 1000, 2500};
    bool all_ok = true;
    for (auto& ai : ALGOS) {
        size_t checks = 0, fails = 0;
        std::mt19937_64 trng(12345);
        auto run_case = [&](const std::string& d, size_t n, u64 seed) {
            std::vector<u64> input = gen_dist(d, n, seed);
            // (a) value correctness under RawLess
            {
                std::vector<u64> work = input, ref = input;
                run_algo(ai.id, work.data(), n, lab::RawLess{}, seed);
                std::sort(ref.begin(), ref.end());
                ++checks;
                if (work != ref) {
                    ++fails;
                    if (fails == 1)
                        std::fprintf(stderr, "  FAIL %s value d=%s n=%zu seed=%" PRIu64 "\n",
                                     ai.name, d.c_str(), n, seed);
                }
            }
            // (b) stability: pack (key<<32 | index), compare with stable_sort
            if (ai.stable) {
                std::vector<u64> packed(n);
                for (size_t i = 0; i < n; ++i)
                    packed[i] = ((input[i] & 0xFFFFFull) << 32) | (u64)i;
                std::vector<u64> work = packed, ref = packed;
                run_algo(ai.id, work.data(), n, lab::KeyLess{}, seed);
                std::stable_sort(ref.begin(), ref.end(), lab::KeyLess{});
                ++checks;
                if (work != ref) {
                    ++fails;
                    if (fails == 1)
                        std::fprintf(stderr, "  FAIL %s stability d=%s n=%zu seed=%" PRIu64 "\n",
                                     ai.name, d.c_str(), n, seed);
                }
            }
            // (c) counting-comparator instantiation gives same result
            {
                std::vector<u64> work = input, ref = input;
                run_algo(ai.id, work.data(), n, lab::Counting<lab::RawLess>{}, seed);
                std::sort(ref.begin(), ref.end());
                ++checks;
                if (work != ref) ++fails;
            }
        };
        for (const char* d : dists)
            for (size_t n : sizes) run_case(d, n, 7);
        for (int t = 0; t < 150; ++t) {
            const char* d = dists[trng() % (sizeof(dists) / sizeof(*dists))];
            run_case(d, trng() % 3000, trng());
        }
        std::printf("%-12s %s (%zu checks, %zu fails)\n", ai.name,
                    fails ? "FAIL" : "ok", checks, fails);
        if (fails) all_ok = false;
    }

    // The three Shellsort gap generators must reproduce their published
    // finite prefixes exactly, including Liu's tuned prefix and rational tail.
    {
        const std::vector<size_t> expected_learned =
            {1, 3, 8, 20, 47, 116, 300, 585, 1416};
        const std::vector<size_t> expected_ciura =
            {1, 4, 10, 23, 57, 132, 301, 701, 1577};
        const std::vector<size_t> expected_tokuda =
            {1, 4, 9, 20, 46, 103, 233, 525, 1182};
        auto ascending = [](const lab::ShellGaps& gaps) {
            return std::vector<size_t>(gaps.values.begin(),
                                       gaps.values.begin() + gaps.size);
        };
        auto check_sequence = [&](const char* name, lab::ShellGaps gaps,
                                  const std::vector<size_t>& expected) {
            gaps.reverse();
            bool ok = ascending(gaps) == expected;
            std::printf("%-12s %s (%zu gaps)\n", name,
                        ok ? "ok" : "FAIL", expected.size());
            all_ok &= ok;
        };
        check_sequence("shell_gaps_new", lab::shell_learned_gaps(2000),
                       expected_learned);
        check_sequence("shell_gaps_ciura", lab::shell_ciura_gaps(2000),
                       expected_ciura);
        check_sequence("shell_gaps_tokuda", lab::shell_tokuda_gaps(2000),
                       expected_tokuda);
    }

    // The prefix-aware entry point must be exactly the ordinary FJ path minus
    // the root comparison whose false result was established by count_run.
    // Include large sizes around the final Jacobsthal groups used by CAP=2048.
    {
        const size_t pair_sizes[] = {
            2, 3, 4, 5, 60, 61, 64, 128, 255, 512, 1024, 1365, 2047,
        };
        std::mt19937_64 rng(0xF17A57u);
        size_t checks = 0, fails = 0;
        auto check = [&](std::vector<u64> input) {
            if (lab::RawLess{}(input[1], input[0])) std::swap(input[0], input[1]);
            std::vector<u64> ordinary = input, known = input;
            lab::g_comps = 0;
            lab::fj_sort_block_capped<lab::FJ_MAX>(
                ordinary.data(), ordinary.size(), lab::Counting<lab::RawLess>{});
            u64 ordinary_comps = lab::g_comps;
            lab::g_comps = 0;
            lab::fj_sort_block_capped_known_pair<lab::FJ_MAX>(
                known.data(), known.size(), lab::Counting<lab::RawLess>{});
            u64 known_comps = lab::g_comps;
            ++checks;
            if (ordinary != known || ordinary_comps != known_comps + 1) ++fails;
        };
        for (size_t n : pair_sizes) {
            std::vector<u64> unique(n);
            for (size_t i = 0; i < n; ++i) unique[i] = i;
            std::shuffle(unique.begin(), unique.end(), rng);
            check(unique);

            std::vector<u64> duplicate(n);
            for (u64& value : duplicate) value = rng() & 15;
            check(duplicate);

            std::vector<u64> descending(n);
            for (size_t i = 0; i < n; ++i) descending[i] = n - 1 - i;
            check(descending);
        }
        std::printf("%-12s %s (%zu checks, %zu fails)\n", "fj_known_pair",
                    fails ? "FAIL" : "ok", checks, fails);
        if (fails) all_ok = false;
    }

    // The gate must cost exactly its probe comparisons plus one of its two
    // portfolio branches run standalone on the same input, produce that
    // branch's exact output, and take the intended branch on characteristic
    // inputs. Choices are deterministic: probe indices come from a fixed-seed
    // generator. Cardinalities near the K=112 duplicate-veto boundary are
    // deliberately absent here; there the veto is probabilistic across
    // generator seeds, which the benchmark grid reports instead. dup16 sits
    // far below the boundary and dup2048 far above it.
    {
        struct GateCase { const char* dist; size_t n; int expect_choice; };
        const GateCase gate_cases[] = {
            {"random", 200000, 2},   {"disp2048", 200000, 2},
            {"disp64", 200000, 1},   {"dup16", 200000, 1},
            {"dup2048", 200000, 2},
            {"runs1024", 200000, 1}, {"nearly1", 200000, 1},
            {"sorted", 200000, 1},   {"reversed", 200000, 1},
            {"equal", 200000, 1},    {"random", 1000, 0},
        };
        size_t checks = 0, fails = 0;
        for (const GateCase& gc : gate_cases) {
            std::vector<u64> input = gen_dist(gc.dist, gc.n, 7);
            std::vector<u64> gate_work = input;
            lab::g_comps = 0;
            lab::hybrid_gate(gate_work.data(), gc.n,
                             lab::Counting<lab::RawLess>{});
            u64 gate_comps = lab::g_comps;
            u64 probe_comps = lab::g_gate_probe_comps;
            int choice = lab::g_gate_choice;
            std::vector<u64> branch_work = input;
            lab::g_comps = 0;
            if (choice == 2)
                lab::hybrid_fj_auto_capped<2048>(branch_work.data(), gc.n,
                                                 lab::Counting<lab::RawLess>{});
            else
                lab::powersort_fj(branch_work.data(), gc.n,
                                  lab::Counting<lab::RawLess>{});
            u64 branch_comps = lab::g_comps;
            ++checks;
            if (choice != gc.expect_choice || gate_work != branch_work ||
                gate_comps != probe_comps + branch_comps ||
                (choice == 0 && probe_comps != 0)) {
                ++fails;
                if (fails == 1)
                    std::fprintf(stderr,
                                 "  FAIL gate d=%s n=%zu choice=%d expect=%d "
                                 "gate=%" PRIu64 " probe=%" PRIu64
                                 " branch=%" PRIu64 "\n",
                                 gc.dist, gc.n, choice, gc.expect_choice,
                                 gate_comps, probe_comps, branch_comps);
            }
        }
        std::printf("%-12s %s (%zu checks, %zu fails)\n", "gate_account",
                    fails ? "FAIL" : "ok", checks, fails);
        if (fails) all_ok = false;
    }
    // The ladder must spend exactly its probe budget plus the selected
    // portfolio branch, and its classification is checked far from the
    // empirical crossover boundaries.
    {
        struct LadderCase { const char* dist; size_t n; int expect_choice; };
        const LadderCase cases[] = {
            {"random", 200000, 2}, {"disp64", 200000, 1},
            {"disp128", 200000, 3}, {"disp256", 200000, 4},
            {"disp512", 200000, 5}, {"disp2048", 200000, 2},
            {"dup16", 200000, 1}, {"runs1024", 200000, 1},
            {"random", 1000, 0},
        };
        size_t checks = 0, fails = 0;
        for (const LadderCase& tc : cases) {
            std::vector<u64> input = gen_dist(tc.dist, tc.n, 7);
            std::vector<u64> result = input;
            lab::g_comps = 0;
            lab::hybrid_ladder(result.data(), tc.n,
                               lab::Counting<lab::RawLess>{});
            const u64 total = lab::g_comps;
            const u64 probe = lab::g_gate_probe_comps;
            const int choice = lab::g_gate_choice;
            std::vector<u64> branch = input;
            lab::g_comps = 0;
            switch (choice) {
                case 2: lab::hybrid_fj_auto_capped<2048>(branch.data(), tc.n,
                         lab::Counting<lab::RawLess>{}); break;
                case 3: lab::hybrid_fj_auto_capped<128>(branch.data(), tc.n,
                         lab::Counting<lab::RawLess>{}); break;
                case 4: lab::hybrid_fj_auto_capped<512>(branch.data(), tc.n,
                         lab::Counting<lab::RawLess>{}); break;
                case 5: lab::hybrid_fj_auto_capped<1024>(branch.data(), tc.n,
                         lab::Counting<lab::RawLess>{}); break;
                default: lab::powersort_fj(branch.data(), tc.n,
                         lab::Counting<lab::RawLess>{}); break;
            }
            const u64 branch_comps = lab::g_comps;
            ++checks;
            if (choice != tc.expect_choice || result != branch ||
                total != probe + branch_comps ||
                (choice == 0 && probe != 0)) {
                ++fails;
                if (fails == 1)
                    std::fprintf(stderr,
                      "  FAIL ladder d=%s n=%zu choice=%d expect=%d total=%" PRIu64
                      " probe=%" PRIu64 " branch=%" PRIu64 "\n",
                      tc.dist, tc.n, choice, tc.expect_choice,
                      total, probe, branch_comps);
            }
        }
        std::printf("%-12s %s (%zu checks, %zu fails)\n", "ladder_account",
                    fails ? "FAIL" : "ok", checks, fails);
        if (fails) all_ok = false;
    }
    // Run-density routing must have exact accounting and match the selected
    // std::sort/Powersort branch on both one-run and high-run-density inputs.
    {
        struct RunGateCase { const char* dist; size_t n; int expect_choice; };
        const RunGateCase cases[] = {
            {"random", 200000, 8}, {"sorted", 200000, 7},
            {"reversed", 200000, 7}, {"equal", 200000, 7},
            {"dup16", 200000, 8}, {"runs32", 200000, 8},
            {"runs1024", 200000, 7}, {"organpipe", 200000, 7},
            {"random", 1000, 0},
        };
        size_t checks = 0, fails = 0;
        for (const RunGateCase& tc : cases) {
            std::vector<u64> input = gen_dist(tc.dist, tc.n, 7);
            std::vector<u64> result = input;
            lab::g_comps = 0;
            lab::hybrid_run_gate(result.data(), tc.n,
                                 lab::Counting<lab::RawLess>{});
            const u64 total = lab::g_comps;
            const u64 probe = lab::g_gate_probe_comps;
            const int choice = lab::g_gate_choice;
            std::vector<u64> branch = input;
            lab::g_comps = 0;
            if (choice == 7)
                lab::powersort(branch.data(), tc.n,
                               lab::Counting<lab::RawLess>{});
            else
                std::sort(branch.begin(), branch.end(),
                          lab::Counting<lab::RawLess>{});
            const u64 branch_comps = lab::g_comps;
            ++checks;
            if (choice != tc.expect_choice || result != branch ||
                total != probe + branch_comps ||
                (choice == 0 && probe != 0)) {
                ++fails;
                if (fails == 1)
                    std::fprintf(stderr,
                      "  FAIL run_gate d=%s n=%zu choice=%d expect=%d total=%" PRIu64
                      " probe=%" PRIu64 " branch=%" PRIu64 "\n",
                      tc.dist, tc.n, choice, tc.expect_choice,
                      total, probe, branch_comps);
            }
        }
        std::printf("%-12s %s (%zu checks, %zu fails)\n", "run_gate_acc",
                    fails ? "FAIL" : "ok", checks, fails);
        if (fails) all_ok = false;
    }
    // The backbone router uses stratified descent density to distinguish
    // scattered extreme-key corruption from localized or broad disorder.
    {
        struct BackboneGateCase { const char* dist; size_t n; int expect_choice; };
        const BackboneGateCase cases[] = {
            {"outpct1", 200000, 11}, {"outpct4", 200000, 11},
            {"outpct12", 200000, 11}, {"outpct16", 200000, 12},
            {"outpct24", 200000, 12}, {"random", 200000, 12},
            {"sorted", 200000, 10}, {"reversed", 200000, 10},
            {"tail10", 200000, 10}, {"disp16", 200000, 12},
            {"random", 1000, 0},
        };
        size_t checks = 0, fails = 0;
        for (const BackboneGateCase& tc : cases) {
            std::vector<u64> input = gen_dist(tc.dist, tc.n, 7);
            std::vector<u64> result = input;
            lab::g_comps = 0;
            lab::hybrid_backbone_gate(result.data(), tc.n,
                                      lab::Counting<lab::RawLess>{});
            const u64 total = lab::g_comps;
            const u64 probe = lab::g_gate_probe_comps;
            const int choice = lab::g_gate_choice;
            std::vector<u64> branch = input;
            lab::g_comps = 0;
            if (choice == 10)
                lab::powersort(branch.data(), tc.n,
                               lab::Counting<lab::RawLess>{});
            else if (choice == 11)
                lab::deletion_backbone_preserve_sort(
                    branch.data(), tc.n, lab::Counting<lab::RawLess>{});
            else
                std::sort(branch.begin(), branch.end(),
                          lab::Counting<lab::RawLess>{});
            const u64 branch_comps = lab::g_comps;
            ++checks;
            if (choice != tc.expect_choice || result != branch ||
                total != probe + branch_comps ||
                (choice == 0 && probe != 0)) {
                ++fails;
                if (fails == 1)
                    std::fprintf(stderr,
                      "  FAIL backbone_gate d=%s n=%zu choice=%d expect=%d total=%" PRIu64
                      " probe=%" PRIu64 " branch=%" PRIu64 "\n",
                      tc.dist, tc.n, choice, tc.expect_choice,
                      total, probe, branch_comps);
            }
        }
        std::printf("%-12s %s (%zu checks, %zu fails)\n", "backbone_gate",
                    fails ? "FAIL" : "ok", checks, fails);
        if (fails) all_ok = false;
    }
    // The sequential descent portfolio spends more probes near modeled
    // density boundaries, then routes sparse, medium, and broad disorder to
    // the specialized backbone, Powersort, and std::sort branches.
    {
        struct DescentPortfolioCase { const char* dist; size_t n; int expect_choice; };
        const DescentPortfolioCase cases[] = {
            {"outpct1", 200000, 11}, {"outpct5", 200000, 11},
            {"outpct14", 200000, 10}, {"outpct18", 200000, 10},
            {"outpct36", 200000, 10}, {"random", 200000, 12},
            {"sorted", 200000, 10}, {"reversed", 200000, 10},
            {"tail10", 200000, 10}, {"random", 1000, 0},
        };
        size_t checks = 0, fails = 0;
        for (const DescentPortfolioCase& tc : cases) {
            std::vector<u64> input = gen_dist(tc.dist, tc.n, 7);
            std::vector<u64> result = input;
            lab::g_comps = 0;
            lab::hybrid_descent_portfolio(result.data(), tc.n,
                                          lab::Counting<lab::RawLess>{});
            const u64 total = lab::g_comps;
            const u64 probe = lab::g_gate_probe_comps;
            const int choice = lab::g_gate_choice;
            std::vector<u64> branch = input;
            lab::g_comps = 0;
            if (choice == 10)
                lab::powersort(branch.data(), tc.n,
                               lab::Counting<lab::RawLess>{});
            else if (choice == 11)
                lab::deletion_backbone_preserve_sort(
                    branch.data(), tc.n, lab::Counting<lab::RawLess>{});
            else
                std::sort(branch.begin(), branch.end(),
                          lab::Counting<lab::RawLess>{});
            const u64 branch_comps = lab::g_comps;
            ++checks;
            if (choice != tc.expect_choice || result != branch ||
                total != probe + branch_comps ||
                (choice == 0 && probe != 0)) {
                ++fails;
                if (fails == 1)
                    std::fprintf(stderr,
                      "  FAIL descent_portfolio d=%s n=%zu choice=%d expect=%d total=%" PRIu64
                      " probe=%" PRIu64 " branch=%" PRIu64 "\n",
                      tc.dist, tc.n, choice, tc.expect_choice,
                      total, probe, branch_comps);
            }
        }
        std::printf("%-12s %s (%zu checks, %zu fails)\n", "descent_port",
                    fails ? "FAIL" : "ok", checks, fails);
        if (fails) all_ok = false;
    }
    // Quantile peeling is certified by checking the residual backbone. If the
    // pivot leaves disorder behind, the restored permutation must still sort.
    {
        struct QuantileBackboneCase { const char* dist; size_t n; int expect_choice; };
        const QuantileBackboneCase cases[] = {
            {"outpct1", 200000, 13}, {"outpct5", 200000, 13},
            {"outpct14", 200000, 13}, {"outpct36", 200000, -1},
            {"random", 200000, 12}, {"sorted", 200000, 10},
            {"reversed", 200000, 10}, {"tail10", 200000, 10},
            {"disp16", 200000, -1}, {"random", 1000, 0},
        };
        size_t checks = 0, fails = 0;
        for (const QuantileBackboneCase& tc : cases) {
            std::vector<u64> input = gen_dist(tc.dist, tc.n, 7);
            std::vector<u64> expected = input;
            std::sort(expected.begin(), expected.end());
            std::vector<u64> result = input;
            lab::g_comps = 0;
            lab::hybrid_quantile_backbone(result.data(), tc.n,
                                          lab::Counting<lab::RawLess>{});
            const u64 total = lab::g_comps;
            const u64 probe = lab::g_gate_probe_comps;
            const int choice = lab::g_gate_choice;
            ++checks;
            if (result != expected || (tc.expect_choice >= 0 &&
                                       choice != tc.expect_choice) ||
                probe > total || (choice == 0 && probe != 0)) {
                ++fails;
                if (fails == 1)
                    std::fprintf(stderr,
                      "  FAIL quantile_backbone d=%s n=%zu choice=%d expect=%d total=%" PRIu64
                      " probe=%" PRIu64 "\n",
                      tc.dist, tc.n, choice, tc.expect_choice, total, probe);
            }
        }
        std::printf("%-12s %s (%zu checks, %zu fails)\n", "quantile_bb",
                    fails ? "FAIL" : "ok", checks, fails);
        if (fails) all_ok = false;
    }
    // Concatenation must preserve the exact permutation and routing of the
    // old repair. It removes comparisons only after a successful certificate;
    // failed certificates and broad-disorder branches remain exact controls.
    {
        const char* cases[] = {"outpct1", "outpct5", "outpct14", "sorted", "random", "dup16"};
        constexpr size_t n = 200000;
        size_t checks = 0, fails = 0;
        for (const char* dist : cases) {
            const auto input = gen_dist(dist, n, 311);
            auto old = input;
            auto revised = input;
            lab::g_comps = 0;
            lab::hybrid_quantile_backbone(old.data(), n, lab::Counting<lab::RawLess>{});
            const u64 old_total = lab::g_comps;
            const u64 old_probes = lab::g_gate_probe_comps;
            const int old_choice = lab::g_gate_choice;
            lab::g_comps = 0;
            lab::hybrid_quantile_concat(revised.data(), n, lab::Counting<lab::RawLess>{});
            ++checks;
            if (old != revised || !std::is_sorted(revised.begin(), revised.end()) ||
                old_choice != lab::g_gate_choice || old_probes != lab::g_gate_probe_comps ||
                (old_choice == 13 ? lab::g_comps >= old_total : lab::g_comps != old_total)) {
                ++fails;
                std::fprintf(stderr, "  FAIL quantile_concat d=%s\n", dist);
            }
        }
        std::printf("%-12s %s (%zu checks, %zu fails)\n", "quantile_cat",
                    fails ? "FAIL" : "ok", checks, fails);
        if (fails) all_ok = false;
    }
    {
        const char* cases[] = {"outpct1", "outpct5", "outpct14", "outpct36",
            "sorted", "reversed", "equal", "nearly1", "random", "uniform64",
            "runs1024", "disp16", "dup16", "organpipe"};
        constexpr size_t n = 200000;
        size_t checks = 0, fails = 0;
        for (const char* dist : cases) {
            auto input = gen_dist(dist, n, 311);
            auto expected = input;
            std::sort(expected.begin(), expected.end());
            lab::g_comps = 0;
            lab::hybrid_certified_portfolio(input.data(), n, lab::Counting<lab::RawLess>{});
            ++checks;
            if (input != expected || lab::g_gate_probe_comps > lab::g_comps) ++fails;
        }
        auto greater = [](u64 a, u64 b) { return a > b; };
        auto input = gen_dist("uniform64", n, 311);
        lab::hybrid_certified_portfolio(input.data(), n, greater);
        ++checks;
        if (!std::is_sorted(input.begin(), input.end(), greater)) ++fails;
        for (size_t count : {size_t{129}, size_t{131073}}) {
            std::vector<std::string> words;
            words.reserve(count);
            for (size_t i = 0; i < count; ++i)
                words.push_back("shared-prefix/" + std::to_string((i * 137) % 1009));
            auto expected = words;
            std::sort(expected.begin(), expected.end());
            auto less = [](const std::string& a, const std::string& b) { return a < b; };
            lab::hybrid_certified_portfolio(words.data(), words.size(), less);
            ++checks;
            if (words != expected) ++fails;
        }
        struct Record { u64 key; u64 payload; };
        std::vector<Record> records(n);
        for (size_t i = 0; i < n; ++i) records[i] = {i % 31, i};
        auto by_key = [](const Record& a, const Record& b) { return a.key < b.key; };
        lab::hybrid_certified_portfolio(records.data(), n, by_key);
        bool record_ok = std::is_sorted(records.begin(), records.end(), by_key);
        std::sort(records.begin(), records.end(),
                  [](const Record& a, const Record& b) { return a.payload < b.payload; });
        for (size_t i = 0; i < n; ++i)
            record_ok &= records[i].payload == i && records[i].key == i % 31;
        ++checks;
        if (!record_ok) ++fails;
        std::printf("%-12s %s (%zu checks, %zu fails)\n", "cert_port",
                    fails ? "FAIL" : "ok", checks, fails);
        if (fails) all_ok = false;
    }
    // The general portfolio must remain correct across each routing family,
    // including any failed quantile certificate and its original-order restore.
    {
        const char* cases[] = {
            "outpct1", "outpct5", "outpct14", "outpct36", "random",
            "sorted", "reversed", "runs32", "runs1024", "nearly1",
            "tail10", "saw13", "organpipe", "disp4", "disp16", "disp64",
            "disp256", "dup2", "dup16", "dup256", "equal",
        };
        size_t checks = 0, fails = 0;
        for (const char* dist : cases) {
            constexpr size_t n = 200000;
            std::vector<u64> input = gen_dist(dist, n, 17);
            std::vector<u64> expected = input;
            std::sort(expected.begin(), expected.end());
            std::vector<u64> result = input;
            lab::g_comps = 0;
            lab::hybrid_general_portfolio(
                result.data(), n, lab::Counting<lab::RawLess>{});
            const u64 total = lab::g_comps;
            const u64 probe = lab::g_gate_probe_comps;
            ++checks;
            if (result != expected || probe > total) {
                ++fails;
                if (fails == 1)
                    std::fprintf(stderr,
                      "  FAIL general_portfolio d=%s choice=%d total=%" PRIu64
                      " probe=%" PRIu64 "\n",
                      dist, lab::g_gate_choice, total, probe);
            }
        }
        std::printf("%-12s %s (%zu checks, %zu fails)\n", "general_port",
                    fails ? "FAIL" : "ok", checks, fails);
        if (fails) all_ok = false;
    }
    // Lock representative mathematical cues to intended portfolio branches:
    // low adjacent disorder plus distance probes separate runs from near-sort,
    // while large adjacent disorder and low gap inversions identify displacement.
    {
        struct GeneralRouteCase { const char* dist; size_t n; int choice; };
        const GeneralRouteCase cases[] = {
            {"nearly1", 200000, 15}, {"runs32", 200000, 12},
            {"runs1024", 200000, 12}, {"runs1024", 1000000, 12},
            {"disp16", 200000, 16}, {"outpct11", 200000, 17},
            {"outpct32", 200000, 12},
            {"random", 200000, 12}, {"sorted", 200000, 10},
            {"reversed", 200000, 10}, {"organpipe", 200000, 10},
            {"tail10", 200000, 10}, {"saw13", 200000, 12},
            {"dup2", 200000, 12}, {"dup16", 200000, 12},
            {"equal", 200000, 18},
        };
        size_t checks = 0, fails = 0;
        for (const GeneralRouteCase& tc : cases) {
            std::vector<u64> result = gen_dist(tc.dist, tc.n, 17);
            lab::g_comps = 0;
            lab::hybrid_general_portfolio(
                result.data(), tc.n, lab::Counting<lab::RawLess>{});
            ++checks;
            if (lab::g_gate_choice != tc.choice ||
                lab::g_gate_probe_comps > lab::g_comps ||
                !std::is_sorted(result.begin(), result.end())) {
                ++fails;
                if (fails == 1)
                    std::fprintf(stderr,
                      "  FAIL general_route d=%s n=%zu choice=%d expect=%d\n",
                      tc.dist, tc.n, lab::g_gate_choice, tc.choice);
            }
        }
        std::printf("%-12s %s (%zu checks, %zu fails)\n", "general_route",
                    fails ? "FAIL" : "ok", checks, fails);
        if (fails) all_ok = false;
    }
    // A sampled prefix route is never a sortedness certificate. In particular,
    // unseen disorder must still be sorted, and failed preflights must preserve
    // the original selector's exact comparison decisions.
    {
        const char* cases[] = {"sorted", "reversed", "equal", "organpipe",
            "nearly1", "runs1024", "random", "tail10", "blindspot", "dup16"};
        constexpr size_t n = 200000;
        size_t checks = 0, fails = 0;
        for (const char* dist : cases) {
            const bool blindspot = std::string(dist) == "blindspot";
            std::vector<u64> input = gen_dist(blindspot ? "sorted" : dist, n, 191);
            if (blindspot) std::swap(input[n / 3 + 7], input[n / 3 + 8]);
            std::vector<u64> result = input;
            std::vector<u64> reference = input;
            std::sort(reference.begin(), reference.end());
            lab::g_comps = 0;
            lab::hybrid_general_prefix(result.data(), n, lab::Counting<lab::RawLess>{});
            const u64 total = lab::g_comps;
            const u64 probes = lab::g_gate_probe_comps;
            const int choice = lab::g_gate_choice;
            std::vector<u64> branch = input;
            lab::g_comps = 0;
            lab::g_gate_probe_comps = 0;
            if (choice == 19)
                lab::powersort(branch.data(), n, lab::Counting<lab::RawLess>{});
            else
                lab::hybrid_general_portfolio(branch.data(), n,
                                             lab::Counting<lab::RawLess>{});
            const u64 branch_probes = lab::g_gate_probe_comps;
            const bool ordered_control = blindspot || std::string(dist) == "sorted" ||
                std::string(dist) == "reversed" || std::string(dist) == "equal";
            ++checks;
            if (result != reference || result != branch || probes < branch_probes ||
                total != lab::g_comps + probes - branch_probes ||
                probes - branch_probes > std::max<size_t>(256, n / 256) - 1 + 32 ||
                (ordered_control && choice != 19)) {
                ++fails;
                std::fprintf(stderr, "  FAIL general_prefix d=%s choice=%d\n", dist, choice);
            }
        }
        auto greater = [](u64 a, u64 b) { return a > b; };
        std::vector<u64> reverse_order = gen_dist("sorted", n, 191);
        lab::hybrid_general_prefix(reverse_order.data(), n, greater);
        ++checks;
        if (!std::is_sorted(reverse_order.begin(), reverse_order.end(), greater)) ++fails;
        std::printf("%-12s %s (%zu checks, %zu fails)\n", "general_pre",
                    fails ? "FAIL" : "ok", checks, fails);
        if (fails) all_ok = false;
    }
    // The inversion portfolio should use insertion only on low-disorder
    // perturbations and otherwise match one of the established runtime
    // branches, with every probe included in comparator accounting.
    {
        struct InvGateCase { const char* dist; size_t n; int expect_choice; };
        const InvGateCase cases[] = {
            {"disp4", 200000, 9}, {"disp16", 200000, 9},
            {"disp32", 200000, 8}, {"random", 200000, 8},
            {"sorted", 200000, 7}, {"reversed", 200000, 7},
            {"runs1024", 200000, 7}, {"tail10", 200000, 7},
            {"random", 1000, 0},
        };
        size_t checks = 0, fails = 0;
        for (const InvGateCase& tc : cases) {
            std::vector<u64> input = gen_dist(tc.dist, tc.n, 7);
            std::vector<u64> result = input;
            lab::g_comps = 0;
            lab::hybrid_inversion_gate(result.data(), tc.n,
                                       lab::Counting<lab::RawLess>{});
            const u64 total = lab::g_comps;
            const u64 probe = lab::g_gate_probe_comps;
            const int choice = lab::g_gate_choice;
            std::vector<u64> branch = input;
            lab::g_comps = 0;
            if (choice == 9)
                lab::inversion_binary_insertion_sort(
                    branch.data(), tc.n, lab::Counting<lab::RawLess>{});
            else if (choice == 7)
                lab::powersort(branch.data(), tc.n,
                               lab::Counting<lab::RawLess>{});
            else
                std::sort(branch.begin(), branch.end(),
                          lab::Counting<lab::RawLess>{});
            const u64 branch_comps = lab::g_comps;
            ++checks;
            if (choice != tc.expect_choice || result != branch ||
                total != probe + branch_comps ||
                (choice == 0 && probe != 0)) {
                ++fails;
                if (fails == 1)
                    std::fprintf(stderr,
                      "  FAIL inversion_gate d=%s n=%zu choice=%d expect=%d total=%" PRIu64
                      " probe=%" PRIu64 " branch=%" PRIu64 "\n",
                      tc.dist, tc.n, choice, tc.expect_choice,
                      total, probe, branch_comps);
            }
        }
        std::printf("%-12s %s (%zu checks, %zu fails)\n", "inv_gate_acc",
                    fails ? "FAIL" : "ok", checks, fails);
        if (fails) all_ok = false;
    }

    // Exercise the rotation merge directly over every short run-size pair,
    // including empty runs and many duplicate-key boundary cases.
    {
        std::mt19937_64 rng(0xA11CE5u);
        size_t checks = 0, fails = 0;
        for (size_t left = 0; left <= 48; ++left) {
            for (size_t right = 0; right <= 48; ++right) {
                for (int trial = 0; trial < 3; ++trial) {
                    std::vector<u64> actual(left + right);
                    for (u64& value : actual) value = rng() % 13;
                    std::sort(actual.begin(), actual.begin() + left);
                    std::sort(actual.begin() + left, actual.end());
                    std::vector<u64> expected = actual;
                    std::inplace_merge(expected.begin(), expected.begin() + left,
                                       expected.end(), lab::RawLess{});
                    lab::rotation_merge(actual.data(), 0, left,
                                        left + right, lab::RawLess{});
                    ++checks;
                    if (actual != expected) ++fails;
                }
            }
        }
        std::printf("%-12s %s (%zu checks, %zu fails)\n", "rotate_merge",
                    fails ? "FAIL" : "ok", checks, fails);
        if (fails) all_ok = false;
    }
    return all_ok;
}

// ---------------------------------------------------------------------------
// Ford–Johnson comparison-count validation
// ---------------------------------------------------------------------------
static u64 fj_theoretical_max(int n) {
    u64 total = 0;
    for (u64 k = 1; k <= (u64)n; ++k) {
        u64 power = 4;
        u64 term = 0;
        while (power < 3 * k) { power <<= 1; ++term; }
        total += term;
    }
    return total;
}

static bool fjcounts(int max_n = 128, int trials_override = 0) {
    if (max_n < 1 || max_n > lab::FJ_MAX || trials_override < 0) return false;
    // Randomized profiles report an observed maximum, never a claimed
    // worst-case. Every trial is additionally checked against the established
    // MergeInsertion upper-bound formula.
    std::printf("n,fj_avg,observed_max,bin_avg,fj_gap_vs_lb,"
                "theoretical_max,lg_nfact\n");
    std::mt19937_64 rng(99);
    for (int n = 1; n <= max_n; ++n) {
        double sum = 0, bsum = 0;
        u64 mx = 0;
        int trials = trials_override ? trials_override : (n <= 64 ? 20000 : 8000);
        std::vector<u64> v(n);
        for (int i = 0; i < n; ++i) v[i] = i;
        for (int t = 0; t < trials; ++t) {
            std::shuffle(v.begin(), v.end(), rng);
            std::vector<u64> w = v;
            lab::g_comps = 0;
            lab::fj_sort_block(w.data(), n, lab::Counting<lab::RawLess>{});
            sum += (double)lab::g_comps;
            mx = std::max(mx, lab::g_comps);
            if (!std::is_sorted(w.begin(), w.end()) ||
                lab::g_comps > fj_theoretical_max(n)) {
                std::fprintf(stderr, "FJ VALIDATION BUG at n=%d\n", n);
                return false;
            }
            w = v;
            lab::g_comps = 0;
            lab::binary_insert_extend(w.data(), 1, (size_t)n,
                                      lab::Counting<lab::RawLess>{});
            bsum += (double)lab::g_comps;
            if (!std::is_sorted(w.begin(), w.end())) {
                std::fprintf(stderr, "BININS BUG at n=%d\n", n);
                return false;
            }
        }
        double lb = std::lgamma(n + 1.0) / std::log(2.0);
        std::printf("%d,%.3f,%" PRIu64 ",%.3f,%.3f,%" PRIu64 ",%.3f\n",
                    n, sum / trials, mx, bsum / trials, sum / trials - lb,
                    fj_theoretical_max(n), lb);
    }
    return true;
}

// ---------------------------------------------------------------------------
// bench
// ---------------------------------------------------------------------------
static size_t fj_stack_bound_bytes() {
    size_t m = lab::g_fj_largest_block;
    size_t cap = lab::g_fj_scratch_cap;
    if (m < 2) return 0;
    size_t depth = 0;
    for (size_t x = m; x > 1; x >>= 1) ++depth;
    // Conservative bound for fj_sort_block's two outer arrays plus every
    // recursive fj_core frame's four fixed-size scratch arrays. The 256-byte
    // allowances cover observed scalar/alignment overhead in each frame.
    size_t outer = cap * (sizeof(int) + sizeof(u64)) + 256;
    size_t frame = (3 * cap + 3) * sizeof(int) + 256;
    return outer + depth * frame;
}

// All algorithms share the input and work buffer. A shuffled cyclic schedule
// balances each algorithm's position over every complete algorithms.size()
// rounds; reshuffle only between complete cycles, never inside a round.
static bool bench_round(const std::string& names, const std::string& dist,
                        size_t n, u64 seed, int reps) {
    std::vector<const AlgoInfo*> algorithms;
    size_t start = 0;
    while (true) {
        const size_t end = names.find(',', start);
        const std::string name = names.substr(start, end - start);
        if (name.empty()) {
            std::fprintf(stderr, "empty algorithm in bench-round\n");
            return false;
        }
        const AlgoInfo* ai = find_algo(name);
        if (std::find(algorithms.begin(), algorithms.end(), ai) != algorithms.end()) {
            std::fprintf(stderr, "duplicate algorithm in bench-round: %s\n", ai->name);
            return false;
        }
        algorithms.push_back(ai);
        if (end == std::string::npos) break;
        start = end + 1;
    }
    if (reps <= 0) {
        std::fprintf(stderr, "bench-round repetitions must be positive\n");
        return false;
    }
    const std::vector<u64> master = gen_dist(dist, n, seed);
    std::vector<u64> reference = master;
    std::sort(reference.begin(), reference.end());
    std::vector<u64> work(n);
    for (const AlgoInfo* ai : algorithms) {
        std::copy(master.begin(), master.end(), work.begin());
        run_algo(ai->id, work.data(), n, lab::RawLess{}, seed);
        if (work != reference) return false;
    }
    std::vector<size_t> order(algorithms.size());
    std::iota(order.begin(), order.end(), size_t{0});
    std::mt19937_64 schedule_rng(seed ^ 0x524F554E44534F52ULL);
    bool all_ok = true;
    for (int r = 0; r < reps; ++r) {
        const size_t round = static_cast<size_t>(r);
        if (round % order.size() == 0)
            std::shuffle(order.begin(), order.end(), schedule_rng);
        for (size_t slot = 0; slot < order.size(); ++slot) {
            const AlgoInfo* ai = algorithms[order[(round + slot) % order.size()]];
            std::copy(master.begin(), master.end(), work.begin());
            lab::g_fj_largest_block = 0;
            lab::g_fj_scratch_cap = 0;
            const u64 t0 = now_ns();
            run_algo(ai->id, work.data(), n, lab::RawLess{}, seed);
            const u64 elapsed = now_ns() - t0;
            const int ok = work == reference ? 1 : 0;
            all_ok &= ok != 0;
            std::printf("%s,%s,%zu,%" PRIu64 ",time,%d,%" PRIu64
                        ",0,0,%zu,0,%d,%zu,%zu,%d,%s\n",
                        ai->name, dist.c_str(), n, seed, r, elapsed,
                        fj_stack_bound_bytes(), ok, lab::g_small_merge,
                        lab::g_fj_run_thresh, lab::FJ_MAX, SORTLAB_BUILD_ID);
        }
    }
    return all_ok;
}

static bool bench(const std::string& algo, const std::string& dist, size_t n,
                  u64 seed, int reps, const std::string& mode) {
    if (mode == "count" && !SORTLAB_TRACK_ALLOCATIONS) {
        std::fprintf(stderr, "count/resource mode requires an allocation-tracked build; "
                     "use a separate resource binary\n");
        return false;
    }
    const AlgoInfo* ai = find_algo(algo);
    std::vector<u64> master = gen_dist(dist, n, seed);
    std::vector<u64> reference = master;
    std::sort(reference.begin(), reference.end());
    std::vector<u64> work(n);
    bool all_ok = true;

    auto verify = [&]() -> int {
        int ok = work == reference ? 1 : 0;
        all_ok &= ok != 0;
        return ok;
    };

    // warmup (also faults in pages)
    std::memcpy(work.data(), master.data(), n * sizeof(u64));
    run_algo(ai->id, work.data(), n, lab::RawLess{}, seed);

    if (mode == "time") {
        for (int r = 0; r < reps; ++r) {
            std::memcpy(work.data(), master.data(), n * sizeof(u64));
            lab::g_fj_largest_block = 0;
            lab::g_fj_scratch_cap = 0;
            u64 t0 = now_ns();
            run_algo(ai->id, work.data(), n, lab::RawLess{}, seed);
            u64 t1 = now_ns();
            std::printf("%s,%s,%zu,%" PRIu64 ",time,%d,%" PRIu64
                        ",0,0,%zu,0,%d,%zu,%zu,%d,%s\n",
                        algo.c_str(), dist.c_str(), n, seed, r, t1 - t0,
                        fj_stack_bound_bytes(), verify(), lab::g_small_merge,
                        lab::g_fj_run_thresh, lab::FJ_MAX, SORTLAB_BUILD_ID);
        }
    } else if (mode == "count") {
        if (ai->native_numeric)
            std::fprintf(stderr, "%s: native SIMD comparisons are uninstrumented; "
                         "comparisons=0 records no Counting<C> calls, not zero logical comparisons\n",
                         ai->name);
        std::memcpy(work.data(), master.data(), n * sizeof(u64));
        lab::g_comps = 0;
        lab::g_merge_cost = 0;
        lab::g_fj_largest_block = 0;
        lab::g_fj_scratch_cap = 0;
        size_t cur0 = g_alloc_cur;
        g_alloc_peak = g_alloc_cur;
        u64 t0 = now_ns();
        run_algo(ai->id, work.data(), n, lab::Counting<lab::RawLess>{}, seed);
        u64 t1 = now_ns();
        size_t aux = g_alloc_peak - cur0;
        std::printf("%s,%s,%zu,%" PRIu64 ",count,0,%" PRIu64 ",%" PRIu64
                    ",%zu,%zu,%" PRIu64 ",%d,%zu,%zu,%d,%s\n",
                    algo.c_str(), dist.c_str(), n, seed, t1 - t0, lab::g_comps,
                    aux, fj_stack_bound_bytes(), lab::g_merge_cost, verify(),
                    lab::g_small_merge, lab::g_fj_run_thresh, lab::FJ_MAX,
                    SORTLAB_BUILD_ID);
    } else {
        std::fprintf(stderr, "unknown mode %s\n", mode.c_str());
        std::exit(2);
    }
    return all_ok;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr,
                     "usage:\n  %s selftest\n  %s fjcounts [max_n] [trials]\n"
                     "  %s bench <algo> <dist> <n> <seed> <reps> <time|count>"
                     " [small_merge] [fj_run_thresh]\n"
                     "  %s bench-round <algo,algo,...> <dist> <n> <seed> <reps>"
                     " [small_merge] [fj_run_thresh]\n"
                     "  %s list | csv-header | build-info\n",
                     argv[0], argv[0], argv[0], argv[0], argv[0]);
        return 2;
    }
    std::string cmd = argv[1];
    if (cmd == "selftest") return selftest() ? 0 : 1;
    if (cmd == "build-info") {
        std::printf("build_id,%s\nallocation_tracking,%d\n", SORTLAB_BUILD_ID,
                    SORTLAB_TRACK_ALLOCATIONS != 0 ? 1 : 0);
        return 0;
    }
    if (cmd == "fjcounts" && argc <= 4) {
        int max_n = argc >= 3 ? std::atoi(argv[2]) : 128;
        int trials = argc >= 4 ? std::atoi(argv[3]) : 0;
        return fjcounts(max_n, trials) ? 0 : 1;
    }
    if (cmd == "csv-header") {
        std::puts("algo,dist,n,seed,mode,rep,time_ns,comparisons,"
                  "heap_aux_bytes,fj_stack_bound_bytes,merge_span_elems,ok,"
                  "small_merge,fj_run_thresh,fj_max,build_id");
        return 0;
    }
    if (cmd == "list") {
        for (auto& ai : ALGOS)
            std::printf("%s,%s,%s\n", ai.name, ai.stable ? "stable" : "unstable",
                        ai.native_numeric ? "simd" : ai.comparison ? "comparison" : "radix");
        return 0;
    }
    if (cmd == "bench" && argc >= 8 && argc <= 10) {
        if (argc >= 9) lab::g_small_merge = std::strtoull(argv[8], nullptr, 10);
        if (argc >= 10) lab::g_fj_run_thresh = std::strtoull(argv[9], nullptr, 10);
        return bench(argv[2], argv[3], std::strtoull(argv[4], nullptr, 10),
                     std::strtoull(argv[5], nullptr, 10), std::atoi(argv[6]),
                     argv[7]) ? 0 : 1;
    }
    if (cmd == "bench-round" && argc >= 7 && argc <= 9) {
        if (argc >= 8) lab::g_small_merge = std::strtoull(argv[7], nullptr, 10);
        if (argc >= 9) lab::g_fj_run_thresh = std::strtoull(argv[8], nullptr, 10);
        return bench_round(argv[2], argv[3], std::strtoull(argv[4], nullptr, 10),
                           std::strtoull(argv[5], nullptr, 10), std::atoi(argv[6])) ? 0 : 1;
    }
    std::fprintf(stderr, "bad args\n");
    return 2;
}
