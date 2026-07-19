# d310ed5 milestone benchmark aggregates

Aggregated 663 validated rows from 2 CSV file(s). Each row below is grouped by algorithm, distribution, n, and mode. Comparison and merge-span metrics are arithmetic means, timing metrics are medians, and memory bounds/peaks are maxima.

Build IDs: `d310ed5`.

For random permutations, comparison excess is `100 * (mean comparisons - lg(n!)) / lg(n!)`; it is reported as `n/a` for other distributions. Timing metrics use only `time` rows, while comparison, heap, and merge metrics use only `count` rows.

## `disp256`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 92,494.3 | 9.249433 | 9.244300–9.253000 | n/a | n/a | n/a | 8,232 | 0.823 | 12,616 | 4.646 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 92,107.7 | 9.210767 | 9.191400–9.234800 | n/a | n/a | n/a | 8,232 | 0.823 | 125,548 | 1.714 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 94,711.7 | 9.471167 | 9.462100–9.482800 | n/a | n/a | n/a | 8,232 | 0.823 | 273,272 | 0.889 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 92,276.3 | 9.227633 | 9.218000–9.233700 | n/a | n/a | n/a | 8,232 | 0.823 | 26,708 | 3.646 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 92,085 | 9.208500 | 9.190700–9.221600 | n/a | n/a | n/a | 8,232 | 0.823 | 57,696 | 2.670 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 92,960.3 | 9.296033 | 9.281100–9.307100 | n/a | n/a | n/a | 8,232 | 0.823 | 0 | 5.585 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 93,145.3 | 9.314533 | 9.310900–9.317300 | n/a | n/a | n/a | 8,104 | 0.810 | 0 | 5.563 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 92,960.3 | 9.296033 | 9.281100–9.307100 | n/a | n/a | n/a | 8,232 | 0.823 | 0 | 5.585 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `disp256`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 932,393.3 | 9.323933 | 9.315890–9.329570 | n/a | n/a | n/a | 8,952 | 0.090 | 12,616 | 4.410 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 933,837 | 9.338370 | 9.333050–9.343770 | n/a | n/a | n/a | 8,952 | 0.090 | 125,548 | 1.540 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 972,561 | 9.725610 | 9.723580–9.729470 | n/a | n/a | n/a | 8,952 | 0.090 | 273,272 | 0.795 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 930,047.7 | 9.300477 | 9.296140–9.305300 | n/a | n/a | n/a | 8,952 | 0.090 | 26,708 | 3.435 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 929,112.3 | 9.291123 | 9.286070–9.296960 | n/a | n/a | n/a | 8,952 | 0.090 | 57,696 | 2.468 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 936,929.7 | 9.369297 | 9.362300–9.374210 | n/a | n/a | n/a | 8,952 | 0.090 | 0 | 5.380 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 936,975.7 | 9.369757 | 9.367430–9.372150 | n/a | n/a | n/a | 8,872 | 0.089 | 0 | 5.377 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 936,929.7 | 9.369297 | 9.362300–9.374210 | n/a | n/a | n/a | 8,952 | 0.090 | 0 | 5.380 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `disp256`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 9,335,271.7 | 9.335272 | 9.332592–9.339205 | n/a | n/a | n/a | 9,488 | 0.009 | 12,616 | 4.101 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 9,443,542.7 | 9.443543 | 9.442169–9.445141 | n/a | n/a | n/a | 9,488 | 0.009 | 125,548 | 1.272 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 9,939,535 | 9.939535 | 9.937900–9.941615 | n/a | n/a | n/a | 9,488 | 0.009 | 273,272 | 0.644 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 9,318,297.7 | 9.318298 | 9.315650–9.322418 | n/a | n/a | n/a | 9,488 | 0.009 | 26,708 | 3.126 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 9,311,310.3 | 9.311310 | 9.310313–9.312794 | n/a | n/a | n/a | 9,488 | 0.009 | 57,696 | 2.165 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 9,370,218.3 | 9.370218 | 9.367250–9.374316 | n/a | n/a | n/a | 9,488 | 0.009 | 0 | 5.073 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 9,373,970 | 9.373970 | 9.369845–9.376383 | n/a | n/a | n/a | 9,672 | 0.010 | 0 | 5.054 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 9,363,565.3 | 9.363565 | 9.360881–9.367342 | n/a | n/a | n/a | 9,488 | 0.009 | 6,204 | 5.073 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `dup16`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 76,811.3 | 7.681133 | 7.680700–7.681800 | n/a | n/a | n/a | 39,856 | 3.986 | 12,616 | 6.624 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 83,974.7 | 8.397467 | 8.393600–8.400500 | n/a | n/a | n/a | 39,856 | 3.986 | 125,548 | 3.750 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 90,898.3 | 9.089833 | 9.087500–9.094000 | n/a | n/a | n/a | 39,856 | 3.986 | 273,272 | 2.813 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 76,526.3 | 7.652633 | 7.650100–7.656300 | n/a | n/a | n/a | 39,856 | 3.986 | 26,708 | 5.624 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 78,937 | 7.893700 | 7.889200–7.896100 | n/a | n/a | n/a | 39,856 | 3.986 | 57,696 | 4.688 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 77,980.3 | 7.798033 | 7.789700–7.806600 | n/a | n/a | n/a | 39,856 | 3.986 | 0 | 7.493 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 78,060.7 | 7.806067 | 7.801700–7.812900 | n/a | n/a | n/a | 39,856 | 3.986 | 0 | 7.471 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 77,980.3 | 7.798033 | 7.789700–7.806600 | n/a | n/a | n/a | 39,856 | 3.986 | 0 | 7.493 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `dup16`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 775,527.7 | 7.755277 | 7.754870–7.755720 | n/a | n/a | n/a | 377,584 | 3.776 | 12,616 | 9.378 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 865,311.3 | 8.653113 | 8.652470–8.654310 | n/a | n/a | n/a | 377,584 | 3.776 | 125,548 | 6.564 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 939,797.7 | 9.397977 | 9.397140–9.399650 | n/a | n/a | n/a | 377,584 | 3.776 | 273,272 | 5.627 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 774,216 | 7.742160 | 7.741120–7.742800 | n/a | n/a | n/a | 377,584 | 3.776 | 26,708 | 8.440 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 807,711 | 8.077110 | 8.076440–8.077620 | n/a | n/a | n/a | 377,584 | 3.776 | 57,696 | 7.503 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 783,898 | 7.838980 | 7.837300–7.840020 | n/a | n/a | n/a | 377,584 | 3.776 | 0 | 10.312 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 783,939.7 | 7.839397 | 7.835050–7.842780 | n/a | n/a | n/a | 377,432 | 3.774 | 0 | 10.309 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 783,898 | 7.838980 | 7.837300–7.840020 | n/a | n/a | n/a | 377,584 | 3.776 | 0 | 10.312 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `dup16`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 7,706,494 | 7.706494 | 7.706144–7.706751 | n/a | n/a | n/a | 3,751,624 | 3.752 | 12,616 | 12.187 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 8,888,331.3 | 8.888331 | 8.887914–8.888549 | n/a | n/a | n/a | 3,751,624 | 3.752 | 125,548 | 9.375 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 9,673,225.3 | 9.673225 | 9.672733–9.673731 | n/a | n/a | n/a | 3,751,624 | 3.752 | 273,272 | 8.437 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 7,826,136 | 7.826136 | 7.825857–7.826466 | n/a | n/a | n/a | 3,751,624 | 3.752 | 26,708 | 11.250 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 8,248,283 | 8.248283 | 8.247909–8.248595 | n/a | n/a | n/a | 3,751,624 | 3.752 | 57,696 | 10.312 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 7,838,704.3 | 7.838704 | 7.838175–7.839039 | n/a | n/a | n/a | 3,751,624 | 3.752 | 0 | 13.123 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 7,841,614.7 | 7.841615 | 7.840262–7.842537 | n/a | n/a | n/a | 3,751,840 | 3.752 | 0 | 13.109 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 7,822,707 | 7.822707 | 7.822357–7.823126 | n/a | n/a | n/a | 3,751,624 | 3.752 | 6,204 | 13.123 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `nearly1`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 37,445 | 3.744500 | 3.644200–3.891400 | n/a | n/a | n/a | 41,496 | 4.150 | 12,616 | 5.924 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 76,928.7 | 7.692867 | 7.622300–7.814400 | n/a | n/a | n/a | 41,512 | 4.151 | 125,548 | 3.761 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 88,802 | 8.880200 | 8.765600–8.945000 | n/a | n/a | n/a | 41,512 | 4.151 | 273,272 | 2.883 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 50,376.3 | 5.037633 | 4.957900–5.095100 | n/a | n/a | n/a | 41,368 | 4.137 | 26,708 | 5.285 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 64,491.3 | 6.449133 | 6.433300–6.477900 | n/a | n/a | n/a | 41,512 | 4.151 | 57,696 | 4.566 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 23,094 | 2.309400 | 2.212900–2.412500 | n/a | n/a | n/a | 41,480 | 4.148 | 0 | 5.971 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 23,138.3 | 2.313833 | 2.260700–2.414800 | n/a | n/a | n/a | 41,480 | 4.148 | 0 | 5.961 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 23,094 | 2.309400 | 2.212900–2.412500 | n/a | n/a | n/a | 41,480 | 4.148 | 0 | 5.971 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `nearly1`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 399,460.7 | 3.994607 | 3.947410–4.036210 | n/a | n/a | n/a | 402,144 | 4.021 | 12,616 | 8.990 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 821,034 | 8.210340 | 8.183170–8.252780 | n/a | n/a | n/a | 402,200 | 4.022 | 125,548 | 6.835 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 930,520.7 | 9.305207 | 9.300400–9.309760 | n/a | n/a | n/a | 402,200 | 4.022 | 273,272 | 5.906 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 558,996 | 5.589960 | 5.573320–5.609990 | n/a | n/a | n/a | 402,088 | 4.021 | 26,708 | 8.459 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 700,009 | 7.000090 | 6.967330–7.034260 | n/a | n/a | n/a | 402,200 | 4.022 | 57,696 | 7.699 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 268,395.3 | 2.683953 | 2.657060–2.704710 | n/a | n/a | n/a | 402,232 | 4.022 | 0 | 9.283 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 268,892 | 2.688920 | 2.658950–2.711520 | n/a | n/a | n/a | 402,232 | 4.022 | 0 | 9.282 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 268,395.3 | 2.683953 | 2.657060–2.704710 | n/a | n/a | n/a | 402,232 | 4.022 | 0 | 9.283 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `nearly1`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 4,609,430 | 4.609430 | 4.592892–4.630609 | n/a | n/a | n/a | 4,001,744 | 4.002 | 12,616 | 12.200 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 8,643,525.3 | 8.643525 | 8.630098–8.651069 | n/a | n/a | n/a | 4,002,216 | 4.002 | 125,548 | 9.884 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 9,732,513 | 9.732513 | 9.725707–9.740819 | n/a | n/a | n/a | 4,002,216 | 4.002 | 273,272 | 8.935 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 6,166,952 | 6.166952 | 6.155828–6.172665 | n/a | n/a | n/a | 4,002,096 | 4.002 | 26,708 | 11.578 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 7,478,708.3 | 7.478708 | 7.474279–7.481746 | n/a | n/a | n/a | 4,002,128 | 4.002 | 57,696 | 10.781 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 3,135,249 | 3.135249 | 3.131752–3.138751 | n/a | n/a | n/a | 4,002,072 | 4.002 | 0 | 12.574 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 3,162,329.3 | 3.162329 | 3.158865–3.167300 | n/a | n/a | n/a | 4,002,072 | 4.002 | 0 | 12.571 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 3,126,676.7 | 3.126677 | 3.123268–3.130239 | n/a | n/a | n/a | 4,002,072 | 4.002 | 6,204 | 12.574 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `organpipe`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 19,998 | 1.999800 | 1.999800–1.999800 | n/a | n/a | n/a | 42,296 | 4.230 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 19,998 | 1.999800 | 1.999800–1.999800 | n/a | n/a | n/a | 42,296 | 4.230 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 19,998 | 1.999800 | 1.999800–1.999800 | n/a | n/a | n/a | 42,296 | 4.230 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 19,998 | 1.999800 | 1.999800–1.999800 | n/a | n/a | n/a | 42,296 | 4.230 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 19,998 | 1.999800 | 1.999800–1.999800 | n/a | n/a | n/a | 42,296 | 4.230 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 19,998 | 1.999800 | 1.999800–1.999800 | n/a | n/a | n/a | 42,296 | 4.230 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 19,998 | 1.999800 | 1.999800–1.999800 | n/a | n/a | n/a | 42,296 | 4.230 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 19,998 | 1.999800 | 1.999800–1.999800 | n/a | n/a | n/a | 42,296 | 4.230 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `organpipe`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 199,998 | 1.999980 | 1.999980–1.999980 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 199,998 | 1.999980 | 1.999980–1.999980 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 199,998 | 1.999980 | 1.999980–1.999980 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 199,998 | 1.999980 | 1.999980–1.999980 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 199,998 | 1.999980 | 1.999980–1.999980 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 199,998 | 1.999980 | 1.999980–1.999980 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 199,998 | 1.999980 | 1.999980–1.999980 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 199,998 | 1.999980 | 1.999980–1.999980 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `organpipe`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `random`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 119,249.3 | 11.924933 | 11.924400–11.925500 | 11.845814 | 0.079119 | +0.668% | 42,304 | 4.230 | 12,616 | 6.987 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 118,768.7 | 11.876867 | 11.875900–11.878600 | 11.845814 | 0.031052 | +0.262% | 42,304 | 4.230 | 125,548 | 3.997 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 118,696.3 | 11.869633 | 11.867200–11.871800 | 11.845814 | 0.023819 | +0.201% | 42,304 | 4.230 | 273,272 | 2.999 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 119,002.7 | 11.900267 | 11.899300–11.902100 | 11.845814 | 0.054452 | +0.460% | 42,304 | 4.230 | 26,708 | 5.987 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 118,837.3 | 11.883733 | 11.883300–11.884400 | 11.845814 | 0.037919 | +0.320% | 42,304 | 4.230 | 57,696 | 4.995 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 119,708 | 11.970800 | 11.966900–11.973600 | 11.845814 | 0.124986 | +1.055% | 42,304 | 4.230 | 0 | 7.948 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 119,773 | 11.977300 | 11.971500–11.984100 | 11.845814 | 0.131486 | +1.110% | 42,304 | 4.230 | 0 | 7.926 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 119,708 | 11.970800 | 11.966900–11.973600 | 11.845814 | 0.124986 | +1.055% | 42,304 | 4.230 | 0 | 7.948 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `random`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 1,524,049.7 | 15.240497 | 15.239530–15.241570 | 15.167042 | 0.073455 | +0.484% | 402,296 | 4.023 | 12,616 | 9.979 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 1,519,430.3 | 15.194303 | 15.193680–15.194900 | 15.167042 | 0.027262 | +0.180% | 402,296 | 4.023 | 125,548 | 6.997 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 1,519,111.3 | 15.191113 | 15.190520–15.191560 | 15.167042 | 0.024072 | +0.159% | 402,296 | 4.023 | 273,272 | 5.999 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 1,521,649.3 | 15.216493 | 15.215990–15.217130 | 15.167042 | 0.049452 | +0.326% | 402,296 | 4.023 | 26,708 | 8.990 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 1,520,209.3 | 15.202093 | 15.201160–15.203120 | 15.167042 | 0.035052 | +0.231% | 402,296 | 4.023 | 57,696 | 7.995 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 1,528,942.7 | 15.289427 | 15.289150–15.289570 | 15.167042 | 0.122385 | +0.807% | 402,296 | 4.023 | 0 | 10.960 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 1,529,125.7 | 15.291257 | 15.290370–15.292780 | 15.167042 | 0.124215 | +0.819% | 402,144 | 4.021 | 0 | 10.956 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 1,528,942.7 | 15.289427 | 15.289150–15.289570 | 15.167042 | 0.122385 | +0.807% | 402,296 | 4.023 | 0 | 10.960 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `random`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 18,561,112 | 18.561112 | 18.560785–18.561350 | 18.488885 | 0.072227 | +0.391% | 4,002,288 | 4.002 | 12,616 | 12.984 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 18,524,270 | 18.524270 | 18.524087–18.524478 | 18.488885 | 0.035385 | +0.191% | 4,002,288 | 4.002 | 125,548 | 9.998 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 18,520,967.7 | 18.520968 | 18.520923–18.521001 | 18.488885 | 0.032083 | +0.174% | 4,002,288 | 4.002 | 273,272 | 8.999 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 18,541,901.3 | 18.541901 | 18.541773–18.542050 | 18.488885 | 0.053017 | +0.287% | 4,002,288 | 4.002 | 26,708 | 11.992 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 18,530,442 | 18.530442 | 18.530303–18.530650 | 18.488885 | 0.041557 | +0.225% | 4,002,288 | 4.002 | 57,696 | 10.996 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 18,599,038.7 | 18.599039 | 18.598521–18.599329 | 18.488885 | 0.110154 | +0.596% | 4,002,288 | 4.002 | 0 | 13.968 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 18,604,336.3 | 18.604336 | 18.604170–18.604436 | 18.488885 | 0.115452 | +0.624% | 4,002,056 | 4.002 | 0 | 13.952 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 18,590,897 | 18.590897 | 18.590682–18.591090 | 18.488885 | 0.102012 | +0.552% | 4,002,288 | 4.002 | 6,204 | 13.968 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 5 | 141,431,207 | 141.4 | 273,272 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 5 | 72,149,089 | 72.149 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 5 | 80,499,382 | 80.499 | 6,204 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `runs1024`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 44,079.3 | 4.407933 | 4.407600–4.408100 | n/a | n/a | n/a | 41,344 | 4.134 | 0 | 3.408 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 44,079.3 | 4.407933 | 4.407600–4.408100 | n/a | n/a | n/a | 41,344 | 4.134 | 0 | 3.408 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 84,111.7 | 8.411167 | 8.410700–8.411600 | n/a | n/a | n/a | 42,304 | 4.230 | 0 | 2.999 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 44,079.3 | 4.407933 | 4.407600–4.408100 | n/a | n/a | n/a | 41,344 | 4.134 | 0 | 3.408 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 44,079.3 | 4.407933 | 4.407600–4.408100 | n/a | n/a | n/a | 41,344 | 4.134 | 0 | 3.408 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 44,079.3 | 4.407933 | 4.407600–4.408100 | n/a | n/a | n/a | 41,344 | 4.134 | 0 | 3.408 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 44,079.3 | 4.407933 | 4.407600–4.408100 | n/a | n/a | n/a | 41,344 | 4.134 | 0 | 3.408 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 44,079.3 | 4.407933 | 4.407600–4.408100 | n/a | n/a | n/a | 41,344 | 4.134 | 0 | 3.408 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `runs1024`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 769,092.7 | 7.690927 | 7.690830–7.691030 | n/a | n/a | n/a | 400,896 | 4.009 | 0 | 6.691 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 769,092.7 | 7.690927 | 7.690830–7.691030 | n/a | n/a | n/a | 400,896 | 4.009 | 0 | 6.691 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 1,289,931 | 12.899310 | 12.899140–12.899450 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 5.999 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 769,092.7 | 7.690927 | 7.690830–7.691030 | n/a | n/a | n/a | 400,896 | 4.009 | 0 | 6.691 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 769,092.7 | 7.690927 | 7.690830–7.691030 | n/a | n/a | n/a | 400,896 | 4.009 | 0 | 6.691 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 769,092.7 | 7.690927 | 7.690830–7.691030 | n/a | n/a | n/a | 400,896 | 4.009 | 0 | 6.691 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 769,092.7 | 7.690927 | 7.690830–7.691030 | n/a | n/a | n/a | 400,896 | 4.009 | 0 | 6.691 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 769,092.7 | 7.690927 | 7.690830–7.691030 | n/a | n/a | n/a | 400,896 | 4.009 | 0 | 6.691 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `runs1024`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 16,740,320 | 16.740320 | 16.740103–16.740537 | n/a | n/a | n/a | 4,002,288 | 4.002 | 273,272 | 8.999 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `runs32`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 114,711 | 11.471100 | 11.468200–11.476000 | n/a | n/a | n/a | 42,304 | 4.230 | 12,616 | 6.987 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 118,254 | 11.825400 | 11.824400–11.827100 | n/a | n/a | n/a | 42,304 | 4.230 | 125,548 | 3.997 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 118,551 | 11.855100 | 11.854400–11.855900 | n/a | n/a | n/a | 42,304 | 4.230 | 0 | 2.999 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 116,745.3 | 11.674533 | 11.670600–11.678200 | n/a | n/a | n/a | 42,304 | 4.230 | 26,708 | 5.987 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 117,739 | 11.773900 | 11.769300–11.778500 | n/a | n/a | n/a | 42,304 | 4.230 | 57,696 | 4.994 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 110,693 | 11.069300 | 11.064500–11.074000 | n/a | n/a | n/a | 42,304 | 4.230 | 0 | 7.944 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 108,678 | 10.867800 | 10.865200–10.872500 | n/a | n/a | n/a | 42,304 | 4.230 | 0 | 7.921 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 110,693 | 11.069300 | 11.064500–11.074000 | n/a | n/a | n/a | 42,304 | 4.230 | 0 | 7.944 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `runs32`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 1,488,017.7 | 14.880177 | 14.879100–14.880800 | n/a | n/a | n/a | 402,296 | 4.023 | 12,616 | 9.980 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 1,516,204 | 15.162040 | 15.161540–15.162930 | n/a | n/a | n/a | 402,296 | 4.023 | 125,548 | 6.997 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 1,518,050.3 | 15.180503 | 15.179410–15.181340 | n/a | n/a | n/a | 402,296 | 4.023 | 273,272 | 5.999 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 1,504,321.7 | 15.043217 | 15.040980–15.045140 | n/a | n/a | n/a | 402,296 | 4.023 | 26,708 | 8.990 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 1,512,328.7 | 15.123287 | 15.120810–15.125440 | n/a | n/a | n/a | 402,296 | 4.023 | 57,696 | 7.995 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 1,456,341 | 14.563410 | 14.562470–14.564500 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 10.956 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 1,456,558.3 | 14.565583 | 14.565540–14.565630 | n/a | n/a | n/a | 402,144 | 4.021 | 0 | 10.952 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 1,456,341 | 14.563410 | 14.562470–14.564500 | n/a | n/a | n/a | 402,296 | 4.023 | 0 | 10.956 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `runs32`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 18,270,198.3 | 18.270198 | 18.269876–18.270413 | n/a | n/a | n/a | 4,002,288 | 4.002 | 12,616 | 12.984 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 18,494,500.3 | 18.494500 | 18.494115–18.494903 | n/a | n/a | n/a | 4,002,288 | 4.002 | 125,548 | 9.998 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 18,507,898.7 | 18.507899 | 18.507745–18.507993 | n/a | n/a | n/a | 4,002,288 | 4.002 | 273,272 | 8.999 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 18,399,825.7 | 18.399826 | 18.399603–18.400249 | n/a | n/a | n/a | 4,002,288 | 4.002 | 26,708 | 11.992 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 18,463,975 | 18.463975 | 18.463810–18.464203 | n/a | n/a | n/a | 4,002,288 | 4.002 | 57,696 | 10.996 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 18,019,755.3 | 18.019755 | 18.019363–18.020256 | n/a | n/a | n/a | 4,002,288 | 4.002 | 0 | 13.967 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 18,014,450 | 18.014450 | 18.013610–18.015068 | n/a | n/a | n/a | 4,002,056 | 4.002 | 0 | 13.952 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 18,005,488 | 18.005488 | 18.005016–18.006020 | n/a | n/a | n/a | 4,002,288 | 4.002 | 6,204 | 13.967 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `saw13`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 73,101 | 7.310100 | 7.310100–7.310100 | n/a | n/a | n/a | 39,224 | 3.922 | 12,616 | 6.538 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 83,122 | 8.312200 | 8.312200–8.312200 | n/a | n/a | n/a | 39,224 | 3.922 | 125,548 | 3.692 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 90,677 | 9.067700 | 9.067700–9.067700 | n/a | n/a | n/a | 39,224 | 3.922 | 273,272 | 2.769 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 73,690 | 7.369000 | 7.369000–7.369000 | n/a | n/a | n/a | 39,224 | 3.922 | 26,708 | 5.538 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 77,261 | 7.726100 | 7.726100–7.726100 | n/a | n/a | n/a | 39,224 | 3.922 | 57,696 | 4.615 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 72,523 | 7.252300 | 7.252300–7.252300 | n/a | n/a | n/a | 39,224 | 3.922 | 0 | 7.385 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 73,156 | 7.315600 | 7.315600–7.315600 | n/a | n/a | n/a | 39,224 | 3.922 | 0 | 7.361 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 72,523 | 7.252300 | 7.252300–7.252300 | n/a | n/a | n/a | 39,224 | 3.922 | 0 | 7.385 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `saw13`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 727,368 | 7.273680 | 7.273680–7.273680 | n/a | n/a | n/a | 371,528 | 3.715 | 12,616 | 9.231 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 857,841 | 8.578410 | 8.578410–8.578410 | n/a | n/a | n/a | 371,528 | 3.715 | 125,548 | 6.462 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 937,939 | 9.379390 | 9.379390–9.379390 | n/a | n/a | n/a | 371,528 | 3.715 | 273,272 | 5.538 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 742,977 | 7.429770 | 7.429770–7.429770 | n/a | n/a | n/a | 371,528 | 3.715 | 26,708 | 8.308 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 790,592 | 7.905920 | 7.905920–7.905920 | n/a | n/a | n/a | 371,528 | 3.715 | 57,696 | 7.385 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 730,997 | 7.309970 | 7.309970–7.309970 | n/a | n/a | n/a | 371,528 | 3.715 | 0 | 10.154 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 731,895 | 7.318950 | 7.318950–7.318950 | n/a | n/a | n/a | 371,384 | 3.714 | 0 | 10.151 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 730,997 | 7.309970 | 7.309970–7.309970 | n/a | n/a | n/a | 371,528 | 3.715 | 0 | 10.154 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `saw13`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 7,496,309 | 7.496309 | 7.496309–7.496309 | n/a | n/a | n/a | 3,694,608 | 3.695 | 12,616 | 12.000 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 8,872,956 | 8.872956 | 8.872956–8.872956 | n/a | n/a | n/a | 3,694,608 | 3.695 | 125,548 | 9.231 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 9,683,743 | 9.683743 | 9.683743–9.683743 | n/a | n/a | n/a | 3,694,608 | 3.695 | 273,272 | 8.308 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 7,698,601 | 7.698601 | 7.698601–7.698601 | n/a | n/a | n/a | 3,694,608 | 3.695 | 26,708 | 11.077 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 8,186,228 | 8.186228 | 8.186228–8.186228 | n/a | n/a | n/a | 3,694,608 | 3.695 | 57,696 | 10.154 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 7,508,402 | 7.508402 | 7.508402–7.508402 | n/a | n/a | n/a | 3,694,608 | 3.695 | 0 | 12.923 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 7,511,232 | 7.511232 | 7.511232–7.511232 | n/a | n/a | n/a | 3,694,384 | 3.694 | 0 | 12.909 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 7,486,930 | 7.486930 | 7.486930–7.486930 | n/a | n/a | n/a | 3,694,608 | 3.695 | 6,204 | 12.923 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `tail10`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 25,939 | 2.593900 | 2.524300–2.676400 | n/a | n/a | n/a | 9,568 | 0.957 | 12,616 | 1.372 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 25,814 | 2.581400 | 2.510400–2.664900 | n/a | n/a | n/a | 9,568 | 0.957 | 125,548 | 1.088 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 25,592.7 | 2.559267 | 2.491500–2.622700 | n/a | n/a | n/a | 9,568 | 0.957 | 248,428 | 0.988 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 25,879 | 2.587900 | 2.517100–2.672200 | n/a | n/a | n/a | 9,568 | 0.957 | 26,708 | 1.272 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 25,945.7 | 2.594567 | 2.525500–2.677900 | n/a | n/a | n/a | 9,568 | 0.957 | 57,696 | 1.188 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 25,993.3 | 2.599333 | 2.530900–2.682500 | n/a | n/a | n/a | 9,568 | 0.957 | 0 | 1.467 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 26,482 | 2.648200 | 2.589700–2.683500 | n/a | n/a | n/a | 9,568 | 0.957 | 0 | 1.463 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 25,993.3 | 2.599333 | 2.530900–2.682500 | n/a | n/a | n/a | 9,568 | 0.957 | 0 | 1.467 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `tail10`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 305,298.7 | 3.052987 | 3.039390–3.059980 | n/a | n/a | n/a | 78,920 | 0.789 | 12,616 | 1.677 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 304,379 | 3.043790 | 3.030770–3.050670 | n/a | n/a | n/a | 78,920 | 0.789 | 125,548 | 1.376 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 303,491.3 | 3.034913 | 3.023710–3.043440 | n/a | n/a | n/a | 78,920 | 0.789 | 273,272 | 1.276 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 305,125.3 | 3.051253 | 3.037550–3.058150 | n/a | n/a | n/a | 78,920 | 0.789 | 26,708 | 1.579 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 304,493.7 | 3.044937 | 3.031720–3.051910 | n/a | n/a | n/a | 78,920 | 0.789 | 57,696 | 1.475 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 305,640 | 3.056400 | 3.042190–3.063900 | n/a | n/a | n/a | 78,920 | 0.789 | 0 | 1.774 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 305,707.3 | 3.057073 | 3.042490–3.065030 | n/a | n/a | n/a | 78,920 | 0.789 | 0 | 1.773 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 305,640 | 3.056400 | 3.042190–3.063900 | n/a | n/a | n/a | 78,920 | 0.789 | 0 | 1.774 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |

## `tail10`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 3,428,006 | 3.428006 | 3.422537–3.432001 | n/a | n/a | n/a | 730,864 | 0.731 | 12,616 | 1.975 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto1024` | 3 | 3,426,970.7 | 3.426971 | 3.426053–3.428645 | n/a | n/a | n/a | 730,864 | 0.731 | 125,548 | 1.678 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto2048` | 3 | 3,427,145.7 | 3.427146 | 3.426161–3.428831 | n/a | n/a | n/a | 730,864 | 0.731 | 273,272 | 1.579 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto256` | 3 | 3,425,584.3 | 3.425584 | 3.420104–3.429665 | n/a | n/a | n/a | 730,864 | 0.731 | 26,708 | 1.876 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `hybrid_fjauto512` | 3 | 3,424,401 | 3.424401 | 3.419028–3.428370 | n/a | n/a | n/a | 730,864 | 0.731 | 57,696 | 1.776 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort` | 3 | 3,431,823.7 | 3.431824 | 3.426400–3.435704 | n/a | n/a | n/a | 730,864 | 0.731 | 0 | 2.074 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fixed` | 3 | 3,432,113.3 | 3.432113 | 3.426519–3.436129 | n/a | n/a | n/a | 730,864 | 0.731 | 0 | 2.072 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
| `powersort_fj` | 3 | 3,430,945.7 | 3.430946 | 3.425458–3.434727 | n/a | n/a | n/a | 730,864 | 0.731 | 6,204 | 2.074 | sm=96, fj-thresh=0, fj-max=2048, build=`d310ed5` |
