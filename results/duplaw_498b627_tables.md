# Duplicate-cardinality response study (498b627)

Aggregated 216 validated rows from 2 CSV file(s). Each row below is grouped by algorithm, distribution, n, and mode. Comparison and merge-span metrics are arithmetic means, timing metrics are medians, and memory bounds/peaks are maxima.

Build IDs: `498b627`.

For random permutations, comparison excess is `100 * (mean comparisons - lg(n!)) / lg(n!)`; it is reported as `n/a` for other distributions. Timing metrics use only `time` rows, while comparison, heap, and merge metrics use only `count` rows.

## `dup1024`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 13,830,782.7 | 13.830783 | 13.826302–13.834663 | n/a | n/a | n/a | 3,998,320 | 3.998 | 273,272 | 8.991 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `hybrid_gate` | 3 | 13,904,319.3 | 13.904319 | 13.900546–13.907918 | n/a | n/a | n/a | 3,998,320 | 3.998 | 6,204 | 13.957 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort` | 3 | 13,922,505.7 | 13.922506 | 13.918644–13.926316 | n/a | n/a | n/a | 3,998,320 | 3.998 | 0 | 13.957 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort_fj` | 3 | 13,902,768.7 | 13.902769 | 13.899203–13.906173 | n/a | n/a | n/a | 3,998,320 | 3.998 | 6,204 | 13.957 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |

## `dup12`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,592,138.3 | 9.592138 | 9.591950–9.592364 | n/a | n/a | n/a | 3,669,296 | 3.669 | 273,272 | 8.250 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `hybrid_gate` | 3 | 7,356,180 | 7.356180 | 7.355744–7.356809 | n/a | n/a | n/a | 3,669,296 | 3.669 | 6,204 | 12.833 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort` | 3 | 7,385,748.7 | 7.385749 | 7.385558–7.385866 | n/a | n/a | n/a | 3,669,296 | 3.669 | 0 | 12.833 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort_fj` | 3 | 7,356,136 | 7.356136 | 7.355664–7.356788 | n/a | n/a | n/a | 3,669,296 | 3.669 | 6,204 | 12.833 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |

## `dup128`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 10,887,796.7 | 10.887797 | 10.887611–10.887941 | n/a | n/a | n/a | 3,971,120 | 3.971 | 273,272 | 8.930 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `hybrid_gate` | 3 | 10,918,228 | 10.918228 | 10.916263–10.919213 | n/a | n/a | n/a | 3,971,120 | 3.971 | 6,204 | 13.872 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort` | 3 | 10,938,465.7 | 10.938466 | 10.936748–10.939459 | n/a | n/a | n/a | 3,971,120 | 3.971 | 0 | 13.872 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort_fj` | 3 | 10,917,818.7 | 10.917819 | 10.916162–10.918877 | n/a | n/a | n/a | 3,971,120 | 3.971 | 6,204 | 13.872 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |

## `dup16`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,672,713.3 | 9.672713 | 9.672221–9.673219 | n/a | n/a | n/a | 3,751,624 | 3.752 | 273,272 | 8.437 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `hybrid_gate` | 3 | 7,811,960.3 | 7.811960 | 7.811556–7.812379 | n/a | n/a | n/a | 3,751,624 | 3.752 | 6,204 | 13.123 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort` | 3 | 7,838,704.3 | 7.838704 | 7.838175–7.839039 | n/a | n/a | n/a | 3,751,624 | 3.752 | 0 | 13.123 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort_fj` | 3 | 7,811,909 | 7.811909 | 7.811523–7.812320 | n/a | n/a | n/a | 3,751,624 | 3.752 | 6,204 | 13.123 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |

## `dup192`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 11,378,575.3 | 11.378575 | 11.378262–11.378922 | n/a | n/a | n/a | 3,981,696 | 3.982 | 273,272 | 8.954 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `hybrid_gate` | 3 | 11,470,442 | 11.470442 | 11.468292–11.473326 | n/a | n/a | n/a | 3,981,696 | 3.982 | 6,204 | 13.906 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort` | 3 | 11,489,901 | 11.489901 | 11.487754–11.492730 | n/a | n/a | n/a | 3,981,696 | 3.982 | 0 | 13.906 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort_fj` | 3 | 11,469,925 | 11.469925 | 11.467852–11.472343 | n/a | n/a | n/a | 3,981,696 | 3.982 | 6,204 | 13.906 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |

## `dup2`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 8,985,072 | 8.985072 | 8.982654–8.988604 | n/a | n/a | n/a | 2,000,304 | 2.000 | 273,272 | 4.501 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `hybrid_gate` | 3 | 4,978,646 | 4.978646 | 4.977709–4.979488 | n/a | n/a | n/a | 2,000,304 | 2.000 | 6,204 | 7.001 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort` | 3 | 5,033,524.3 | 5.033524 | 5.033168–5.034097 | n/a | n/a | n/a | 2,000,304 | 2.000 | 0 | 7.001 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort_fj` | 3 | 4,978,635 | 4.978635 | 4.977699–4.979472 | n/a | n/a | n/a | 2,000,304 | 2.000 | 6,204 | 7.001 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |

## `dup24`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,830,047.3 | 9.830047 | 9.829818–9.830168 | n/a | n/a | n/a | 3,835,320 | 3.835 | 273,272 | 8.625 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `hybrid_gate` | 3 | 8,429,979.3 | 8.429979 | 8.429500–8.430850 | n/a | n/a | n/a | 3,835,320 | 3.835 | 6,204 | 13.414 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort` | 3 | 8,454,466.7 | 8.454467 | 8.453852–8.455324 | n/a | n/a | n/a | 3,835,320 | 3.835 | 0 | 13.414 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort_fj` | 3 | 8,429,888.7 | 8.429889 | 8.429406–8.430756 | n/a | n/a | n/a | 3,835,320 | 3.835 | 6,204 | 13.414 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |

## `dup256`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 11,782,301.3 | 11.782301 | 11.780323–11.783560 | n/a | n/a | n/a | 3,986,568 | 3.987 | 273,272 | 8.965 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `hybrid_gate` | 3 | 11,922,133.3 | 11.922133 | 11.919077–11.923887 | n/a | n/a | n/a | 3,986,568 | 3.987 | 6,204 | 13.921 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort` | 3 | 11,941,590.7 | 11.941591 | 11.938097–11.943485 | n/a | n/a | n/a | 3,986,568 | 3.987 | 0 | 13.921 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort_fj` | 3 | 11,921,460 | 11.921460 | 11.918160–11.923186 | n/a | n/a | n/a | 3,986,568 | 3.987 | 6,204 | 13.921 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |

## `dup32`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,931,543.3 | 9.931543 | 9.931439–9.931667 | n/a | n/a | n/a | 3,876,336 | 3.876 | 273,272 | 8.719 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `hybrid_gate` | 3 | 8,875,971.7 | 8.875972 | 8.874553–8.876794 | n/a | n/a | n/a | 3,876,336 | 3.876 | 6,204 | 13.557 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort` | 3 | 8,899,685 | 8.899685 | 8.898817–8.900241 | n/a | n/a | n/a | 3,876,336 | 3.876 | 0 | 13.557 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort_fj` | 3 | 8,875,896.7 | 8.875897 | 8.874490–8.876722 | n/a | n/a | n/a | 3,876,336 | 3.876 | 6,204 | 13.557 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |

## `dup384`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 12,389,658.3 | 12.389658 | 12.388801–12.390587 | n/a | n/a | n/a | 3,992,144 | 3.992 | 273,272 | 8.977 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `hybrid_gate` | 3 | 12,463,160 | 12.463160 | 12.461757–12.465638 | n/a | n/a | n/a | 3,992,144 | 3.992 | 6,204 | 13.938 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort` | 3 | 12,482,019.3 | 12.482019 | 12.479470–12.485540 | n/a | n/a | n/a | 3,992,144 | 3.992 | 0 | 13.938 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort_fj` | 3 | 12,462,403.3 | 12.462403 | 12.460431–12.465458 | n/a | n/a | n/a | 3,992,144 | 3.992 | 6,204 | 13.938 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |

## `dup4`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,239,439.7 | 9.239440 | 9.239189–9.239840 | n/a | n/a | n/a | 3,002,152 | 3.002 | 273,272 | 6.752 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `hybrid_gate` | 3 | 5,643,670 | 5.643670 | 5.643619–5.643722 | n/a | n/a | n/a | 3,002,152 | 3.002 | 6,204 | 10.503 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort` | 3 | 5,685,392 | 5.685392 | 5.685184–5.685571 | n/a | n/a | n/a | 3,002,152 | 3.002 | 0 | 10.503 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort_fj` | 3 | 5,643,652.7 | 5.643653 | 5.643601–5.643699 | n/a | n/a | n/a | 3,002,152 | 3.002 | 6,204 | 10.503 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |

## `dup48`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 10,155,755.3 | 10.155755 | 10.155355–10.156073 | n/a | n/a | n/a | 3,919,728 | 3.920 | 273,272 | 8.814 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `hybrid_gate` | 3 | 9,459,507.3 | 9.459507 | 9.456202–9.462519 | n/a | n/a | n/a | 3,919,728 | 3.920 | 6,204 | 13.700 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort` | 3 | 9,481,635.7 | 9.481636 | 9.478703–9.484739 | n/a | n/a | n/a | 3,919,728 | 3.920 | 0 | 13.700 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort_fj` | 3 | 9,459,368.7 | 9.459369 | 9.455975–9.462411 | n/a | n/a | n/a | 3,919,728 | 3.920 | 6,204 | 13.700 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |

## `dup512`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 12,838,432 | 12.838432 | 12.832841–12.842624 | n/a | n/a | n/a | 3,994,536 | 3.995 | 273,272 | 8.982 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `hybrid_gate` | 3 | 12,919,905.7 | 12.919906 | 12.918706–12.922072 | n/a | n/a | n/a | 3,994,536 | 3.995 | 6,204 | 13.945 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort` | 3 | 12,938,554.7 | 12.938555 | 12.936846–12.941259 | n/a | n/a | n/a | 3,994,536 | 3.995 | 0 | 13.945 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort_fj` | 3 | 12,918,925.7 | 12.918926 | 12.917206–12.921823 | n/a | n/a | n/a | 3,994,536 | 3.995 | 6,204 | 13.945 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |

## `dup6`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,377,152.7 | 9.377153 | 9.376707–9.377811 | n/a | n/a | n/a | 3,336,424 | 3.336 | 273,272 | 7.500 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `hybrid_gate` | 3 | 6,216,730.3 | 6.216730 | 6.215992–6.217585 | n/a | n/a | n/a | 3,336,424 | 3.336 | 6,204 | 11.666 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort` | 3 | 6,255,449.3 | 6.255449 | 6.254967–6.256332 | n/a | n/a | n/a | 3,336,424 | 3.336 | 0 | 11.666 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort_fj` | 3 | 6,216,706.3 | 6.216706 | 6.215975–6.217553 | n/a | n/a | n/a | 3,336,424 | 3.336 | 6,204 | 11.666 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |

## `dup64`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 10,308,791 | 10.308791 | 10.308158–10.309349 | n/a | n/a | n/a | 3,939,712 | 3.940 | 273,272 | 8.859 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `hybrid_gate` | 3 | 9,904,085 | 9.904085 | 9.903956–9.904163 | n/a | n/a | n/a | 3,939,712 | 3.940 | 6,204 | 13.769 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort` | 3 | 9,925,868.7 | 9.925869 | 9.925715–9.926042 | n/a | n/a | n/a | 3,939,712 | 3.940 | 0 | 13.769 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort_fj` | 3 | 9,903,999 | 9.903999 | 9.903863–9.904069 | n/a | n/a | n/a | 3,939,712 | 3.940 | 6,204 | 13.769 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |

## `dup768`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 13,375,408.3 | 13.375408 | 13.373902–13.376632 | n/a | n/a | n/a | 3,997,208 | 3.997 | 273,272 | 8.988 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `hybrid_gate` | 3 | 13,446,415 | 13.446415 | 13.438817–13.452402 | n/a | n/a | n/a | 3,997,208 | 3.997 | 6,204 | 13.953 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort` | 3 | 13,464,808.7 | 13.464809 | 13.456913–13.470215 | n/a | n/a | n/a | 3,997,208 | 3.997 | 0 | 13.953 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort_fj` | 3 | 13,445,241.7 | 13.445242 | 13.437167–13.451116 | n/a | n/a | n/a | 3,997,208 | 3.997 | 6,204 | 13.953 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |

## `dup8`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,460,506 | 9.460506 | 9.460217–9.460690 | n/a | n/a | n/a | 3,502,312 | 3.502 | 273,272 | 7.875 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `hybrid_gate` | 3 | 6,633,844 | 6.633844 | 6.633319–6.634502 | n/a | n/a | n/a | 3,502,312 | 3.502 | 6,204 | 12.250 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort` | 3 | 6,667,550.3 | 6.667550 | 6.666972–6.668383 | n/a | n/a | n/a | 3,502,312 | 3.502 | 0 | 12.250 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort_fj` | 3 | 6,633,803.3 | 6.633803 | 6.633260–6.634469 | n/a | n/a | n/a | 3,502,312 | 3.502 | 6,204 | 12.250 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |

## `dup96`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 10,645,156 | 10.645156 | 10.644460–10.645531 | n/a | n/a | n/a | 3,960,904 | 3.961 | 273,272 | 8.907 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `hybrid_gate` | 3 | 10,469,551.3 | 10.469551 | 10.467758–10.471287 | n/a | n/a | n/a | 3,960,904 | 3.961 | 6,204 | 13.839 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort` | 3 | 10,490,080.7 | 10.490081 | 10.488196–10.491579 | n/a | n/a | n/a | 3,960,904 | 3.961 | 0 | 13.839 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
| `powersort_fj` | 3 | 10,469,185.7 | 10.469186 | 10.467084–10.470984 | n/a | n/a | n/a | 3,960,904 | 3.961 | 6,204 | 13.839 | sm=96, fj-thresh=0, fj-max=2048, build=`498b627` |
