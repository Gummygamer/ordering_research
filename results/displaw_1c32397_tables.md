# 1c32397 displacement-response aggregates

Aggregated 264 validated rows from 1 CSV file(s). Each row below is grouped by algorithm, distribution, n, and mode. Comparison and merge-span metrics are arithmetic means, timing metrics are medians, and memory bounds/peaks are maxima.

Build IDs: `1c32397`.

For random permutations, comparison excess is `100 * (mean comparisons - lg(n!)) / lg(n!)`; it is reported as `n/a` for other distributions. Timing metrics use only `time` rows, while comparison, heap, and merge metrics use only `count` rows.

## `disp1024`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 11,294,963 | 11.294963 | 11.294062–11.295822 | n/a | n/a | n/a | 31,608 | 0.032 | 12,616 | 6.379 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto1024` | 3 | 11,260,329.7 | 11.260330 | 11.259407–11.260980 | n/a | n/a | n/a | 31,608 | 0.032 | 125,548 | 3.405 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto2048` | 3 | 11,247,388.3 | 11.247388 | 11.244790–11.249992 | n/a | n/a | n/a | 31,608 | 0.032 | 273,272 | 2.420 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto256` | 3 | 11,278,980 | 11.278980 | 11.278645–11.279509 | n/a | n/a | n/a | 31,608 | 0.032 | 26,708 | 5.390 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto512` | 3 | 11,268,838.7 | 11.268839 | 11.267509–11.269595 | n/a | n/a | n/a | 31,608 | 0.032 | 57,696 | 4.398 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort` | 3 | 11,340,100.7 | 11.340101 | 11.339790–11.340419 | n/a | n/a | n/a | 31,608 | 0.032 | 0 | 7.361 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fixed` | 3 | 11,344,236.3 | 11.344236 | 11.342457–11.345390 | n/a | n/a | n/a | 31,616 | 0.032 | 0 | 7.344 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fj` | 3 | 11,321,516.7 | 11.321517 | 11.321148–11.321993 | n/a | n/a | n/a | 31,608 | 0.032 | 6,204 | 7.361 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |

## `disp128`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 8,364,292 | 8.364292 | 8.361331–8.370173 | n/a | n/a | n/a | 6,144 | 0.006 | 12,616 | 2.940 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto1024` | 3 | 8,954,493 | 8.954493 | 8.953504–8.956372 | n/a | n/a | n/a | 6,144 | 0.006 | 125,548 | 0.584 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto2048` | 3 | 9,665,806.7 | 9.665807 | 9.665202–9.666381 | n/a | n/a | n/a | 6,144 | 0.006 | 273,272 | 0.291 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto256` | 3 | 8,372,504.3 | 8.372504 | 8.369305–8.378514 | n/a | n/a | n/a | 6,144 | 0.006 | 26,708 | 2.002 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto512` | 3 | 8,479,858.7 | 8.479859 | 8.477130–8.481828 | n/a | n/a | n/a | 6,144 | 0.006 | 57,696 | 1.155 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort` | 3 | 8,399,428.3 | 8.399428 | 8.395974–8.405587 | n/a | n/a | n/a | 6,144 | 0.006 | 0 | 3.895 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fixed` | 3 | 8,399,817 | 8.399817 | 8.397897–8.402547 | n/a | n/a | n/a | 6,000 | 0.006 | 0 | 3.878 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fj` | 3 | 8,383,432.7 | 8.383433 | 8.379691–8.389587 | n/a | n/a | n/a | 6,144 | 0.006 | 6,204 | 3.895 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |

## `disp16`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 5,991,601.3 | 5.991601 | 5.990740–5.992808 | n/a | n/a | n/a | 2,720 | 0.003 | 12,616 | 0.379 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto1024` | 3 | 8,360,151.3 | 8.360151 | 8.359885–8.360310 | n/a | n/a | n/a | 2,720 | 0.003 | 125,548 | 0.047 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto2048` | 3 | 9,293,116.7 | 9.293117 | 9.292991–9.293258 | n/a | n/a | n/a | 2,720 | 0.003 | 273,272 | 0.024 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto256` | 3 | 6,669,163.3 | 6.669163 | 6.668447–6.669701 | n/a | n/a | n/a | 2,720 | 0.003 | 26,708 | 0.189 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto512` | 3 | 7,474,855.7 | 7.474856 | 7.474400–7.475758 | n/a | n/a | n/a | 2,720 | 0.003 | 57,696 | 0.094 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort` | 3 | 5,542,747.3 | 5.542747 | 5.542062–5.543751 | n/a | n/a | n/a | 2,720 | 0.003 | 0 | 0.755 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fixed` | 3 | 5,549,488 | 5.549488 | 5.549026–5.549747 | n/a | n/a | n/a | 2,680 | 0.003 | 0 | 0.742 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fj` | 3 | 5,529,320 | 5.529320 | 5.528595–5.530134 | n/a | n/a | n/a | 2,720 | 0.003 | 6,204 | 0.755 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |

## `disp2048`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 12,286,437 | 12.286437 | 12.285614–12.287199 | n/a | n/a | n/a | 63,992 | 0.064 | 12,616 | 7.493 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto1024` | 3 | 12,254,778.7 | 12.254779 | 12.253441–12.255629 | n/a | n/a | n/a | 63,992 | 0.064 | 125,548 | 4.512 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto2048` | 3 | 12,246,512.3 | 12.246512 | 12.244750–12.247401 | n/a | n/a | n/a | 63,992 | 0.064 | 273,272 | 3.516 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto256` | 3 | 12,270,237 | 12.270237 | 12.269976–12.270736 | n/a | n/a | n/a | 63,992 | 0.064 | 26,708 | 6.502 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto512` | 3 | 12,260,696 | 12.260696 | 12.259714–12.261656 | n/a | n/a | n/a | 63,992 | 0.064 | 57,696 | 5.508 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort` | 3 | 12,331,746.3 | 12.331746 | 12.330939–12.332340 | n/a | n/a | n/a | 63,992 | 0.064 | 0 | 8.475 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fixed` | 3 | 12,338,518.7 | 12.338519 | 12.337821–12.339105 | n/a | n/a | n/a | 64,072 | 0.064 | 0 | 8.461 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fj` | 3 | 12,312,385.3 | 12.312385 | 12.312081–12.312960 | n/a | n/a | n/a | 63,992 | 0.064 | 6,204 | 8.475 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |

## `disp256`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 9,327,773.3 | 9.327773 | 9.325107–9.331700 | n/a | n/a | n/a | 9,488 | 0.009 | 12,616 | 4.101 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto1024` | 3 | 9,442,519.3 | 9.442519 | 9.441146–9.444117 | n/a | n/a | n/a | 9,488 | 0.009 | 125,548 | 1.272 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto2048` | 3 | 9,939,023.3 | 9.939023 | 9.937389–9.941103 | n/a | n/a | n/a | 9,488 | 0.009 | 273,272 | 0.644 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto256` | 3 | 9,314,259.3 | 9.314259 | 9.311620–9.318376 | n/a | n/a | n/a | 9,488 | 0.009 | 26,708 | 3.126 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto512` | 3 | 9,309,266.7 | 9.309267 | 9.308270–9.310749 | n/a | n/a | n/a | 9,488 | 0.009 | 57,696 | 2.165 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort` | 3 | 9,370,218.3 | 9.370218 | 9.367250–9.374316 | n/a | n/a | n/a | 9,488 | 0.009 | 0 | 5.073 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fixed` | 3 | 9,373,970 | 9.373970 | 9.369845–9.376383 | n/a | n/a | n/a | 9,672 | 0.010 | 0 | 5.054 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fj` | 3 | 9,352,622.3 | 9.352622 | 9.350002–9.356331 | n/a | n/a | n/a | 9,488 | 0.009 | 6,204 | 5.073 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |

## `disp32`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 6,496,087.7 | 6.496088 | 6.495155–6.496758 | n/a | n/a | n/a | 3,120 | 0.003 | 12,616 | 0.894 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto1024` | 3 | 8,484,706 | 8.484706 | 8.484148–8.485595 | n/a | n/a | n/a | 3,040 | 0.003 | 125,548 | 0.113 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto2048` | 3 | 9,383,306.7 | 9.383307 | 9.382562–9.383827 | n/a | n/a | n/a | 3,024 | 0.003 | 273,272 | 0.056 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto256` | 3 | 6,964,770.7 | 6.964771 | 6.963623–6.965597 | n/a | n/a | n/a | 3,120 | 0.003 | 26,708 | 0.448 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto512` | 3 | 7,660,741 | 7.660741 | 7.660382–7.661234 | n/a | n/a | n/a | 3,088 | 0.003 | 57,696 | 0.225 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort` | 3 | 6,338,686.3 | 6.338686 | 6.335074–6.341058 | n/a | n/a | n/a | 3,120 | 0.003 | 0 | 1.614 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fixed` | 3 | 6,338,881.3 | 6.338881 | 6.337285–6.340199 | n/a | n/a | n/a | 3,152 | 0.003 | 0 | 1.596 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fj` | 3 | 6,326,086.7 | 6.326087 | 6.322809–6.328055 | n/a | n/a | n/a | 3,120 | 0.003 | 6,204 | 1.614 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |

## `disp4`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 5,538,927.3 | 5.538927 | 5.538531–5.539584 | n/a | n/a | n/a | 2,392 | 0.002 | 12,616 | 0.058 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto1024` | 3 | 8,137,363.7 | 8.137364 | 8.136996–8.137890 | n/a | n/a | n/a | 2,392 | 0.002 | 125,548 | 0.007 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto2048` | 3 | 9,092,355.3 | 9.092355 | 9.091822–9.092664 | n/a | n/a | n/a | 2,392 | 0.002 | 273,272 | 0.004 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto256` | 3 | 6,339,047 | 6.339047 | 6.338489–6.340041 | n/a | n/a | n/a | 2,392 | 0.002 | 26,708 | 0.029 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto512` | 3 | 7,213,236.7 | 7.213237 | 7.212368–7.214137 | n/a | n/a | n/a | 2,392 | 0.002 | 57,696 | 0.014 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort` | 3 | 4,873,028.3 | 4.873028 | 4.872386–4.873875 | n/a | n/a | n/a | 2,400 | 0.002 | 0 | 0.116 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fixed` | 3 | 4,885,962.7 | 4.885963 | 4.884333–4.887129 | n/a | n/a | n/a | 2,400 | 0.002 | 0 | 0.115 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fj` | 3 | 4,844,968.7 | 4.844969 | 4.844342–4.845913 | n/a | n/a | n/a | 2,400 | 0.002 | 6,204 | 0.116 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |

## `disp4096`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 13,281,473 | 13.281473 | 13.275839–13.286648 | n/a | n/a | n/a | 119,008 | 0.119 | 12,616 | 8.577 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto1024` | 3 | 13,250,937.7 | 13.250938 | 13.245277–13.256637 | n/a | n/a | n/a | 119,008 | 0.119 | 125,548 | 5.594 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto2048` | 3 | 13,247,477.3 | 13.247477 | 13.241148–13.252836 | n/a | n/a | n/a | 119,008 | 0.119 | 273,272 | 4.596 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto256` | 3 | 13,265,580.7 | 13.265581 | 13.259935–13.270704 | n/a | n/a | n/a | 119,008 | 0.119 | 26,708 | 7.586 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto512` | 3 | 13,256,365.3 | 13.256365 | 13.250494–13.261917 | n/a | n/a | n/a | 119,008 | 0.119 | 57,696 | 6.591 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort` | 3 | 13,326,427.3 | 13.326427 | 13.321090–13.331569 | n/a | n/a | n/a | 119,008 | 0.119 | 0 | 9.561 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fixed` | 3 | 13,333,409 | 13.333409 | 13.328264–13.338833 | n/a | n/a | n/a | 118,944 | 0.119 | 0 | 9.543 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fj` | 3 | 13,307,527.7 | 13.307528 | 13.302333–13.312306 | n/a | n/a | n/a | 119,008 | 0.119 | 6,204 | 9.561 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |

## `disp512`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 10,308,741 | 10.308741 | 10.307437–10.310151 | n/a | n/a | n/a | 16,864 | 0.017 | 12,616 | 5.252 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto1024` | 3 | 10,269,217 | 10.269217 | 10.268122–10.269851 | n/a | n/a | n/a | 16,864 | 0.017 | 125,548 | 2.304 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto2048` | 3 | 10,420,161.7 | 10.420162 | 10.418896–10.421104 | n/a | n/a | n/a | 16,864 | 0.017 | 273,272 | 1.380 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto256` | 3 | 10,293,045.7 | 10.293046 | 10.291582–10.294065 | n/a | n/a | n/a | 16,864 | 0.017 | 26,708 | 4.266 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto512` | 3 | 10,282,781 | 10.282781 | 10.281234–10.284741 | n/a | n/a | n/a | 16,864 | 0.017 | 57,696 | 3.280 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort` | 3 | 10,353,212.3 | 10.353212 | 10.352143–10.354725 | n/a | n/a | n/a | 16,864 | 0.017 | 0 | 6.230 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fixed` | 3 | 10,357,680 | 10.357680 | 10.355750–10.359587 | n/a | n/a | n/a | 16,800 | 0.017 | 0 | 6.215 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fj` | 3 | 10,335,017.3 | 10.335017 | 10.333858–10.336380 | n/a | n/a | n/a | 16,864 | 0.017 | 6,204 | 6.230 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |

## `disp64`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 7,377,995 | 7.377995 | 7.375348–7.381136 | n/a | n/a | n/a | 4,016 | 0.004 | 12,616 | 1.820 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto1024` | 3 | 8,673,197.7 | 8.673198 | 8.670995–8.674496 | n/a | n/a | n/a | 3,888 | 0.004 | 125,548 | 0.259 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto2048` | 3 | 9,501,471.3 | 9.501471 | 9.500675–9.502175 | n/a | n/a | n/a | 3,888 | 0.004 | 273,272 | 0.130 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto256` | 3 | 7,528,972.7 | 7.528973 | 7.528381–7.529413 | n/a | n/a | n/a | 4,016 | 0.004 | 26,708 | 1.029 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto512` | 3 | 7,980,170.3 | 7.980170 | 7.978639–7.981155 | n/a | n/a | n/a | 4,016 | 0.004 | 57,696 | 0.519 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort` | 3 | 7,376,971.7 | 7.376972 | 7.374036–7.378995 | n/a | n/a | n/a | 4,016 | 0.004 | 0 | 2.720 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fixed` | 3 | 7,377,973.3 | 7.377973 | 7.375157–7.379501 | n/a | n/a | n/a | 4,096 | 0.004 | 0 | 2.702 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fj` | 3 | 7,362,997.3 | 7.362997 | 7.360305–7.365137 | n/a | n/a | n/a | 4,016 | 0.004 | 6,204 | 2.720 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |

## `disp8`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto` | 3 | 5,722,832.7 | 5.722833 | 5.722210–5.723237 | n/a | n/a | n/a | 2,480 | 0.002 | 12,616 | 0.153 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto1024` | 3 | 8,253,451.3 | 8.253451 | 8.253007–8.253959 | n/a | n/a | n/a | 2,480 | 0.002 | 125,548 | 0.019 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto2048` | 3 | 9,201,720 | 9.201720 | 9.201264–9.202019 | n/a | n/a | n/a | 2,480 | 0.002 | 273,272 | 0.010 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto256` | 3 | 6,487,106 | 6.487106 | 6.486756–6.487642 | n/a | n/a | n/a | 2,480 | 0.002 | 26,708 | 0.077 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `hybrid_fjauto512` | 3 | 7,341,285.3 | 7.341285 | 7.340841–7.341777 | n/a | n/a | n/a | 2,480 | 0.002 | 57,696 | 0.038 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort` | 3 | 5,109,352.7 | 5.109353 | 5.109186–5.109669 | n/a | n/a | n/a | 2,488 | 0.002 | 0 | 0.306 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fixed` | 3 | 5,121,965 | 5.121965 | 5.121808–5.122134 | n/a | n/a | n/a | 2,488 | 0.002 | 0 | 0.300 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
| `powersort_fj` | 3 | 5,090,328 | 5.090328 | 5.090032–5.090517 | n/a | n/a | n/a | 2,488 | 0.002 | 6,204 | 0.306 | sm=96, fj-thresh=0, fj-max=2048, build=`1c32397` |
