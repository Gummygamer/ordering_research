#pragma once

// Experimental ascending-u64 specialization. The sample chooses work only;
// correctness depends on an exact certificate. Intrinsic comparisons are not
// represented by the scalar comparator counter.
#if defined(SORTLAB_HAVE_X86_SIMD) && defined(__AVX512F__) && defined(__AVX512DQ__)
#define SORTLAB_HAVE_SIMD_CERTIFIED 1
#include <bit>
#include <immintrin.h>

namespace lab {

// All values are unsigned: zero can pad removed lanes in a prefix maximum.
// The inclusive prefix maximum exceeds a retained value iff there is a
// preceding retained value greater than it (including the previous vector).
inline __m512i retained_prefix_max(__m512i values, uint64_t previous) {
    const __m512i shift1 = _mm512_set_epi64(6, 5, 4, 3, 2, 1, 0, 0);
    const __m512i shift2 = _mm512_set_epi64(5, 4, 3, 2, 1, 0, 0, 0);
    const __m512i shift4 = _mm512_set_epi64(3, 2, 1, 0, 0, 0, 0, 0);
    values = _mm512_max_epu64(values, _mm512_set1_epi64(
        std::bit_cast<int64_t>(previous)));
    values = _mm512_max_epu64(values,
        _mm512_maskz_permutexvar_epi64(0xfe, shift1, values));
    values = _mm512_max_epu64(values,
        _mm512_maskz_permutexvar_epi64(0xfc, shift2, values));
    return _mm512_max_epu64(values,
        _mm512_maskz_permutexvar_epi64(0xf0, shift4, values));
}

inline bool certified_partition_u64(uint64_t* a, size_t n, uint64_t pivot,
                                    size_t reserve_hint) {
    if (n == 0) return true;
    size_t capacity = std::min(n, std::max<size_t>(8, reserve_hint));
    // Default initialization intentionally leaves this trivial scratch unset.
    std::unique_ptr<uint64_t[]> high(new uint64_t[capacity]);
    size_t high_size = 0;
    size_t backbone = 0;
    size_t read = 0;
    uint64_t previous = 0;
    bool ordered = true;
    const __m512i vp = _mm512_set1_epi64(std::bit_cast<int64_t>(pivot));
    auto grow = [&](size_t needed) {
        if (needed <= capacity) return;
        const size_t next = std::min(n, std::max(needed, capacity + capacity / 2));
        std::unique_ptr<uint64_t[]> replacement(new uint64_t[next]);
        std::memcpy(replacement.get(), high.get(), high_size * sizeof(uint64_t));
        high.swap(replacement);
        capacity = next;
    };
    for (; n - read >= 8; read += 8) {
        const __m512i keys = _mm512_loadu_si512(a + read);
        const __mmask8 low = _mm512_cmp_epu64_mask(keys, vp, _MM_CMPINT_LT);
        const __mmask8 upper = static_cast<__mmask8>(~low);
        const size_t low_count = static_cast<size_t>(std::popcount(
            static_cast<unsigned>(low)));
        const size_t high_count = 8 - low_count;
        grow(high_size + high_count);
        const __m512i retained = _mm512_maskz_mov_epi64(low, keys);
        const __m512i prefix = retained_prefix_max(retained, previous);
        if ((_mm512_cmp_epu64_mask(keys, prefix, _MM_CMPINT_LT) & low) != 0)
            ordered = false;
        previous = static_cast<uint64_t>(_mm_extract_epi64(
            _mm512_extracti64x2_epi64(prefix, 3), 1));
        // All eight input lanes have been loaded. Since backbone <= read,
        // this compact store cannot overwrite unread input.
        _mm512_mask_compressstoreu_epi64(a + backbone, low, keys);
        _mm512_mask_compressstoreu_epi64(high.get() + high_size, upper, keys);
        backbone += low_count;
        high_size += high_count;
    }
    for (; read < n; ++read) {
        const uint64_t key = a[read];
        if (key < pivot) {
            if (key < previous) ordered = false;
            previous = std::max(previous, key);
            a[backbone++] = key;
        } else {
            grow(high_size + 1);
            high[high_size++] = key;
        }
    }
    assert(backbone + high_size == n);
    const bool success = ordered && high_size <= n / 2;
    if (success && high_size > 1) x86simdsortStatic::qsort(high.get(), high_size);
    std::memcpy(a + backbone, high.get(), high_size * sizeof(uint64_t));
    if (!success && n > 1) x86simdsortStatic::qsort(a, n);
    return success;
}

inline void simd_certified_u64(uint64_t* a, size_t n) {
    g_gate_probe_comps = 0;
    g_gate_choice = 30;
    if (n < 131072) {
        if (n > 1) x86simdsortStatic::qsort(a, n);
        return;
    }
    constexpr size_t BINS = 16;
    constexpr size_t PER_BIN = 64;
    constexpr size_t PAIRS = BINS * PER_BIN;
    std::array<uint64_t, 2 * PAIRS> sample{};
    std::mt19937_64 rng(0x51A7E2A1ULL);
    size_t descents = 0;
    size_t monotone_bins = 0;
    size_t active_bins = 0;
    size_t low_ascending_bins = 0;
    size_t equal_pairs = 0;
    for (size_t bin = 0; bin < BINS; ++bin) {
        const size_t lo = bin * n / BINS;
        const size_t hi = (bin + 1) * n / BINS;
        size_t down = 0, up = 0;
        for (size_t j = 0; j < PER_BIN; ++j) {
            const size_t pos = lo + static_cast<size_t>(rng() % (hi - lo - 1));
            const uint64_t left = a[pos], right = a[pos + 1];
            sample[2 * (bin * PER_BIN + j)] = left;
            sample[2 * (bin * PER_BIN + j) + 1] = right;
            down += static_cast<size_t>(right < left);
            up += static_cast<size_t>(left < right);
        }
        descents += down;
        equal_pairs += PER_BIN - down - up;
        active_bins += static_cast<size_t>(down != 0);
        monotone_bins += static_cast<size_t>(up <= 1 || down <= 1);
        low_ascending_bins += static_cast<size_t>(up <= 1);
    }
    // Reuse the generic portfolio's duplicate threshold; do not spend a
    // partition pass on low-cardinality data already handled well by SIMD.
    if (equal_pairs * 100 > PAIRS * 4) {
        x86simdsortStatic::qsort(a, n);
        return;
    }
    if (monotone_bins >= 13 && (active_bins < 4 || low_ascending_bins >= 13)) {
        g_gate_choice = 31;
        powersort(a, n, RawLess{});
        return;
    }
    const double rate = static_cast<double>(descents) / static_cast<double>(PAIRS);
    const double margin = 1.96 * std::sqrt(rate * (1 - rate) /
        static_cast<double>(PAIRS)) + 1.0 / static_cast<double>(PAIRS);
    const double p = 1 - std::sqrt(std::max(0.0,
        1 - 2 * std::min(0.5, rate + margin)));
    if (p >= 0.5) {
        x86simdsortStatic::qsort(a, n);
        return;
    }
    const double fraction = std::min(0.5, p + 1.96 * std::sqrt(p * (1 - p) /
        static_cast<double>(sample.size())) + 1.0 / static_cast<double>(sample.size()));
    const size_t rank = std::min(sample.size() - 1,
        static_cast<size_t>((1 - fraction) * static_cast<double>(sample.size())));
    std::nth_element(sample.begin(), sample.begin() + rank, sample.end());
    const bool success = certified_partition_u64(a, n, sample[rank],
        static_cast<size_t>(static_cast<double>(n) * fraction) + 8);
    g_gate_choice = success ? 32 : 33;
}

} // namespace lab
#endif
