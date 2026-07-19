// algos.h — instrumented sorting algorithms for the ordering-research lab.
//
// All algorithms operate on trivially-copyable T with a strict-weak "less"
// comparator Cmp. Comparison counting is done by wrapping Cmp (Counting<>),
// auxiliary memory by global operator new/delete instrumentation (main.cpp).
#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <memory>
#include <type_traits>
#include <vector>

namespace lab {

extern uint64_t g_comps;       // incremented by Counting comparator
extern uint64_t g_merge_cost;  // elements moved by run-merging sorts (post-trim)
extern size_t g_small_merge;   // hybrid: below this min-run-length, use plain merge
extern size_t g_fj_run_thresh; // adaptive hybrid: natural prefix >= this -> binary-extend
extern size_t g_fj_largest_block; // largest FJ block used by the measured call
extern size_t g_fj_scratch_cap;   // compile-time scratch cap of that FJ variant

struct RawLess {
    template <class T>
    bool operator()(const T& a, const T& b) const { return a < b; }
};

// Key-only order for stability tests: value layout (key << 32) | original_index.
struct KeyLess {
    bool operator()(uint64_t a, uint64_t b) const { return (a >> 32) < (b >> 32); }
};

template <class C>
struct Counting {
    C c{};
    template <class T>
    bool operator()(const T& a, const T& b) const { ++g_comps; return c(a, b); }
};

// ---------------------------------------------------------------------------
// small helpers
// ---------------------------------------------------------------------------

template <class T, class C>
void insertion_sort(T* a, size_t n, C cmp) {
    for (size_t i = 1; i < n; ++i) {
        T v = a[i];
        size_t j = i;
        while (j > 0 && cmp(v, a[j - 1])) { a[j] = a[j - 1]; --j; }
        a[j] = v;
    }
}

// a[0..sorted) already sorted; extend sortedness to a[0..n). Stable.
template <class T, class C>
void binary_insert_extend(T* a, size_t sorted, size_t n, C cmp) {
    for (size_t i = sorted ? sorted : 1; i < n; ++i) {
        T v = a[i];
        size_t lo = 0, hi = i;
        while (lo < hi) {
            size_t m = lo + ((hi - lo) >> 1);
            if (cmp(v, a[m])) hi = m; else lo = m + 1;
        }
        std::memmove(a + lo + 1, a + lo, (i - lo) * sizeof(T));
        a[lo] = v;
    }
}

// Length of maximal run starting at lo; strictly-descending runs are reversed
// in place (strictness keeps stable sorts stable).
template <class T, class C>
size_t count_run(T* a, size_t lo, size_t hi, C cmp) {
    size_t i = lo + 1;
    if (i == hi) return 1;
    if (cmp(a[i], a[lo])) {
        ++i;
        while (i < hi && cmp(a[i], a[i - 1])) ++i;
        std::reverse(a + lo, a + i);
    } else {
        ++i;
        while (i < hi && !cmp(a[i], a[i - 1])) ++i;
    }
    return i - lo;
}

inline size_t compute_minrun(size_t n) {  // CPython: result in [32, 64]
    size_t r = 0;
    while (n >= 64) { r |= n & 1; n >>= 1; }
    return n + r;
}

// Current CPython (3.14+) emits a sequence of floor/ceil run targets rather
// than one fixed minrun. On all-short inputs this creates exactly 2^e nearly
// equal runs, avoiding the alphabetic-tree rounding loss of a fixed target.
struct MinRunGenerator {
    size_t n, e = 0, mask = 0, current = 0;

    explicit MinRunGenerator(size_t n_, size_t bound = 64,
                             bool inclusive_cap = false) : n(n_) {
        assert(bound >= 2);
        if (inclusive_cap) {
            // Smallest e with ceil(n / 2^e) <= bound.
            for (;;) {
                size_t low_mask = (size_t{1} << e) - 1;
                size_t q = n >> e;
                if (q < bound || (q == bound && (n & low_mask) == 0)) break;
                ++e;
            }
        } else {
            // Exact current-CPython rule for its nominal bound of 64.
            while ((n >> e) >= bound) ++e;
        }
        mask = (size_t{1} << e) - 1;
    }

    size_t next() {
        current += n;
        size_t result = current >> e;
        current &= mask;
        return result;
    }
};

// ---------------------------------------------------------------------------
// galloping searches (CPython listsort semantics)
// ---------------------------------------------------------------------------

// lower bound: returns k in [0,n] with a[0..k) < key <= a[k..n)
template <class T, class C>
size_t gallop_left(const T& key, const T* a, size_t n, size_t hint, C cmp) {
    int64_t nn = (int64_t)n, h = (int64_t)hint;
    int64_t lastofs = 0, ofs = 1;
    if (cmp(a[h], key)) {                       // a[hint] < key: gallop right
        int64_t maxofs = nn - h;
        while (ofs < maxofs && cmp(a[h + ofs], key)) {
            lastofs = ofs; ofs = (ofs << 1) + 1;
        }
        if (ofs > maxofs) ofs = maxofs;
        lastofs += h; ofs += h;
    } else {                                    // key <= a[hint]: gallop left
        int64_t maxofs = h + 1;
        while (ofs < maxofs && !cmp(a[h - ofs], key)) {
            lastofs = ofs; ofs = (ofs << 1) + 1;
        }
        if (ofs > maxofs) ofs = maxofs;
        int64_t t = lastofs; lastofs = h - ofs; ofs = h - t;
    }
    ++lastofs;                                  // a[lastofs-1] < key <= a[ofs]
    while (lastofs < ofs) {
        int64_t m = lastofs + ((ofs - lastofs) >> 1);
        if (cmp(a[m], key)) lastofs = m + 1; else ofs = m;
    }
    return (size_t)ofs;
}

// upper bound: returns k in [0,n] with a[0..k) <= key < a[k..n)
template <class T, class C>
size_t gallop_right(const T& key, const T* a, size_t n, size_t hint, C cmp) {
    int64_t nn = (int64_t)n, h = (int64_t)hint;
    int64_t lastofs = 0, ofs = 1;
    if (cmp(key, a[h])) {                       // key < a[hint]: gallop left
        int64_t maxofs = h + 1;
        while (ofs < maxofs && cmp(key, a[h - ofs])) {
            lastofs = ofs; ofs = (ofs << 1) + 1;
        }
        if (ofs > maxofs) ofs = maxofs;
        int64_t t = lastofs; lastofs = h - ofs; ofs = h - t;
    } else {                                    // a[hint] <= key: gallop right
        int64_t maxofs = nn - h;
        while (ofs < maxofs && !cmp(key, a[h + ofs])) {
            lastofs = ofs; ofs = (ofs << 1) + 1;
        }
        if (ofs > maxofs) ofs = maxofs;
        lastofs += h; ofs += h;
    }
    ++lastofs;
    while (lastofs < ofs) {
        int64_t m = lastofs + ((ofs - lastofs) >> 1);
        if (cmp(key, a[m])) ofs = m; else lastofs = m + 1;
    }
    return (size_t)ofs;
}

// ---------------------------------------------------------------------------
// shared run-merging state (timsort / powersort / hybrid)
// ---------------------------------------------------------------------------

template <class T, class C>
struct MergeState {
    static constexpr int64_t MIN_GALLOP = 7;

    T* a; size_t n; C cmp;
    int64_t min_gallop = MIN_GALLOP;
    size_t small_merge = 0;      // min-side length below which to use plain merge
    std::unique_ptr<T[]> tmp; size_t tmpcap = 0;
    // forced = run was manufactured by the base sorter (unstructured content),
    // as opposed to a natural run found in the input.
    struct Run { size_t base, len; int power; bool forced; };
    std::vector<Run> pending;

    MergeState(T* a_, size_t n_, C c) : a(a_), n(n_), cmp(c) { pending.reserve(96); }

    T* ensure_tmp(size_t need) {
        if (tmpcap < need) {
            tmp.reset();                 // free before growing: honest n/2 peak
            tmp.reset(new T[need]);
            tmpcap = need;
        }
        return tmp.get();
    }

    // merge pending[i] and pending[i+1]
    void merge_at(size_t i) {
        size_t base1 = pending[i].base,     len1 = pending[i].len;
        size_t base2 = pending[i + 1].base, len2 = pending[i + 1].len;
        bool both_forced = pending[i].forced && pending[i + 1].forced;
        assert(base1 + len1 == base2);
        pending[i].len = len1 + len2;
        pending[i].forced = both_forced;
        if (i + 2 < pending.size()) pending[i + 1] = pending[i + 2];  // timsort's -3 case
        pending.pop_back();

        // Small merges between two FORCED runs (base-sorted, unstructured):
        // per-merge trim gallops (~4-6 comps) are pure overhead there; use a
        // plain branchless merge. Merges touching a natural run always take
        // the trim+gallop path — structured data is where galloping wins.
        if (both_forced && std::min(len1, len2) < small_merge) {
            g_merge_cost += len1 + len2;
            if (len1 <= len2) merge_small_lo(base1, len1, base2, len2);
            else              merge_small_hi(base1, len1, base2, len2);
            return;
        }

        // trim: run1 prefix already <= b[0]; run2 suffix already >= a-last
        size_t k = gallop_right(a[base2], a + base1, len1, 0, cmp);
        base1 += k; len1 -= k;
        if (len1 == 0) return;
        len2 = gallop_left(a[base1 + len1 - 1], a + base2, len2, len2 - 1, cmp);
        if (len2 == 0) return;
        g_merge_cost += len1 + len2;
        if (len1 <= len2) merge_lo(base1, len1, base2, len2);
        else              merge_hi(base1, len1, base2, len2);
    }

    // stable plain merge, left run copied out; no trim/gallop invariants needed
    void merge_small_lo(size_t base1, size_t len1, size_t base2, size_t len2) {
        T* t = ensure_tmp(len1);
        std::memcpy(t, a + base1, len1 * sizeof(T));
        size_t i = 0, j = 0;
        T* pb = a + base2;
        T* dest = a + base1;
        while (i < len1 && j < len2) {
            bool tb = cmp(pb[j], t[i]);
            *dest++ = tb ? pb[j] : t[i];
            j += tb; i += !tb;
        }
        if (i < len1) std::memcpy(dest, t + i, (len1 - i) * sizeof(T));
        // remaining right-run elements are already in place
    }

    void merge_small_hi(size_t base1, size_t len1, size_t base2, size_t len2) {
        T* t = ensure_tmp(len2);
        std::memcpy(t, a + base2, len2 * sizeof(T));
        int64_t i = (int64_t)len1 - 1, j = (int64_t)len2 - 1;
        T* pa = a + base1;
        T* dest = a + base2 + len2 - 1;
        while (i >= 0 && j >= 0) {
            bool ta = cmp(t[j], pa[i]);      // b < a: a is strictly larger
            *dest-- = ta ? pa[i] : t[j];
            i -= ta; j -= !ta;
        }
        while (j >= 0) *dest-- = t[j--];
        // remaining left-run elements are already in place
    }

    // len1 <= len2; invariants (post-trim): a[base1] > a[base2],
    // a[base1+len1-1] > everything in run2.
    void merge_lo(size_t base1, size_t len1, size_t base2, size_t len2) {
        T* t = ensure_tmp(len1);
        std::memcpy(t, a + base1, len1 * sizeof(T));
        const T* pa = t;
        T* pb = a + base2;
        T* dest = a + base1;
        int64_t mg = min_gallop;

        *dest++ = *pb++; --len2;
        if (len2 == 0) goto copy_a;
        if (len1 == 1) goto copy_b;

        for (;;) {
            int64_t acount = 0, bcount = 0;
            for (;;) {
                if (cmp(*pb, *pa)) {
                    *dest++ = *pb++; ++bcount; acount = 0;
                    if (--len2 == 0) goto copy_a;
                    if (bcount >= mg) break;
                } else {
                    *dest++ = *pa++; ++acount; bcount = 0;
                    --len1;
                    if (len1 == 1) goto copy_b;
                    if (acount >= mg) break;
                }
            }
            ++mg;
            do {
                mg -= (mg > 1);
                size_t k = gallop_right(*pb, pa, len1, 0, cmp);
                acount = (int64_t)k;
                if (k) {
                    std::memcpy(dest, pa, k * sizeof(T));
                    dest += k; pa += k; len1 -= k;
                    if (len1 == 1) goto copy_b;
                    if (len1 == 0) goto copy_a;   // unreachable by invariant
                }
                *dest++ = *pb++;
                if (--len2 == 0) goto copy_a;
                k = gallop_left(*pa, pb, len2, 0, cmp);
                bcount = (int64_t)k;
                if (k) {
                    std::memmove(dest, pb, k * sizeof(T));
                    dest += k; pb += k; len2 -= k;
                    if (len2 == 0) goto copy_a;
                }
                *dest++ = *pa++;
                --len1;
                if (len1 == 1) goto copy_b;
            } while (acount >= MIN_GALLOP || bcount >= MIN_GALLOP);
            ++mg;
        }
    copy_a:                                      // run2 exhausted
        std::memcpy(dest, pa, len1 * sizeof(T));
        min_gallop = mg; return;
    copy_b:                                      // single a element left (the max)
        std::memmove(dest, pb, len2 * sizeof(T));
        dest[len2] = *pa;
        min_gallop = mg; return;
    }

    // len1 > len2; merge from the right.
    void merge_hi(size_t base1, size_t len1, size_t base2, size_t len2) {
        T* t = ensure_tmp(len2);
        std::memcpy(t, a + base2, len2 * sizeof(T));
        T* basea = a + base1;
        T* pa = a + base1 + len1 - 1;
        const T* pb = t + len2 - 1;
        T* dest = a + base2 + len2 - 1;
        int64_t mg = min_gallop;

        *dest-- = *pa--; --len1;
        if (len1 == 0) goto copy_b2;             // unreachable (len1 > len2 >= 1)
        if (len2 == 1) goto copy_a2;

        for (;;) {
            int64_t acount = 0, bcount = 0;
            for (;;) {
                if (cmp(*pb, *pa)) {             // b < a: a goes right
                    *dest-- = *pa--; ++acount; bcount = 0;
                    if (--len1 == 0) goto copy_b2;
                    if (acount >= mg) break;
                } else {                          // a <= b: b goes right (stable)
                    *dest-- = *pb--; ++bcount; acount = 0;
                    --len2;
                    if (len2 == 1) goto copy_a2;
                    if (bcount >= mg) break;
                }
            }
            ++mg;
            do {
                mg -= (mg > 1);
                size_t k = len1 - gallop_right(*pb, basea, len1, len1 - 1, cmp);
                acount = (int64_t)k;
                if (k) {
                    dest -= k; pa -= k;
                    std::memmove(dest + 1, pa + 1, k * sizeof(T));
                    len1 -= k;
                    if (len1 == 0) goto copy_b2;
                }
                *dest-- = *pb--;
                --len2;
                if (len2 == 1) goto copy_a2;
                k = len2 - gallop_left(*pa, t, len2, len2 - 1, cmp);
                bcount = (int64_t)k;
                if (k) {
                    dest -= k; pb -= k;
                    std::memcpy(dest + 1, pb + 1, k * sizeof(T));
                    len2 -= k;
                    if (len2 == 1) goto copy_a2;
                    if (len2 == 0) goto copy_b2; // unreachable by invariant
                }
                *dest-- = *pa--;
                if (--len1 == 0) goto copy_b2;
            } while (acount >= MIN_GALLOP || bcount >= MIN_GALLOP);
            ++mg;
        }
    copy_a2:                                     // one b left: it is the global min
        std::memmove(dest - len1 + 1, pa - len1 + 1, len1 * sizeof(T));
        *(dest - len1) = *pb;
        min_gallop = mg; return;
    copy_b2:                                     // run1 exhausted
        std::memcpy(dest - len2 + 1, t, len2 * sizeof(T));
        min_gallop = mg; return;
    }

    // Timsort stack invariants (2015 corrected version).
    void merge_collapse() {
        auto& p = pending;
        while (p.size() > 1) {
            size_t k = p.size() - 2;
            if ((k > 0 && p[k - 1].len <= p[k].len + p[k + 1].len) ||
                (k > 1 && p[k - 2].len <= p[k - 1].len + p[k].len)) {
                if (p[k - 1].len < p[k + 1].len) --k;
                merge_at(k);
            } else if (p[k].len <= p[k + 1].len) {
                merge_at(k);
            } else break;
        }
    }

    void merge_force_collapse() {
        auto& p = pending;
        while (p.size() > 1) {
            size_t k = p.size() - 2;
            if (k > 0 && p[k - 1].len < p[k + 1].len) --k;
            merge_at(k);
        }
    }

    // Powersort node power (CPython powerloop): runs (s1,n1) and (s1+n1,n2).
    int powerloop(size_t s1, size_t n1, size_t n2) const {
        int result = 0;
        uint64_t va = 2 * (uint64_t)s1 + n1;       // 2*midpoint numerators
        uint64_t vb = va + n1 + n2;
        for (;;) {
            ++result;
            if (va >= n) { va -= n; vb -= n; }
            else if (vb >= n) break;
            va <<= 1; vb <<= 1;
        }
        return result;
    }
};

// ---------------------------------------------------------------------------
// timsort
// ---------------------------------------------------------------------------

template <class T, class C>
void timsort(T* a, size_t n, C cmp) {
    if (n < 2) return;
    size_t minrun = compute_minrun(n);
    MergeState<T, C> ms(a, n, cmp);
    size_t lo = 0;
    while (lo < n) {
        size_t run = count_run(a, lo, n, cmp);
        if (run < minrun) {
            size_t force = std::min(minrun, n - lo);
            binary_insert_extend(a + lo, run, force, cmp);
            run = force;
        }
        ms.pending.push_back({lo, run, 0, false});
        ms.merge_collapse();
        lo += run;
    }
    ms.merge_force_collapse();
}

// ---------------------------------------------------------------------------
// powersort (Munro–Wild policy, CPython-style) with pluggable base sorter
// ---------------------------------------------------------------------------

// BaseSorter: void(T* seg, size_t sorted_prefix, size_t m, C cmp)
template <class T, class C, class NextMinrun, class BaseSorter>
void powersort_impl_next(T* a, size_t n, C cmp, NextMinrun next_minrun,
                         BaseSorter base, size_t small_merge = 0) {
    if (n < 2) return;
    MergeState<T, C> ms(a, n, cmp);
    ms.small_merge = small_merge;
    auto& p = ms.pending;

    auto next_run = [&](size_t lo, bool& forced) -> size_t {
        size_t run = count_run(a, lo, n, cmp);
        size_t minrun = next_minrun();
        forced = false;
        if (run < minrun) {
            size_t force = std::min(minrun, n - lo);
            if (force > run) {
                base(a + lo, run, force, cmp);
                run = force;
                forced = true;
            }
        }
        return run;
    };

    size_t lo = 0;
    bool f = false;
    size_t run = next_run(lo, f);
    p.push_back({lo, run, 0, f});
    lo += run;
    while (lo < n) {
        bool f2 = false;
        size_t run2 = next_run(lo, f2);
        int pw = ms.powerloop(p.back().base, p.back().len, run2);
        while (p.size() > 1 && p[p.size() - 2].power > pw)
            ms.merge_at(p.size() - 2);
        p.back().power = pw;
        p.push_back({lo, run2, 0, f2});
        lo += run2;
    }
    ms.merge_force_collapse();
}

template <class T, class C, class BaseSorter>
void powersort_impl(T* a, size_t n, C cmp, size_t minrun, BaseSorter base,
                    size_t small_merge = 0) {
    powersort_impl_next(a, n, cmp, [minrun]() { return minrun; }, base,
                        small_merge);
}

template <class T, class C>
void powersort(T* a, size_t n, C cmp) {
    MinRunGenerator minruns(n);
    powersort_impl_next(a, n, cmp, [&minruns]() { return minruns.next(); },
                        [](T* seg, size_t pre, size_t m, C c) {
                            binary_insert_extend(seg, pre, m, c);
                        });
}

// Fixed-minrun ablation matching the pre-3.14 powersort implementation.
template <class T, class C>
void powersort_fixed(T* a, size_t n, C cmp) {
    powersort_impl(a, n, cmp, compute_minrun(n),
                   [](T* seg, size_t pre, size_t m, C c) {
                       binary_insert_extend(seg, pre, m, c);
                   });
}

// ---------------------------------------------------------------------------
// Ford–Johnson merge-insertion (for small blocks; not stable)
// ---------------------------------------------------------------------------

inline constexpr int FJ_MAX = 2048;

// Sort ids[0..m) ascending by v[id]. ids are indices into v (all < FJ_MAX).
template <int CAP, class T, class C>
void fj_core_capped(const T* v, int* ids, int m, C cmp) {
    static_assert(CAP >= 2 && CAP <= FJ_MAX);
    if (m <= 1) return;
    if (m == 2) {
        if (cmp(v[ids[1]], v[ids[0]])) std::swap(ids[0], ids[1]);
        return;
    }
    int half = m / 2;
    bool odd = (m & 1) != 0;
    int strag = odd ? ids[m - 1] : -1;

    int w[CAP / 2 + 1];
    int partner[CAP];
    for (int i = 0; i < half; ++i) {
        int x = ids[2 * i], y = ids[2 * i + 1];
        if (cmp(v[y], v[x])) std::swap(x, y);    // v[x] <= v[y]
        w[i] = y; partner[y] = x;
    }

    fj_core_capped<CAP>(v, w, half, cmp);        // sort winners (main chain)

    int chain[CAP + 1];
    int wpos[CAP / 2 + 1];
    int clen = 0;
    chain[clen++] = partner[w[0]];               // free insertion: l1 <= w1
    for (int i = 0; i < half; ++i) { chain[clen] = w[i]; wpos[i] = clen; ++clen; }

    // Jacobsthal group order over 1-based pair index jb (jb == half+1: straggler)
    static constexpr int jac[] = {
        1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365
    };
    int M = half + (odd ? 1 : 0);
    for (int g = 1; jac[g - 1] < M; ++g) {
        int hi_jb = std::min(jac[g], M);
        for (int jb = hi_jb; jb > jac[g - 1]; --jb) {
            int item, bound;
            if (jb <= half) { item = partner[w[jb - 1]]; bound = wpos[jb - 1]; }
            else            { item = strag;              bound = clen; }
            int lo2 = 0, hi2 = bound;
            while (lo2 < hi2) {
                int mid = lo2 + ((hi2 - lo2) >> 1);
                if (cmp(v[item], v[chain[mid]])) hi2 = mid; else lo2 = mid + 1;
            }
            std::memmove(chain + lo2 + 1, chain + lo2, (clen - lo2) * sizeof(int));
            chain[lo2] = item; ++clen;
            for (int i = 0; i < half; ++i) if (wpos[i] >= lo2) ++wpos[i];
        }
    }
    std::memcpy(ids, chain, m * sizeof(int));
}

template <int CAP, class T, class C>
void fj_sort_block_capped(T* a, size_t m, C cmp) {
    static_assert(CAP >= 2 && CAP <= FJ_MAX);
    assert(m <= (size_t)CAP);
    if (m < 2) return;
    g_fj_largest_block = std::max(g_fj_largest_block, m);
    g_fj_scratch_cap = std::max(g_fj_scratch_cap, (size_t)CAP);
    int ids[CAP];
    for (int i = 0; i < (int)m; ++i) ids[i] = i;
    fj_core_capped<CAP>(a, ids, (int)m, cmp);
    T tmpb[CAP];
    std::memcpy(tmpb, a, m * sizeof(T));
    for (size_t i = 0; i < m; ++i) a[i] = tmpb[ids[i]];
}

template <class T, class C>
void fj_sort_block(T* a, size_t m, C cmp) {
    fj_sort_block_capped<FJ_MAX>(a, m, cmp);
}

// hybrid: powersort merge policy + galloping merges + Ford–Johnson base blocks.
// Short natural runs are discarded and the whole BLOCK is FJ-sorted (FJ needs
// no presorted prefix and is within ~0.03n of the information bound).
template <int BLOCK, class T, class C>
void hybrid_fj(T* a, size_t n, C cmp) {
    static_assert(BLOCK >= 2 && BLOCK <= FJ_MAX);
    powersort_impl(a, n, cmp, (size_t)BLOCK,
                   [](T* seg, size_t /*pre*/, size_t m, C c) {
                       fj_sort_block_capped<BLOCK>(seg, m, c);
                   },
                   g_small_merge);
}

inline size_t default_fj_run_threshold(size_t block) {
    // For smaller blocks the random-input FJ advantage after reusing the first
    // known pair is less than one comparison per block and proved sensitive to
    // the input distribution (notably low-displacement data). Stay with binary
    // insertion there; blocks 60..78 showed a robust crossover at prefix 3.
    if (block < 60) return 2;
    if (block <= 78) return 3;
    if (block <= 128) return 4;
    size_t ceil_log2 = 0;
    for (size_t x = block - 1; x; x >>= 1) ++ceil_log2;
    return std::max<size_t>(4, ceil_log2 - 3);
}

inline size_t fj_run_threshold(size_t block) {
    return g_fj_run_thresh ? g_fj_run_thresh
                           : default_fj_run_threshold(block);
}

// run-adaptive hybrid: Ford–Johnson on unstructured blocks, but if count_run
// found a natural sorted prefix of length >= g_fj_run_thresh, salvage it with
// binary-insertion-extend instead of discarding it (FJ re-sorts from scratch).
// Crossover math: extending from prefix r to B costs ~(B-r)*lg B; FJ(B) costs
// ~lg B! regardless of r — so FJ only pays off for small r.
template <int BLOCK, class T, class C>
void hybrid_fj_adaptive(T* a, size_t n, C cmp) {
    static_assert(BLOCK >= 2 && BLOCK <= FJ_MAX);
    powersort_impl(a, n, cmp, (size_t)BLOCK,
                   [](T* seg, size_t pre, size_t m, C c) {
                       if (pre >= fj_run_threshold(m))
                           binary_insert_extend(seg, pre, m, c);
                       else
                           fj_sort_block_capped<BLOCK>(seg, m, c);
                   },
                   g_small_merge);
}

// stable ablation: same policy/merges as hybrid_fj but binary-insertion base
// (isolates the Ford–Johnson contribution at equal block size).
template <int BLOCK, class T, class C>
void hybrid_bin(T* a, size_t n, C cmp) {
    powersort_impl(a, n, cmp, (size_t)BLOCK,
                   [](T* seg, size_t pre, size_t m, C c) {
                       binary_insert_extend(seg, pre, m, c);
                   },
                   g_small_merge);
}

// Comparison-improved powersort: retain CPython's dynamic minrun sequence and
// merge policy, but choose the cheaper base case after count_run. Ford–Johnson
// wins on the upper end of CPython's minrun range when only the mandatory
// two-element natural prefix is known; binary insertion wins once a third
// known-sorted element can be reused. Smaller minruns conservatively retain
// binary insertion because their small average FJ gain was distribution-
// sensitive in the validation grid.
template <class T, class C>
void powersort_fj(T* a, size_t n, C cmp) {
    MinRunGenerator minruns(n);
    powersort_impl_next(
        a, n, cmp, [&minruns]() { return minruns.next(); },
        [](T* seg, size_t pre, size_t m, C c) {
            size_t threshold = fj_run_threshold(m);
            if (pre >= threshold)
                binary_insert_extend(seg, pre, m, c);
            else
                fj_sort_block_capped<64>(seg, m, c);
        },
        0);
}

// Auto-tuned FJ hybrid. A CPython-style generator emits floor/ceil block sizes
// around n/2^k, with exactly 2^k blocks on unstructured inputs and every block
// <= MAX_BLOCK. This avoids both merge-tree rounding loss and a short tail.
// Extending a natural prefix r to B
// costs ~(B-r)*lg B, FJ costs ~lg B! regardless of r. The crossover is a
// small absolute prefix length (configured by g_fj_run_thresh), because the
// measured average FJ advantage over binary insertion is only a few
// comparisons per block even as B grows.
// g_small_merge controls the optional plain-merge cutoff. Keeping it below B
// lets the first block merge trim and gallop, which is especially important
// on low-cardinality inputs; its random-input overhead is only O(n/B).
template <size_t MAX_BLOCK, class T, class C>
void hybrid_fj_auto_capped(T* a, size_t n, C cmp) {
    static_assert(MAX_BLOCK >= 2 && MAX_BLOCK <= (size_t)FJ_MAX);
    MinRunGenerator blocks(n, MAX_BLOCK, true);
    powersort_impl_next(a, n, cmp, [&blocks]() { return blocks.next(); },
                   [](T* seg, size_t pre, size_t m, C c) {
                       if (pre >= fj_run_threshold(m))
                           binary_insert_extend(seg, pre, m, c);
                       else
                           fj_sort_block_capped<(int)MAX_BLOCK>(seg, m, c);
                   },
                   g_small_merge);
}

template <class T, class C>
void hybrid_fj_auto(T* a, size_t n, C cmp) {
    hybrid_fj_auto_capped<128>(a, n, cmp);
}

// ---------------------------------------------------------------------------
// heapsort
// ---------------------------------------------------------------------------

template <class T, class C>
void heapsort(T* a, size_t n, C cmp) {
    if (n < 2) return;
    auto sift = [&](size_t root, size_t end) {
        size_t j = root;
        for (;;) {
            size_t c = 2 * j + 1;
            if (c >= end) break;
            if (c + 1 < end && cmp(a[c], a[c + 1])) ++c;
            if (cmp(a[j], a[c])) { std::swap(a[j], a[c]); j = c; }
            else break;
        }
    };
    for (size_t i = n / 2; i-- > 0;) sift(i, n);
    for (size_t e = n - 1; e > 0; --e) { std::swap(a[0], a[e]); sift(0, e); }
}

// ---------------------------------------------------------------------------
// classic quicksort: median-of-3 + Hoare-style partition + introspection
// ---------------------------------------------------------------------------

template <class T, class C>
void sort3(T& x, T& y, T& z, C cmp) {           // x <= y <= z afterwards
    if (cmp(y, x)) std::swap(x, y);
    if (cmp(z, y)) {
        std::swap(y, z);
        if (cmp(y, x)) std::swap(x, y);
    }
}

template <class T, class C>
void quick_mo3_rec(T* a, int64_t lo, int64_t hi, int depth, C cmp) {
    while (hi - lo > 24) {
        if (depth-- == 0) { heapsort(a + lo, (size_t)(hi - lo), cmp); return; }
        int64_t mid = lo + (hi - lo) / 2;
        sort3(a[lo], a[mid], a[hi - 1], cmp);
        std::swap(a[lo], a[mid]);                // median to lo; a[hi-1] is sentinel
        T piv = a[lo];
        int64_t i = lo, j = hi - 1;
        for (;;) {
            do ++i; while (cmp(a[i], piv));
            do --j; while (cmp(piv, a[j]));
            if (i >= j) break;
            std::swap(a[i], a[j]);
        }
        std::swap(a[lo], a[j]);                  // pivot into final position j
        if (j - lo < hi - (j + 1)) { quick_mo3_rec(a, lo, j, depth, cmp); lo = j + 1; }
        else                       { quick_mo3_rec(a, j + 1, hi, depth, cmp); hi = j; }
    }
    insertion_sort(a + lo, (size_t)(hi - lo), cmp);
}

template <class T, class C>
void quick_mo3(T* a, size_t n, C cmp) {
    if (n < 2) return;
    int depth = 2 * (63 - __builtin_clzll(n));
    quick_mo3_rec(a, 0, (int64_t)n, depth, cmp);
}

// ---------------------------------------------------------------------------
// dual-pivot quicksort (Yaroslavskiy)
// ---------------------------------------------------------------------------

template <class T, class C>
void dual_pivot_rec(T* a, int64_t lo, int64_t hi, int depth, C cmp) {  // [lo, hi]
    while (true) {
        int64_t len = hi - lo + 1;
        if (len < 2) return;
        if (len < 24) { insertion_sort(a + lo, (size_t)len, cmp); return; }
        if (depth-- == 0) { heapsort(a + lo, (size_t)len, cmp); return; }
        int64_t third = len / 3;
        if (cmp(a[lo + third], a[lo])) std::swap(a[lo], a[lo + third]);
        if (cmp(a[hi], a[hi - third])) std::swap(a[hi - third], a[hi]);
        if (cmp(a[hi], a[lo])) std::swap(a[lo], a[hi]);
        T p = a[lo], q = a[hi];
        int64_t lt = lo + 1, gt = hi - 1, i = lo + 1;
        while (i <= gt) {
            if (cmp(a[i], p)) { std::swap(a[i], a[lt]); ++lt; ++i; }
            else if (cmp(q, a[i])) {
                while (i < gt && cmp(q, a[gt])) --gt;
                std::swap(a[i], a[gt]); --gt;
            } else ++i;
        }
        --lt; ++gt;
        std::swap(a[lo], a[lt]); std::swap(a[hi], a[gt]);
        dual_pivot_rec(a, lo, lt - 1, depth, cmp);
        if (cmp(p, q)) dual_pivot_rec(a, lt + 1, gt - 1, depth, cmp);
        lo = gt + 1;                              // tail-iterate right part
    }
}

template <class T, class C>
void dual_pivot(T* a, size_t n, C cmp) {
    if (n < 2) return;
    int depth = 2 * (63 - __builtin_clzll(n));
    dual_pivot_rec(a, 0, (int64_t)n - 1, depth, cmp);
}

// ---------------------------------------------------------------------------
// branchless-Lomuto introsort ("Lomuto's comeback", Orson Peters 2023)
// ---------------------------------------------------------------------------

template <class T, class C>
T med3v(T x, T y, T z, C cmp) {                  // median by value
    if (cmp(y, x)) std::swap(x, y);
    if (cmp(z, y)) return cmp(z, x) ? x : z;
    return y;
}

// cyclic-swap partition by (v < piv); returns split m: [lo,m) < piv <= [m,hi)
template <class T, class C>
int64_t part_lt(T* a, int64_t lo, int64_t hi, T piv, C cmp) {
    int64_t l = lo;
    for (int64_t r = lo; r < hi; ++r) {
        T v = a[r];
        a[r] = a[l];
        a[l] = v;
        l += (int64_t)cmp(v, piv);
    }
    return l;
}

template <class T, class C>
int64_t part_le(T* a, int64_t lo, int64_t hi, T piv, C cmp) {
    int64_t l = lo;
    for (int64_t r = lo; r < hi; ++r) {
        T v = a[r];
        a[r] = a[l];
        a[l] = v;
        l += (int64_t)!cmp(piv, v);
    }
    return l;
}

template <class T, class C>
void bl_quick_rec(T* a, int64_t lo, int64_t hi, int depth, C cmp) {
    while (hi - lo > 24) {
        if (depth-- == 0) { heapsort(a + lo, (size_t)(hi - lo), cmp); return; }
        int64_t len = hi - lo;
        T piv;
        if (len > 512) {
            int64_t s = len / 8;
            piv = med3v(med3v(a[lo], a[lo + s], a[lo + 2 * s], cmp),
                        med3v(a[lo + 3 * s], a[lo + 4 * s], a[lo + 5 * s], cmp),
                        med3v(a[lo + 6 * s], a[lo + 7 * s], a[hi - 1], cmp), cmp);
        } else {
            piv = med3v(a[lo], a[lo + len / 2], a[hi - 1], cmp);
        }
        int64_t m = part_lt(a, lo, hi, piv, cmp);
        if (m == lo) {                            // piv is the minimum: strip equals
            lo = part_le(a, lo, hi, piv, cmp);
            continue;
        }
        if (m - lo < hi - m) { bl_quick_rec(a, lo, m, depth, cmp); lo = m; }
        else                 { bl_quick_rec(a, m, hi, depth, cmp); hi = m; }
    }
    insertion_sort(a + lo, (size_t)(hi - lo), cmp);
}

template <class T, class C>
void bl_quick(T* a, size_t n, C cmp) {
    if (n < 2) return;
    int depth = 2 * (63 - __builtin_clzll(n));
    bl_quick_rec(a, 0, (int64_t)n, depth, cmp);
}

// ---------------------------------------------------------------------------
// plain top-down mergesort (stable; binary-insertion base; n/2 buffer)
// ---------------------------------------------------------------------------

template <class T, class C>
void merge_td_rec(T* a, size_t lo, size_t hi, T* buf, C cmp) {
    if (hi - lo <= 24) { binary_insert_extend(a + lo, 1, hi - lo, cmp); return; }
    size_t mid = lo + (hi - lo) / 2;
    merge_td_rec(a, lo, mid, buf, cmp);
    merge_td_rec(a, mid, hi, buf, cmp);
    if (!cmp(a[mid], a[mid - 1])) return;         // halves already ordered
    g_merge_cost += hi - lo;
    size_t n1 = mid - lo;
    std::memcpy(buf, a + lo, n1 * sizeof(T));
    size_t i = 0, j = mid, d = lo;
    while (i < n1 && j < hi) {
        if (cmp(a[j], buf[i])) a[d++] = a[j++];
        else                   a[d++] = buf[i++];
    }
    if (i < n1) std::memcpy(a + d, buf + i, (n1 - i) * sizeof(T));
}

template <class T, class C>
void merge_td(T* a, size_t n, C cmp) {
    if (n < 2) return;
    std::unique_ptr<T[]> buf(new T[(n + 1) / 2]);
    merge_td_rec(a, 0, n, buf.get(), cmp);
}

// ---------------------------------------------------------------------------
// LSD radix sort (u64; non-comparison speed reference)
// ---------------------------------------------------------------------------

inline void radix_sort_u64(uint64_t* a, size_t n) {
    if (n < 2) return;
    std::unique_ptr<uint64_t[]> bufp(new uint64_t[n]);
    uint64_t* src = a;
    uint64_t* dst = bufp.get();
    for (int shift = 0; shift < 64; shift += 8) {
        size_t cnt[256] = {0};
        for (size_t i = 0; i < n; ++i) ++cnt[(src[i] >> shift) & 255];
        if (cnt[(src[0] >> shift) & 255] == n) continue;
        size_t p[256], pos = 0;
        for (int b = 0; b < 256; ++b) { p[b] = pos; pos += cnt[b]; }
        for (size_t i = 0; i < n; ++i) dst[p[(src[i] >> shift) & 255]++] = src[i];
        std::swap(src, dst);
    }
    if (src != a) std::memcpy(a, src, n * sizeof(uint64_t));
}

}  // namespace lab
