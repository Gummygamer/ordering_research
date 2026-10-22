// algos.h — instrumented sorting algorithms for the ordering-research lab.
//
// All algorithms operate on trivially-copyable T with a strict-weak "less"
// comparator Cmp. Comparison counting is done by wrapping Cmp (Counting<>),
// auxiliary memory by global operator new/delete instrumentation (main.cpp).
#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <memory>
#include <limits>
#include <random>
#include <type_traits>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

namespace lab {

extern uint64_t g_comps;       // incremented by Counting comparator
extern uint64_t g_merge_cost;  // summed merged spans after trimming
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

// Inversion-adaptive binary insertion. The adjacent check makes ordered input
// linear; for an out-of-place item, exponential search brackets its insertion
// point and binary search finds the stable upper bound. Element transport is
// proportional to the inversion count. A linear move budget bounds exposure
// on a misleading presortedness signal, then completes with std::sort.
template <class T, class C>
void inversion_binary_insertion_sort(T* a, size_t n, C cmp) {
    const size_t move_budget = n > std::numeric_limits<size_t>::max() / 16
        ? std::numeric_limits<size_t>::max() : 16 * n;
    size_t moved = 0;
    for (size_t i = 1; i < n; ++i) {
        if (!cmp(a[i], a[i - 1])) continue;
        T value = a[i];
        size_t step = 1;
        size_t left = 0;
        size_t right = i;
        while (step < i) {
            const size_t pos = i - step;
            if (!cmp(value, a[pos])) {
                left = pos + 1;
                break;
            }
            right = pos + 1;
            if (step > i / 2) break;
            step *= 2;
        }
        size_t lo = left, hi = right;
        while (lo < hi) {
            const size_t mid = lo + ((hi - lo) >> 1);
            if (cmp(value, a[mid])) hi = mid;
            else lo = mid + 1;
        }
        const size_t shift = i - lo;
        if (shift > move_budget - moved) {
            std::stable_sort(a, a + n, cmp);
            return;
        }
        std::memmove(a + lo + 1, a + lo, shift * sizeof(T));
        moved += shift;
        a[lo] = value;
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

// Current CPython development source emits a sequence of floor/ceil run targets
// rather than one fixed minrun. On all-short inputs this creates exactly 2^e
// nearly equal runs, avoiding the alphabetic-tree rounding loss of a fixed
// target.
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
                         BaseSorter base, size_t small_merge = 0,
                         size_t first_run = 0) {
    if (n < 2) return;
    assert(first_run <= n);
    MergeState<T, C> ms(a, n, cmp);
    ms.small_merge = small_merge;
    auto& p = ms.pending;

    auto next_run = [&](size_t lo, bool& forced) -> size_t {
        size_t run = lo == 0 && first_run != 0 ? first_run : count_run(a, lo, n, cmp);
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

// The caller supplies a verified ascending first run (reversing a strict
// descending run beforehand). Consume the usual first minrun target, while
// reusing the ordering work rather than scanning that run a second time.
template <class T, class C>
void powersort_from_first_run(T* a, size_t n, size_t first_run, C cmp) {
    assert(first_run > 0 && first_run <= n);
    MinRunGenerator minruns(n);
    powersort_impl_next(a, n, cmp, [&minruns]() { return minruns.next(); },
                        [](T* seg, size_t pre, size_t m, C c) {
                            binary_insert_extend(seg, pre, m, c);
                        }, 0, first_run);
}

// Fixed-minrun ablation matching the older CPython powersort run targeting.
template <class T, class C>
void powersort_fixed(T* a, size_t n, C cmp) {
    powersort_impl(a, n, cmp, compute_minrun(n),
                   [](T* seg, size_t pre, size_t m, C c) {
                       binary_insert_extend(seg, pre, m, c);
                   });
}

// Pingpong Powersort, following Moltmann, Nakajima, and Wild (ESA 2026).
// Runs on the pending stack are copied to an auxiliary array; the current run
// remains in the input. Each merge streams the stack run and current run into
// the input. The final merge can target the auxiliary array, but we keep the
// simpler input-destination path here so the implementation stays directly
// comparable to this lab's current Powersort run policy and galloping baseline.
// This variant intentionally uses ordinary stable merges (the paper's setup
// does not gallop), and therefore measures the few-moves choreography rather
// than the paper's separate virtual-page memory scheme.
template <class T, class C>
void pingpong_powersort(T* a, size_t n, C cmp) {
    if (n < 2) return;
    struct Run { size_t base, len; int power; };
    std::vector<Run> pending;
    pending.reserve(96);
    std::unique_ptr<T[]> saved(new T[n]);
    MinRunGenerator minruns(n);

    auto next_run = [&](size_t lo) {
        size_t run = count_run(a, lo, n, cmp);
        size_t minrun = minruns.next();
        if (run < minrun) {
            size_t force = std::min(minrun, n - lo);
            binary_insert_extend(a + lo, run, force, cmp);
            run = force;
        }
        return run;
    };
    auto node_power = [&](size_t s1, size_t n1, size_t n2) {
        int result = 0;
        uint64_t va = 2 * (uint64_t)s1 + n1;
        uint64_t vb = va + n1 + n2;
        for (;;) {
            ++result;
            if (va >= n) { va -= n; vb -= n; }
            else if (vb >= n) break;
            va <<= 1; vb <<= 1;
        }
        return result;
    };
    auto merge = [&](const Run& left, const Run& right) {
        assert(left.base + left.len == right.base);
        g_merge_cost += left.len + right.len;
        size_t i = 0, j = 0, out = left.base;
        const T* l = saved.get() + left.base;
        while (i < left.len && j < right.len) {
            if (cmp(a[right.base + j], l[i]))
                a[out++] = a[right.base + j++];
            else
                a[out++] = l[i++];
        }
        while (i < left.len) a[out++] = l[i++];
        // Any remaining right suffix is already in its final location.
    };

    size_t curr_base = 0;
    size_t curr_len = next_run(0);
    while (curr_base + curr_len < n) {
        const size_t next_base = curr_base + curr_len;
        const size_t next_len = next_run(next_base);
        const int power = node_power(curr_base, curr_len, next_len);
        while (!pending.empty() && pending.back().power >= power) {
            Run left = pending.back();
            pending.pop_back();
            merge(left, {curr_base, curr_len, 0});
            curr_base = left.base;
            curr_len += left.len;
        }
        std::memcpy(saved.get() + curr_base, a + curr_base,
                    curr_len * sizeof(T));
        pending.push_back({curr_base, curr_len, power});
        curr_base = next_base;
        curr_len = next_len;
    }
    while (!pending.empty()) {
        Run left = pending.back();
        pending.pop_back();
        merge(left, {curr_base, curr_len, 0});
        curr_base = left.base;
        curr_len += left.len;
    }
}

// ---------------------------------------------------------------------------
// Ford–Johnson merge-insertion (for small blocks; not stable)
// ---------------------------------------------------------------------------

inline constexpr int FJ_MAX = 2048;

// Sort ids[0..m) ascending by v[id]. ids are indices into v (all < FJ_MAX).
template <int CAP, bool FIRST_PAIR_ORDERED, class T, class C>
void fj_core_capped(const T* v, int* ids, int m, C cmp) {
    static_assert(CAP >= 2 && CAP <= FJ_MAX);
    if (m <= 1) return;
    if (m == 2) {
        if constexpr (!FIRST_PAIR_ORDERED) {
            if (cmp(v[ids[1]], v[ids[0]])) std::swap(ids[0], ids[1]);
        }
        return;
    }
    int half = m / 2;
    bool odd = (m & 1) != 0;
    int strag = odd ? ids[m - 1] : -1;

    int w[CAP / 2 + 1];
    int partner[CAP];
    for (int i = 0; i < half; ++i) {
        int x = ids[2 * i], y = ids[2 * i + 1];
        if constexpr (FIRST_PAIR_ORDERED) {
            if (i != 0 && cmp(v[y], v[x])) std::swap(x, y);
        } else {
            if (cmp(v[y], v[x])) std::swap(x, y);
        }
        w[i] = y; partner[y] = x;
    }

    // Only the root input pair came from count_run. Winner recursion has no
    // corresponding fact to reuse and always takes the ordinary path.
    fj_core_capped<CAP, false>(v, w, half, cmp); // sort winners (main chain)

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

template <int CAP, bool FIRST_PAIR_ORDERED, class T, class C>
void fj_sort_block_capped_impl(T* a, size_t m, C cmp) {
    static_assert(CAP >= 2 && CAP <= FJ_MAX);
    assert(m <= (size_t)CAP);
    if (m < 2) return;
    g_fj_largest_block = std::max(g_fj_largest_block, m);
    g_fj_scratch_cap = std::max(g_fj_scratch_cap, (size_t)CAP);
    int ids[CAP];
    for (int i = 0; i < (int)m; ++i) ids[i] = i;
    fj_core_capped<CAP, FIRST_PAIR_ORDERED>(a, ids, (int)m, cmp);
    T tmpb[CAP];
    std::memcpy(tmpb, a, m * sizeof(T));
    for (size_t i = 0; i < m; ++i) a[i] = tmpb[ids[i]];
}

template <int CAP, class T, class C>
void fj_sort_block_capped(T* a, size_t m, C cmp) {
    fj_sort_block_capped_impl<CAP, false>(a, m, cmp);
}

// count_run has already established a[0] <= a[1] under cmp. Reusing that fact
// skips exactly the ordinary root pair comparison; all later FJ decisions are
// unchanged. This entry point is only for base calls made after count_run.
template <int CAP, class T, class C>
void fj_sort_block_capped_known_pair(T* a, size_t m, C cmp) {
    assert(m >= 2);
    fj_sort_block_capped_impl<CAP, true>(a, m, cmp);
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
                       fj_sort_block_capped_known_pair<BLOCK>(seg, m, c);
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
                           fj_sort_block_capped_known_pair<BLOCK>(seg, m, c);
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
                fj_sort_block_capped_known_pair<64>(seg, m, c);
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
                           fj_sort_block_capped_known_pair<(int)MAX_BLOCK>(seg, m, c);
                   },
                   g_small_merge);
}

template <class T, class C>
void hybrid_fj_auto(T* a, size_t n, C cmp) {
    hybrid_fj_auto_capped<128>(a, n, cmp);
}

// ---------------------------------------------------------------------------
// sampled portfolio gate: powersort_fj vs. hybrid_fj_auto_capped<2048>
// ---------------------------------------------------------------------------

// Telemetry for selftest accounting; the benchmark CSV schema is unchanged.
extern uint64_t g_gate_probe_comps;  // comparator calls spent probing
extern int g_gate_choice;            // branch selected by the active hybrid gate

// The displacement grid (results/displaw_1c32397_analysis.md) gave sharp
// sampled crossovers: auto2048 wins random permutations and disp>=1024 by up
// to ~0.09 comparisons/element but loses up to ~6.6 on structured inputs,
// while PFJ never lost to Powersort. With stakes that asymmetric the gate
// probes through the counted comparator and selects auto2048 only when every
// disorder test passes; any veto falls back to PFJ. The tests: a duplicate
// veto that counts equal pairs over the full adjacent sample and fires iff
// equal_pairs * 112 >= adjacent — a cardinality estimate at boundary K=112,
// pre-registered in results/duplaw_498b627_analysis.md from the measured
// auto2048/PFJ crossover K in (96, 128); an adjacent-descent window (natural
// runs and near-sortedness); and inversion fractions at dyadic distances
// 64/256/1024. Displacement thresholds come from the dispX noise model
// P(inversion at distance d) ~= Phi(-d/(sqrt(2)*sigma)) fitted to the
// seeds-1..3 crossover labels; the deep-disorder rule accepts sigma >= ~700
// and random permutations with >=3-sigma sampling margins. Probe indices use
// a fixed-seed generator, so the gate is a deterministic function of the
// input. This is a distributional portfolio heuristic, not an adversarial
// guarantee, and both branches are unstable.
template <class T, class C>
void hybrid_gate(T* a, size_t n, C cmp) {
    constexpr size_t GATE_MIN_N = 131072;  // below: probes cost too much of n
    g_gate_probe_comps = 0;
    if (n < GATE_MIN_N) {
        g_gate_choice = 0;
        powersort_fj(a, n, cmp);
        return;
    }
    std::mt19937_64 rng(0x6A7E5EEDULL);
    const size_t adjacent = std::min<size_t>(2048, n / 512);
    const size_t per_distance = std::min<size_t>(1024, n / 1024);
    constexpr size_t DUP_VETO_K = 112;  // veto iff K-hat <= 112; see above
    size_t descents = 0, equal_pairs = 0;
    for (size_t t = 0; t < adjacent; ++t) {
        size_t i = (size_t)(rng() % (n - 1));
        ++g_gate_probe_comps;
        if (cmp(a[i + 1], a[i])) { ++descents; continue; }
        ++g_gate_probe_comps;
        if (!cmp(a[i], a[i + 1])) ++equal_pairs;
    }
    bool deep = equal_pairs * DUP_VETO_K < adjacent;
    deep = deep && descents * 10 >= adjacent * 3 && descents * 10 <= adjacent * 7;
    constexpr size_t distances[3] = {64, 256, 1024};
    constexpr size_t inv_min_permille[3] = {350, 300, 150};
    for (int k = 0; deep && k < 3; ++k) {
        const size_t d = distances[k];
        size_t inversions = 0;
        for (size_t t = 0; t < per_distance; ++t) {
            size_t i = (size_t)(rng() % (n - d));
            ++g_gate_probe_comps;
            if (cmp(a[i + d], a[i])) ++inversions;
        }
        deep = inversions * 1000 >= inv_min_permille[k] * per_distance;
    }
    if (deep) {
        g_gate_choice = 2;
        hybrid_fj_auto_capped<2048>(a, n, cmp);
    } else {
        g_gate_choice = 1;
        powersort_fj(a, n, cmp);
    }
}

// Empirical displacement ladder. Adjacent/equality samples reject clearly
// structured or duplicate-heavy inputs; a 256-position inversion sample
// then selects among the FJ block caps observed to win at increasing
// displacement scales. This is a distribution-specific portfolio heuristic,
// not a worst-case guarantee. The thresholds are deliberately exposed in the
// research notes and evaluated on held-out seeds.
template <class T, class C>
void hybrid_ladder(T* a, size_t n, C cmp) {
    constexpr size_t MIN_N = 131072;
    g_gate_probe_comps = 0;
    if (n < MIN_N) {
        g_gate_choice = 0;
        powersort_fj(a, n, cmp);
        return;
    }
    std::mt19937_64 rng(0x1ADD3A5EULL);
    const size_t adjacent = std::min<size_t>(2048, n / 512);
    const size_t per_distance = std::min<size_t>(4096, n / 128);
    size_t descents = 0, equal_pairs = 0;
    for (size_t t = 0; t < adjacent; ++t) {
        const size_t i = (size_t)(rng() % (n - 1));
        ++g_gate_probe_comps;
        if (cmp(a[i + 1], a[i])) { ++descents; continue; }
        ++g_gate_probe_comps;
        if (!cmp(a[i], a[i + 1])) ++equal_pairs;
    }
    // The existing gate's pre-registered K=112 cardinality boundary.
    bool eligible = equal_pairs * 112 < adjacent;
    eligible = eligible && descents * 10 >= adjacent * 3 &&
               descents * 10 <= adjacent * 7;
    size_t inversions = 0;
    constexpr size_t probe_distance = 256;
    if (eligible) {
        for (size_t t = 0; t < per_distance; ++t) {
            const size_t i = (size_t)(rng() % (n - probe_distance));
            ++g_gate_probe_comps;
            if (cmp(a[i + probe_distance], a[i])) ++inversions;
        }
    }
    // Approximate Phi(-256/(sqrt(2)*sigma)) bins, used only as a
    // predictor over the existing sigma/distribution suite.
    const size_t rate = eligible ? inversions * 1000 / per_distance : 0;
    if (!eligible || rate < 20) {
        g_gate_choice = 1;
        powersort_fj(a, n, cmp);
    } else if (rate < 160) {
        g_gate_choice = 3;
        hybrid_fj_auto_capped<128>(a, n, cmp);
    } else if (rate < 300) {
        g_gate_choice = 4;
        hybrid_fj_auto_capped<512>(a, n, cmp);
    } else if (rate < 400) {
        g_gate_choice = 5;
        hybrid_fj_auto_capped<1024>(a, n, cmp);
    } else {
        g_gate_choice = 2;
        hybrid_fj_auto_capped<2048>(a, n, cmp);
    }
}

// Runtime portfolio based on stratified natural-run density. The caller owns
// probe accounting so this helper can be composed into a second-level policy.
template <class T, class C>
void run_gate_sort_by_density(T* a, size_t n, C cmp) {
    std::mt19937_64 rng(0x5A7A11ULL);
    constexpr size_t BINS = 16;
    constexpr size_t PER_BIN = 128;
    constexpr size_t MONOTONE_PERMILLE = 20;
    size_t low_run_bins = 0;
    for (size_t b = 0; b < BINS; ++b) {
        const size_t lo = b * n / BINS;
        const size_t hi = (b + 1) * n / BINS;
        const size_t span = hi - lo;
        size_t ascents = 0, descents = 0;
        for (size_t t = 0; t < PER_BIN; ++t) {
            const size_t i = lo + (size_t)(rng() % (span - 1));
            ++g_gate_probe_comps;
            if (cmp(a[i + 1], a[i])) {
                ++descents;
            } else {
                ++g_gate_probe_comps;
                if (cmp(a[i], a[i + 1])) ++ascents;
            }
        }
        if (ascents * 1000 <= MONOTONE_PERMILLE * PER_BIN ||
            descents * 1000 <= MONOTONE_PERMILLE * PER_BIN)
            ++low_run_bins;
    }
    const bool low_run_density = low_run_bins >= 13;
    if (low_run_density) {
        g_gate_choice = 7;
        powersort(a, n, cmp);
    } else {
        g_gate_choice = 8;
        std::sort(a, a + n, cmp);
    }
}

// Runtime portfolio based on stratified natural-run density. A set of bins
// that are each nearly monotone predicts long runs and locally concentrated
// disorder (for example, a sorted prefix with a random tail). Powersort can
// exploit that structure without making std::sort scan the whole array.
// Thresholds are host/workload hypotheses, not a speed guarantee.
template <class T, class C>
void hybrid_run_gate(T* a, size_t n, C cmp) {
    constexpr size_t MIN_N = 131072;
    g_gate_probe_comps = 0;
    if (n < MIN_N) {
        g_gate_choice = 0;
        std::sort(a, a + n, cmp);
        return;
    }
    run_gate_sort_by_density(a, n, cmp);
}

// Inversion-sensitive portfolio. A short adjacent sample protects fully
// monotone inputs, which Powersort handles particularly well. A fixed-lag
// inversion sample then estimates whether disorder remains local: low rates
// at lag 64 route to inversion-sensitive binary insertion; otherwise the
// existing natural-run gate chooses its runtime branch. The insertion
// candidate has an O(n) move budget and falls back to std::sort on overflow.
// The cutoff is empirical for the declared displacement workloads.
template <class T, class C>
void hybrid_inversion_gate(T* a, size_t n, C cmp) {
    constexpr size_t MIN_N = 131072;
    constexpr size_t ADJ_SAMPLES = 256;
    constexpr size_t GAP = 64;
    constexpr size_t GAP_SAMPLES = 2048;
    constexpr size_t MAX_GAP_INVERSIONS = 8;
    g_gate_probe_comps = 0;
    if (n < MIN_N) {
        g_gate_choice = 0;
        std::sort(a, a + n, cmp);
        return;
    }
    std::mt19937_64 rng(0x1A7E510ULL);
    size_t adjacent_descents = 0;
    for (size_t t = 0; t < ADJ_SAMPLES; ++t) {
        const size_t i = (size_t)(rng() % (n - 1));
        ++g_gate_probe_comps;
        if (cmp(a[i + 1], a[i])) ++adjacent_descents;
    }
    if (adjacent_descents == 0) {
        // No sampled adjacent inversions strongly suggests long monotone
        // regions; use the run-adaptive branch directly and avoid a second
        // round of samples on this fast path.
        g_gate_choice = 7;
        powersort(a, n, cmp);
        return;
    }
    size_t gap_inversions = 0;
    for (size_t t = 0; t < GAP_SAMPLES; ++t) {
        const size_t i = (size_t)(rng() % (n - GAP));
        ++g_gate_probe_comps;
        if (cmp(a[i + GAP], a[i])) ++gap_inversions;
    }
    if (gap_inversions <= MAX_GAP_INVERSIONS) {
        g_gate_choice = 9;
        inversion_binary_insertion_sort(a, n, cmp);
    } else {
        run_gate_sort_by_density(a, n, cmp);
    }
}

// Self-verifying bounded-displacement sorter. For an input whose maximum
// rank displacement is Delta, a min-heap over Delta+1 consecutive unread
// values emits the next sorted item. Since Delta is unknown, start with a
// small window and double it after any emitted-order violation. Each attempt
// writes into a separate buffer, so failed guesses leave the input intact.
// The final width n is a heap sort and therefore guarantees correctness for
// every strict-weak-order comparator. This trades O(n) output storage for an
// exact, distribution-free verifier around the displacement-sensitive core.
template <class T, class C>
void adaptive_window_heap_sort(T* a, size_t n, C cmp) {
    if (n < 2) return;

    std::vector<T> output(n);
    std::vector<T> heap;
    size_t width = std::min<size_t>(n, 8);

    for (;;) {
        heap.clear();
        heap.reserve(width);
        size_t next = 0;
        const size_t initial = std::min(width, n);
        for (; next < initial; ++next) heap.push_back(a[next]);

        auto push = [&](T value) {
            heap.push_back(std::move(value));
            size_t child = heap.size() - 1;
            while (child > 0) {
                const size_t parent = (child - 1) / 2;
                if (!cmp(heap[child], heap[parent])) break;
                std::swap(heap[child], heap[parent]);
                child = parent;
            }
        };
        auto pop_min = [&]() {
            T result = std::move(heap.front());
            if (heap.size() == 1) {
                heap.pop_back();
                return result;
            }
            heap.front() = std::move(heap.back());
            heap.pop_back();
            size_t parent = 0;
            for (;;) {
                const size_t left = parent * 2 + 1;
                if (left >= heap.size()) break;
                size_t child = left;
                const size_t right = left + 1;
                if (right < heap.size() && cmp(heap[right], heap[left]))
                    child = right;
                if (!cmp(heap[child], heap[parent])) break;
                std::swap(heap[parent], heap[child]);
                parent = child;
            }
            return result;
        };

        bool ordered = true;
        size_t written = 0;
        while (!heap.empty()) {
            T value = pop_min();
            if (written > 0 && cmp(value, output[written - 1])) {
                ordered = false;
                break;
            }
            output[written++] = std::move(value);
            if (next < n) push(a[next++]);
        }
        if (ordered && written == n) {
            std::move(output.begin(), output.end(), a);
            return;
        }
        if (width == n) {
            // A valid strict weak ordering makes this unreachable: with a
            // full-input heap, each emitted item is globally minimal.
            std::sort(a, a + n, cmp);
            return;
        }
        width = width > n / 2 ? n : width * 2;
    }
}

// Deletion-backbone sorter. A descent between the current backbone top and
// the next input item is a witnessed inversion. Removing both endpoints and
// continuing leaves a nondecreasing subsequence. These disjoint inversion
// pairs imply that q removed items satisfy q <= 2k, where k is the minimum
// deletions needed to obtain a nondecreasing subsequence (n - LNDS length).
// Sort the outliers and merge them backward into the compacted backbone. The
// outlier budget bounds storage and restores the processed prefix before the
// std::sort fallback; the input therefore remains exactly sortable on every
// path, without trusting a sample estimate of k.
template <class T, class C>
void rotation_merge(T* a, size_t first, size_t middle, size_t last, C cmp) {
    if (first == middle || middle == last) return;
    if (!cmp(a[middle], a[middle - 1])) return;
    if (last - first == 2) {
        std::swap(a[first], a[middle]);
        return;
    }

    size_t first_cut;
    size_t second_cut;
    if (middle - first > last - middle) {
        first_cut = first + (middle - first) / 2;
        second_cut = static_cast<size_t>(
            std::lower_bound(a + middle, a + last, a[first_cut], cmp) - a);
    } else {
        second_cut = middle + (last - middle) / 2;
        first_cut = static_cast<size_t>(
            std::upper_bound(a + first, a + middle, a[second_cut], cmp) - a);
    }
    const size_t new_middle = static_cast<size_t>(
        std::rotate(a + first_cut, a + middle, a + second_cut) - a);
    rotation_merge(a, first, first_cut, new_middle, cmp);
    rotation_merge(a, new_middle, second_cut, last, cmp);
}

template <class T, class C>
void deletion_backbone_sort_impl(T* a, size_t n, C cmp,
                                 bool route_late_overflow,
                                 bool preserve_backbone_late = false,
                                 bool rotate_merge_late = false) {
    if (n < 2) return;
    const size_t budget = std::max<size_t>(2, n / 16);
    std::vector<T> outliers;
    size_t backbone = 0;
    for (size_t read = 0; read < n; ++read) {
        if (backbone == 0 || !cmp(a[read], a[backbone - 1])) {
            if (backbone != read) a[backbone] = std::move(a[read]);
            ++backbone;
            continue;
        }
        if (outliers.empty()) outliers.reserve(std::min<size_t>(budget + 2, 4096));
        outliers.push_back(std::move(a[backbone - 1]));
        outliers.push_back(std::move(a[read]));
        --backbone;
        if (outliers.size() > budget) {
            if (route_late_overflow && preserve_backbone_late &&
                read >= n / 4) {
                // The unread suffix is untouched. Complete a sorted prefix
                // from the backbone and extracted outliers, sort only that
                // suffix, then merge the two sorted ranges.
                const size_t prefix = read + 1;
                std::sort(outliers.begin(), outliers.end(), cmp);
                size_t left = backbone;
                size_t right = outliers.size();
                size_t out = prefix;
                while (left > 0 && right > 0) {
                    if (cmp(outliers[right - 1], a[left - 1]))
                        a[--out] = std::move(a[--left]);
                    else
                        a[--out] = std::move(outliers[--right]);
                }
                while (right > 0) a[--out] = std::move(outliers[--right]);
                powersort(a + prefix, n - prefix, cmp);
                if (rotate_merge_late)
                    rotation_merge(a, 0, prefix, n, cmp);
                else
                    std::inplace_merge(a, a + prefix, a + n, cmp);
                return;
            }
            // backbone + outliers.size() == read + 1: restore the exact
            // processed multiset, leaving the unread suffix untouched.
            for (size_t j = 0; j < outliers.size(); ++j)
                a[backbone + j] = std::move(outliers[j]);
            if (route_late_overflow && read >= n / 4)
                powersort(a, n, cmp);
            else
                std::sort(a, a + n, cmp);
            return;
        }
    }

    if (outliers.empty()) return;
    std::sort(outliers.begin(), outliers.end(), cmp);
    size_t left = backbone;
    size_t right = outliers.size();
    size_t out = n;
    while (left > 0 && right > 0) {
        if (cmp(outliers[right - 1], a[left - 1]))
            a[--out] = std::move(a[--left]);
        else
            a[--out] = std::move(outliers[--right]);
    }
    while (right > 0) a[--out] = std::move(outliers[--right]);
}

template <class T, class C>
void deletion_backbone_sort(T* a, size_t n, C cmp) {
    deletion_backbone_sort_impl(a, n, cmp, false);
}

// A fallback portfolio using scan progress as a cheap signal: reaching the
// outlier budget late suggests a sparse-corruption input whose many surviving
// ordered runs favor Powersort; reaching it early suggests broad disorder and
// routes to std::sort. The n/4 decision is empirical and does not affect
// correctness; both fallback branches receive a restored permutation.
template <class T, class C>
void deletion_backbone_route(T* a, size_t n, C cmp) {
    deletion_backbone_sort_impl(a, n, cmp, true);
}

// Late-overflow ablation: preserve the completed sorted backbone, then sort
// only the untouched suffix with Powersort and merge the two sorted ranges.
// The n/4 routing cutoff is inherited unchanged from deletion_backbone_route.
template <class T, class C>
void deletion_backbone_preserve_sort(T* a, size_t n, C cmp) {
    deletion_backbone_sort_impl(a, n, cmp, true, true);
}

// Memory-conscious final merge: use recursive binary partitioning and
// rotations instead of std::inplace_merge's temporary buffer. Auxiliary
// merge state is logarithmic stack space; element rotation work is higher.
template <class T, class C>
void deletion_backbone_rotate_sort(T* a, size_t n, C cmp) {
    deletion_backbone_sort_impl(a, n, cmp, true, true, true);
}

// Stratified adjacent-descent router for sparse extreme-key corruption.
// If disorder is localized to a few bins, Powersort retains its run advantage.
// If each bin has modest but distributed descent density, the deletion-backbone
// continuation exploits the sorted subsequence. Broad disorder goes to std::sort.
template <class T, class C>
void hybrid_backbone_gate(T* a, size_t n, C cmp) {
    constexpr size_t MIN_N = 131072;
    constexpr size_t BINS = 16;
    constexpr size_t PER_BIN = 64;
    constexpr size_t MONOTONE_PERMILLE = 20;
    constexpr size_t MAX_DESCENT_PERMILLE = 125;
    g_gate_probe_comps = 0;
    if (n < MIN_N) {
        g_gate_choice = 0;
        std::sort(a, a + n, cmp);
        return;
    }

    std::mt19937_64 rng(0xBACC0AE5ULL);
    size_t low_run_bins = 0;
    size_t active_bins = 0;
    size_t total_descents = 0;
    for (size_t bin = 0; bin < BINS; ++bin) {
        const size_t lo = bin * n / BINS;
        const size_t hi = (bin + 1) * n / BINS;
        const size_t span = hi - lo;
        size_t ascents = 0;
        size_t descents = 0;
        for (size_t trial = 0; trial < PER_BIN; ++trial) {
            const size_t i = lo + static_cast<size_t>(rng() % (span - 1));
            ++g_gate_probe_comps;
            if (cmp(a[i + 1], a[i])) {
                ++descents;
            } else {
                ++g_gate_probe_comps;
                if (cmp(a[i], a[i + 1])) ++ascents;
            }
        }
        total_descents += descents;
        if (descents > 0) ++active_bins;
        if (ascents * 1000 <= MONOTONE_PERMILLE * PER_BIN ||
            descents * 1000 <= MONOTONE_PERMILLE * PER_BIN)
            ++low_run_bins;
    }

    const bool sparse_scattered = total_descents > 0 && active_bins >= 4 &&
        total_descents * 1000 <= MAX_DESCENT_PERMILLE * BINS * PER_BIN;
    if (sparse_scattered ||
        (low_run_bins < 13 && total_descents * 1000 <=
         MAX_DESCENT_PERMILLE * BINS * PER_BIN)) {
        g_gate_choice = 11;
        deletion_backbone_preserve_sort(a, n, cmp);
    } else if (low_run_bins >= 13) {
        g_gate_choice = 10;
        powersort(a, n, cmp);
    } else {
        g_gate_choice = 12;
        std::sort(a, a + n, cmp);
    }
}

// Sequential descent-density portfolio. The outpct model has expected
// descent density d=p-p^2/2, so invert it to estimate corruption fraction
// p=1-sqrt(1-2d). A normal interval avoids committing to a route near either
// boundary: sparse corruption uses the deletion-backbone repair, medium
// corruption uses Powersort, and broad disorder uses std::sort. Sampling is
// stratified by position and doubles only while an uncertainty interval
// overlaps a route boundary. The low-run/activity check keeps localized
// disorder (for example, a random tail) on Powersort.
template <class T, class C>
void hybrid_descent_portfolio(T* a, size_t n, C cmp) {
    constexpr size_t MIN_N = 131072;
    constexpr size_t BINS = 16;
    constexpr size_t INITIAL_PER_BIN = 64;
    constexpr size_t MAX_PER_BIN = 512;
    constexpr size_t MONOTONE_PERMILLE = 20;
    constexpr double SPARSE_P = 0.125;
    constexpr double BROAD_P = 0.45;
    g_gate_probe_comps = 0;
    if (n < MIN_N) {
        g_gate_choice = 0;
        std::sort(a, a + n, cmp);
        return;
    }

    std::mt19937_64 rng(0xD35C3A71ULL);
    std::array<size_t, BINS> ascents{};
    std::array<size_t, BINS> descents{};
    size_t per_bin = 0;
    double descent_rate = 0.0;
    double p_lower = 0.0;
    double p_upper = 1.0;
    size_t active_bins = 0;
    size_t low_run_bins = 0;
    bool localized_or_monotone = false;

    for (size_t target = INITIAL_PER_BIN; target <= MAX_PER_BIN; target *= 2) {
        for (size_t bin = 0; bin < BINS; ++bin) {
            const size_t lo = bin * n / BINS;
            const size_t hi = (bin + 1) * n / BINS;
            const size_t span = hi - lo;
            for (size_t trial = per_bin; trial < target; ++trial) {
                const size_t i = lo + static_cast<size_t>(rng() % (span - 1));
                ++g_gate_probe_comps;
                if (cmp(a[i + 1], a[i])) {
                    ++descents[bin];
                } else {
                    ++g_gate_probe_comps;
                    if (cmp(a[i], a[i + 1])) ++ascents[bin];
                }
            }
        }
        per_bin = target;
        size_t total_ascents = 0;
        size_t total_descents = 0;
        active_bins = 0;
        low_run_bins = 0;
        size_t low_ascending_bins = 0;
        for (size_t bin = 0; bin < BINS; ++bin) {
            total_ascents += ascents[bin];
            total_descents += descents[bin];
            if (descents[bin] != 0) ++active_bins;
            if (ascents[bin] * 1000 <= MONOTONE_PERMILLE * per_bin ||
                descents[bin] * 1000 <= MONOTONE_PERMILLE * per_bin)
                ++low_run_bins;
            if (ascents[bin] * 1000 <= MONOTONE_PERMILLE * per_bin)
                ++low_ascending_bins;
        }

        const size_t samples = BINS * per_bin;
        const double sample_count = static_cast<double>(samples);
        descent_rate = static_cast<double>(total_descents) / sample_count;
        const double margin = 1.96 * std::sqrt(
            descent_rate * (1.0 - descent_rate) / sample_count) +
            1.0 / sample_count;
        const double d_lower = std::max(0.0, descent_rate - margin);
        const double d_upper = std::min(0.5, descent_rate + margin);
        auto invert_density = [](double d) {
            return 1.0 - std::sqrt(std::max(0.0, 1.0 - 2.0 * d));
        };
        p_lower = invert_density(d_lower);
        p_upper = invert_density(d_upper);

        // Sorted, reversed, and localized-tail inputs have many low-run bins
        // but do not have the distributed nonzero descents of outpct inputs.
        localized_or_monotone = low_run_bins >= 13 &&
            (active_bins < 4 || low_ascending_bins >= 13);
        if (localized_or_monotone) break;

        const bool sparse_route = active_bins >= 4 && p_upper < SPARSE_P;
        const bool powersort_route = p_lower > SPARSE_P && p_upper < BROAD_P;
        const bool std_route = p_lower >= BROAD_P;
        if (sparse_route || powersort_route || std_route) break;
    }

    if (localized_or_monotone) {
        g_gate_choice = 10;
        powersort(a, n, cmp);
    } else if (active_bins >= 4 && p_upper < SPARSE_P) {
        g_gate_choice = 11;
        deletion_backbone_preserve_sort(a, n, cmp);
    } else if (p_lower > SPARSE_P && p_upper < BROAD_P) {
        g_gate_choice = 10;
        powersort(a, n, cmp);
    } else {
        // At the sample cap, route ambiguous cases by the point estimate but
        // require a separated interval before choosing the specialized path.
        const double p_hat = 1.0 - std::sqrt(
            std::max(0.0, 1.0 - 2.0 * descent_rate));
        if (p_hat >= BROAD_P) {
            g_gate_choice = 12;
            std::sort(a, a + n, cmp);
        } else {
            g_gate_choice = 10;
            powersort(a, n, cmp);
        }
    }
}

// Quantile-peeling sort for inputs whose disorder consists of scattered
// high keys above an ordered backbone. A descent sample estimates p via
// d=p-p^2/2; a conservative sample quantile supplies a pivot. The scan peels
// values at/above the pivot while certifying that the remainder is ordered.
// On a successful certificate, sort the peeled values and merge them back
// into the backbone. A failed certificate restores the same permutation and
// lets Powersort handle the resulting ordered-prefix/unordered-suffix layout.
template <class T, class C>
void hybrid_quantile_backbone(T* a, size_t n, C cmp) {
    constexpr size_t MIN_N = 131072;
    constexpr size_t BINS = 16;
    constexpr size_t PER_BIN = 64;
    constexpr size_t SAMPLE_KEYS = BINS * PER_BIN * 2;
    constexpr size_t MONOTONE_PERMILLE = 20;
    g_gate_probe_comps = 0;
    if (n < MIN_N) {
        g_gate_choice = 0;
        std::sort(a, a + n, cmp);
        return;
    }

    std::mt19937_64 rng(0x51A7E2A1ULL);
    std::vector<T> sample;
    sample.reserve(SAMPLE_KEYS);
    std::array<size_t, BINS> ascents{};
    std::array<size_t, BINS> descents{};
    auto probe_cmp = [&](const T& x, const T& y) {
        ++g_gate_probe_comps;
        return cmp(x, y);
    };
    for (size_t bin = 0; bin < BINS; ++bin) {
        const size_t lo = bin * n / BINS;
        const size_t hi = (bin + 1) * n / BINS;
        const size_t span = hi - lo;
        for (size_t trial = 0; trial < PER_BIN; ++trial) {
            const size_t i = lo + static_cast<size_t>(rng() % (span - 1));
            sample.push_back(a[i]);
            sample.push_back(a[i + 1]);
            if (probe_cmp(a[i + 1], a[i])) {
                ++descents[bin];
            } else if (probe_cmp(a[i], a[i + 1])) {
                ++ascents[bin];
            }
        }
    }

    size_t total_descents = 0;
    size_t active_bins = 0;
    size_t low_run_bins = 0;
    size_t low_ascending_bins = 0;
    for (size_t bin = 0; bin < BINS; ++bin) {
        total_descents += descents[bin];
        if (descents[bin] != 0) ++active_bins;
        if (ascents[bin] * 1000 <= MONOTONE_PERMILLE * PER_BIN ||
            descents[bin] * 1000 <= MONOTONE_PERMILLE * PER_BIN)
            ++low_run_bins;
        if (ascents[bin] * 1000 <= MONOTONE_PERMILLE * PER_BIN)
            ++low_ascending_bins;
    }
    if (low_run_bins >= 13 &&
        (active_bins < 4 || low_ascending_bins >= 13)) {
        g_gate_choice = 10;
        powersort(a, n, cmp);
        return;
    }

    const double descent_rate = static_cast<double>(total_descents) /
                                static_cast<double>(BINS * PER_BIN);
    const double margin = 1.96 * std::sqrt(
        descent_rate * (1.0 - descent_rate) /
        static_cast<double>(BINS * PER_BIN)) +
        1.0 / static_cast<double>(BINS * PER_BIN);
    const double p_upper = 1.0 - std::sqrt(std::max(
        0.0, 1.0 - 2.0 * std::min(0.5, descent_rate + margin)));
    if (p_upper >= 0.5) {
        g_gate_choice = 12;
        std::sort(a, a + n, cmp);
        return;
    }

    // Inflate the estimated high-key fraction to absorb both descent-rate
    // uncertainty and the finite sample-quantile error. Excess ordinary high
    // keys are harmless; a missed exceptional key is caught by verification.
    const double quantile_margin = 1.96 * std::sqrt(
        p_upper * (1.0 - p_upper) / static_cast<double>(SAMPLE_KEYS)) +
        1.0 / static_cast<double>(SAMPLE_KEYS);
    const double high_fraction = std::min(0.5, p_upper + quantile_margin);
    const size_t pivot_rank = std::min(SAMPLE_KEYS - 1,
        static_cast<size_t>((1.0 - high_fraction) * SAMPLE_KEYS));
    std::nth_element(sample.begin(), sample.begin() + pivot_rank, sample.end(),
                     probe_cmp);
    const T pivot = sample[pivot_rank];

    const size_t reserve_hint = std::min(n / 2,
        std::max<size_t>(32, static_cast<size_t>(
            static_cast<double>(n) * high_fraction)));
    std::vector<T> high;
    high.reserve(reserve_hint);
    size_t backbone = 0;
    bool ordered_backbone = true;
    for (size_t read = 0; read < n; ++read) {
        if (cmp(a[read], pivot)) {
            if (backbone > 0 && cmp(a[read], a[backbone - 1]))
                ordered_backbone = false;
            if (backbone != read) a[backbone] = std::move(a[read]);
            ++backbone;
        } else {
            high.push_back(std::move(a[read]));
        }
    }

    if (!ordered_backbone || high.size() > n / 2) {
        for (size_t i = 0; i < high.size(); ++i)
            a[backbone + i] = std::move(high[i]);
        g_gate_choice = 10;
        powersort(a, n, cmp);
        return;
    }
    if (high.empty()) {
        g_gate_choice = 13;
        return;
    }

    std::sort(high.begin(), high.end(), cmp);
    size_t left = backbone;
    size_t right = high.size();
    size_t out = n;
    while (left > 0 && right > 0) {
        if (cmp(high[right - 1], a[left - 1]))
            a[--out] = std::move(a[--left]);
        else
            a[--out] = std::move(high[--right]);
    }
    while (right > 0) a[--out] = std::move(high[--right]);
    g_gate_choice = 13;
}

// The quicksort definition follows the adaptive portfolios. Declare it here
// so generic comparators from outside lab do not depend on ADL to find it.
template <class T, class C>
void bl_quick(T* a, size_t n, C cmp);

// General-purpose portfolio: use sampled descents, positional shape, and
// multi-distance inversions to route among established adaptive sorting
// strategies. Comparisons aid diagnosis; the objective is measured latency.
template <class T, class C>
void hybrid_general_portfolio(T* a, size_t n, C cmp) {
    constexpr size_t MIN_N = 131072;
    constexpr size_t BINS = 16;
    g_gate_probe_comps = 0;
    if (n < MIN_N) {
        g_gate_choice = 0;
        std::sort(a, a + n, cmp);
        return;
    }
    const size_t per_bin = n < 500000 ? 24 : 32;
    const size_t sample_pairs = BINS * per_bin;
    const double sample_pair_count = static_cast<double>(sample_pairs);
    std::mt19937_64 rng(0x6E3A91D5ULL);
    std::array<size_t, BINS> ascents{};
    std::array<size_t, BINS> descents{};
    size_t equal_pairs = 0;
    std::vector<T> sampled_left_values;
    sampled_left_values.reserve(sample_pairs);
    std::vector<T> descent_left_values;
    descent_left_values.reserve(sample_pairs);
    std::vector<T> representatives;
    representatives.reserve(BINS);
    auto probe_cmp = [&](const T& x, const T& y) {
        ++g_gate_probe_comps;
        return cmp(x, y);
    };

    for (size_t bin = 0; bin < BINS; ++bin) {
        const size_t lo = bin * n / BINS;
        const size_t hi = (bin + 1) * n / BINS;
        const size_t span = hi - lo;
        representatives.push_back(a[lo + span / 2]);
        for (size_t trial = 0; trial < per_bin; ++trial) {
            const size_t i = lo + static_cast<size_t>(rng() % (span - 1));
            sampled_left_values.push_back(a[i]);
            if (probe_cmp(a[i + 1], a[i])) {
                ++descents[bin];
                descent_left_values.push_back(a[i]);
            } else if (probe_cmp(a[i], a[i + 1])) {
                ++ascents[bin];
            } else {
                ++equal_pairs;
            }
        }
    }

    size_t total_ascents = 0;
    size_t total_descents = 0;
    size_t monotone_bins = 0;
    size_t active_bins = 0;
    size_t first_active_bin = BINS;
    size_t last_active_bin = 0;
    for (size_t bin = 0; bin < BINS; ++bin) {
        total_ascents += ascents[bin];
        total_descents += descents[bin];
        if (descents[bin] > 0) {
            ++active_bins;
            first_active_bin = std::min(first_active_bin, bin);
            last_active_bin = bin;
        }
        if (ascents[bin] == 0 || descents[bin] == 0) ++monotone_bins;
    }

    // A few values sampled at fixed positional landmarks expose globally
    // monotone and single-turn shapes while random collections of sorted
    // blocks still look unordered. A separate low-activity route admits a
    // small noisy suffix without classifying shuffled sorted blocks as runs.
    size_t direction_changes = 0;
    int previous_direction = 0;
    for (size_t i = 1; i < representatives.size(); ++i) {
        int direction = 0;
        if (probe_cmp(representatives[i], representatives[i - 1])) {
            direction = -1;
        } else if (probe_cmp(representatives[i - 1], representatives[i])) {
            direction = 1;
        }
        if (direction != 0) {
            if (previous_direction != 0 && direction != previous_direction)
                ++direction_changes;
            previous_direction = direction;
        }
    }
    const double descent_rate = static_cast<double>(total_descents) /
                                sample_pair_count;
    size_t large_gap_inversions = 0;
    bool sampled_large_gap = false;
    if (descent_rate < 0.05 || active_bins <= 3) {
        // Two scales avoid aliasing the period of shuffled fixed-size runs.
        // A single n/32 gap can be nearly aligned with each run, making the
        // later point systematically farther along its sorted block.
        const std::array<size_t, 2> gaps{
            std::max<size_t>(64, n / 32), n / 8};
        constexpr size_t GAP_SAMPLES = 64;
        for (size_t gap : gaps) {
            size_t inversions = 0;
            for (size_t i = 0; i < GAP_SAMPLES; ++i) {
                const size_t lo = i * (n - gap) / GAP_SAMPLES;
                const size_t hi = (i + 1) * (n - gap) / GAP_SAMPLES;
                const size_t pos = lo +
                    static_cast<size_t>(rng() % (hi - lo + 1));
                if (probe_cmp(a[pos + gap], a[pos])) ++inversions;
            }
            large_gap_inversions = std::max(large_gap_inversions, inversions);
        }
        sampled_large_gap = true;
    }
    const bool smooth_global_shape = monotone_bins >= 15 &&
        direction_changes <= 1 &&
        ((total_ascents == 0 || total_descents == 0) ||
         direction_changes == 1);
    const bool localized_tail_shape = monotone_bins >= 13 &&
        total_descents > 0 && active_bins <= 3 && direction_changes <= 3 &&
        (first_active_bin >= BINS - 3 || last_active_bin < 3) &&
        sampled_large_gap && large_gap_inversions <= 16;
    const bool run_adaptive_shape = smooth_global_shape || localized_tail_shape;
    const double margin = 1.96 * std::sqrt(
        descent_rate * (1.0 - descent_rate) /
        sample_pair_count) + 1.0 / sample_pair_count;
    const double p_upper = 1.0 - std::sqrt(std::max(
        0.0, 1.0 - 2.0 * std::min(0.5, descent_rate + margin)));

    if (equal_pairs == sample_pairs) {
        const T& first = a[0];
        bool all_equal = true;
        uint64_t equality_scan_comps = 0;
        for (size_t i = 1; i < n; ++i) {
            ++equality_scan_comps;
            if (cmp(a[i], first)) {
                all_equal = false;
                break;
            }
            ++equality_scan_comps;
            if (cmp(first, a[i])) {
                all_equal = false;
                break;
            }
        }
        g_gate_probe_comps += equality_scan_comps;
        if (all_equal) {
            g_gate_choice = 18;
            return;
        }
    }

    bool descent_lefts_are_extreme = false;
    size_t repeated_sample_values = 0;
    if (descent_rate < 0.05 && total_descents > 0) {
        const size_t high_cut = (sampled_left_values.size() * 9) / 10;
        std::nth_element(sampled_left_values.begin(),
                         sampled_left_values.begin() +
                             static_cast<std::ptrdiff_t>(high_cut),
                         sampled_left_values.end(), probe_cmp);
        const T& high_threshold = sampled_left_values[high_cut];
        size_t extreme_descents = 0;
        for (const T& left : descent_left_values)
            if (!probe_cmp(left, high_threshold)) ++extreme_descents;
        descent_lefts_are_extreme =
            extreme_descents * 2 >= total_descents;
    }
    if (descent_rate >= 0.05 && descent_rate < 0.15) {
        std::sort(sampled_left_values.begin(), sampled_left_values.end(), probe_cmp);
        for (size_t i = 1; i < sampled_left_values.size(); ++i)
            if (!probe_cmp(sampled_left_values[i - 1], sampled_left_values[i]))
                ++repeated_sample_values;
    }
    const double sampled_duplicate_rate =
        static_cast<double>(repeated_sample_values) /
        static_cast<double>(sampled_left_values.size() - 1);

    auto run_powersort = [&]() {
        g_gate_choice = 10;
        powersort(a, n, cmp);
    };
    auto run_bl_quick = [&]() {
        g_gate_choice = 12;
        bl_quick(a, n, cmp);
    };
    auto run_quantile_route = [&]() {
        const uint64_t outer_probe = g_gate_probe_comps;
        hybrid_quantile_backbone(a, n, cmp);
        g_gate_probe_comps += outer_probe;
        g_gate_choice = 17;
    };
    auto run_near_sorted_route = [&]() {
        if (sampled_large_gap && large_gap_inversions > 16) {
            run_bl_quick();
        } else if (descent_lefts_are_extreme || p_upper >= 0.055) {
            run_quantile_route();
        } else {
            hybrid_descent_portfolio(a, n, cmp);
            g_gate_choice = 15;
        }
    };

    // Preserve globally smooth shapes before the density estimator. This
    // catches reverse order and single-turn inputs such as organpipe.
    if (total_ascents == 0 && total_descents == 0 && equal_pairs > 0) {
        run_quantile_route();
        return;
    }
    if (equal_pairs * 100 > sample_pairs * 4 ||
        sampled_duplicate_rate > 0.04) {
        run_bl_quick();
        return;
    }
    if (run_adaptive_shape) {
        run_powersort();
        return;
    }
    if (descent_rate < 0.05) {
        run_near_sorted_route();
        return;
    }

    // Dense adjacent descents can still be short-range displacement. A
    // 64-apart sample separates this family from genuinely broad disorder.
    if (descent_rate >= 0.35 && descent_rate <= 0.65) {
        size_t gap64_inversions = 0;
        constexpr size_t GAP64_SAMPLES = 128;
        for (size_t i = 0; i < GAP64_SAMPLES; ++i) {
            const size_t lo = i * (n - 64) / GAP64_SAMPLES;
            const size_t hi = (i + 1) * (n - 64) / GAP64_SAMPLES;
            const size_t pos = lo + static_cast<size_t>(rng() % (hi - lo + 1));
            if (probe_cmp(a[pos + 64], a[pos])) ++gap64_inversions;
        }
        if (gap64_inversions <= 2) {
            const uint64_t outer_probe = g_gate_probe_comps;
            hybrid_inversion_gate(a, n, cmp);
            g_gate_probe_comps += outer_probe;
            g_gate_choice = 16;
            return;
        }
    }

    if (p_upper >= 0.32) {
        run_bl_quick();
        return;
    }
    run_quantile_route();
}

// Prefix-guided variant. A long monotone prefix plus consistent landmarks
// admits the existing first-run detector. Entire monotone inputs finish there;
// otherwise Powersort consumes its verified first run without rescanning it.
// The preflight adds at most max(256,n/256)-1 + 32 comparator calls to either
// Powersort or the unchanged general portfolio. Rejected preflights do not
// mutate the permutation; admitted strict-descending runs are normalized by
// count_run before Powersort consumes them.
template <class T, class C>
void hybrid_general_prefix(T* a, size_t n, C cmp) {
    if (n < 131072) {
        hybrid_general_portfolio(a, n, cmp);
        return;
    }
    uint64_t preflight_comps = 0;
    auto probe_cmp = [&](const T& x, const T& y) {
        ++preflight_comps;
        return cmp(x, y);
    };
    const bool descending = probe_cmp(a[1], a[0]);
    const size_t target = std::max<size_t>(256, n / 256);
    size_t run = 2;
    if (descending)
        while (run < target && probe_cmp(a[run], a[run - 1])) ++run;
    else
        while (run < target && !probe_cmp(a[run], a[run - 1])) ++run;
    bool consistent = run == target;
    size_t previous = 0;
    for (size_t bin = 1; consistent && bin <= 16; ++bin) {
        const size_t pos = bin * (n - 1) / 16;
        const bool coarse_less = probe_cmp(a[pos], a[previous]);
        const bool local_less = probe_cmp(a[pos], a[pos - 1]);
        consistent = coarse_less == descending && local_less == descending;
        previous = pos;
    }
    if (consistent) {
        g_gate_probe_comps = preflight_comps;
        g_gate_choice = 19;
        run = count_run(a, 0, n, cmp);
        if (run < n) powersort_from_first_run(a, n, run, cmp);
        return;
    }
    hybrid_general_portfolio(a, n, cmp);
    g_gate_probe_comps += preflight_comps;
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

// Directional Mergesort++ (Jin and Xu, 2026): a fixed balanced merge tree
// propagates whether each child is wholly ascending or strictly descending.
// Skip checks retain natural runs; backward/forward half-buffered merges are
// selected to exhaust a pure child as early as possible. The recursion uses
// O(log n) stack words; the paper's separate bit-stack traversal reduces this
// to O(1), which is outside this implementation.
template <class T, class C>
void directional_mergesort(T* a, size_t n, C cmp) {
    if (n < 2) return;
    std::unique_ptr<T[]> buf(new T[(n + 1) / 2]);
    struct Purity { bool ascending, descending; };

    auto merge_forward = [&](size_t lo, size_t mid, size_t hi) {
        const size_t left_len = mid - lo;
        std::memcpy(buf.get(), a + lo, left_len * sizeof(T));
        size_t i = 0, j = mid, out = lo;
        while (i < left_len && j < hi) {
            if (cmp(a[j], buf[i])) a[out++] = a[j++];
            else                   a[out++] = buf[i++];
        }
        if (i < left_len)
            std::memcpy(a + out, buf.get() + i, (left_len - i) * sizeof(T));
        g_merge_cost += hi - lo;
    };
    auto merge_backward = [&](size_t lo, size_t mid, size_t hi) {
        const size_t right_len = hi - mid;
        std::memcpy(buf.get(), a + mid, right_len * sizeof(T));
        size_t i = mid, j = right_len, out = hi;
        while (i > lo && j > 0) {
            // On equality take from the right so the left equal element
            // remains earlier in the final stable order.
            if (!cmp(buf[j - 1], a[i - 1])) a[--out] = buf[--j];
            else                            a[--out] = a[--i];
        }
        if (j > 0) std::memcpy(a + lo, buf.get(), j * sizeof(T));
        g_merge_cost += hi - lo;
    };

    auto sort_rec = [&](auto&& self, size_t lo, size_t hi) -> Purity {
        const size_t len = hi - lo;
        if (len == 1) return {true, true};
        if (len == 2) {
            if (cmp(a[lo + 1], a[lo])) return {false, true};
            return {true, false};
        }
        const size_t mid = lo + len / 2;
        Purity left = self(self, lo, mid);
        Purity right = self(self, mid, hi);

        if (left.descending && right.descending && cmp(a[mid], a[mid - 1]))
            return {false, true};

        if (left.descending) std::reverse(a + lo, a + mid);
        if (right.descending) std::reverse(a + mid, a + hi);

        if (!(left.descending && right.descending) &&
            !cmp(a[mid], a[mid - 1]))
            return {left.ascending && right.ascending, false};

        if (right.ascending || !(right.descending || left.ascending))
            merge_backward(lo, mid, hi);
        else
            merge_forward(lo, mid, hi);
        return {false, false};
    };

    Purity result = sort_rec(sort_rec, 0, n);
    if (result.descending) std::reverse(a, a + n);
}

// ---------------------------------------------------------------------------
// Shellsort gap-sequence study: Liu's learned/tuned rational-geometric rule,
// Ciura's prefix extended by 2.25, and Tokuda's rounded geometric rule.
// A fixed-size gap buffer keeps the sort itself free of dynamic gap storage.
// ---------------------------------------------------------------------------

struct ShellGaps {
    std::array<size_t, 128> values{};
    size_t size = 0;

    void push(size_t gap, size_t n) {
        if (gap == 0 || gap >= n) return;
        for (size_t i = 0; i < size; ++i)
            if (values[i] == gap) return;
        assert(size < values.size());
        values[size++] = gap;
    }

    void reverse() {
        std::reverse(values.begin(), values.begin() + size);
    }
};

// The largest rational power needed for any 64-bit array length is under
// 3,200 bits. A fixed 4,096-bit integer keeps exact gap generation on-stack
// with no heap allocation while leaving ample headroom for size_t inputs.
using ShellExactInt = boost::multiprecision::number<
    boost::multiprecision::cpp_int_backend<
        4096, 4096, boost::multiprecision::signed_magnitude,
        boost::multiprecision::unchecked, void>>;
static_assert(std::numeric_limits<size_t>::digits <= 64,
              "Shellsort's fixed-width gap arithmetic supports up to 64-bit size_t");

template <class T, class C>
void shellsort_with_gaps(T* a, size_t n, C cmp, const ShellGaps& gaps) {
    for (size_t gi = 0; gi < gaps.size; ++gi) {
        const size_t gap = gaps.values[gi];
        for (size_t i = gap; i < n; ++i) {
            T value = a[i];
            size_t j = i;
            while (j >= gap && cmp(value, a[j - gap])) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = value;
        }
    }
}

inline ShellGaps shell_learned_gaps(size_t n) {
    ShellGaps gaps;
    constexpr size_t prefix[] = {1, 3, 8, 20, 47, 116, 300, 585};
    for (size_t gap : prefix) gaps.push(gap, n);

    constexpr uint64_t alpha_num = 420574650882923ull;
    constexpr uint64_t alpha_den = 7668945023518835ull;
    constexpr uint64_t ratio_num = 582942583375009ull;
    constexpr uint64_t ratio_den = 250000000000000ull;
    ShellExactInt numerator = alpha_num;
    ShellExactInt denominator = alpha_den;
    for (int t = 0; t < 12; ++t) {
        numerator *= ratio_num;
        denominator *= ratio_den;
    }
    for (;;) {
        ShellExactInt exact_gap = numerator / denominator;
        if (exact_gap >= n) break;
        gaps.push(exact_gap.convert_to<size_t>(), n);
        numerator *= ratio_num;
        denominator *= ratio_den;
    }
    gaps.reverse();
    return gaps;
}

inline ShellGaps shell_ciura_gaps(size_t n) {
    ShellGaps gaps;
    constexpr size_t prefix[] = {1, 4, 10, 23, 57, 132, 301, 701};
    for (size_t gap : prefix) gaps.push(gap, n);
    size_t gap = prefix[sizeof(prefix) / sizeof(prefix[0]) - 1];
    while (gap < n && gap <= (SIZE_MAX - 2) / 9) {
        size_t next = (gap * 9 + 2) / 4; // nearest integer to 2.25 * gap
        if (next <= gap || next >= n) break;
        gaps.push(next, n);
        gap = next;
    }
    gaps.reverse();
    return gaps;
}

inline ShellGaps shell_tokuda_gaps(size_t n) {
    ShellGaps gaps;
    gaps.push(1, n);
    ShellExactInt nine_power = 9; // 9^k, k starts at 1
    ShellExactInt four_power = 4; // 4^k
    for (;;) {
        ShellExactInt numerator = 9 * nine_power - 4 * four_power;
        ShellExactInt denominator = 5 * four_power;
        ShellExactInt exact_gap = (numerator + denominator - 1) / denominator;
        if (exact_gap >= n) break;
        gaps.push(exact_gap.convert_to<size_t>(), n);
        nine_power *= 9;
        four_power *= 4;
    }
    gaps.reverse();
    return gaps;
}

template <class T, class C>
void shellsort_learned(T* a, size_t n, C cmp) {
    shellsort_with_gaps(a, n, cmp, shell_learned_gaps(n));
}

template <class T, class C>
void shellsort_ciura(T* a, size_t n, C cmp) {
    shellsort_with_gaps(a, n, cmp, shell_ciura_gaps(n));
}

template <class T, class C>
void shellsort_tokuda(T* a, size_t n, C cmp) {
    shellsort_with_gaps(a, n, cmp, shell_tokuda_gaps(n));
}

// SkeletonSort (van der Hoog, Rotenberg, and Rutschmann, 2026). A skeleton
// tree keeps only the branching nodes of the original balanced index tree.
// Splitting the tree by random pivots lets partitioning skip whole subtrees
// whose extrema lie on one side of the pivot. Equal-key leaves remain in
// original index order, extending the paper's distinct-key algorithm stably.
template <class T, class C>
void skeleton_sort(T* a, size_t n, C cmp, uint64_t seed = 0x534b454c45544f4eULL) {
    if (n < 2) return;

    struct Node {
        size_t left, right; // nil for leaves; left is also the free-list link
        size_t item;        // original input index for a leaf
        size_t count;
        size_t min_item, max_item;
    };
    constexpr size_t nil = std::numeric_limits<size_t>::max();
    std::vector<Node> nodes;
    size_t free_head = nil;
    auto allocate = [&]() {
        if (free_head != nil) {
            size_t id = free_head;
            free_head = nodes[id].left;
            return id;
        }
        nodes.emplace_back();
        return nodes.size() - 1;
    };
    auto release = [&](size_t id) {
        nodes[id].left = free_head;
        free_head = id;
    };
    auto leaf = [&](size_t i) {
        size_t id = allocate();
        nodes[id] = {nil, nil, i, 1, i, i};
        return id;
    };
    auto join = [&](size_t left, size_t right) {
        if (left == nil) return right;
        if (right == nil) return left;
        size_t id = allocate();
        size_t min_item = cmp(a[nodes[left].min_item], a[nodes[right].min_item])
            ? nodes[left].min_item : nodes[right].min_item;
        size_t max_item = cmp(a[nodes[left].max_item], a[nodes[right].max_item])
            ? nodes[right].max_item : nodes[left].max_item;
        nodes[id] = {left, right, nil,
                     nodes[left].count + nodes[right].count, min_item, max_item};
        return id;
    };

    // Build the perfect index tree over the next power of two, omitting
    // padding leaves and shortcutting unary nodes to obtain its n-leaf
    // skeleton. Indices, rather than pointers, survive pool growth.
    auto build = [&](auto&& self, size_t lo, size_t hi) -> size_t {
        if (lo >= n) return nil;
        if (hi - lo == 1) return leaf(lo);
        size_t mid = lo + (hi - lo) / 2;
        size_t left = self(self, lo, mid);
        size_t right = self(self, mid, hi);
        return join(left, right);
    };
    size_t padded = 1;
    while (padded < n) padded <<= 1;
    size_t root = build(build, 0, padded);

    struct Split { size_t less, equal, greater; };
    auto split = [&](auto&& self, size_t id, size_t pivot) -> Split {
        if (id == nil) return {nil, nil, nil};
        const Node& node = nodes[id];
        const T& low = a[node.min_item];
        const T& high = a[node.max_item];
        const T& p = a[pivot];
        if (!cmp(low, p) && !cmp(p, low) &&
            !cmp(high, p) && !cmp(p, high))
            return {nil, id, nil};
        if (cmp(p, low)) return {nil, nil, id};
        if (cmp(high, p)) return {id, nil, nil};
        if (node.left == nil) {
            if (cmp(a[node.item], p)) return {id, nil, nil};
            if (cmp(p, a[node.item])) return {nil, nil, id};
            return {nil, id, nil};
        }

        size_t old_left = node.left;
        size_t old_right = node.right;
        Split l = self(self, old_left, pivot);
        Split r = self(self, old_right, pivot);
        Split out{join(l.less, r.less), join(l.equal, r.equal),
                  join(l.greater, r.greater)};
        release(id);
        return out;
    };

    std::mt19937_64 rng(seed);
    std::vector<size_t> order;
    order.reserve(n);
    auto emit_destroy = [&](auto&& self, size_t id) -> void {
        if (id == nil) return;
        size_t left = nodes[id].left;
        size_t right = nodes[id].right;
        if (left == nil) {
            order.push_back(nodes[id].item);
        } else {
            self(self, left);
            self(self, right);
        }
        release(id);
    };
    auto sort_tree = [&](auto&& self, size_t id) -> void {
        if (id == nil) return;
        std::uniform_int_distribution<size_t> choose(0, nodes[id].count - 1);
        size_t rank = choose(rng);
        size_t leaf_id = id;
        while (nodes[leaf_id].left != nil) {
            size_t left = nodes[leaf_id].left;
            if (rank < nodes[left].count) leaf_id = left;
            else { rank -= nodes[left].count; leaf_id = nodes[leaf_id].right; }
        }
        size_t pivot = nodes[leaf_id].item;
        Split parts = split(split, id, pivot);
        self(self, parts.less);
        emit_destroy(emit_destroy, parts.equal);
        self(self, parts.greater);
    };
    sort_tree(sort_tree, root);

    // Apply the output permutation in place. The top bit marks visited
    // permutation entries; a second n-element value buffer is unnecessary.
    constexpr size_t visited = size_t(1) << (sizeof(size_t) * 8 - 1);
    assert(n < visited);
    for (size_t start = 0; start < n; ++start) {
        if (order[start] & visited) continue;
        T temp = a[start];
        size_t cur = start;
        for (;;) {
            size_t next = order[cur] & ~visited;
            order[cur] |= visited;
            if (next == start) { a[cur] = temp; break; }
            a[cur] = a[next];
            cur = next;
        }
    }
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
