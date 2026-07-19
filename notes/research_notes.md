# Research notes — recent theory on ordering (comparison sorting) algorithms

Date: 2026-07-19

## 1. Run-adaptive merging: Powersort (the current theory→practice success)

- Munro & Wild, ESA 2018, "Nearly-Optimal Mergesorts": *peeksort* and *powersort*
  compute a merge tree that is within a constant number of comparisons of the
  optimal alphabetic binary search tree over existing runs. Merge cost is
  n·(H(run-length distribution)) + O(n), i.e. optimally adaptive to runs.
  https://arxiv.org/abs/1805.04154
- Powersort replaced Timsort's (provably suboptimal) merge rules in CPython 3.11+
  and PyPy; the run detection/galloping machinery was kept.
  https://en.wikipedia.org/wiki/Powersort
- Cawley Gelling, Nebel, Smith, Wild 2022/23: *Multiway Powersort* — same idea for
  k-way merges (nearly-optimal k-ary search trees). https://arxiv.org/abs/2209.06909

## 2. Comparison-count frontier (constant-factor optimality)

- Information-theoretic bound: lg(n!) = n lg n − 1.4427·n + 0.5·lg n + O(1).
- MergeInsertion (Ford–Johnson 1959) is still essentially the best known
  comparison count for small n (optimal for n ≤ 11, n = 20, 21, ...).
- QuickXsort / QuickMergesort with MergeInsertion base cases:
  n lg n − 1.3999n + o(n) comparisons *on average*, constant extra space
  (Edelkamp & Weiß; also "QuickXsort — A Fast Sorting Scheme in Theory and
  Practice"). https://arxiv.org/abs/1307.3033 , https://arxiv.org/pdf/1811.01259
- Iwama & Teruyama, "Improved Average Complexity for Comparison-Based Sorting":
  gap to the lower bound at most 0.0321n + o(n) via (1,2)-insertion.
  https://arxiv.org/pdf/1705.00849
- Plain top-down mergesort: n lg n − 1.248n avg; std introsort is far above the
  bound (partitioning wastes comparisons); binary-insertion base cases matter.

## 3. Learning-augmented sorting (2023–2025 theory wave)

- Bai & Coester, "Sorting with Predictions" (NeurIPS 2023): with positional
  predictions having per-item error η_i, simple algorithms achieve
  O(Σ_i log(η_i + 2)) *clean* comparisons — degrading smoothly from O(n)
  (perfect predictions) to O(n log n). Proven optimal for the error measure.
  https://arxiv.org/abs/2311.00749
- Related: LearnedSort as learning-augmented samplesort (SSDBM 2023);
  PCF Learned Sort, O(n log log n) expected (https://arxiv.org/pdf/2405.07122);
  learning-augmented priority queues (https://arxiv.org/pdf/2406.04793).

## 4. Engineering state of the art (what actually ships)

- Rust std (2024 rewrite, Bergdoll & Peters): *driftsort* (stable; derived from
  glidesort: Timsort-style run adaptivity + pdqsort-style pattern defeating +
  branchless merging) and *ipnsort* (unstable). Up to 2.4× faster random-input
  sorting, up to 17× on low-cardinality inputs.
  https://github.com/Voultapher/sort-research-rs (driftsort/ipnsort writeups)
- Key engineering ideas: branchless Lomuto partition ("Lomuto's comeback",
  Orson Peters 2023), branchless merges, galloping only when it pays,
  cardinality-adaptive 3-way partitioning.
- CPython keeps Timsort's galloping merge kernel under powersort's policy.

## 5. Where the open experimental space is (this project)

1. Powersort gives an (essentially) optimal *merge tree*; Ford–Johnson gives
   (essentially) optimal *base cases*; galloping gives entropy-adaptive
   *merges*. Nobody ships the three together. → Build `hybrid_fj`:
   powersort policy + FJ merge-insertion base blocks + galloping merges.
   Question: how close to lg(n!) can a practical, run-adaptive sort get?
2. Reproduce the Bai–Coester law with a "place by prediction, then clean"
   pipeline: comparisons should scale ≈ n·lg(σ) + O(n) for displacement σ.
   The cleaner can be powersort/timsort itself (galloping merges are exactly
   a Σ log η_i mechanism).
3. Metrics tracked for every algorithm: wall time, exact comparison count,
   peak auxiliary heap bytes (global operator new/delete instrumentation),
   and total merge cost (elements moved in merges) where applicable.
