# Deletion-backbone bounded-memory rotation merge v4

Aggregated 15,840 validated rows from 2 CSV file(s). Each row below is grouped by algorithm, distribution, n, and mode. Comparison and merge-span metrics are arithmetic means, timing metrics are medians, and memory bounds/peaks are maxima.

Build IDs: `backbone-rotate-v4`.

For random permutations, comparison excess is `100 * (mean comparisons - lg(n!)) / lg(n!)`; it is reported as `n/a` for other distributions. Timing metrics use only `time` rows, while comparison, heap, and merge metrics use only `count` rows.

## `disp16`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 3,919,078 | 19.595390 | 19.470290–19.666385 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 3,919,078 | 19.595390 | 19.470290–19.666385 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 3,919,078 | 19.595390 | 19.470290–19.666385 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 3,919,078 | 19.595390 | 19.470290–19.666385 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 1,471,179.3 | 7.355897 | 7.352595–7.359965 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 1,468,875.3 | 7.344377 | 7.341075–7.348445 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 1,091,191.7 | 5.455958 | 5.453645–5.457500 | n/a | n/a | n/a | 2,664 | 0.013 | 0 | 0.935 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 3,779,295.3 | 18.896477 | 18.804215–18.989360 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 4,981,292 | 24.906 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 4,493,653 | 22.468 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 4,457,200 | 22.286 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 4,362,853 | 21.814 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 4,828,288 | 24.141 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 4,430,529 | 22.153 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 5,910,002 | 29.550 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 4,305,872 | 21.529 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `disp16`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 22,292,602.3 | 22.292602 | 22.166429–22.477923 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 22,292,602.3 | 22.292602 | 22.166429–22.477923 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 22,292,602.3 | 22.292602 | 22.166429–22.477923 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 22,292,602.3 | 22.292602 | 22.166429–22.477923 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 11,998,998 | 11.998998 | 7.339833–21.316902 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 7,337,673.3 | 7.337673 | 7.337529–7.337955 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 5,542,411 | 5.542411 | 5.541725–5.543421 | n/a | n/a | n/a | 2,720 | 0.003 | 0 | 0.755 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 21,416,432.3 | 21.416432 | 21.311482–21.598968 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 23,344,784 | 23.345 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 22,832,372 | 22.832 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 22,626,154 | 22.626 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 22,741,892 | 22.742 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 20,812,218 | 20.812 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 20,802,046 | 20.802 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 26,295,402 | 26.295 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 21,806,378 | 21.806 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct1`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 455,624.7 | 2.278123 | 2.271215–2.291215 | n/a | n/a | n/a | 32,768 | 0.164 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 455,624.7 | 2.278123 | 2.271215–2.291215 | n/a | n/a | n/a | 32,768 | 0.164 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 455,624.7 | 2.278123 | 2.271215–2.291215 | n/a | n/a | n/a | 32,768 | 0.164 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 455,624.7 | 2.278123 | 2.271215–2.291215 | n/a | n/a | n/a | 32,768 | 0.164 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 2,802,687.3 | 14.013437 | 1.686240–38.665560 | n/a | n/a | n/a | 10,392 | 0.052 | 0 | 3.577 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 3,219,995 | 16.099975 | 16.049205–16.142410 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 331,979 | 1.659895 | 1.654345–1.668740 | n/a | n/a | n/a | 10,392 | 0.052 | 0 | 5.365 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 7,749,859.3 | 38.749297 | 38.633700–38.865020 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 1,167,120 | 5.836 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 1,130,497 | 5.652 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 1,144,325 | 5.722 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 1,180,162 | 5.901 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 1,465,288 | 7.326 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 5,885,680 | 29.428 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 1,273,399 | 6.367 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 15,512,340 | 77.562 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct1`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 2,330,286.3 | 2.330286 | 2.322280–2.345521 | n/a | n/a | n/a | 393,216 | 0.393 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 2,330,286.3 | 2.330286 | 2.322280–2.345521 | n/a | n/a | n/a | 393,216 | 0.393 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 2,330,286.3 | 2.330286 | 2.322280–2.345521 | n/a | n/a | n/a | 393,216 | 0.393 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 2,330,286.3 | 2.330286 | 2.322280–2.345521 | n/a | n/a | n/a | 393,216 | 0.393 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 1,888,270.3 | 1.888270 | 1.879706–1.900361 | n/a | n/a | n/a | 43,088 | 0.043 | 0 | 6.525 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 18,371,716.3 | 18.371716 | 18.368344–18.374918 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 1,881,890 | 1.881890 | 1.873326–1.893981 | n/a | n/a | n/a | 43,088 | 0.043 | 0 | 6.525 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 43,683,289 | 43.683289 | 43.557161–43.779308 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 6,501,679 | 6.502 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 6,461,627 | 6.462 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 6,499,946 | 6.500 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 6,577,613 | 6.578 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 8,588,074 | 8.588 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 33,520,377 | 33.520 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 8,225,496 | 8.225 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 86,826,429 | 86.826 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct10`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 1,211,210.7 | 6.056053 | 6.026090–6.099390 | n/a | n/a | n/a | 667,256 | 3.336 | 0 | 4.398 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 1,047,825.3 | 5.239127 | 5.208590–5.283190 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 4.398 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 1,065,859.7 | 5.329298 | 5.319140–5.348660 | n/a | n/a | n/a | 508,704 | 2.544 | 0 | 5.507 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 4,709,224.7 | 23.546123 | 23.256675–23.846420 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 4,501,971 | 22.509855 | 22.279200–22.669315 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 3,365,128.7 | 16.825643 | 16.821290–16.828380 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 1,131,357.3 | 5.656787 | 5.652490–5.662740 | n/a | n/a | n/a | 82,616 | 0.413 | 0 | 6.582 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 4,495,776.7 | 22.478883 | 22.248205–22.638370 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 3,312,213 | 16.561 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 3,469,771 | 17.349 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 3,362,655 | 16.813 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 5,260,418 | 26.302 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 5,162,775 | 25.814 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 3,350,561 | 16.753 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 3,281,643 | 16.408 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 5,118,121 | 25.591 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct10`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 6,582,957 | 6.582957 | 6.529859–6.627390 | n/a | n/a | n/a | 3,167,008 | 3.167 | 0 | 5.154 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 5,769,287.7 | 5.769288 | 5.716463–5.813649 | n/a | n/a | n/a | 797,096 | 0.797 | 0 | 5.154 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 6,111,869 | 6.111869 | 6.106710–6.115039 | n/a | n/a | n/a | 2,373,432 | 2.373 | 0 | 6.346 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 26,634,340.3 | 26.634340 | 25.733292–27.415295 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 25,843,942.7 | 25.843943 | 25.063578–26.636474 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 19,432,639.7 | 19.432640 | 19.429340–19.436956 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 6,176,911.3 | 6.176911 | 6.174793–6.180549 | n/a | n/a | n/a | 404,040 | 0.404 | 0 | 7.684 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 25,837,725.7 | 25.837726 | 25.057346–26.630261 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 18,214,331 | 18.214 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 20,733,211 | 20.733 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 20,063,789 | 20.064 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 35,601,815 | 35.602 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 35,213,574 | 35.214 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 24,215,681 | 24.216 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 22,557,986 | 22.558 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 37,932,811 | 37.933 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct2`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 518,766.7 | 2.593833 | 2.588715–2.600275 | n/a | n/a | n/a | 98,304 | 0.492 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 518,766.7 | 2.593833 | 2.588715–2.600275 | n/a | n/a | n/a | 98,304 | 0.492 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 518,766.7 | 2.593833 | 2.588715–2.600275 | n/a | n/a | n/a | 98,304 | 0.492 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 518,766.7 | 2.593833 | 2.588715–2.600275 | n/a | n/a | n/a | 98,304 | 0.492 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 6,336,139.7 | 31.680698 | 31.551860–31.902430 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 3,253,679 | 16.268395 | 16.246785–16.290015 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 505,511.3 | 2.527557 | 2.524150–2.530830 | n/a | n/a | n/a | 18,432 | 0.092 | 0 | 5.834 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 6,329,780.7 | 31.648903 | 31.520085–31.870620 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 1,400,800 | 7.004 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 1,437,631 | 7.188 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 1,417,059 | 7.085 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 1,398,056 | 6.990 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 10,735,691 | 53.678 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 6,156,180 | 30.781 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 2,376,830 | 11.884 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 10,590,559 | 52.953 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct2`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 2,698,951 | 2.698951 | 2.670023–2.728243 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 2,698,951 | 2.698951 | 2.670023–2.728243 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 2,698,951 | 2.698951 | 2.670023–2.728243 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 2,698,951 | 2.698951 | 2.670023–2.728243 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 36,355,139 | 36.355139 | 36.153458–36.606742 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 18,656,607 | 18.656607 | 18.651232–18.663274 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 2,983,670.3 | 2.983670 | 2.977905–2.987518 | n/a | n/a | n/a | 83,896 | 0.084 | 0 | 6.953 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 36,348,779.3 | 36.348779 | 36.147096–36.600380 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 8,127,036 | 8.127 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 8,221,688 | 8.222 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 8,145,594 | 8.146 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 8,354,363 | 8.354 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 61,602,137 | 61.602 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 35,737,626 | 35.738 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 14,513,722 | 14.514 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 61,554,180 | 61.554 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct3`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 583,801.3 | 2.919007 | 2.906280–2.929010 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 583,801.3 | 2.919007 | 2.906280–2.929010 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 583,801.3 | 2.919007 | 2.906280–2.929010 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 583,801.3 | 2.919007 | 2.906280–2.929010 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 5,560,623 | 27.803115 | 27.535990–27.996385 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 3,277,586 | 16.387930 | 16.377725–16.403250 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 655,426.7 | 3.277133 | 3.270720–3.289000 | n/a | n/a | n/a | 26,368 | 0.132 | 0 | 6.048 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 5,554,288 | 27.771440 | 27.504335–27.964700 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 1,786,271 | 8.931 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 1,846,576 | 9.233 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 1,795,592 | 8.978 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 1,832,038 | 9.160 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 8,825,295 | 44.126 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 6,442,410 | 32.212 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 3,307,506 | 16.538 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 8,895,414 | 44.477 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct3`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 3,086,844.3 | 3.086844 | 3.038234–3.142987 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 3,086,844.3 | 3.086844 | 3.038234–3.142987 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 3,086,844.3 | 3.086844 | 3.038234–3.142987 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 3,086,844.3 | 3.086844 | 3.038234–3.142987 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 32,786,585.7 | 32.786586 | 32.654000–32.900511 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 18,833,720.7 | 18.833721 | 18.828562–18.837968 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 3,834,811.3 | 3.834811 | 3.825694–3.843943 | n/a | n/a | n/a | 123,560 | 0.124 | 0 | 7.137 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 32,780,247.3 | 32.780247 | 32.647667–32.894167 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 9,762,293 | 9.762 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 9,837,124 | 9.837 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 9,759,729 | 9.760 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 9,851,585 | 9.852 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 54,908,379 | 54.908 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 37,219,108 | 37.219 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 19,209,840 | 19.210 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 54,244,042 | 54.244 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct4`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 691,856.3 | 3.459282 | 3.435310–3.497525 | n/a | n/a | n/a | 460,896 | 2.304 | 0 | 1.030 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 655,526.3 | 3.277632 | 3.257020–3.312285 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 1.030 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 647,624.7 | 3.238123 | 3.230015–3.252140 | n/a | n/a | n/a | 534,624 | 2.673 | 0 | 2.620 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 5,377,273.7 | 26.886368 | 24.953840–30.499380 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 5,246,219 | 26.231095 | 26.194420–26.293265 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 3,302,396.3 | 16.511982 | 16.490605–16.527495 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 772,101.7 | 3.860508 | 3.830450–3.890715 | n/a | n/a | n/a | 34,432 | 0.172 | 0 | 6.168 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 5,239,905 | 26.199525 | 26.162885–26.261690 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 2,406,361 | 12.032 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 2,529,364 | 12.647 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 3,020,451 | 15.102 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 8,150,636 | 40.753 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 9,161,559 | 45.808 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 6,783,689 | 33.918 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 4,043,495 | 20.217 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 9,043,453 | 45.217 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct4`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 3,811,828 | 3.811828 | 3.781473–3.830121 | n/a | n/a | n/a | 2,154,400 | 2.154 | 0 | 1.253 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 3,627,893 | 3.627893 | 3.596265–3.647950 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 1.253 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 3,409,747 | 3.409747 | 3.408300–3.411011 | n/a | n/a | n/a | 2,469,656 | 2.470 | 0 | 2.926 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 31,881,320.3 | 31.881320 | 29.354334–35.046242 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 31,167,630 | 31.167630 | 30.889159–31.340756 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 18,990,509 | 18.990509 | 18.983225–19.003278 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 4,422,184.3 | 4.422184 | 4.415927–4.426686 | n/a | n/a | n/a | 163,256 | 0.163 | 0 | 7.242 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 31,161,308.7 | 31.161309 | 30.882841–31.334430 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 14,342,646 | 14.343 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 14,759,685 | 14.760 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 16,536,418 | 16.536 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 52,803,074 | 52.803 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 56,309,443 | 56.309 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 38,281,839 | 38.282 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 22,892,780 | 22.893 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 56,338,061 | 56.338 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct5`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 794,294.7 | 3.971473 | 3.951520–3.986950 | n/a | n/a | n/a | 708,376 | 3.542 | 0 | 2.030 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 733,690.3 | 3.668452 | 3.644340–3.688085 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 2.030 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 731,605.7 | 3.658028 | 3.648420–3.670445 | n/a | n/a | n/a | 773,288 | 3.866 | 0 | 3.616 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 5,108,891.3 | 25.544457 | 24.956505–26.232535 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 4,964,350.3 | 24.821752 | 24.746305–24.888225 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 3,315,821 | 16.579105 | 16.564000–16.587790 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 862,232.3 | 4.311162 | 4.304735–4.323145 | n/a | n/a | n/a | 42,520 | 0.213 | 0 | 6.261 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 4,958,057.3 | 24.790287 | 24.714795–24.856810 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 3,317,928 | 16.590 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 3,531,632 | 17.658 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 3,787,844 | 18.939 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 8,914,862 | 44.574 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 9,274,811 | 46.374 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 6,978,339 | 34.892 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 4,683,047 | 23.415 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 9,248,966 | 46.245 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct5`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 4,317,532.7 | 4.317533 | 4.284950–4.350195 | n/a | n/a | n/a | 3,408,072 | 3.408 | 0 | 2.430 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 4,011,093.7 | 4.011094 | 3.980205–4.043951 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 2.430 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 3,933,278.7 | 3.933279 | 3.927583–3.939102 | n/a | n/a | n/a | 3,644,048 | 3.644 | 0 | 4.083 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 30,271,324.3 | 30.271324 | 30.134392–30.375553 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 29,309,628 | 29.309628 | 29.080045–29.577338 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 19,098,952 | 19.098952 | 19.091709–19.111201 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 4,864,267.3 | 4.864267 | 4.859732–4.873333 | n/a | n/a | n/a | 202,888 | 0.203 | 0 | 7.326 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 29,303,324.3 | 29.303324 | 29.073745–29.571034 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 18,431,426 | 18.431 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 18,538,894 | 18.539 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 20,856,252 | 20.856 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 53,297,290 | 53.297 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 55,667,976 | 55.668 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 39,709,229 | 39.709 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 25,749,746 | 25.750 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 55,211,068 | 55.211 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct6`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 925,020.7 | 4.625103 | 4.605565–4.654605 | n/a | n/a | n/a | 876,136 | 4.381 | 0 | 2.678 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 848,803.7 | 4.244018 | 4.224020–4.277350 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 2.678 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 815,750.3 | 4.078752 | 4.072275–4.085285 | n/a | n/a | n/a | 659,784 | 3.299 | 0 | 4.452 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 5,234,206 | 26.171030 | 25.707060–26.729020 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 4,779,090.7 | 23.895453 | 23.745490–24.150865 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 3,328,093 | 16.640465 | 16.614050–16.658305 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 934,125.3 | 4.670627 | 4.658125–4.688550 | n/a | n/a | n/a | 50,600 | 0.253 | 0 | 6.332 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 4,772,818.3 | 23.864092 | 23.714190–24.119470 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 3,916,154 | 19.581 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 4,196,179 | 20.981 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 4,390,933 | 21.955 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 9,963,773 | 49.819 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 9,359,448 | 46.797 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 7,097,646 | 35.488 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 5,100,586 | 25.503 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 9,152,699 | 45.763 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct6`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 5,027,342 | 5.027342 | 4.991177–5.045767 | n/a | n/a | n/a | 4,234,480 | 4.234 | 0 | 3.180 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 4,644,434.7 | 4.644435 | 4.607618–4.663759 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 3.180 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 4,399,562.3 | 4.399562 | 4.397438–4.400719 | n/a | n/a | n/a | 2,913,344 | 2.913 | 0 | 5.040 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 30,261,065.3 | 30.261065 | 29.856744–30.712893 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 28,204,610.7 | 28.204611 | 27.997882–28.431490 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 19,185,038.3 | 19.185038 | 19.179435–19.195694 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 5,207,945.3 | 5.207945 | 5.204707–5.212984 | n/a | n/a | n/a | 242,432 | 0.242 | 0 | 7.401 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 28,198,327 | 28.198327 | 27.991593–28.425216 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 21,649,580 | 21.650 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 22,522,893 | 22.523 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 23,709,242 | 23.709 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 56,508,732 | 56.509 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 54,817,395 | 54.817 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 40,204,168 | 40.204 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 28,199,737 | 28.200 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 55,240,560 | 55.241 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct7`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 1,121,590.3 | 5.607952 | 5.576035–5.639335 | n/a | n/a | n/a | 878,624 | 4.393 | 0 | 3.149 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 948,919.7 | 4.744598 | 4.712430–4.777140 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 3.149 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 879,467.7 | 4.397338 | 4.386240–4.409200 | n/a | n/a | n/a | 282,240 | 1.411 | 0 | 4.575 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 4,913,487 | 24.567435 | 24.352075–24.841350 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 4,786,247.7 | 23.931238 | 23.881645–23.966645 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 3,338,941.7 | 16.694708 | 16.668725–16.711560 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 995,141.7 | 4.975708 | 4.967380–4.984250 | n/a | n/a | n/a | 58,768 | 0.294 | 0 | 6.396 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 4,779,995.7 | 23.899978 | 23.850435–23.935380 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 4,793,493 | 23.967 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 4,964,354 | 24.822 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 4,906,506 | 24.533 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 9,777,915 | 48.890 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 10,234,181 | 51.171 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 7,362,465 | 36.812 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 5,606,280 | 28.031 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 10,095,529 | 50.478 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct7`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 5,533,161 | 5.533161 | 5.469795–5.601721 | n/a | n/a | n/a | 4,236,376 | 4.236 | 0 | 3.993 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 4,669,105.3 | 4.669105 | 4.605406–4.737943 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 3.993 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 4,763,048 | 4.763048 | 4.757092–4.768857 | n/a | n/a | n/a | 1,278,936 | 1.279 | 0 | 5.247 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 28,390,178.7 | 28.390179 | 28.280467–28.453381 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 27,651,414 | 27.651414 | 27.370204–28.068128 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 19,263,279 | 19.263279 | 19.258522–19.272533 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 5,496,193.3 | 5.496193 | 5.489655–5.500685 | n/a | n/a | n/a | 282,768 | 0.283 | 0 | 7.473 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 27,645,147.7 | 27.645148 | 27.363943–28.061857 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 20,364,285 | 20.364 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 18,394,938 | 18.395 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 20,752,999 | 20.753 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 41,320,350 | 41.320 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 39,947,208 | 39.947 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 25,461,514 | 25.462 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 20,897,719 | 20.898 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 43,438,449 | 43.438 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct8`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 1,225,267.7 | 6.126338 | 5.973235–6.372285 | n/a | n/a | n/a | 792,240 | 3.961 | 0 | 3.504 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 1,056,374 | 5.281870 | 5.128920–5.527770 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 3.504 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 947,130 | 4.735650 | 4.728430–4.742005 | n/a | n/a | n/a | 372,336 | 1.862 | 0 | 4.980 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 4,968,716 | 24.843580 | 23.774430–25.561620 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 4,670,005.3 | 23.350027 | 22.682795–23.832270 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 3,347,873.3 | 16.739367 | 16.712445–16.753975 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 1,047,684.3 | 5.238422 | 5.235270–5.243450 | n/a | n/a | n/a | 66,928 | 0.335 | 0 | 6.460 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 4,663,771 | 23.318855 | 22.651595–23.801140 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 4,036,185 | 20.181 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 5,223,671 | 26.118 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 3,590,940 | 17.955 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 6,800,002 | 34.000 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 7,088,764 | 35.444 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 6,020,582 | 30.103 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 3,690,104 | 18.451 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 8,146,698 | 40.733 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct8`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 5,900,975 | 5.900975 | 5.881790–5.923557 | n/a | n/a | n/a | 3,784,992 | 3.785 | 0 | 4.463 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 5,056,651.3 | 5.056651 | 5.037665–5.079346 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 4.463 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 5,105,885.3 | 5.105885 | 5.101862–5.107989 | n/a | n/a | n/a | 1,690,760 | 1.691 | 0 | 5.714 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 29,072,362 | 29.072362 | 28.455695–30.113133 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 27,587,843.3 | 27.587843 | 27.459935–27.682069 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 19,325,177 | 19.325177 | 19.321876–19.330919 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 5,744,301.3 | 5.744301 | 5.743464–5.745401 | n/a | n/a | n/a | 323,144 | 0.323 | 0 | 7.543 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 27,581,595.7 | 27.581596 | 27.453693–27.675817 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 28,287,139 | 28.287 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 28,840,751 | 28.841 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 14,065,000 | 14.065 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 35,177,118 | 35.177 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 38,081,249 | 38.081 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 30,563,656 | 30.564 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 24,797,879 | 24.798 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 59,154,024 | 59.154 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct9`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 1,271,469.7 | 6.357348 | 6.320450–6.386535 | n/a | n/a | n/a | 719,256 | 3.596 | 0 | 3.796 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 1,105,487.7 | 5.527438 | 5.491040–5.555990 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 3.796 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 1,049,443 | 5.247215 | 5.139025–5.419325 | n/a | n/a | n/a | 431,968 | 2.160 | 0 | 5.261 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 4,798,682.3 | 23.993412 | 23.204240–24.581890 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 4,585,036.3 | 22.925182 | 22.651890–23.336190 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 3,355,432.7 | 16.777163 | 16.748835–16.792175 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 1,091,061 | 5.455305 | 5.446300–5.463510 | n/a | n/a | n/a | 74,760 | 0.374 | 0 | 6.519 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 4,578,822 | 22.894110 | 22.620855–23.305085 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 3,224,613 | 16.123 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 3,408,729 | 17.044 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 3,285,108 | 16.426 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 5,810,768 | 29.054 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 5,938,102 | 29.691 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 3,784,538 | 18.923 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 3,669,097 | 18.345 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 6,172,340 | 30.862 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `outpct9`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 6,332,373 | 6.332373 | 6.226203–6.527808 | n/a | n/a | n/a | 3,444,648 | 3.445 | 0 | 4.842 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 5,504,301.7 | 5.504302 | 5.398002–5.699913 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 4.842 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 5,451,535 | 5.451535 | 5.437213–5.459145 | n/a | n/a | n/a | 1,998,040 | 1.998 | 0 | 6.058 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 29,009,452.3 | 29.009452 | 27.501245–30.354572 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 26,821,475.3 | 26.821475 | 26.410798–27.424519 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 19,381,616.3 | 19.381616 | 19.378157–19.386428 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 5,968,126.7 | 5.968127 | 5.964362–5.970604 | n/a | n/a | n/a | 363,528 | 0.364 | 0 | 7.614 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 26,815,244 | 26.815244 | 26.404573–27.418291 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 16,843,106 | 16.843 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 18,079,884 | 18.080 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 15,972,278 | 15.972 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 32,770,011 | 32.770 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 36,968,499 | 36.968 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 22,606,741 | 22.607 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 19,275,074 | 19.275 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 36,390,428 | 36.390 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `random`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 4,342,213 | 21.711065 | 21.179180–22.278635 | 16.166996 | 5.544069 | +34.293% | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 4,342,213 | 21.711065 | 21.179180–22.278635 | 16.166996 | 5.544069 | +34.293% | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 4,342,213 | 21.711065 | 21.179180–22.278635 | 16.166996 | 5.544069 | +34.293% | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 4,342,213 | 21.711065 | 21.179180–22.278635 | 16.166996 | 5.544069 | +34.293% | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 4,383,127.3 | 21.915637 | 21.018680–23.583625 | 16.166996 | 5.748641 | +35.558% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 3,442,756 | 17.213780 | 17.213290–17.214105 | 16.166996 | 1.046784 | +6.475% | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 3,257,881 | 16.289405 | 16.288630–16.290135 | 16.166996 | 0.122409 | +0.757% | 802,304 | 4.012 | 0 | 11.959 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 4,377,723.3 | 21.888617 | 20.991725–23.556470 | 16.166996 | 5.721621 | +35.391% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 13,803,361 | 69.017 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 12,952,349 | 64.762 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 13,158,230 | 65.791 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 13,400,099 | 67.000 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 13,329,629 | 66.648 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 16,023,415 | 80.117 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 18,237,110 | 91.186 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 13,803,792 | 69.019 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `random`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 24,517,330.3 | 24.517330 | 24.278334–24.748290 | 18.488885 | 6.028446 | +32.606% | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 24,517,330.3 | 24.517330 | 24.278334–24.748290 | 18.488885 | 6.028446 | +32.606% | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 24,517,330.3 | 24.517330 | 24.278334–24.748290 | 18.488885 | 6.028446 | +32.606% | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 24,517,330.3 | 24.517330 | 24.278334–24.748290 | 18.488885 | 6.028446 | +32.606% | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 24,074,096.7 | 24.074097 | 23.927990–24.303033 | 18.488885 | 5.585212 | +30.208% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 19,952,980.7 | 19.952981 | 19.952624–19.953329 | 18.488885 | 1.464096 | +7.919% | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 18,598,978 | 18.598978 | 18.598839–18.599049 | 18.488885 | 0.110093 | +0.595% | 4,002,304 | 4.002 | 0 | 13.967 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 24,068,716 | 24.068716 | 23.922625–24.297631 | 18.488885 | 5.579831 | +30.179% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 64,765,954 | 64.766 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 74,272,518 | 74.273 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 66,551,474 | 66.551 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 72,965,274 | 72.965 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 77,033,002 | 77.033 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 85,553,691 | 85.554 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 94,040,694 | 94.041 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 72,229,827 | 72.230 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `reversed`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 3,239,029 | 16.195145 | 16.195145–16.195145 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 3,239,029 | 16.195145 | 16.195145–16.195145 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 3,239,029 | 16.195145 | 16.195145–16.195145 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 3,239,029 | 16.195145 | 16.195145–16.195145 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 204,351 | 1.021755 | 1.021755–1.021755 | n/a | n/a | n/a | 2,304 | 0.012 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 1,678,818 | 8.394090 | 8.394090–8.394090 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 199,999 | 0.999995 | 0.999995–0.999995 | n/a | n/a | n/a | 2,304 | 0.012 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 3,232,778 | 16.163890 | 16.163890–16.163890 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 1,072,210 | 5.361 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 1,068,235 | 5.341 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 1,074,718 | 5.374 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 1,086,092 | 5.430 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 103,446 | 0.517 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 2,200,119 | 11.001 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 83,215 | 0.416 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 1,036,569 | 5.183 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `reversed`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 18,162,333 | 18.162333 | 18.162333–18.162333 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 18,162,333 | 18.162333 | 18.162333–18.162333 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 18,162,333 | 18.162333 | 18.162333–18.162333 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 18,162,333 | 18.162333 | 18.162333–18.162333 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 1,004,351 | 1.004351 | 1.004351–1.004351 | n/a | n/a | n/a | 2,304 | 0.002 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 9,413,019 | 9.413019 | 9.413019–9.413019 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 2,304 | 0.002 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 18,131,082 | 18.131082 | 18.131082–18.131082 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 6,060,100 | 6.060 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 6,087,524 | 6.088 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 6,130,128 | 6.130 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 6,086,331 | 6.086 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 789,595 | 0.790 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 12,936,072 | 12.936 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 746,306 | 0.746 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 5,755,755 | 5.756 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `sorted`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 199,999 | 0.999995 | 0.999995–0.999995 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 199,999 | 0.999995 | 0.999995–0.999995 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 199,999 | 0.999995 | 0.999995–0.999995 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 199,999 | 0.999995 | 0.999995–0.999995 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 200,255 | 1.001275 | 1.001275–1.001275 | n/a | n/a | n/a | 2,304 | 0.012 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 199,999 | 0.999995 | 0.999995–0.999995 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 199,999 | 0.999995 | 0.999995–0.999995 | n/a | n/a | n/a | 2,304 | 0.012 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 4,526,699 | 22.633495 | 22.633495–22.633495 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 182,404 | 0.912 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 201,602 | 1.008 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 196,297 | 0.981 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 200,335 | 1.002 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 92,968 | 0.465 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 119,200 | 0.596 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 89,839 | 0.449 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 1,884,251 | 9.421 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `sorted`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 1,000,255 | 1.000255 | 1.000255–1.000255 | n/a | n/a | n/a | 2,304 | 0.002 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 2,304 | 0.002 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 25,604,781 | 25.604781 | 25.604781–25.604781 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 1,112,581 | 1.113 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 1,141,694 | 1.142 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 1,109,487 | 1.109 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 1,094,695 | 1.095 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 774,770 | 0.775 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 824,839 | 0.825 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 781,466 | 0.781 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 11,242,825 | 11.243 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `tail10`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 941,505.7 | 4.707528 | 4.695570–4.713640 | n/a | n/a | n/a | 235,312 | 1.177 | 0 | 0.518 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 860,725 | 4.303625 | 4.288680–4.311695 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.518 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 849,506.7 | 4.247533 | 4.227960–4.260530 | n/a | n/a | n/a | 332,096 | 1.660 | 0 | 2.189 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 4,570,942.7 | 22.854713 | 22.481160–23.547910 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 640,710 | 3.203550 | 3.182920–3.215675 | n/a | n/a | n/a | 157,128 | 0.786 | 0 | 1.874 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 2,206,389.3 | 11.031947 | 11.031580–11.032240 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 634,418 | 3.172090 | 3.151460–3.184215 | n/a | n/a | n/a | 157,128 | 0.786 | 0 | 1.874 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 4,397,215 | 21.986075 | 21.531525–22.612595 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 1,653,573 | 8.268 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 2,628,315 | 13.142 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 1,817,507 | 9.088 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 4,551,389 | 22.757 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 1,473,350 | 7.367 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 2,688,963 | 13.445 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 1,464,125 | 7.321 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 4,274,949 | 21.375 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

## `tail10`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 5,013,025.7 | 5.013026 | 4.996520–5.042777 | n/a | n/a | n/a | 1,044,544 | 1.045 | 0 | 0.648 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 3 | 4,602,845.3 | 4.602845 | 4.585895–4.632586 | n/a | n/a | n/a | 786,720 | 0.787 | 0 | 0.648 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 3 | 4,497,084 | 4.497084 | 4.477123–4.507806 | n/a | n/a | n/a | 1,467,512 | 1.468 | 0 | 2.442 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 3 | 32,119,756.3 | 32.119756 | 25.519908–44.977550 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 3 | 3,428,066.3 | 3.428066 | 3.408645–3.438451 | n/a | n/a | n/a | 723,144 | 0.723 | 0 | 2.074 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 3 | 12,833,282.7 | 12.833283 | 12.833038–12.833666 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 3 | 3,421,770 | 3.421770 | 3.402341–3.432158 | n/a | n/a | n/a | 723,144 | 0.723 | 0 | 2.074 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 3 | 31,392,021.7 | 31.392022 | 25.010677–43.837967 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 10,188,742 | 10.189 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_rotate` | 63 | 14,694,958 | 14.695 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_route` | 63 | 10,539,649 | 10.540 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `deletion_backbone_sort` | 63 | 27,620,985 | 27.621 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `hybrid_inversion_gate` | 63 | 8,724,788 | 8.725 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `inversion_binsert` | 63 | 18,047,948 | 18.048 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `powersort` | 63 | 8,795,949 | 8.796 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
| `std_sort` | 63 | 25,830,344 | 25.830 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-rotate-v4` |
