# Portfolio gate study (e67f8ae)

Aggregated 380 validated rows from 3 CSV file(s). Each row below is grouped by algorithm, distribution, n, and mode. Comparison and merge-span metrics are arithmetic means, timing metrics are medians, and memory bounds/peaks are maxima.

Build IDs: `e67f8ae`.

For random permutations, comparison excess is `100 * (mean comparisons - lg(n!)) / lg(n!)`; it is reported as `n/a` for other distributions. Timing metrics use only `time` rows, while comparison, heap, and merge metrics use only `count` rows.

## `disp1024`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 11,247,388.3 | 11.247388 | 11.244790–11.249992 | n/a | n/a | n/a | 31,608 | 0.032 | 273,272 | 2.420 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 11,253,250.7 | 11.253251 | 11.250637–11.255857 | n/a | n/a | n/a | 31,608 | 0.032 | 273,272 | 2.420 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 11,340,100.7 | 11.340101 | 11.339790–11.340419 | n/a | n/a | n/a | 31,608 | 0.032 | 0 | 7.361 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 11,321,516.7 | 11.321517 | 11.321148–11.321993 | n/a | n/a | n/a | 31,608 | 0.032 | 6,204 | 7.361 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `disp128`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,665,806.7 | 9.665807 | 9.665202–9.666381 | n/a | n/a | n/a | 6,144 | 0.006 | 273,272 | 0.291 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 8,387,659 | 8.387659 | 8.383616–8.393479 | n/a | n/a | n/a | 6,144 | 0.006 | 6,204 | 3.895 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 8,399,428.3 | 8.399428 | 8.395974–8.405587 | n/a | n/a | n/a | 6,144 | 0.006 | 0 | 3.895 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 8,383,432.7 | 8.383433 | 8.379691–8.389587 | n/a | n/a | n/a | 6,144 | 0.006 | 6,204 | 3.895 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `disp1536`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 11,830,448.7 | 11.830449 | 11.828523–11.832359 | n/a | n/a | n/a | 45,088 | 0.045 | 273,272 | 3.048 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 11,836,306 | 11.836306 | 11.834412–11.838162 | n/a | n/a | n/a | 45,088 | 0.045 | 273,272 | 3.048 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 11,921,345.3 | 11.921345 | 11.918683–11.923560 | n/a | n/a | n/a | 45,088 | 0.045 | 0 | 8.003 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 11,902,235 | 11.902235 | 11.899856–11.904392 | n/a | n/a | n/a | 45,088 | 0.045 | 6,204 | 8.003 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `disp16`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,293,116.7 | 9.293117 | 9.292991–9.293258 | n/a | n/a | n/a | 2,720 | 0.003 | 273,272 | 0.024 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 5,533,259.7 | 5.533260 | 5.532544–5.534068 | n/a | n/a | n/a | 2,720 | 0.003 | 6,204 | 0.755 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 5,542,747.3 | 5.542747 | 5.542062–5.543751 | n/a | n/a | n/a | 2,720 | 0.003 | 0 | 0.755 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 5,529,320 | 5.529320 | 5.528595–5.530134 | n/a | n/a | n/a | 2,720 | 0.003 | 6,204 | 0.755 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `disp192`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,807,736.7 | 9.807737 | 9.806089–9.808978 | n/a | n/a | n/a | 7,832 | 0.008 | 273,272 | 0.461 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 8,949,850 | 8.949850 | 8.948978–8.951319 | n/a | n/a | n/a | 7,832 | 0.008 | 6,204 | 4.582 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 8,961,609.7 | 8.961610 | 8.960673–8.962873 | n/a | n/a | n/a | 7,832 | 0.008 | 0 | 4.582 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 8,944,989.3 | 8.944989 | 8.944085–8.946445 | n/a | n/a | n/a | 7,832 | 0.008 | 6,204 | 4.582 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `disp2048`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 12,246,512.3 | 12.246512 | 12.244750–12.247401 | n/a | n/a | n/a | 63,992 | 0.064 | 273,272 | 3.516 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 12,252,379.7 | 12.252380 | 12.250622–12.253274 | n/a | n/a | n/a | 63,992 | 0.064 | 273,272 | 3.516 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 12,331,746.3 | 12.331746 | 12.330939–12.332340 | n/a | n/a | n/a | 63,992 | 0.064 | 0 | 8.475 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 12,312,385.3 | 12.312385 | 12.312081–12.312960 | n/a | n/a | n/a | 63,992 | 0.064 | 6,204 | 8.475 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `disp256`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,939,023.3 | 9.939023 | 9.937389–9.941103 | n/a | n/a | n/a | 9,488 | 0.009 | 273,272 | 0.644 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 9,357,517 | 9.357517 | 9.354899–9.361216 | n/a | n/a | n/a | 9,488 | 0.009 | 6,204 | 5.073 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 9,370,218.3 | 9.370218 | 9.367250–9.374316 | n/a | n/a | n/a | 9,488 | 0.009 | 0 | 5.073 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 9,352,622.3 | 9.352622 | 9.350002–9.356331 | n/a | n/a | n/a | 9,488 | 0.009 | 6,204 | 5.073 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `disp3072`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 12,836,341.7 | 12.836342 | 12.834124–12.837561 | n/a | n/a | n/a | 95,048 | 0.095 | 273,272 | 4.154 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 12,842,228.7 | 12.842229 | 12.840012–12.843464 | n/a | n/a | n/a | 95,048 | 0.095 | 273,272 | 4.154 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 12,917,427.3 | 12.917427 | 12.915083–12.918635 | n/a | n/a | n/a | 95,048 | 0.095 | 0 | 9.117 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 12,897,880 | 12.897880 | 12.895155–12.899250 | n/a | n/a | n/a | 95,048 | 0.095 | 6,204 | 9.117 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `disp32`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,383,306.7 | 9.383307 | 9.382562–9.383827 | n/a | n/a | n/a | 3,024 | 0.003 | 273,272 | 0.056 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 6,330,010 | 6.330010 | 6.326729–6.331967 | n/a | n/a | n/a | 3,120 | 0.003 | 6,204 | 1.614 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 6,338,686.3 | 6.338686 | 6.335074–6.341058 | n/a | n/a | n/a | 3,120 | 0.003 | 0 | 1.614 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 6,326,086.7 | 6.326087 | 6.322809–6.328055 | n/a | n/a | n/a | 3,120 | 0.003 | 6,204 | 1.614 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `disp384`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 10,182,959.7 | 10.182960 | 10.179851–10.184577 | n/a | n/a | n/a | 13,408 | 0.013 | 273,272 | 1.013 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 9,930,230.3 | 9.930230 | 9.928142–9.933368 | n/a | n/a | n/a | 13,408 | 0.013 | 6,204 | 5.748 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 9,942,350 | 9.942350 | 9.940312–9.945372 | n/a | n/a | n/a | 13,408 | 0.013 | 0 | 5.748 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 9,924,368.3 | 9.924368 | 9.922278–9.927487 | n/a | n/a | n/a | 13,408 | 0.013 | 6,204 | 5.748 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `disp4`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,092,355.3 | 9.092355 | 9.091822–9.092664 | n/a | n/a | n/a | 2,392 | 0.002 | 273,272 | 0.004 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 4,849,018.7 | 4.849019 | 4.848417–4.849926 | n/a | n/a | n/a | 2,400 | 0.002 | 6,204 | 0.116 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 4,873,028.3 | 4.873028 | 4.872386–4.873875 | n/a | n/a | n/a | 2,400 | 0.002 | 0 | 0.116 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 4,844,968.7 | 4.844969 | 4.844342–4.845913 | n/a | n/a | n/a | 2,400 | 0.002 | 6,204 | 0.116 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `disp4096`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 13,247,477.3 | 13.247477 | 13.241148–13.252836 | n/a | n/a | n/a | 119,008 | 0.119 | 273,272 | 4.596 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 13,253,325 | 13.253325 | 13.247003–13.258682 | n/a | n/a | n/a | 119,008 | 0.119 | 273,272 | 4.596 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 13,326,427.3 | 13.326427 | 13.321090–13.331569 | n/a | n/a | n/a | 119,008 | 0.119 | 0 | 9.561 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 13,307,527.7 | 13.307528 | 13.302333–13.312306 | n/a | n/a | n/a | 119,008 | 0.119 | 6,204 | 9.561 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `disp512`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 10,420,161.7 | 10.420162 | 10.418896–10.421104 | n/a | n/a | n/a | 16,864 | 0.017 | 273,272 | 1.380 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 10,340,868.3 | 10.340868 | 10.339731–10.342215 | n/a | n/a | n/a | 16,864 | 0.017 | 6,204 | 6.230 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 10,353,212.3 | 10.353212 | 10.352143–10.354725 | n/a | n/a | n/a | 16,864 | 0.017 | 0 | 6.230 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 10,335,017.3 | 10.335017 | 10.333858–10.336380 | n/a | n/a | n/a | 16,864 | 0.017 | 6,204 | 6.230 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `disp64`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,501,471.3 | 9.501471 | 9.500675–9.502175 | n/a | n/a | n/a | 3,888 | 0.004 | 273,272 | 0.130 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 7,366,908 | 7.366908 | 7.364202–7.369030 | n/a | n/a | n/a | 4,016 | 0.004 | 6,204 | 2.720 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 7,376,971.7 | 7.376972 | 7.374036–7.378995 | n/a | n/a | n/a | 4,016 | 0.004 | 0 | 2.720 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 7,362,997.3 | 7.362997 | 7.360305–7.365137 | n/a | n/a | n/a | 4,016 | 0.004 | 6,204 | 2.720 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `disp768`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 10,860,385.7 | 10.860386 | 10.859324–10.861562 | n/a | n/a | n/a | 23,408 | 0.023 | 273,272 | 1.970 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 10,866,243.3 | 10.866243 | 10.865186–10.867407 | n/a | n/a | n/a | 23,408 | 0.023 | 273,272 | 1.970 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 10,926,087.3 | 10.926087 | 10.923514–10.928032 | n/a | n/a | n/a | 23,408 | 0.023 | 0 | 6.890 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 10,907,263.7 | 10.907264 | 10.905245–10.909224 | n/a | n/a | n/a | 23,408 | 0.023 | 6,204 | 6.890 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `disp8`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,201,720 | 9.201720 | 9.201264–9.202019 | n/a | n/a | n/a | 2,480 | 0.002 | 273,272 | 0.010 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 5,094,291.3 | 5.094291 | 5.093997–5.094466 | n/a | n/a | n/a | 2,488 | 0.002 | 6,204 | 0.306 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 5,109,352.7 | 5.109353 | 5.109186–5.109669 | n/a | n/a | n/a | 2,488 | 0.002 | 0 | 0.306 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 5,090,328 | 5.090328 | 5.090032–5.090517 | n/a | n/a | n/a | 2,488 | 0.002 | 6,204 | 0.306 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `disp96`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,593,633.3 | 9.593633 | 9.588979–9.598450 | n/a | n/a | n/a | 4,776 | 0.005 | 273,272 | 0.208 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 7,988,564.7 | 7.988565 | 7.984687–7.993862 | n/a | n/a | n/a | 4,776 | 0.005 | 6,204 | 3.406 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 7,999,430.3 | 7.999430 | 7.995929–8.004300 | n/a | n/a | n/a | 4,776 | 0.005 | 0 | 3.406 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 7,984,645.3 | 7.984645 | 7.980762–7.989967 | n/a | n/a | n/a | 4,776 | 0.005 | 6,204 | 3.406 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `dup16`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,672,713.3 | 9.672713 | 9.672221–9.673219 | n/a | n/a | n/a | 3,751,624 | 3.752 | 273,272 | 8.437 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 7,811,960.3 | 7.811960 | 7.811556–7.812379 | n/a | n/a | n/a | 3,751,624 | 3.752 | 6,204 | 13.123 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 7,838,704.3 | 7.838704 | 7.838175–7.839039 | n/a | n/a | n/a | 3,751,624 | 3.752 | 0 | 13.123 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 7,811,909 | 7.811909 | 7.811523–7.812320 | n/a | n/a | n/a | 3,751,624 | 3.752 | 6,204 | 13.123 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `dup256`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 11,782,301.3 | 11.782301 | 11.780323–11.783560 | n/a | n/a | n/a | 3,986,568 | 3.987 | 273,272 | 8.965 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 11,922,133.3 | 11.922133 | 11.919077–11.923887 | n/a | n/a | n/a | 3,986,568 | 3.987 | 6,204 | 13.921 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 11,941,590.7 | 11.941591 | 11.938097–11.943485 | n/a | n/a | n/a | 3,986,568 | 3.987 | 0 | 13.921 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 11,921,460 | 11.921460 | 11.918160–11.923186 | n/a | n/a | n/a | 3,986,568 | 3.987 | 6,204 | 13.921 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `nearly1`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,732,449.7 | 9.732450 | 9.725641–9.740757 | n/a | n/a | n/a | 4,002,216 | 4.002 | 273,272 | 8.935 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 3,130,080 | 3.130080 | 3.126684–3.133664 | n/a | n/a | n/a | 4,002,072 | 4.002 | 6,204 | 12.574 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 3,135,249 | 3.135249 | 3.131752–3.138751 | n/a | n/a | n/a | 4,002,072 | 4.002 | 0 | 12.574 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 3,126,208.7 | 3.126209 | 3.122805–3.129789 | n/a | n/a | n/a | 4,002,072 | 4.002 | 6,204 | 12.574 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `organpipe`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 2,005,837 | 2.005837 | 2.005837–2.005837 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `random`, n=10,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 118,688.3 | 11.868833 | 11.866400–11.871000 | 11.845814 | 0.023019 | +0.194% | 42,304 | 4.230 | 273,272 | 2.999 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 119,708 | 11.970800 | 11.966900–11.973600 | 11.845814 | 0.124986 | +1.055% | 42,304 | 4.230 | 0 | 7.948 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 119,708 | 11.970800 | 11.966900–11.973600 | 11.845814 | 0.124986 | +1.055% | 42,304 | 4.230 | 0 | 7.948 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 119,708 | 11.970800 | 11.966900–11.973600 | 11.845814 | 0.124986 | +1.055% | 42,304 | 4.230 | 0 | 7.948 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `random`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 1,519,047.3 | 15.190473 | 15.189880–15.190920 | 15.167042 | 0.023432 | +0.154% | 402,296 | 4.023 | 273,272 | 5.999 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 1,528,942.7 | 15.289427 | 15.289150–15.289570 | 15.167042 | 0.122385 | +0.807% | 402,296 | 4.023 | 0 | 10.960 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 1,528,942.7 | 15.289427 | 15.289150–15.289570 | 15.167042 | 0.122385 | +0.807% | 402,296 | 4.023 | 0 | 10.960 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 1,528,942.7 | 15.289427 | 15.289150–15.289570 | 15.167042 | 0.122385 | +0.807% | 402,296 | 4.023 | 0 | 10.960 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `random`, n=262,144

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 4,348,637 | 16.588734 | 16.588577–16.588825 | 16.557344 | 0.031389 | +0.190% | 1,050,880 | 4.009 | 298,116 | 6.999 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 4,350,177 | 16.594608 | 16.594398–16.594746 | 16.557344 | 0.037264 | +0.225% | 1,050,880 | 4.009 | 298,116 | 6.999 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 4,377,220.3 | 16.697770 | 16.696941–16.698563 | 16.557344 | 0.140426 | +0.848% | 1,050,880 | 4.009 | 0 | 12.939 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 4,377,220.3 | 16.697770 | 16.696941–16.698563 | 16.557344 | 0.140426 | +0.848% | 1,050,880 | 4.009 | 0 | 12.939 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `random`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 6 | 18,520,526.3 | 18.520526 | 18.520338–18.520848 | 18.488885 | 0.031642 | +0.171% | 4,002,304 | 4.002 | 273,272 | 8.999 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 6 | 18,526,382.3 | 18.526382 | 18.526186–18.526688 | 18.488885 | 0.037498 | +0.203% | 4,002,304 | 4.002 | 273,272 | 8.999 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 6 | 18,599,080.2 | 18.599080 | 18.598521–18.599663 | 18.488885 | 0.110195 | +0.596% | 4,002,304 | 4.002 | 0 | 13.968 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 6 | 18,579,687.7 | 18.579688 | 18.578692–18.580189 | 18.488885 | 0.090803 | +0.491% | 4,002,304 | 4.002 | 6,204 | 13.968 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 5 | 130,575,924 | 130.6 | 273,272 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 5 | 131,490,530 | 131.5 | 273,272 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 5 | 71,795,332 | 71.795 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 5 | 77,175,255 | 77.175 | 6,204 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `runs1024`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 16,740,316 | 16.740316 | 16.740099–16.740533 | n/a | n/a | n/a | 4,002,288 | 4.002 | 273,272 | 8.999 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 10,954,041 | 10.954041 | 10.954031–10.954050 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `runs32`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 18,507,786.7 | 18.507787 | 18.507633–18.507881 | n/a | n/a | n/a | 4,002,288 | 4.002 | 273,272 | 8.999 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 18,008,307 | 18.008307 | 18.007835–18.008839 | n/a | n/a | n/a | 4,002,288 | 4.002 | 6,204 | 13.967 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 18,019,755.3 | 18.019755 | 18.019363–18.020256 | n/a | n/a | n/a | 4,002,288 | 4.002 | 0 | 13.967 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 18,004,464 | 18.004464 | 18.003992–18.004996 | n/a | n/a | n/a | 4,002,288 | 4.002 | 6,204 | 13.967 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `saw13`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 9,683,467 | 9.683467 | 9.683467–9.683467 | n/a | n/a | n/a | 3,694,608 | 3.695 | 273,272 | 8.308 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 7,488,167 | 7.488167 | 7.488167–7.488167 | n/a | n/a | n/a | 3,694,608 | 3.695 | 6,204 | 12.923 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 7,508,402 | 7.508402 | 7.508402–7.508402 | n/a | n/a | n/a | 3,694,608 | 3.695 | 0 | 12.923 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 7,484,409 | 7.484409 | 7.484409–7.484409 | n/a | n/a | n/a | 3,694,608 | 3.695 | 6,204 | 12.923 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |

## `tail10`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 3 | 3,427,093.7 | 3.427094 | 3.426109–3.428779 | n/a | n/a | n/a | 730,864 | 0.731 | 273,272 | 1.579 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `hybrid_gate` | 3 | 3,433,679.3 | 3.433679 | 3.428187–3.437474 | n/a | n/a | n/a | 730,864 | 0.731 | 6,204 | 2.074 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort` | 3 | 3,431,823.7 | 3.431824 | 3.426400–3.435704 | n/a | n/a | n/a | 730,864 | 0.731 | 0 | 2.074 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
| `powersort_fj` | 3 | 3,429,860.3 | 3.429860 | 3.424365–3.433655 | n/a | n/a | n/a | 730,864 | 0.731 | 6,204 | 2.074 | sm=96, fj-thresh=0, fj-max=2048, build=`e67f8ae` |
