# de3837c prefix-aware FJ aggregates

Aggregated 663 validated rows from 2 CSV file(s). Each row below is grouped by algorithm, distribution, n, and mode. Comparison and merge-span metrics are arithmetic means, timing metrics are medians, and memory bounds/peaks are maxima.

Build IDs: `de3837c`.

For random permutations, comparison excess is `100 * (mean comparisons - lg(n!)) / lg(n!)`; it is reported as `n/a` for other distributions. Timing metrics use only `time` rows, while comparison, heap, and merge metrics use only `count` rows.

## `disp256`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 92,399.3 | 9.239933 | 9.235000–9.242800 | n/a | n/a | n/a | 8,232 | 0.823 | 12,616 | 4.646 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 92,091.7 | 9.209167 | 9.189800–9.233200 | n/a | n/a | n/a | 8,232 | 0.823 | 125,548 | 1.714 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 94,703.7 | 9.470367 | 9.461300–9.482000 | n/a | n/a | n/a | 8,232 | 0.823 | 273,272 | 0.889 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 92,213.7 | 9.221367 | 9.211600–9.227700 | n/a | n/a | n/a | 8,232 | 0.823 | 26,708 | 3.646 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 92,053 | 9.205300 | 9.187500–9.218400 | n/a | n/a | n/a | 8,232 | 0.823 | 57,696 | 2.670 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 92,960.3 | 9.296033 | 9.281100–9.307100 | n/a | n/a | n/a | 8,232 | 0.823 | 0 | 5.585 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 93,145.3 | 9.314533 | 9.310900–9.317300 | n/a | n/a | n/a | 8,104 | 0.810 | 0 | 5.563 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 92,960.3 | 9.296033 | 9.281100–9.307100 | n/a | n/a | n/a | 8,232 | 0.823 | 0 | 5.585 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `disp256`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 931,457.7 | 9.314577 | 9.306590–9.320200 | n/a | n/a | n/a | 8,952 | 0.090 | 12,616 | 4.410 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 933,709.3 | 9.337093 | 9.331780–9.342490 | n/a | n/a | n/a | 8,952 | 0.090 | 125,548 | 1.540 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 972,497 | 9.724970 | 9.722940–9.728830 | n/a | n/a | n/a | 8,952 | 0.090 | 273,272 | 0.795 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 929,542.3 | 9.295423 | 9.291090–9.300270 | n/a | n/a | n/a | 8,952 | 0.090 | 26,708 | 3.435 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 928,857 | 9.288570 | 9.283520–9.294400 | n/a | n/a | n/a | 8,952 | 0.090 | 57,696 | 2.468 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 936,929.7 | 9.369297 | 9.362300–9.374210 | n/a | n/a | n/a | 8,952 | 0.090 | 0 | 5.380 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 936,975.7 | 9.369757 | 9.367430–9.372150 | n/a | n/a | n/a | 8,872 | 0.089 | 0 | 5.377 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 936,929.7 | 9.369297 | 9.362300–9.374210 | n/a | n/a | n/a | 8,952 | 0.090 | 0 | 5.380 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `disp256`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 9,327,773.3 | 9.327773 | 9.325107–9.331700 | n/a | n/a | n/a | 9,488 | 0.009 | 12,616 | 4.101 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 9,442,519.3 | 9.442519 | 9.441146–9.444117 | n/a | n/a | n/a | 9,488 | 0.009 | 125,548 | 1.272 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 9,939,023.3 | 9.939023 | 9.937389–9.941103 | n/a | n/a | n/a | 9,488 | 0.009 | 273,272 | 0.644 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 9,314,259.3 | 9.314259 | 9.311620–9.318376 | n/a | n/a | n/a | 9,488 | 0.009 | 26,708 | 3.126 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 9,309,266.7 | 9.309267 | 9.308270–9.310749 | n/a | n/a | n/a | 9,488 | 0.009 | 57,696 | 2.165 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 9,370,218.3 | 9.370218 | 9.367250–9.374316 | n/a | n/a | n/a | 9,488 | 0.009 | 0 | 5.073 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 9,373,970 | 9.373970 | 9.369845–9.376383 | n/a | n/a | n/a | 9,672 | 0.010 | 0 | 5.054 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 9,352,622.3 | 9.352622 | 9.350002–9.356331 | n/a | n/a | n/a | 9,488 | 0.009 | 6,204 | 5.073 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `dup16`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 76,726.7 | 7.672667 | 7.672300–7.673000 | n/a | n/a | n/a | 39,856 | 3.986 | 12,616 | 6.624 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 83,958.7 | 8.395867 | 8.392000–8.398900 | n/a | n/a | n/a | 39,856 | 3.986 | 125,548 | 3.750 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 90,890.3 | 9.089033 | 9.086700–9.093200 | n/a | n/a | n/a | 39,856 | 3.986 | 273,272 | 2.813 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 76,464 | 7.646400 | 7.643800–7.650000 | n/a | n/a | n/a | 39,856 | 3.986 | 26,708 | 5.624 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 78,905 | 7.890500 | 7.886000–7.892900 | n/a | n/a | n/a | 39,856 | 3.986 | 57,696 | 4.688 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 77,980.3 | 7.798033 | 7.789700–7.806600 | n/a | n/a | n/a | 39,856 | 3.986 | 0 | 7.493 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 78,060.7 | 7.806067 | 7.801700–7.812900 | n/a | n/a | n/a | 39,856 | 3.986 | 0 | 7.471 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 77,980.3 | 7.798033 | 7.789700–7.806600 | n/a | n/a | n/a | 39,856 | 3.986 | 0 | 7.493 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `dup16`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 774,587.7 | 7.745877 | 7.745470–7.746390 | n/a | n/a | n/a | 377,584 | 3.776 | 12,616 | 9.378 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 865,183.3 | 8.651833 | 8.651190–8.653030 | n/a | n/a | n/a | 377,584 | 3.776 | 125,548 | 6.564 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 939,733.7 | 9.397337 | 9.396500–9.399010 | n/a | n/a | n/a | 377,584 | 3.776 | 273,272 | 5.627 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 773,712 | 7.737120 | 7.736090–7.737740 | n/a | n/a | n/a | 377,584 | 3.776 | 26,708 | 8.440 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 807,456 | 8.074560 | 8.073910–8.075060 | n/a | n/a | n/a | 377,584 | 3.776 | 57,696 | 7.503 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 783,898 | 7.838980 | 7.837300–7.840020 | n/a | n/a | n/a | 377,584 | 3.776 | 0 | 10.312 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 783,939.7 | 7.839397 | 7.835050–7.842780 | n/a | n/a | n/a | 377,432 | 3.774 | 0 | 10.309 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 783,898 | 7.838980 | 7.837300–7.840020 | n/a | n/a | n/a | 377,584 | 3.776 | 0 | 10.312 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `dup16`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 7,699,017.7 | 7.699018 | 7.698668–7.699276 | n/a | n/a | n/a | 3,751,624 | 3.752 | 12,616 | 12.187 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 8,887,307.7 | 8.887308 | 8.886890–8.887526 | n/a | n/a | n/a | 3,751,624 | 3.752 | 125,548 | 9.375 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 9,672,713.3 | 9.672713 | 9.672221–9.673219 | n/a | n/a | n/a | 3,751,624 | 3.752 | 273,272 | 8.437 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 7,822,115.7 | 7.822116 | 7.821832–7.822452 | n/a | n/a | n/a | 3,751,624 | 3.752 | 26,708 | 11.250 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 8,246,241.7 | 8.246242 | 8.245868–8.246553 | n/a | n/a | n/a | 3,751,624 | 3.752 | 57,696 | 10.312 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 7,838,704.3 | 7.838704 | 7.838175–7.839039 | n/a | n/a | n/a | 3,751,624 | 3.752 | 0 | 13.123 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 7,841,614.7 | 7.841615 | 7.840262–7.842537 | n/a | n/a | n/a | 3,751,840 | 3.752 | 0 | 13.109 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 7,811,909 | 7.811909 | 7.811523–7.812320 | n/a | n/a | n/a | 3,751,624 | 3.752 | 6,204 | 13.123 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `nearly1`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 37,440.3 | 3.744033 | 3.643700–3.890900 | n/a | n/a | n/a | 41,496 | 4.150 | 12,616 | 5.924 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 76,927.3 | 7.692733 | 7.622200–7.814200 | n/a | n/a | n/a | 41,512 | 4.151 | 125,548 | 3.761 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 88,801.3 | 8.880133 | 8.765500–8.944900 | n/a | n/a | n/a | 41,512 | 4.151 | 273,272 | 2.883 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 50,371.3 | 5.037133 | 4.957400–5.094700 | n/a | n/a | n/a | 41,368 | 4.137 | 26,708 | 5.285 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 64,488.3 | 6.448833 | 6.432900–6.477700 | n/a | n/a | n/a | 41,512 | 4.151 | 57,696 | 4.566 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 23,094 | 2.309400 | 2.212900–2.412500 | n/a | n/a | n/a | 41,480 | 4.148 | 0 | 5.971 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 23,138.3 | 2.313833 | 2.260700–2.414800 | n/a | n/a | n/a | 41,480 | 4.148 | 0 | 5.961 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 23,094 | 2.309400 | 2.212900–2.412500 | n/a | n/a | n/a | 41,480 | 4.148 | 0 | 5.971 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `nearly1`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 399,407 | 3.994070 | 3.946880–4.035600 | n/a | n/a | n/a | 402,144 | 4.021 | 12,616 | 8.990 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 821,020.3 | 8.210203 | 8.183040–8.252660 | n/a | n/a | n/a | 402,200 | 4.022 | 125,548 | 6.835 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 930,513 | 9.305130 | 9.300330–9.309670 | n/a | n/a | n/a | 402,200 | 4.022 | 273,272 | 5.906 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 558,955 | 5.589550 | 5.572870–5.609630 | n/a | n/a | n/a | 402,088 | 4.021 | 26,708 | 8.459 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 699,986.3 | 6.999863 | 6.967140–7.033980 | n/a | n/a | n/a | 402,200 | 4.022 | 57,696 | 7.699 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 268,395.3 | 2.683953 | 2.657060–2.704710 | n/a | n/a | n/a | 402,232 | 4.022 | 0 | 9.283 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 268,892 | 2.688920 | 2.658950–2.711520 | n/a | n/a | n/a | 402,232 | 4.022 | 0 | 9.282 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 268,395.3 | 2.683953 | 2.657060–2.704710 | n/a | n/a | n/a | 402,232 | 4.022 | 0 | 9.283 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `nearly1`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 4,608,965 | 4.608965 | 4.592455–4.630131 | n/a | n/a | n/a | 4,001,744 | 4.002 | 12,616 | 12.200 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 8,643,408.7 | 8.643409 | 8.629973–8.650960 | n/a | n/a | n/a | 4,002,216 | 4.002 | 125,548 | 9.884 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 9,732,449.7 | 9.732450 | 9.725641–9.740757 | n/a | n/a | n/a | 4,002,216 | 4.002 | 273,272 | 8.935 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 6,166,625.7 | 6.166626 | 6.155507–6.172317 | n/a | n/a | n/a | 4,002,096 | 4.002 | 26,708 | 11.578 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 7,478,511 | 7.478511 | 7.474073–7.481570 | n/a | n/a | n/a | 4,002,128 | 4.002 | 57,696 | 10.781 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 3,135,249 | 3.135249 | 3.131752–3.138751 | n/a | n/a | n/a | 4,002,072 | 4.002 | 0 | 12.574 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 3,162,329.3 | 3.162329 | 3.158865–3.167300 | n/a | n/a | n/a | 4,002,072 | 4.002 | 0 | 12.571 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 3,126,208.7 | 3.126209 | 3.122805–3.129789 | n/a | n/a | n/a | 4,002,072 | 4.002 | 6,204 | 12.574 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `organpipe`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 19,998 | 1.999800 | 1.999800–1.999800 | n/a | n/a | n/a | 42,296 | 4.230 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 19,998 | 1.999800 | 1.999800–1.999800 | n/a | n/a | n/a | 42,296 | 4.230 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 19,998 | 1.999800 | 1.999800–1.999800 | n/a | n/a | n/a | 42,296 | 4.230 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 19,998 | 1.999800 | 1.999800–1.999800 | n/a | n/a | n/a | 42,296 | 4.230 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 19,998 | 1.999800 | 1.999800–1.999800 | n/a | n/a | n/a | 42,296 | 4.230 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 19,998 | 1.999800 | 1.999800–1.999800 | n/a | n/a | n/a | 42,296 | 4.230 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 19,998 | 1.999800 | 1.999800–1.999800 | n/a | n/a | n/a | 42,296 | 4.230 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 19,998 | 1.999800 | 1.999800–1.999800 | n/a | n/a | n/a | 42,296 | 4.230 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `organpipe`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 199,998 | 1.999980 | 1.999980–1.999980 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 199,998 | 1.999980 | 1.999980–1.999980 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 199,998 | 1.999980 | 1.999980–1.999980 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 199,998 | 1.999980 | 1.999980–1.999980 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 199,998 | 1.999980 | 1.999980–1.999980 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 199,998 | 1.999980 | 1.999980–1.999980 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 199,998 | 1.999980 | 1.999980–1.999980 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 199,998 | 1.999980 | 1.999980–1.999980 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `organpipe`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `random`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 119,163 | 11.916300 | 11.916000–11.916700 | 11.845814 | 0.070486 | +0.595% | 42,304 | 4.230 | 12,616 | 6.987 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 118,752.7 | 11.875267 | 11.874300–11.877000 | 11.845814 | 0.029452 | +0.249% | 42,304 | 4.230 | 125,548 | 3.997 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 118,688.3 | 11.868833 | 11.866400–11.871000 | 11.845814 | 0.023019 | +0.194% | 42,304 | 4.230 | 273,272 | 2.999 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 118,939 | 11.893900 | 11.893000–11.895700 | 11.845814 | 0.048086 | +0.406% | 42,304 | 4.230 | 26,708 | 5.987 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 118,805.3 | 11.880533 | 11.880100–11.881200 | 11.845814 | 0.034719 | +0.293% | 42,304 | 4.230 | 57,696 | 4.995 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 119,708 | 11.970800 | 11.966900–11.973600 | 11.845814 | 0.124986 | +1.055% | 42,304 | 4.230 | 0 | 7.948 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 119,773 | 11.977300 | 11.971500–11.984100 | 11.845814 | 0.131486 | +1.110% | 42,304 | 4.230 | 0 | 7.926 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 119,708 | 11.970800 | 11.966900–11.973600 | 11.845814 | 0.124986 | +1.055% | 42,304 | 4.230 | 0 | 7.948 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `random`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 1,523,106.7 | 15.231067 | 15.230200–15.232050 | 15.167042 | 0.064025 | +0.422% | 402,296 | 4.023 | 12,616 | 9.979 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 1,519,302.3 | 15.193023 | 15.192400–15.193620 | 15.167042 | 0.025982 | +0.171% | 402,296 | 4.023 | 125,548 | 6.997 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 1,519,047.3 | 15.190473 | 15.189880–15.190920 | 15.167042 | 0.023432 | +0.154% | 402,296 | 4.023 | 273,272 | 5.999 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 1,521,146.7 | 15.211467 | 15.211030–15.212070 | 15.167042 | 0.044425 | +0.293% | 402,296 | 4.023 | 26,708 | 8.990 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 1,519,954.3 | 15.199543 | 15.198600–15.200570 | 15.167042 | 0.032502 | +0.214% | 402,296 | 4.023 | 57,696 | 7.995 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 1,528,942.7 | 15.289427 | 15.289150–15.289570 | 15.167042 | 0.122385 | +0.807% | 402,296 | 4.023 | 0 | 10.960 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 1,529,125.7 | 15.291257 | 15.290370–15.292780 | 15.167042 | 0.124215 | +0.819% | 402,144 | 4.021 | 0 | 10.956 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 1,528,942.7 | 15.289427 | 15.289150–15.289570 | 15.167042 | 0.122385 | +0.807% | 402,296 | 4.023 | 0 | 10.960 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `random`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 18,553,594 | 18.553594 | 18.553264–18.553836 | 18.488885 | 0.064709 | +0.350% | 4,002,288 | 4.002 | 12,616 | 12.984 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 18,523,246.7 | 18.523247 | 18.523063–18.523455 | 18.488885 | 0.034362 | +0.186% | 4,002,288 | 4.002 | 125,548 | 9.998 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 18,520,455.7 | 18.520456 | 18.520411–18.520489 | 18.488885 | 0.031571 | +0.171% | 4,002,288 | 4.002 | 273,272 | 8.999 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 18,537,869.7 | 18.537870 | 18.537741–18.538025 | 18.488885 | 0.048985 | +0.265% | 4,002,288 | 4.002 | 26,708 | 11.992 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 18,528,400.7 | 18.528401 | 18.528260–18.528610 | 18.488885 | 0.039516 | +0.214% | 4,002,288 | 4.002 | 57,696 | 10.996 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 18,599,038.7 | 18.599039 | 18.598521–18.599329 | 18.488885 | 0.110154 | +0.596% | 4,002,288 | 4.002 | 0 | 13.968 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 18,604,336.3 | 18.604336 | 18.604170–18.604436 | 18.488885 | 0.115452 | +0.624% | 4,002,056 | 4.002 | 0 | 13.952 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 18,580,017.7 | 18.580018 | 18.579784–18.580189 | 18.488885 | 0.091133 | +0.493% | 4,002,288 | 4.002 | 6,204 | 13.968 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 5 | 141,616,629 | 141.6 | 273,272 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 5 | 72,584,529 | 72.585 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 5 | 81,597,021 | 81.597 | 6,204 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `runs1024`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 44,079.3 | 4.407933 | 4.407600–4.408100 | n/a | n/a | n/a | 41,344 | 4.134 | 0 | 3.408 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 44,079.3 | 4.407933 | 4.407600–4.408100 | n/a | n/a | n/a | 41,344 | 4.134 | 0 | 3.408 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 84,111.7 | 8.411167 | 8.410700–8.411600 | n/a | n/a | n/a | 42,304 | 4.230 | 0 | 2.999 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 44,079.3 | 4.407933 | 4.407600–4.408100 | n/a | n/a | n/a | 41,344 | 4.134 | 0 | 3.408 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 44,079.3 | 4.407933 | 4.407600–4.408100 | n/a | n/a | n/a | 41,344 | 4.134 | 0 | 3.408 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 44,079.3 | 4.407933 | 4.407600–4.408100 | n/a | n/a | n/a | 41,344 | 4.134 | 0 | 3.408 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 44,079.3 | 4.407933 | 4.407600–4.408100 | n/a | n/a | n/a | 41,344 | 4.134 | 0 | 3.408 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 44,079.3 | 4.407933 | 4.407600–4.408100 | n/a | n/a | n/a | 41,344 | 4.134 | 0 | 3.408 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `runs1024`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 769,092.7 | 7.690927 | 7.690830–7.691030 | n/a | n/a | n/a | 400,896 | 4.009 | 0 | 6.691 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 769,092.7 | 7.690927 | 7.690830–7.691030 | n/a | n/a | n/a | 400,896 | 4.009 | 0 | 6.691 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 1,289,931 | 12.899310 | 12.899140–12.899450 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 5.999 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 769,092.7 | 7.690927 | 7.690830–7.691030 | n/a | n/a | n/a | 400,896 | 4.009 | 0 | 6.691 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 769,092.7 | 7.690927 | 7.690830–7.691030 | n/a | n/a | n/a | 400,896 | 4.009 | 0 | 6.691 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 769,092.7 | 7.690927 | 7.690830–7.691030 | n/a | n/a | n/a | 400,896 | 4.009 | 0 | 6.691 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 769,092.7 | 7.690927 | 7.690830–7.691030 | n/a | n/a | n/a | 400,896 | 4.009 | 0 | 6.691 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 769,092.7 | 7.690927 | 7.690830–7.691030 | n/a | n/a | n/a | 400,896 | 4.009 | 0 | 6.691 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `runs1024`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 16,740,316 | 16.740316 | 16.740099–16.740533 | n/a | n/a | n/a | 4,002,288 | 4.002 | 273,272 | 8.999 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `runs32`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 114,702 | 11.470200 | 11.467300–11.475100 | n/a | n/a | n/a | 42,304 | 4.230 | 12,616 | 6.987 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 118,251 | 11.825100 | 11.824100–11.826800 | n/a | n/a | n/a | 42,304 | 4.230 | 125,548 | 3.997 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 118,551 | 11.855100 | 11.854400–11.855900 | n/a | n/a | n/a | 42,304 | 4.230 | 0 | 2.999 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 116,737.3 | 11.673733 | 11.669800–11.677400 | n/a | n/a | n/a | 42,304 | 4.230 | 26,708 | 5.987 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 117,734 | 11.773400 | 11.768800–11.778000 | n/a | n/a | n/a | 42,304 | 4.230 | 57,696 | 4.994 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 110,693 | 11.069300 | 11.064500–11.074000 | n/a | n/a | n/a | 42,304 | 4.230 | 0 | 7.944 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 108,678 | 10.867800 | 10.865200–10.872500 | n/a | n/a | n/a | 42,304 | 4.230 | 0 | 7.921 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 110,693 | 11.069300 | 11.064500–11.074000 | n/a | n/a | n/a | 42,304 | 4.230 | 0 | 7.944 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `runs32`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 1,487,921.7 | 14.879217 | 14.878140–14.879840 | n/a | n/a | n/a | 402,296 | 4.023 | 12,616 | 9.980 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 1,516,180 | 15.161800 | 15.161300–15.162690 | n/a | n/a | n/a | 402,296 | 4.023 | 125,548 | 6.997 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 1,518,036.3 | 15.180363 | 15.179270–15.181200 | n/a | n/a | n/a | 402,296 | 4.023 | 273,272 | 5.999 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 1,504,257.7 | 15.042577 | 15.040340–15.044500 | n/a | n/a | n/a | 402,296 | 4.023 | 26,708 | 8.990 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 1,512,288.7 | 15.122887 | 15.120410–15.125040 | n/a | n/a | n/a | 402,296 | 4.023 | 57,696 | 7.995 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 1,456,341 | 14.563410 | 14.562470–14.564500 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 10.956 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 1,456,558.3 | 14.565583 | 14.565540–14.565630 | n/a | n/a | n/a | 402,144 | 4.021 | 0 | 10.952 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 1,456,341 | 14.563410 | 14.562470–14.564500 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 10.956 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `runs32`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 18,269,430.3 | 18.269430 | 18.269108–18.269645 | n/a | n/a | n/a | 4,002,288 | 4.002 | 12,616 | 12.984 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 18,494,308.3 | 18.494308 | 18.493923–18.494711 | n/a | n/a | n/a | 4,002,288 | 4.002 | 125,548 | 9.998 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 18,507,786.7 | 18.507787 | 18.507633–18.507881 | n/a | n/a | n/a | 4,002,288 | 4.002 | 273,272 | 8.999 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 18,399,313.7 | 18.399314 | 18.399091–18.399737 | n/a | n/a | n/a | 4,002,288 | 4.002 | 26,708 | 11.992 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 18,463,655 | 18.463655 | 18.463490–18.463883 | n/a | n/a | n/a | 4,002,288 | 4.002 | 57,696 | 10.996 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 18,019,755.3 | 18.019755 | 18.019363–18.020256 | n/a | n/a | n/a | 4,002,288 | 4.002 | 0 | 13.967 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 18,014,450 | 18.014450 | 18.013610–18.015068 | n/a | n/a | n/a | 4,002,056 | 4.002 | 0 | 13.952 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 18,004,464 | 18.004464 | 18.003992–18.004996 | n/a | n/a | n/a | 4,002,288 | 4.002 | 6,204 | 13.967 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `saw13`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 73,084 | 7.308400 | 7.308400–7.308400 | n/a | n/a | n/a | 39,224 | 3.922 | 12,616 | 6.538 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 83,116 | 8.311600 | 8.311600–8.311600 | n/a | n/a | n/a | 39,224 | 3.922 | 125,548 | 3.692 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 90,673 | 9.067300 | 9.067300–9.067300 | n/a | n/a | n/a | 39,224 | 3.922 | 273,272 | 2.769 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 73,674 | 7.367400 | 7.367400–7.367400 | n/a | n/a | n/a | 39,224 | 3.922 | 26,708 | 5.538 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 77,251 | 7.725100 | 7.725100–7.725100 | n/a | n/a | n/a | 39,224 | 3.922 | 57,696 | 4.615 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 72,523 | 7.252300 | 7.252300–7.252300 | n/a | n/a | n/a | 39,224 | 3.922 | 0 | 7.385 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 73,156 | 7.315600 | 7.315600–7.315600 | n/a | n/a | n/a | 39,224 | 3.922 | 0 | 7.361 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 72,523 | 7.252300 | 7.252300–7.252300 | n/a | n/a | n/a | 39,224 | 3.922 | 0 | 7.385 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `saw13`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 727,135 | 7.271350 | 7.271350–7.271350 | n/a | n/a | n/a | 371,528 | 3.715 | 12,616 | 9.231 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 857,783 | 8.577830 | 8.577830–8.577830 | n/a | n/a | n/a | 371,528 | 3.715 | 125,548 | 6.462 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 937,905 | 9.379050 | 9.379050–9.379050 | n/a | n/a | n/a | 371,528 | 3.715 | 273,272 | 5.538 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 742,823 | 7.428230 | 7.428230–7.428230 | n/a | n/a | n/a | 371,528 | 3.715 | 26,708 | 8.308 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 790,496 | 7.904960 | 7.904960–7.904960 | n/a | n/a | n/a | 371,528 | 3.715 | 57,696 | 7.385 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 730,997 | 7.309970 | 7.309970–7.309970 | n/a | n/a | n/a | 371,528 | 3.715 | 0 | 10.154 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 731,895 | 7.318950 | 7.318950–7.318950 | n/a | n/a | n/a | 371,384 | 3.714 | 0 | 10.151 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 730,997 | 7.309970 | 7.309970–7.309970 | n/a | n/a | n/a | 371,528 | 3.715 | 0 | 10.154 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `saw13`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 7,494,418 | 7.494418 | 7.494418–7.494418 | n/a | n/a | n/a | 3,694,608 | 3.695 | 12,616 | 12.000 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 8,872,483 | 8.872483 | 8.872483–8.872483 | n/a | n/a | n/a | 3,694,608 | 3.695 | 125,548 | 9.231 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 9,683,467 | 9.683467 | 9.683467–9.683467 | n/a | n/a | n/a | 3,694,608 | 3.695 | 273,272 | 8.308 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 7,697,341 | 7.697341 | 7.697341–7.697341 | n/a | n/a | n/a | 3,694,608 | 3.695 | 26,708 | 11.077 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 8,185,441 | 8.185441 | 8.185441–8.185441 | n/a | n/a | n/a | 3,694,608 | 3.695 | 57,696 | 10.154 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 7,508,402 | 7.508402 | 7.508402–7.508402 | n/a | n/a | n/a | 3,694,608 | 3.695 | 0 | 12.923 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 7,511,232 | 7.511232 | 7.511232–7.511232 | n/a | n/a | n/a | 3,694,384 | 3.694 | 0 | 12.909 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 7,484,409 | 7.484409 | 7.484409–7.484409 | n/a | n/a | n/a | 3,694,608 | 3.695 | 6,204 | 12.923 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `tail10`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 25,932 | 2.593200 | 2.523500–2.676000 | n/a | n/a | n/a | 9,568 | 0.957 | 12,616 | 1.372 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 25,812 | 2.581200 | 2.510200–2.664700 | n/a | n/a | n/a | 9,568 | 0.957 | 125,548 | 1.088 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 25,591.7 | 2.559167 | 2.491400–2.622600 | n/a | n/a | n/a | 9,568 | 0.957 | 248,428 | 0.988 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 25,873 | 2.587300 | 2.516500–2.671700 | n/a | n/a | n/a | 9,568 | 0.957 | 26,708 | 1.272 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 25,942 | 2.594200 | 2.525100–2.677500 | n/a | n/a | n/a | 9,568 | 0.957 | 57,696 | 1.188 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 25,993.3 | 2.599333 | 2.530900–2.682500 | n/a | n/a | n/a | 9,568 | 0.957 | 0 | 1.467 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 26,482 | 2.648200 | 2.589700–2.683500 | n/a | n/a | n/a | 9,568 | 0.957 | 0 | 1.463 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 25,993.3 | 2.599333 | 2.530900–2.682500 | n/a | n/a | n/a | 9,568 | 0.957 | 0 | 1.467 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `tail10`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 305,206.3 | 3.052063 | 3.038460–3.059040 | n/a | n/a | n/a | 78,920 | 0.789 | 12,616 | 1.677 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 304,366 | 3.043660 | 3.030640–3.050540 | n/a | n/a | n/a | 78,920 | 0.789 | 125,548 | 1.376 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 303,484.3 | 3.034843 | 3.023640–3.043370 | n/a | n/a | n/a | 78,920 | 0.789 | 273,272 | 1.276 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 305,075 | 3.050750 | 3.037040–3.057650 | n/a | n/a | n/a | 78,920 | 0.789 | 26,708 | 1.579 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 304,467.7 | 3.044677 | 3.031460–3.051650 | n/a | n/a | n/a | 78,920 | 0.789 | 57,696 | 1.475 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 305,640 | 3.056400 | 3.042190–3.063900 | n/a | n/a | n/a | 78,920 | 0.789 | 0 | 1.774 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 305,707.3 | 3.057073 | 3.042490–3.065030 | n/a | n/a | n/a | 78,920 | 0.789 | 0 | 1.773 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 305,640 | 3.056400 | 3.042190–3.063900 | n/a | n/a | n/a | 78,920 | 0.789 | 0 | 1.774 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |

## `tail10`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 3,427,249.7 | 3.427250 | 3.421789–3.431239 | n/a | n/a | n/a | 730,864 | 0.731 | 12,616 | 1.975 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto1024` | 3 | 3,426,867.7 | 3.426868 | 3.425950–3.428542 | n/a | n/a | n/a | 730,864 | 0.731 | 125,548 | 1.678 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto2048` | 3 | 3,427,093.7 | 3.427094 | 3.426109–3.428779 | n/a | n/a | n/a | 730,864 | 0.731 | 273,272 | 1.579 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto256` | 3 | 3,425,181.3 | 3.425181 | 3.419699–3.429266 | n/a | n/a | n/a | 730,864 | 0.731 | 26,708 | 1.876 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `hybrid_fjauto512` | 3 | 3,424,196.3 | 3.424196 | 3.418824–3.428165 | n/a | n/a | n/a | 730,864 | 0.731 | 57,696 | 1.776 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort` | 3 | 3,431,823.7 | 3.431824 | 3.426400–3.435704 | n/a | n/a | n/a | 730,864 | 0.731 | 0 | 2.074 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fixed` | 3 | 3,432,113.3 | 3.432113 | 3.426519–3.436129 | n/a | n/a | n/a | 730,864 | 0.731 | 0 | 2.072 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
| `powersort_fj` | 3 | 3,429,860.3 | 3.429860 | 3.424365–3.433655 | n/a | n/a | n/a | 730,864 | 0.731 | 6,204 | 2.074 | sm=96, fj-thresh=0, fj-max=2048, build=`de3837c` |
