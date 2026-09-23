// main.cpp — harness: generators, metrics (time / comparisons / aux memory),
// selftest, Ford–Johnson count validation, bench CLI.
#include "algos.h"

#include <cinttypes>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <string>

#ifndef SORTLAB_BUILD_ID
#define SORTLAB_BUILD_ID "dev"
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
    A_HFJ8, A_HFJ12, A_HFJ16, A_HFJ21, A_HFJ32, A_HFJ42,
    A_HFJ56, A_HFJ62, A_HFJ64, A_HFJA62,
    A_HFJ85, A_HFJ123, A_HFJ128, A_HFJAUTO, A_HFJAUTO256, A_HFJAUTO512,
    A_HFJAUTO1024, A_HFJAUTO2048, A_HGATE,
    A_HBIN21, A_HBIN32, A_HBIN62, A_HBIN123,
    A_RADIX,
};
struct AlgoInfo { const char* name; Algo id; bool stable; bool comparison; };
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
    {"hybrid_bin21", A_HBIN21,    true,  true},
    {"hybrid_bin32", A_HBIN32,    true,  true},
    {"hybrid_bin62", A_HBIN62,    true,  true},
    {"hybrid_bin123", A_HBIN123,  true,  true},
    {"radix_lsd",   A_RADIX,      false, false},
};
static const AlgoInfo* find_algo(const std::string& name) {
    for (auto& ai : ALGOS) if (name == ai.name) return &ai;
    std::fprintf(stderr, "unknown algo %s\n", name.c_str());
    std::exit(2);
}

template <class Cmp>
static void run_algo(Algo id, u64* a, size_t n, Cmp cmp) {
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
        case A_HBIN21:     lab::hybrid_bin<21>(a, n, cmp); break;
        case A_HBIN32:     lab::hybrid_bin<32>(a, n, cmp); break;
        case A_HBIN62:     lab::hybrid_bin<62>(a, n, cmp); break;
        case A_HBIN123:    lab::hybrid_bin<123>(a, n, cmp); break;
        case A_RADIX:      lab::radix_sort_u64(a, n); break;
    }
}

// ---------------------------------------------------------------------------
// selftest
// ---------------------------------------------------------------------------
static bool selftest() {
    const char* dists[] = {"random", "dup2", "dup6", "dup16", "equal",
                           "sorted", "reversed", "runs32", "nearly1", "saw13",
                           "organpipe", "disp16", "tail10"};
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
                run_algo(ai.id, work.data(), n, lab::RawLess{});
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
                run_algo(ai.id, work.data(), n, lab::KeyLess{});
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
                run_algo(ai.id, work.data(), n, lab::Counting<lab::RawLess>{});
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

static bool bench(const std::string& algo, const std::string& dist, size_t n,
                  u64 seed, int reps, const std::string& mode) {
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
    run_algo(ai->id, work.data(), n, lab::RawLess{});

    if (mode == "time") {
        for (int r = 0; r < reps; ++r) {
            std::memcpy(work.data(), master.data(), n * sizeof(u64));
            lab::g_fj_largest_block = 0;
            lab::g_fj_scratch_cap = 0;
            u64 t0 = now_ns();
            run_algo(ai->id, work.data(), n, lab::RawLess{});
            u64 t1 = now_ns();
            std::printf("%s,%s,%zu,%" PRIu64 ",time,%d,%" PRIu64
                        ",0,0,%zu,0,%d,%zu,%zu,%d,%s\n",
                        algo.c_str(), dist.c_str(), n, seed, r, t1 - t0,
                        fj_stack_bound_bytes(), verify(), lab::g_small_merge,
                        lab::g_fj_run_thresh, lab::FJ_MAX, SORTLAB_BUILD_ID);
        }
    } else if (mode == "count") {
        std::memcpy(work.data(), master.data(), n * sizeof(u64));
        lab::g_comps = 0;
        lab::g_merge_cost = 0;
        lab::g_fj_largest_block = 0;
        lab::g_fj_scratch_cap = 0;
        size_t cur0 = g_alloc_cur;
        g_alloc_peak = g_alloc_cur;
        u64 t0 = now_ns();
        run_algo(ai->id, work.data(), n, lab::Counting<lab::RawLess>{});
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
                     "  %s list | csv-header\n",
                     argv[0], argv[0], argv[0], argv[0]);
        return 2;
    }
    std::string cmd = argv[1];
    if (cmd == "selftest") return selftest() ? 0 : 1;
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
                        ai.comparison ? "comparison" : "radix");
        return 0;
    }
    if (cmd == "bench" && argc >= 8 && argc <= 10) {
        if (argc >= 9) lab::g_small_merge = std::strtoull(argv[8], nullptr, 10);
        if (argc >= 10) lab::g_fj_run_thresh = std::strtoull(argv[9], nullptr, 10);
        return bench(argv[2], argv[3], std::strtoull(argv[4], nullptr, 10),
                     std::strtoull(argv[5], nullptr, 10), std::atoi(argv[6]),
                     argv[7]) ? 0 : 1;
    }
    std::fprintf(stderr, "bad args\n");
    return 2;
}
