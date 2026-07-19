# K=112 duplicate-veto evaluation (97869f3)

Aggregated 492 validated rows from 2 CSV file(s). Each row below is grouped by algorithm, distribution, n, and mode. Comparison and merge-span metrics are arithmetic means, timing metrics are medians, and memory bounds/peaks are maxima.

Build IDs: `97869f3`.

For random permutations, comparison excess is `100 * (mean comparisons - lg(n!)) / lg(n!)`; it is reported as `n/a` for other distributions. Timing metrics use only `time` rows, while comparison, heap, and merge metrics use only `count` rows.

## `disp1024`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 11,247,388.3 | 11.247388 | 11.244790–11.249992 | n/a | n/a | n/a | 31,608 | 0.032 | 273,272 | 2.420 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 11,253,250.7 | 11.253251 | 11.250637–11.255857 | n/a | n/a | n/a | 31,608 | 0.032 | 273,272 | 2.420 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 11,340,100.7 | 11.340101 | 11.339790–11.340419 | n/a | n/a | n/a | 31,608 | 0.032 | 0 | 7.361 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 11,321,516.7 | 11.321517 | 11.321148–11.321993 | n/a | n/a | n/a | 31,608 | 0.032 | 6,204 | 7.361 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `disp128`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,665,806.7 | 9.665807 | 9.665202–9.666381 | n/a | n/a | n/a | 6,144 | 0.006 | 273,272 | 0.291 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 8,387,659 | 8.387659 | 8.383616–8.393479 | n/a | n/a | n/a | 6,144 | 0.006 | 6,204 | 3.895 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 8,399,428.3 | 8.399428 | 8.395974–8.405587 | n/a | n/a | n/a | 6,144 | 0.006 | 0 | 3.895 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 8,383,432.7 | 8.383433 | 8.379691–8.389587 | n/a | n/a | n/a | 6,144 | 0.006 | 6,204 | 3.895 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `disp16`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,293,116.7 | 9.293117 | 9.292991–9.293258 | n/a | n/a | n/a | 2,720 | 0.003 | 273,272 | 0.024 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 5,533,259.7 | 5.533260 | 5.532544–5.534068 | n/a | n/a | n/a | 2,720 | 0.003 | 6,204 | 0.755 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 5,542,747.3 | 5.542747 | 5.542062–5.543751 | n/a | n/a | n/a | 2,720 | 0.003 | 0 | 0.755 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 5,529,320 | 5.529320 | 5.528595–5.530134 | n/a | n/a | n/a | 2,720 | 0.003 | 6,204 | 0.755 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `disp2048`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 12,246,512.3 | 12.246512 | 12.244750–12.247401 | n/a | n/a | n/a | 63,992 | 0.064 | 273,272 | 3.516 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 12,252,379.7 | 12.252380 | 12.250622–12.253274 | n/a | n/a | n/a | 63,992 | 0.064 | 273,272 | 3.516 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 12,331,746.3 | 12.331746 | 12.330939–12.332340 | n/a | n/a | n/a | 63,992 | 0.064 | 0 | 8.475 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 12,312,385.3 | 12.312385 | 12.312081–12.312960 | n/a | n/a | n/a | 63,992 | 0.064 | 6,204 | 8.475 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `disp256`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,939,023.3 | 9.939023 | 9.937389–9.941103 | n/a | n/a | n/a | 9,488 | 0.009 | 273,272 | 0.644 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 9,357,517 | 9.357517 | 9.354899–9.361216 | n/a | n/a | n/a | 9,488 | 0.009 | 6,204 | 5.073 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 9,370,218.3 | 9.370218 | 9.367250–9.374316 | n/a | n/a | n/a | 9,488 | 0.009 | 0 | 5.073 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 9,352,622.3 | 9.352622 | 9.350002–9.356331 | n/a | n/a | n/a | 9,488 | 0.009 | 6,204 | 5.073 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `disp32`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,383,306.7 | 9.383307 | 9.382562–9.383827 | n/a | n/a | n/a | 3,024 | 0.003 | 273,272 | 0.056 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 6,330,010 | 6.330010 | 6.326729–6.331967 | n/a | n/a | n/a | 3,120 | 0.003 | 6,204 | 1.614 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 6,338,686.3 | 6.338686 | 6.335074–6.341058 | n/a | n/a | n/a | 3,120 | 0.003 | 0 | 1.614 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 6,326,086.7 | 6.326087 | 6.322809–6.328055 | n/a | n/a | n/a | 3,120 | 0.003 | 6,204 | 1.614 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `disp4`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,092,355.3 | 9.092355 | 9.091822–9.092664 | n/a | n/a | n/a | 2,392 | 0.002 | 273,272 | 0.004 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 4,849,018.7 | 4.849019 | 4.848417–4.849926 | n/a | n/a | n/a | 2,400 | 0.002 | 6,204 | 0.116 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 4,873,028.3 | 4.873028 | 4.872386–4.873875 | n/a | n/a | n/a | 2,400 | 0.002 | 0 | 0.116 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 4,844,968.7 | 4.844969 | 4.844342–4.845913 | n/a | n/a | n/a | 2,400 | 0.002 | 6,204 | 0.116 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `disp4096`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 13,247,477.3 | 13.247477 | 13.241148–13.252836 | n/a | n/a | n/a | 119,008 | 0.119 | 273,272 | 4.596 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 13,253,325 | 13.253325 | 13.247003–13.258682 | n/a | n/a | n/a | 119,008 | 0.119 | 273,272 | 4.596 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 13,326,427.3 | 13.326427 | 13.321090–13.331569 | n/a | n/a | n/a | 119,008 | 0.119 | 0 | 9.561 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 13,307,527.7 | 13.307528 | 13.302333–13.312306 | n/a | n/a | n/a | 119,008 | 0.119 | 6,204 | 9.561 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `disp512`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 10,420,161.7 | 10.420162 | 10.418896–10.421104 | n/a | n/a | n/a | 16,864 | 0.017 | 273,272 | 1.380 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 10,340,868.3 | 10.340868 | 10.339731–10.342215 | n/a | n/a | n/a | 16,864 | 0.017 | 6,204 | 6.230 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 10,353,212.3 | 10.353212 | 10.352143–10.354725 | n/a | n/a | n/a | 16,864 | 0.017 | 0 | 6.230 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 10,335,017.3 | 10.335017 | 10.333858–10.336380 | n/a | n/a | n/a | 16,864 | 0.017 | 6,204 | 6.230 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `disp64`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,501,471.3 | 9.501471 | 9.500675–9.502175 | n/a | n/a | n/a | 3,888 | 0.004 | 273,272 | 0.130 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 7,366,908 | 7.366908 | 7.364202–7.369030 | n/a | n/a | n/a | 4,016 | 0.004 | 6,204 | 2.720 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 7,376,971.7 | 7.376972 | 7.374036–7.378995 | n/a | n/a | n/a | 4,016 | 0.004 | 0 | 2.720 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 7,362,997.3 | 7.362997 | 7.360305–7.365137 | n/a | n/a | n/a | 4,016 | 0.004 | 6,204 | 2.720 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `disp8`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,201,720 | 9.201720 | 9.201264–9.202019 | n/a | n/a | n/a | 2,480 | 0.002 | 273,272 | 0.010 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 5,094,291.3 | 5.094291 | 5.093997–5.094466 | n/a | n/a | n/a | 2,488 | 0.002 | 6,204 | 0.306 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 5,109,352.7 | 5.109353 | 5.109186–5.109669 | n/a | n/a | n/a | 2,488 | 0.002 | 0 | 0.306 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 5,090,328 | 5.090328 | 5.090032–5.090517 | n/a | n/a | n/a | 2,488 | 0.002 | 6,204 | 0.306 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `dup1024`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 13,828,564.3 | 13.828564 | 13.826721–13.831328 | n/a | n/a | n/a | 3,998,256 | 3.998 | 273,272 | 8.991 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 13,834,438.3 | 13.834438 | 13.832604–13.837203 | n/a | n/a | n/a | 3,998,256 | 3.998 | 273,272 | 8.991 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 13,920,771.3 | 13.920771 | 13.917345–13.925744 | n/a | n/a | n/a | 3,998,256 | 3.998 | 0 | 13.957 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 13,900,906 | 13.900906 | 13.897241–13.905703 | n/a | n/a | n/a | 3,998,256 | 3.998 | 6,204 | 13.957 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `dup12`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,591,839 | 9.591839 | 9.591421–9.592350 | n/a | n/a | n/a | 3,668,760 | 3.669 | 273,272 | 8.250 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 7,358,397.3 | 7.358397 | 7.357133–7.359731 | n/a | n/a | n/a | 3,668,760 | 3.669 | 6,204 | 12.833 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 7,384,690.3 | 7.384690 | 7.384132–7.385806 | n/a | n/a | n/a | 3,668,760 | 3.669 | 0 | 12.833 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 7,355,389 | 7.355389 | 7.354084–7.356747 | n/a | n/a | n/a | 3,668,760 | 3.669 | 6,204 | 12.833 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `dup128`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 10,887,519.7 | 10.887520 | 10.886885–10.887949 | n/a | n/a | n/a | 3,971,760 | 3.972 | 273,272 | 8.929 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 10,902,732.3 | 10.902732 | 10.892773–10.921846 | n/a | n/a | n/a | 3,971,760 | 3.972 | 273,272 | 10.577 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 10,940,762 | 10.940762 | 10.938861–10.942941 | n/a | n/a | n/a | 3,971,760 | 3.972 | 0 | 13.872 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 10,920,419 | 10.920419 | 10.918923–10.922320 | n/a | n/a | n/a | 3,971,760 | 3.972 | 6,204 | 13.872 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `dup16`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 6 | 9,672,501 | 9.672501 | 9.672090–9.673219 | n/a | n/a | n/a | 3,753,080 | 3.753 | 273,272 | 8.437 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 6 | 7,814,902.3 | 7.814902 | 7.814212–7.815884 | n/a | n/a | n/a | 3,753,080 | 3.753 | 6,204 | 13.124 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 6 | 7,838,964.2 | 7.838964 | 7.838175–7.840819 | n/a | n/a | n/a | 3,753,080 | 3.753 | 0 | 13.124 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 6 | 7,811,905.5 | 7.811905 | 7.811209–7.812874 | n/a | n/a | n/a | 3,753,080 | 3.753 | 6,204 | 13.124 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `dup192`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 11,378,063 | 11.378063 | 11.377798–11.378270 | n/a | n/a | n/a | 3,981,248 | 3.981 | 273,272 | 8.953 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 11,383,925 | 11.383925 | 11.383657–11.384146 | n/a | n/a | n/a | 3,981,248 | 3.981 | 273,272 | 8.953 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 11,487,371.7 | 11.487372 | 11.484350–11.491847 | n/a | n/a | n/a | 3,981,248 | 3.981 | 0 | 13.905 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 11,467,519.3 | 11.467519 | 11.464591–11.472093 | n/a | n/a | n/a | 3,981,248 | 3.981 | 6,204 | 13.905 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `dup2`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 8,984,977 | 8.984977 | 8.983839–8.986341 | n/a | n/a | n/a | 2,002,176 | 2.002 | 273,272 | 4.501 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 4,982,146 | 4.982146 | 4.981828–4.982372 | n/a | n/a | n/a | 2,002,176 | 2.002 | 6,204 | 7.001 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 5,033,356.7 | 5.033357 | 5.033056–5.033551 | n/a | n/a | n/a | 2,002,176 | 2.002 | 0 | 7.001 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 4,978,718.3 | 4.978718 | 4.978388–4.978949 | n/a | n/a | n/a | 2,002,176 | 2.002 | 6,204 | 7.001 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `dup24`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,829,841.3 | 9.829841 | 9.829549–9.830190 | n/a | n/a | n/a | 3,835,872 | 3.836 | 273,272 | 8.625 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 8,433,245 | 8.433245 | 8.430454–8.436468 | n/a | n/a | n/a | 3,835,872 | 3.836 | 6,204 | 13.414 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 8,454,964 | 8.454964 | 8.452646–8.457699 | n/a | n/a | n/a | 3,835,872 | 3.836 | 0 | 13.414 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 8,430,267 | 8.430267 | 8.427490–8.433502 | n/a | n/a | n/a | 3,835,872 | 3.836 | 6,204 | 13.414 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `dup256`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 6 | 11,781,212.7 | 11.781213 | 11.777041–11.783560 | n/a | n/a | n/a | 3,987,008 | 3.987 | 273,272 | 8.965 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 6 | 11,787,078.5 | 11.787078 | 11.782889–11.789415 | n/a | n/a | n/a | 3,987,008 | 3.987 | 273,272 | 8.965 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 6 | 11,942,603.3 | 11.942603 | 11.938097–11.946147 | n/a | n/a | n/a | 3,987,008 | 3.987 | 0 | 13.921 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 6 | 11,922,302 | 11.922302 | 11.918160–11.926044 | n/a | n/a | n/a | 3,987,008 | 3.987 | 6,204 | 13.921 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `dup32`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,931,321.3 | 9.931321 | 9.930874–9.931554 | n/a | n/a | n/a | 3,878,616 | 3.879 | 273,272 | 8.718 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 8,877,723.7 | 8.877724 | 8.875877–8.880806 | n/a | n/a | n/a | 3,878,616 | 3.879 | 6,204 | 13.556 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 8,898,757.7 | 8.898758 | 8.896846–8.901982 | n/a | n/a | n/a | 3,878,616 | 3.879 | 0 | 13.556 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 8,874,763 | 8.874763 | 8.872900–8.877853 | n/a | n/a | n/a | 3,878,616 | 3.879 | 6,204 | 13.556 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `dup384`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 12,390,295.3 | 12.390295 | 12.388402–12.391576 | n/a | n/a | n/a | 3,991,856 | 3.992 | 273,272 | 8.976 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 12,396,126.7 | 12.396127 | 12.394213–12.397460 | n/a | n/a | n/a | 3,991,856 | 3.992 | 273,272 | 8.976 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 12,483,659.3 | 12.483659 | 12.481524–12.484969 | n/a | n/a | n/a | 3,991,856 | 3.992 | 0 | 13.938 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 12,463,882 | 12.463882 | 12.461970–12.464995 | n/a | n/a | n/a | 3,991,856 | 3.992 | 6,204 | 13.938 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `dup4`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,239,460 | 9.239460 | 9.238545–9.240461 | n/a | n/a | n/a | 3,001,768 | 3.002 | 273,272 | 6.749 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 5,646,439 | 5.646439 | 5.645368–5.647443 | n/a | n/a | n/a | 3,001,768 | 3.002 | 6,204 | 10.498 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 5,684,958 | 5.684958 | 5.683978–5.686232 | n/a | n/a | n/a | 3,001,768 | 3.002 | 0 | 10.498 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 5,643,261.3 | 5.643261 | 5.642206–5.644252 | n/a | n/a | n/a | 3,001,768 | 3.002 | 6,204 | 10.498 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `dup48`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 10,155,297.3 | 10.155297 | 10.155021–10.155534 | n/a | n/a | n/a | 3,919,080 | 3.919 | 273,272 | 8.813 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 9,459,745.3 | 9.459745 | 9.457977–9.460837 | n/a | n/a | n/a | 3,919,080 | 3.919 | 6,204 | 13.700 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 9,479,332.3 | 9.479332 | 9.477000–9.480961 | n/a | n/a | n/a | 3,919,080 | 3.919 | 0 | 13.700 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 9,456,794 | 9.456794 | 9.455060–9.457846 | n/a | n/a | n/a | 3,919,080 | 3.919 | 6,204 | 13.700 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `dup512`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 12,835,851 | 12.835851 | 12.833283–12.840444 | n/a | n/a | n/a | 3,994,392 | 3.994 | 273,272 | 8.982 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 12,841,731.3 | 12.841731 | 12.839136–12.846338 | n/a | n/a | n/a | 3,994,392 | 3.994 | 273,272 | 8.982 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 12,936,157 | 12.936157 | 12.934273–12.939271 | n/a | n/a | n/a | 3,994,392 | 3.994 | 0 | 13.946 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 12,916,555.3 | 12.916555 | 12.914813–12.919594 | n/a | n/a | n/a | 3,994,392 | 3.994 | 6,204 | 13.946 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `dup6`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,377,188.3 | 9.377188 | 9.376849–9.377717 | n/a | n/a | n/a | 3,334,792 | 3.335 | 273,272 | 7.501 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 6,220,540.3 | 6.220540 | 6.220156–6.220840 | n/a | n/a | n/a | 3,334,792 | 3.335 | 6,204 | 11.668 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 6,255,685 | 6.255685 | 6.255450–6.255967 | n/a | n/a | n/a | 3,334,792 | 3.335 | 0 | 11.668 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 6,217,425.7 | 6.217426 | 6.217003–6.217725 | n/a | n/a | n/a | 3,334,792 | 3.335 | 6,204 | 11.668 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `dup64`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 10,308,396.3 | 10.308396 | 10.308206–10.308512 | n/a | n/a | n/a | 3,940,984 | 3.941 | 273,272 | 8.859 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 9,907,732.7 | 9.907733 | 9.906124–9.908884 | n/a | n/a | n/a | 3,940,984 | 3.941 | 6,204 | 13.769 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 9,926,551.3 | 9.926551 | 9.924513–9.928282 | n/a | n/a | n/a | 3,940,984 | 3.941 | 0 | 13.769 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 9,904,774.3 | 9.904774 | 9.903180–9.905927 | n/a | n/a | n/a | 3,940,984 | 3.941 | 6,204 | 13.769 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `dup768`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 13,380,589.7 | 13.380590 | 13.376638–13.384006 | n/a | n/a | n/a | 3,997,000 | 3.997 | 273,272 | 8.988 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 13,386,431.7 | 13.386432 | 13.382469–13.389863 | n/a | n/a | n/a | 3,997,000 | 3.997 | 273,272 | 8.988 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 13,465,158 | 13.465158 | 13.461680–13.470018 | n/a | n/a | n/a | 3,997,000 | 3.997 | 0 | 13.954 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 13,445,760.3 | 13.445760 | 13.442497–13.450670 | n/a | n/a | n/a | 3,997,000 | 3.997 | 6,204 | 13.954 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `dup8`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,460,256.7 | 9.460257 | 9.459508–9.461060 | n/a | n/a | n/a | 3,502,648 | 3.503 | 273,272 | 7.875 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 6,636,982 | 6.636982 | 6.636194–6.638201 | n/a | n/a | n/a | 3,502,648 | 3.503 | 6,204 | 12.251 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 6,666,889.7 | 6.666890 | 6.666104–6.667946 | n/a | n/a | n/a | 3,502,648 | 3.503 | 0 | 12.251 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 6,633,930 | 6.633930 | 6.633154–6.635139 | n/a | n/a | n/a | 3,502,648 | 3.503 | 6,204 | 12.251 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `dup96`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 10,645,059.3 | 10.645059 | 10.644856–10.645290 | n/a | n/a | n/a | 3,961,016 | 3.961 | 273,272 | 8.906 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 10,590,150.7 | 10.590151 | 10.468585–10.651135 | n/a | n/a | n/a | 3,961,016 | 3.961 | 273,272 | 10.550 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 10,487,786.3 | 10.487786 | 10.485772–10.491064 | n/a | n/a | n/a | 3,961,016 | 3.961 | 0 | 13.838 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 10,466,960.3 | 10.466960 | 10.464779–10.470456 | n/a | n/a | n/a | 3,961,016 | 3.961 | 6,204 | 13.838 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `nearly1`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,732,449.7 | 9.732450 | 9.725641–9.740757 | n/a | n/a | n/a | 4,002,216 | 4.002 | 273,272 | 8.935 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 3,130,080 | 3.130080 | 3.126684–3.133664 | n/a | n/a | n/a | 4,002,072 | 4.002 | 6,204 | 12.574 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 3,135,249 | 3.135249 | 3.131752–3.138751 | n/a | n/a | n/a | 4,002,072 | 4.002 | 0 | 12.574 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 3,126,208.7 | 3.126209 | 3.122805–3.129789 | n/a | n/a | n/a | 4,002,072 | 4.002 | 6,204 | 12.574 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `organpipe`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 2,005,837 | 2.005837 | 2.005837–2.005837 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `random`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 118,688.3 | 11.868833 | 11.866400–11.871000 | 11.845814 | 0.023019 | +0.194% | 42,304 | 4.230 | 273,272 | 2.999 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 119,708 | 11.970800 | 11.966900–11.973600 | 11.845814 | 0.124986 | +1.055% | 42,304 | 4.230 | 0 | 7.948 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 119,708 | 11.970800 | 11.966900–11.973600 | 11.845814 | 0.124986 | +1.055% | 42,304 | 4.230 | 0 | 7.948 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 119,708 | 11.970800 | 11.966900–11.973600 | 11.845814 | 0.124986 | +1.055% | 42,304 | 4.230 | 0 | 7.948 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `random`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 1,519,047.3 | 15.190473 | 15.189880–15.190920 | 15.167042 | 0.023432 | +0.154% | 402,296 | 4.023 | 273,272 | 5.999 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 1,528,942.7 | 15.289427 | 15.289150–15.289570 | 15.167042 | 0.122385 | +0.807% | 402,296 | 4.023 | 0 | 10.960 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 1,528,942.7 | 15.289427 | 15.289150–15.289570 | 15.167042 | 0.122385 | +0.807% | 402,296 | 4.023 | 0 | 10.960 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 1,528,942.7 | 15.289427 | 15.289150–15.289570 | 15.167042 | 0.122385 | +0.807% | 402,296 | 4.023 | 0 | 10.960 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `random`, n=262,144

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 4,348,637 | 16.588734 | 16.588577–16.588825 | 16.557344 | 0.031389 | +0.190% | 1,050,880 | 4.009 | 298,116 | 6.999 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 4,350,177 | 16.594608 | 16.594398–16.594746 | 16.557344 | 0.037264 | +0.225% | 1,050,880 | 4.009 | 298,116 | 6.999 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 4,377,220.3 | 16.697770 | 16.696941–16.698563 | 16.557344 | 0.140426 | +0.848% | 1,050,880 | 4.009 | 0 | 12.939 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 4,377,220.3 | 16.697770 | 16.696941–16.698563 | 16.557344 | 0.140426 | +0.848% | 1,050,880 | 4.009 | 0 | 12.939 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `random`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 18,520,455.7 | 18.520456 | 18.520411–18.520489 | 18.488885 | 0.031571 | +0.171% | 4,002,288 | 4.002 | 273,272 | 8.999 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 18,526,328 | 18.526328 | 18.526291–18.526354 | 18.488885 | 0.037443 | +0.203% | 4,002,288 | 4.002 | 273,272 | 8.999 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 18,599,038.7 | 18.599039 | 18.598521–18.599329 | 18.488885 | 0.110154 | +0.596% | 4,002,288 | 4.002 | 0 | 13.968 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 18,580,017.7 | 18.580018 | 18.579784–18.580189 | 18.488885 | 0.091133 | +0.493% | 4,002,288 | 4.002 | 6,204 | 13.968 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `runs1024`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 16,740,316 | 16.740316 | 16.740099–16.740533 | n/a | n/a | n/a | 4,002,288 | 4.002 | 273,272 | 8.999 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 10,954,041 | 10.954041 | 10.954031–10.954050 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `runs32`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 18,507,786.7 | 18.507787 | 18.507633–18.507881 | n/a | n/a | n/a | 4,002,288 | 4.002 | 273,272 | 8.999 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 18,008,307 | 18.008307 | 18.007835–18.008839 | n/a | n/a | n/a | 4,002,288 | 4.002 | 6,204 | 13.967 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 18,019,755.3 | 18.019755 | 18.019363–18.020256 | n/a | n/a | n/a | 4,002,288 | 4.002 | 0 | 13.967 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 18,004,464 | 18.004464 | 18.003992–18.004996 | n/a | n/a | n/a | 4,002,288 | 4.002 | 6,204 | 13.967 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `saw13`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,683,467 | 9.683467 | 9.683467–9.683467 | n/a | n/a | n/a | 3,694,608 | 3.695 | 273,272 | 8.308 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 7,488,167 | 7.488167 | 7.488167–7.488167 | n/a | n/a | n/a | 3,694,608 | 3.695 | 6,204 | 12.923 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 7,508,402 | 7.508402 | 7.508402–7.508402 | n/a | n/a | n/a | 3,694,608 | 3.695 | 0 | 12.923 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 7,484,409 | 7.484409 | 7.484409–7.484409 | n/a | n/a | n/a | 3,694,608 | 3.695 | 6,204 | 12.923 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |

## `tail10`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 3,427,093.7 | 3.427094 | 3.426109–3.428779 | n/a | n/a | n/a | 730,864 | 0.731 | 273,272 | 1.579 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `hybrid_gate` | 3 | 3,433,679.3 | 3.433679 | 3.428187–3.437474 | n/a | n/a | n/a | 730,864 | 0.731 | 6,204 | 2.074 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort` | 3 | 3,431,823.7 | 3.431824 | 3.426400–3.435704 | n/a | n/a | n/a | 730,864 | 0.731 | 0 | 2.074 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
| `powersort_fj` | 3 | 3,429,860.3 | 3.429860 | 3.424365–3.433655 | n/a | n/a | n/a | 730,864 | 0.731 | 6,204 | 2.074 | sm=96, fj-thresh=0, fj-max=2048, build=`97869f3` |
