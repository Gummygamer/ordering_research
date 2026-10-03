# Learned Shellsort sequence: comparison, runtime, and memory analysis

Analysis updated 2026-10-03. This report interprets the existing data introduced
by [ca1c755](https://github.com/Gummygamer/ordering_research/commit/ca1c7550229b58b156957ba5cf41e21c8a860e91);
it adds no benchmark runs. The evidence supports modest, distribution-dependent
comparison savings from the learned gaps relative to Ciura and Tokuda, with
regressions elsewhere. It does not establish a generally faster sorter.

## Evidence and measurement scope

The CLI benchmarks `uint64_t` values. All 315 Shellsort-study rows have
`ok=1` and build ID `shell-paper-2609-fixed`. Exact output agreement and the
reported selftests support correctness on the tested cases; they do not prove
performance generalization.

- [Primary grid](shellsort_2609_all.csv): five algorithms, six distributions,
  n=1,000,000; count seeds 1--3 and five serial timing repetitions at seed 1.
- [Additional count seeds](shellsort_2609_heldout.csv): seeds 4--6 for random,
  `runs1024`, `nearly1`, and reversed, giving six count rows per algorithm
  for these categories. `dup16` and sorted retain three count rows.
- [Large-input grid](shellsort_2609_paperscale.csv): only the three Shellsort
  variants, n=10,000,000, five distributions, one count seed (1999).
- [Generated aggregates](shellsort_2609_tables.md): arithmetic means for
  comparisons, medians for time, and maxima for tracked heap peaks.

Only `mode=time` rows measure runtime with the raw comparator. The
`time_ns` field in count rows includes instrumentation and must not be used
as a speed result. This is especially relevant to the 10m grid, whose count
jobs were allowed to run concurrently.

## Observations at one million elements

Each cell below is **mean comparisons/element / median ns/element**. Counts
and times summarize different samples: the time sample always uses seed 1.

| Input | shell_learned | shell_ciura | shell_tokuda | powersort | std_sort |
| --- | ---: | ---: | ---: | ---: | ---: |
| random | 32.090 / 168.128 | 31.905 / 129.191 | 32.058 / 123.964 | 18.599 / 83.543 | 23.928 / 59.182 |
| dup16 | 17.770 / 41.961 | 17.778 / 36.887 | 18.166 / 39.682 | 7.839 / 45.946 | 18.217 / 19.688 |
| runs1024 | 30.821 / 86.372 | 29.768 / 79.670 | 30.863 / 80.085 | 10.950 / 41.122 | 25.723 / 49.598 |
| nearly1 | 26.952 / 98.633 | 26.992 / 99.548 | 27.161 / 101.019 | 3.136 / 12.090 | 25.282 / 10.749 |
| reversed | 20.763 / 16.725 | 21.156 / 19.169 | 21.297 / 20.010 | 1.000 / 0.862 | 18.131 / 5.770 |
| sorted | 15.070 / 15.519 | 15.171 / 17.031 | 15.602 / 15.350 | 1.000 / 0.610 | 25.605 / 9.737 |

On random input, learned Shellsort uses about 72.5% more comparisons than
Powersort and its measured median takes 2.012 times as long. Against
`std_sort`, the corresponding differences are about 34.1% more comparisons
and 2.841 times the median time. Ciura uses fewer comparisons than the learned
sequence on all six random seeds; the learned/Tokuda ordering varies by seed.
Both classical Shellsort variants have lower measured random timing medians
than the learned variant. The random timing ranges are 154.311--190.388
ns/element for learned, 127.870--137.112 for Ciura, and 116.371--125.701 for
Tokuda. These describe this execution sample, without providing a confidence
interval for other inputs or machines.

The three Shellsort variants share the same gapped-insertion sorting loop.
Their sequences account for the comparison differences, while their gap
generation also contributes to runtime. The learned sequence has lower mean
counts than both baselines on `dup16`, `nearly1`, reversed, and sorted.
The learned/Ciura difference on `dup16` is only about 0.042%, and seed ranges
overlap. On `runs1024`, learned improves slightly on Tokuda but regresses
against Ciura. No sequence dominates both counts and timing throughout this
suite; close timing medians should not be treated as established speed gains.

Powersort uses fewer comparisons than every other tested method in all six
categories. Its run detection is particularly effective on sorted and
reversed input, requiring exactly n-1 comparisons. The lowest observed time
medians belong to `std_sort` on random, `dup16`, and `nearly1`, and to
Powersort on `runs1024`, reversed, and sorted.

Comparison count and runtime are distinct outcomes. For example,
`std_sort` compares more than Powersort on random input while running faster
in this sample. Learned Shellsort also has a lower timing median than
Powersort on `dup16` (41.961 versus 45.946 ns/element), despite more than
twice as many comparisons. The harness does not establish which movement,
cache, branch, or other implementation costs caused these differences.

## What the ten-million-element sample shows

These are exact comparisons/element on the five particular arrays at seed 1999:

| Input | shell_learned | shell_ciura | shell_tokuda |
| --- | ---: | ---: | ---: |
| random | 38.668 | 38.383 | 38.498 |
| dup16 | 20.505 | 20.639 | 20.993 |
| runs1024 | 36.696 | 38.236 | 36.565 |
| nearly1 | 33.389 | 33.441 | 33.535 |
| reversed | 23.975 | 24.995 | 25.708 |

Summing comparisons over these five equal-size inputs gives 1,532,329,405 for
learned, 1,556,934,728 for Ciura, and 1,552,985,928 for Tokuda. Thus learned
uses 1.580% fewer total comparisons than Ciura and 1.330% fewer than Tokuda
on this panel. It nevertheless loses to both on random input and to Tokuda
on `runs1024`. The aggregate depends on the selected distributions and
their weights; it is not a universal percentage improvement.

One row per input provides no estimate of between-seed variation. A displayed
range with equal endpoints means one observation, not zero population
variance. This grid contains no valid timing measurements and no Powersort
or `std_sort` rows, so it supports neither a 10m speed ranking nor a
five-method comparison at that size.

## Memory and stability

The three Shellsort variants and `std_sort` report zero tracked auxiliary
heap in the count grid. Shellsort uses a fixed 128-entry gap buffer; learned
and Tokuda gap generation also use fixed-width 4096-bit arithmetic. These
objects occupy stack storage. Zero tracked heap is not zero total auxiliary
memory, and `fj_stack_bound_bytes=0` only means that the separate
Ford--Johnson scratch bound does not apply.

Powersort's random 1m peak is 4,002,304 bytes (about 4.002 bytes/element).
Its sorted and reversed peaks are only 2,304 bytes. The metric excludes the
input vector and other allocations present before the sort, and does not
measure total process memory or the full stack. It demonstrates a local
heap-storage tradeoff rather than a complete memory ranking.

The Shellsort variants and `std_sort` are unstable; the local Powersort is
stable. Applications requiring preservation of equal-key order must account
for that difference when choosing an algorithm.

## Statistical limits and relation to prior work

Five repetitions of seed 1 measure execution variation for one generated
array, not five independently generated inputs. Additional count seeds
strengthen evidence within four local generators, but add no runtime
replication. Sorted and reversed generators are deterministic across seeds,
so their repeated count rows are not independent input samples. Observed
seed ranges are descriptive, and these small panels do not justify broad
significance, worst-case, or scaling claims.

The [five-seed follow-up in 084c2da](https://github.com/Gummygamer/ordering_research/commit/084c2da28796b04d3c648cab63cdfade4a7715c8)
compares Powersort, `powersort_fj`, and `hybrid_fjauto2048`; it supplies
no additional Shellsort timing data. With 15 serial repetitions per
algorithm/seed, PFJ's paired timing delta still ranges from -11.02% to
+24.02% despite fewer comparisons. CPU frequency was not pinned and
algorithm order was not interleaved. This supports keeping comparison
savings and speed claims separate; it cannot be pooled with the Shellsort
sample as if it tested the same algorithms and build.

[Liu's paper, section 3.2](https://arxiv.org/html/2609.29881v1#S3.SS2)
uses 25 tasks: five sizes from 10,000,001 to 100,000,000 and five input
types, with seed 1999. It counts comparisons and array writes, reports
equal-task geometric means, and evaluates total operations as well as each
component. The local 10m check uses a different size, local generators, and
a sum of comparisons across five inputs. It does not reproduce that panel
or objective. `merge_span_elems` is a merge-work proxy, not an exact move
counter; its zero value for Shellsort cannot be interpreted as zero movement.

The repository executes the frozen practical gap sequence, without a model
or retraining at sort time. It implements neither the RL discovery process
nor the unit-companion completion above 10^1000 used in the paper's
asymptotic claim. The benchmark does not verify that theorem, establish an
average-case constant, or predict behavior on untested sizes, distributions,
record types, comparator costs, compilers, or hardware.

A stronger runtime claim would require serial measurements over independent
seeds, interleaved or randomized algorithm order, documented CPU conditions,
and uncertainty estimates for paired timing differences. A closer replication
of Liu would also require matching its sizes, generators, and exact move
accounting. The present report supports the observed count, timing, heap,
and stability tradeoffs within the recorded experiment.
