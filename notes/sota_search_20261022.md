# SOTA search: expanded baselines and evaluation scope

The active goal is to continue until obtaining a new state-of-the-art sorting
algorithm. The existing v16 result only establishes competitiveness against
the lab's six internal baselines; it cannot establish SOTA. The three prefix
variants remain negative development results and are not promoted.

## Baseline audit, before inspecting its timings

Add unmodified, pinned pdqsort, sequential IPS4o, and x86-simd-sort, preserving
their licenses and recording hashes. These are credited reference algorithms,
not new lab contributions. Generic comparator algorithms remain the project's
current scope; specialized numeric SIMD and radix implementations are also
measured so primitive-key speed gaps cannot be hidden behind weak scalar
references. A future claim must identify its type/comparator, stability,
memory, thread count, workload, size, compiler, and hardware scope explicitly.
No claim of an unqualified universal winner follows from a finite local grid.

The initial baseline-audit profile uses twelve distributions, n=200k and 1m,
input seeds 301--302, ten algorithms, and twenty balanced rounds. It produces
480 resource/count-mode rows and 9,600 timing rows. `uniform64` fills uint64
storage with full-range PRNG outputs; `uniform32` uses uniformly sampled low
32 bits, and `highbits32` places that entropy in the high 32 bits. Existing
`random` remains the original rank permutation to preserve prior experiments.
This avoids evaluating primitive numeric sorters only on compressed ranks.

The build uses GCC 15.2, -O3 -march=native, and the existing single-threaded
harness. Pin timing to CPU 2 and retain balanced round identities. Do not run
compilation, count jobs, or another timing process concurrently with timing.
CPU frequency is still variable under powersave, and hardware counters are
unavailable. New sorter hypotheses must be selected on development evidence
and frozen before fresh evaluation. Prefix-heldout seeds 201--203 remain
unused; new candidate holdouts should use a separately declared seed range.

## Remaining evidence needed for a SOTA claim

This first audit is not a SOTA proof or a final benchmark suite. It must guide
the next mechanism, with stronger tests at small and cache-exceeding sizes,
more data families, adversarial arrangements, and non-integer/payload types.
Comparator-call counts remain diagnostics; evaluate latency and resources.
Short-case uncertainty and dependence between rounds need explicit attention.
Any speed claim must survive independent repeats and comparison with relevant
leading implementations, including additional libraries where appropriate.

Primary sources consulted on 2026-10-22:

- [pdqsort source and design](https://github.com/orlp/pdqsort)
- [IPS4o implementation](https://github.com/ips4o/ips4o) and
  [experimental study](https://arxiv.org/abs/2009.13569)
- [x86-simd-sort](https://github.com/numpy/x86-simd-sort)
- [VQSort](https://github.com/google/highway/tree/master/hwy/contrib/sort)

VQSort and other relevant competitors still need integration or independent
measurement before using a broad SOTA label. This goal remains active.

## Initial audit results

All 10,080 rows validated: 480 count/resource rows and 9,600 uninstrumented timing rows. The strict build, expanded sorting selftest, eight timing/analysis checks, and upstream snapshot verification passed.

| Input, n=1m | v16 ns/key | PDQ branchless | IPS4o | x86 SIMD |
|---|---:|---:|---:|---:|
| random | 23.34 | 20.59 | 18.88 | 5.48 |
| uniform64 | 24.06 | 20.93 | 19.44 | 5.60 |
| uniform32 | 23.75 | 20.79 | 19.40 | 5.48 |
| highbits32 | 23.83 | 20.99 | 19.47 | 5.58 |
| sorted | 0.54 | 0.85 | 0.53 | 5.59 |
| reversed | 0.69 | 1.31 | 0.68 | 5.59 |
| equal | 0.45 | 0.74 | 0.49 | 0.29 |
| nearly1 | 3.35 | 7.49 | 13.33 | 5.74 |
| runs1024 | 24.58 | 21.90 | 20.07 | 5.91 |
| dup16 | 3.71 | 3.77 | 3.07 | 1.20 |
| outpct1 | 1.75 | 15.99 | 12.82 | 5.91 |
| disp16 | 19.69 | 16.44 | 19.14 | 5.71 |

Against the strongest generic comparator baseline per case, v16 has median regret +20.21%, with 15/48 cases within 5%. Against all references including SIMD/radix it has median regret +232.82%. These are local measurements on the audit grid, not a SOTA claim.

Random and full-width disordered keys expose the weak old fallback. Nearly sorted data and sparse high-key corruption retain a structural advantage. The next candidate should pair the existing verified repair mechanism with stronger disordered fallbacks and test its additional work, then broaden the suite and competitors before making a SOTA claim.
