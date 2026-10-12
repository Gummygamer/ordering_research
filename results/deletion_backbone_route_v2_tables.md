# Deletion-backbone overflow routing v2

Aggregated 11,880 validated rows from 2 CSV file(s). Each row below is grouped by algorithm, distribution, n, and mode. Comparison and merge-span metrics are arithmetic means, timing metrics are medians, and memory bounds/peaks are maxima.

Build IDs: `backbone-route-v2`.

For random permutations, comparison excess is `100 * (mean comparisons - lg(n!)) / lg(n!)`; it is reported as `n/a` for other distributions. Timing metrics use only `time` rows, while comparison, heap, and merge metrics use only `count` rows.

## `disp16`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 3,934,558 | 19.672790 | 19.494190–19.893590 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 3,934,558 | 19.672790 | 19.494190–19.893590 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 1,470,218 | 7.351090 | 7.347810–7.355700 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 1,467,914 | 7.339570 | 7.336290–7.344180 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 1,090,273 | 5.451365 | 5.448410–5.454745 | n/a | n/a | n/a | 2,688 | 0.013 | 0 | 0.932 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 3,800,740.3 | 19.003702 | 18.891510–19.209795 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 5,467,921 | 27.340 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 5,464,729 | 27.324 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 4,898,949 | 24.495 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 4,501,950 | 22.510 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 6,243,395 | 31.217 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 5,354,564 | 26.773 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `disp16`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 22,080,718.3 | 22.080718 | 22.052331–22.100226 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 22,080,718.3 | 22.080718 | 22.052331–22.100226 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 11,956,757.3 | 11.956757 | 7.340364–21.188169 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 7,338,199.3 | 7.338199 | 7.337103–7.339435 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 5,542,066 | 5.542066 | 5.541084–5.543960 | n/a | n/a | n/a | 2,712 | 0.003 | 0 | 0.753 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 21,220,226.7 | 21.220227 | 21.182755–21.278978 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 26,133,828 | 26.134 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 26,236,103 | 26.236 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 24,788,154 | 24.788 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 21,893,761 | 21.894 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 31,435,611 | 31.436 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 24,102,542 | 24.103 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct1`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 455,819 | 2.279095 | 2.268850–2.288915 | n/a | n/a | n/a | 32,768 | 0.164 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 455,819 | 2.279095 | 2.268850–2.288915 | n/a | n/a | n/a | 32,768 | 0.164 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 2,854,123.7 | 14.270618 | 1.699745–39.406480 | n/a | n/a | n/a | 10,288 | 0.051 | 0 | 3.570 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 3,230,540.3 | 16.152702 | 16.097305–16.208915 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 333,738.3 | 1.668692 | 1.664500–1.673705 | n/a | n/a | n/a | 10,288 | 0.051 | 0 | 5.359 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 7,819,585.7 | 39.097928 | 38.914950–39.374600 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 464,073 | 2.320 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 455,420 | 2.277 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 807,627 | 4.038 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 2,563,670 | 12.818 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 738,009 | 3.690 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 9,073,398 | 45.367 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct1`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 2,348,059.7 | 2.348060 | 2.323315–2.369688 | n/a | n/a | n/a | 393,216 | 0.393 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 2,348,059.7 | 2.348060 | 2.323315–2.369688 | n/a | n/a | n/a | 393,216 | 0.393 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 1,882,341.7 | 1.882342 | 1.877881–1.885222 | n/a | n/a | n/a | 42,688 | 0.043 | 0 | 6.522 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 18,344,823.3 | 18.344823 | 18.338656–18.352596 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 1,875,960.7 | 1.875961 | 1.871497–1.878844 | n/a | n/a | n/a | 42,688 | 0.043 | 0 | 6.522 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 43,627,017 | 43.627017 | 43.554119–43.677955 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 2,903,372 | 2.903 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 2,849,521 | 2.850 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 5,023,314 | 5.023 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 14,652,236 | 14.652 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 4,858,937 | 4.859 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 51,821,469 | 51.821 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct10`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 1,111,572.7 | 5.557863 | 5.361650–5.661965 | n/a | n/a | n/a | 480,832 | 2.404 | 0 | 5.485 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 4,625,263.3 | 23.126317 | 22.741925–23.564040 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 4,488,569.3 | 22.442847 | 22.120905–22.879535 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 3,364,938.7 | 16.824693 | 16.808210–16.833060 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 1,131,733.3 | 5.658667 | 5.654555–5.666250 | n/a | n/a | n/a | 82,472 | 0.412 | 0 | 6.580 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 4,482,363 | 22.411815 | 22.089880–22.848480 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 3,813,596 | 19.068 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 6,042,806 | 30.214 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 6,686,319 | 33.432 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 3,781,614 | 18.908 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 4,045,510 | 20.228 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 6,467,395 | 32.337 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct10`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 5,993,848 | 5.993848 | 5.760023–6.110983 | n/a | n/a | n/a | 2,241,568 | 2.242 | 0 | 6.316 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 26,856,601.3 | 26.856601 | 26.340812–27.216739 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 25,871,302.7 | 25.871303 | 25.300901–26.209668 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 19,427,759.3 | 19.427759 | 19.423125–19.432441 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 6,177,906.3 | 6.177906 | 6.175881–6.180586 | n/a | n/a | n/a | 402,872 | 0.403 | 0 | 7.685 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 25,865,094.3 | 25.865094 | 25.294699–26.203447 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 17,715,269 | 17.715 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 32,372,720 | 32.373 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 36,043,154 | 36.043 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 23,929,214 | 23.929 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 22,293,752 | 22.294 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 36,089,753 | 36.090 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct2`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 519,991.7 | 2.599958 | 2.586340–2.615010 | n/a | n/a | n/a | 98,304 | 0.492 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 519,991.7 | 2.599958 | 2.586340–2.615010 | n/a | n/a | n/a | 98,304 | 0.492 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 6,421,508.7 | 32.107543 | 31.921340–32.369580 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 3,257,710 | 16.288550 | 16.232690–16.327475 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 505,420.3 | 2.527102 | 2.509770–2.540110 | n/a | n/a | n/a | 18,256 | 0.091 | 0 | 5.835 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 6,415,152.3 | 32.075762 | 31.889535–32.337815 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 613,970 | 3.070 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 647,331 | 3.237 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 6,282,633 | 31.413 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 2,831,749 | 14.159 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 1,337,215 | 6.686 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 6,387,572 | 31.938 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct2`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 2,700,033.3 | 2.700033 | 2.680316–2.720049 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 2,700,033.3 | 2.700033 | 2.680316–2.720049 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 36,231,000.3 | 36.231000 | 36.150507–36.318781 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 18,652,923.3 | 18.652923 | 18.639771–18.670777 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 2,979,572.7 | 2.979573 | 2.972743–2.986739 | n/a | n/a | n/a | 82,736 | 0.083 | 0 | 6.954 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 36,224,633.7 | 36.224634 | 36.144137–36.312418 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 4,113,968 | 4.114 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 4,202,271 | 4.202 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 35,326,254 | 35.326 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 16,578,836 | 16.579 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 7,180,676 | 7.181 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 30,698,866 | 30.699 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct3`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 583,868.7 | 2.919343 | 2.898315–2.946220 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 583,868.7 | 2.919343 | 2.898315–2.946220 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 5,630,996.3 | 28.154982 | 27.997450–28.345450 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 3,278,743.3 | 16.393717 | 16.388175–16.398580 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 655,889 | 3.279445 | 3.271245–3.286040 | n/a | n/a | n/a | 26,424 | 0.132 | 0 | 6.052 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 5,624,663 | 28.123315 | 27.965790–28.313820 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 818,976 | 4.095 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 840,209 | 4.201 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 5,004,464 | 25.022 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 3,014,342 | 15.072 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 1,964,951 | 9.825 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 5,237,883 | 26.189 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct3`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 3,102,158 | 3.102158 | 3.094781–3.115504 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 3,102,158 | 3.102158 | 3.094781–3.115504 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 32,453,290 | 32.453290 | 32.149828–32.699276 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 18,834,432.7 | 18.834433 | 18.825735–18.840438 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 3,821,066 | 3.821066 | 3.818840–3.822630 | n/a | n/a | n/a | 123,704 | 0.124 | 0 | 7.134 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 32,446,944.7 | 32.446945 | 32.143484–32.692924 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 4,805,040 | 4.805 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 4,852,502 | 4.853 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 27,774,976 | 27.775 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 16,157,646 | 16.158 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 10,676,202 | 10.676 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 32,270,717 | 32.271 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct4`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 645,590 | 3.227950 | 3.216295–3.238890 | n/a | n/a | n/a | 544,480 | 2.722 | 0 | 2.627 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 5,573,263 | 27.866315 | 26.660885–29.143890 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 5,308,068 | 26.540340 | 26.238925–27.102485 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 3,300,005.3 | 16.500027 | 16.482845–16.514610 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 771,910.7 | 3.859553 | 3.846000–3.876460 | n/a | n/a | n/a | 34,472 | 0.172 | 0 | 6.174 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 5,301,754.7 | 26.508773 | 26.207345–27.070950 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 1,497,854 | 7.489 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 5,130,681 | 25.653 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 5,193,117 | 25.966 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 2,828,690 | 14.143 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 2,373,118 | 11.866 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 4,418,290 | 22.091 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct4`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 3,420,439 | 3.420439 | 3.407277–3.429134 | n/a | n/a | n/a | 2,620,768 | 2.621 | 0 | 2.942 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 30,438,548 | 30.438548 | 29.711028–31.748949 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 31,091,566.7 | 31.091567 | 31.024914–31.178793 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 18,992,386.7 | 18.992387 | 18.984375–18.997517 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 4,418,967.7 | 4.418968 | 4.416043–4.420638 | n/a | n/a | n/a | 164,072 | 0.164 | 0 | 7.242 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 31,085,240.7 | 31.085241 | 31.018591–31.172469 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 9,789,606 | 9.790 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 28,153,810 | 28.154 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 31,165,388 | 31.165 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 19,395,058 | 19.395 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 13,744,431 | 13.744 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 33,287,838 | 33.288 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct5`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 734,055.7 | 3.670278 | 3.647675–3.690625 | n/a | n/a | n/a | 779,320 | 3.897 | 0 | 3.620 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 5,131,612.7 | 25.658063 | 25.037190–26.109985 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 5,081,550.7 | 25.407753 | 24.937620–26.147980 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 3,314,183 | 16.570915 | 16.554535–16.589240 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 862,778 | 4.313890 | 4.296360–4.327115 | n/a | n/a | n/a | 42,312 | 0.212 | 0 | 6.259 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 5,075,258.3 | 25.376292 | 24.906145–26.116565 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 1,991,501 | 9.958 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 4,619,499 | 23.097 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 5,104,144 | 25.521 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 3,356,997 | 16.785 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 2,723,379 | 13.617 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 4,982,989 | 24.915 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct5`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 3,923,077.3 | 3.923077 | 3.918819–3.929988 | n/a | n/a | n/a | 3,764,416 | 3.764 | 0 | 4.096 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 29,885,268.3 | 29.885268 | 29.388778–30.576090 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 29,612,948 | 29.612948 | 29.499648–29.673636 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 19,097,004.7 | 19.097005 | 19.092229–19.101950 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 4,856,337 | 4.856337 | 4.848457–4.861131 | n/a | n/a | n/a | 203,736 | 0.204 | 0 | 7.325 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 29,606,648.7 | 29.606649 | 29.493348–29.667331 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 10,686,372 | 10.686 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 28,398,523 | 28.399 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 29,707,335 | 29.707 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 18,471,806 | 18.472 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 13,791,497 | 13.791 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 31,433,246 | 31.433 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct6`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 817,412.7 | 4.087063 | 4.078255–4.104120 | n/a | n/a | n/a | 635,520 | 3.178 | 0 | 4.449 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 5,303,117 | 26.515585 | 26.358930–26.736350 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 4,812,843.7 | 24.064218 | 23.829490–24.392250 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 3,329,976.7 | 16.649883 | 16.637275–16.664750 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 935,754.3 | 4.678772 | 4.670570–4.685135 | n/a | n/a | n/a | 50,288 | 0.251 | 0 | 6.330 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 4,806,569.3 | 24.032847 | 23.798095–24.360930 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 2,316,207 | 11.581 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 5,441,772 | 27.209 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 5,252,123 | 26.261 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 2,997,263 | 14.986 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 2,518,593 | 12.593 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 4,984,397 | 24.922 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct6`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 4,397,440.7 | 4.397441 | 4.390286–4.407005 | n/a | n/a | n/a | 3,113,144 | 3.113 | 0 | 5.041 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 30,747,336.3 | 30.747336 | 30.198898–31.195515 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 28,011,373 | 28.011373 | 27.927788–28.130671 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 19,179,843.3 | 19.179843 | 19.177552–19.183325 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 5,202,647.3 | 5.202647 | 5.197059–5.212521 | n/a | n/a | n/a | 243,056 | 0.243 | 0 | 7.400 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 28,005,092 | 28.005092 | 27.921496–28.124405 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 12,618,319 | 12.618 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 34,474,184 | 34.474 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 33,770,458 | 33.770 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 21,298,063 | 21.298 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 15,857,927 | 15.858 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 31,585,632 | 31.586 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct7`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 883,097.7 | 4.415488 | 4.413175–4.417460 | n/a | n/a | n/a | 260,480 | 1.302 | 0 | 4.563 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 5,148,717 | 25.743585 | 24.175910–28.680210 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 4,799,846.7 | 23.999233 | 23.757275–24.170175 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 3,340,267.3 | 16.701337 | 16.688865–16.715685 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 996,628 | 4.983140 | 4.977145–4.990475 | n/a | n/a | n/a | 58,104 | 0.291 | 0 | 6.396 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 4,793,589.3 | 23.967947 | 23.726000–24.138915 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 2,945,040 | 14.725 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 5,789,483 | 28.947 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 5,119,274 | 25.596 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 3,639,409 | 18.197 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 3,341,433 | 16.707 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 6,088,264 | 30.441 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct7`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 4,761,336.7 | 4.761337 | 4.760461–4.762799 | n/a | n/a | n/a | 1,279,344 | 1.279 | 0 | 5.241 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 27,796,013.3 | 27.796013 | 27.275934–28.750308 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 27,138,744.3 | 27.138744 | 26.657977–27.709209 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 19,257,316.3 | 19.257316 | 19.255977–19.258186 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 5,493,379.3 | 5.493379 | 5.492544–5.494223 | n/a | n/a | n/a | 283,184 | 0.283 | 0 | 7.472 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 27,132,478 | 27.132478 | 26.651708–27.702931 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 15,266,633 | 15.267 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 27,149,786 | 27.150 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 33,425,988 | 33.426 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 21,670,227 | 21.670 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 17,468,981 | 17.469 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 30,431,248 | 30.431 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct8`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 946,776 | 4.733880 | 4.723580–4.745005 | n/a | n/a | n/a | 373,816 | 1.869 | 0 | 4.986 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 5,029,288 | 25.146440 | 24.438380–25.898075 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 4,771,673.3 | 23.858367 | 23.599990–24.125490 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 3,350,079.3 | 16.750397 | 16.728570–16.764425 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 1,046,595.3 | 5.232977 | 5.226460–5.243400 | n/a | n/a | n/a | 66,264 | 0.331 | 0 | 6.458 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 4,765,436.7 | 23.827183 | 23.568780–24.094315 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 3,241,933 | 16.210 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 6,205,857 | 31.029 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 6,218,731 | 31.094 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 3,789,803 | 18.949 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 3,543,032 | 17.715 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 6,368,779 | 31.844 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct8`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 5,107,130.3 | 5.107130 | 5.102273–5.113520 | n/a | n/a | n/a | 1,686,552 | 1.687 | 0 | 5.699 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 29,224,259.7 | 29.224260 | 28.230444–31.200465 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 27,259,124 | 27.259124 | 26.898125–27.564843 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 19,319,450.3 | 19.319450 | 19.317094–19.322491 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 5,746,751.7 | 5.746752 | 5.744644–5.748414 | n/a | n/a | n/a | 323,272 | 0.323 | 0 | 7.544 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 27,252,874.7 | 27.252875 | 26.891889–27.558591 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 16,839,944 | 16.840 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 34,123,982 | 34.124 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 33,570,817 | 33.571 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 22,760,420 | 22.760 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 19,755,487 | 19.755 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 33,652,468 | 33.652 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct9`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 1,013,813 | 5.069065 | 5.040370–5.114875 | n/a | n/a | n/a | 436,104 | 2.181 | 0 | 5.264 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 4,950,683.3 | 24.753417 | 24.282600–25.166390 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 4,626,326 | 23.131630 | 22.761895–23.350390 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 3,357,957.7 | 16.789788 | 16.771135–16.804605 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 1,092,952.3 | 5.464762 | 5.462190–5.468725 | n/a | n/a | n/a | 74,408 | 0.372 | 0 | 6.520 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 4,620,108 | 23.100540 | 22.730785–23.319300 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 2,862,384 | 14.312 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 5,346,351 | 26.732 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 5,282,909 | 26.415 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 3,407,606 | 17.038 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 3,248,705 | 16.244 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 5,281,034 | 26.405 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `outpct9`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 5,587,657.3 | 5.587657 | 5.453333–5.855870 | n/a | n/a | n/a | 2,004,384 | 2.004 | 0 | 6.049 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 28,425,793 | 28.425793 | 26.961159–29.489718 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 26,477,690.7 | 26.477691 | 25.493261–27.297559 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 19,377,211.7 | 19.377212 | 19.373979–19.381092 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 5,969,277.7 | 5.969278 | 5.965352–5.971294 | n/a | n/a | n/a | 362,632 | 0.363 | 0 | 7.614 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 26,471,464.3 | 26.471464 | 25.487037–27.291319 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 18,117,372 | 18.117 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 33,786,398 | 33.786 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 32,843,445 | 32.843 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 21,728,707 | 21.729 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 19,964,340 | 19.964 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 37,585,517 | 37.586 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `random`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 4,337,463.7 | 21.687318 | 21.489380–21.855995 | 16.166996 | 5.520322 | +34.146% | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 4,337,463.7 | 21.687318 | 21.489380–21.855995 | 16.166996 | 5.520322 | +34.146% | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 4,270,215.7 | 21.351078 | 20.981345–22.079810 | 16.166996 | 5.184082 | +32.066% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 3,442,826.3 | 17.214132 | 17.210845–17.216830 | 16.166996 | 1.047136 | +6.477% | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 3,257,801.7 | 16.289008 | 16.287140–16.291665 | 16.166996 | 0.122012 | +0.755% | 802,304 | 4.012 | 0 | 11.960 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 4,264,831.7 | 21.324158 | 20.954620–22.052760 | 16.166996 | 5.157162 | +31.899% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 11,435,435 | 57.177 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 12,098,769 | 60.494 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 12,260,328 | 61.302 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 14,672,885 | 73.364 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 17,469,386 | 87.347 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 12,371,240 | 61.856 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `random`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 24,518,646 | 24.518646 | 23.911361–25.146518 | 18.488885 | 6.029761 | +32.613% | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 24,518,646 | 24.518646 | 23.911361–25.146518 | 18.488885 | 6.029761 | +32.613% | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 24,371,244 | 24.371244 | 23.879591–25.232106 | 18.488885 | 5.882359 | +31.816% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 19,951,468.7 | 19.951469 | 19.950657–19.952875 | 18.488885 | 1.462584 | +7.911% | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 18,598,999.3 | 18.598999 | 18.598163–18.599699 | 18.488885 | 0.110115 | +0.596% | 4,002,304 | 4.002 | 0 | 13.968 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 24,365,873.3 | 24.365873 | 23.874223–25.226718 | 18.488885 | 5.876989 | +31.787% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 73,232,249 | 73.232 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 72,956,663 | 72.957 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 63,888,060 | 63.888 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 90,367,700 | 90.368 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 101,533,404 | 101.5 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 70,266,383 | 70.266 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `reversed`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 3,239,029 | 16.195145 | 16.195145–16.195145 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 3,239,029 | 16.195145 | 16.195145–16.195145 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 204,351 | 1.021755 | 1.021755–1.021755 | n/a | n/a | n/a | 2,304 | 0.012 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 1,678,818 | 8.394090 | 8.394090–8.394090 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 199,999 | 0.999995 | 0.999995–0.999995 | n/a | n/a | n/a | 2,304 | 0.012 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 3,232,778 | 16.163890 | 16.163890–16.163890 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 1,168,530 | 5.843 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 1,157,133 | 5.786 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 131,681 | 0.658 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 2,307,762 | 11.539 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 94,112 | 0.471 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 1,100,165 | 5.501 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `reversed`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 18,162,333 | 18.162333 | 18.162333–18.162333 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 18,162,333 | 18.162333 | 18.162333–18.162333 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 1,004,351 | 1.004351 | 1.004351–1.004351 | n/a | n/a | n/a | 2,304 | 0.002 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 9,413,019 | 9.413019 | 9.413019–9.413019 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 2,304 | 0.002 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 18,131,082 | 18.131082 | 18.131082–18.131082 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 6,775,958 | 6.776 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 7,094,278 | 7.094 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 970,628 | 0.971 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 14,430,852 | 14.431 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 949,515 | 0.950 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 6,390,202 | 6.390 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `sorted`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 199,999 | 0.999995 | 0.999995–0.999995 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 199,999 | 0.999995 | 0.999995–0.999995 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 200,255 | 1.001275 | 1.001275–1.001275 | n/a | n/a | n/a | 2,304 | 0.012 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 199,999 | 0.999995 | 0.999995–0.999995 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 199,999 | 0.999995 | 0.999995–0.999995 | n/a | n/a | n/a | 2,304 | 0.012 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 4,526,699 | 22.633495 | 22.633495–22.633495 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 128,442 | 0.642 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 131,622 | 0.658 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 60,704 | 0.304 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 88,130 | 0.441 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 65,043 | 0.325 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 1,413,542 | 7.068 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `sorted`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 1,000,255 | 1.000255 | 1.000255–1.000255 | n/a | n/a | n/a | 2,304 | 0.002 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 2,304 | 0.002 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 25,604,781 | 25.604781 | 25.604781–25.604781 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 914,986 | 0.915 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 869,250 | 0.869 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 728,305 | 0.728 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 751,487 | 0.751 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 737,880 | 0.738 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 10,462,975 | 10.463 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `tail10`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 852,432.3 | 4.262162 | 4.256745–4.267885 | n/a | n/a | n/a | 335,208 | 1.676 | 0 | 2.188 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 4,769,519.7 | 23.847598 | 22.814105–25.041685 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 644,627 | 3.223135 | 3.217070–3.228740 | n/a | n/a | n/a | 159,936 | 0.800 | 0 | 1.875 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 2,206,053.3 | 11.030267 | 11.029920–11.030460 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 638,332.7 | 3.191663 | 3.185625–3.197280 | n/a | n/a | n/a | 159,936 | 0.800 | 0 | 1.875 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 4,585,582.3 | 22.927912 | 21.891985–24.184315 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 2,043,107 | 10.216 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 5,625,172 | 28.126 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 1,645,657 | 8.228 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 3,501,791 | 17.509 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 1,721,241 | 8.606 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 4,877,153 | 24.386 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

## `tail10`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 3 | 4,492,470 | 4.492470 | 4.474139–4.507284 | n/a | n/a | n/a | 1,466,032 | 1.466 | 0 | 2.442 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 3 | 27,654,415.7 | 27.654416 | 26.325770–29.041557 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 3 | 3,425,898.7 | 3.425899 | 3.407744–3.438702 | n/a | n/a | n/a | 722,424 | 0.722 | 0 | 2.073 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 3 | 12,832,671.7 | 12.832672 | 12.832250–12.833284 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 3 | 3,419,602.3 | 3.419602 | 3.401452–3.432409 | n/a | n/a | n/a | 722,424 | 0.722 | 0 | 2.073 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 3 | 26,802,598 | 26.802598 | 25.173361–28.727344 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_route` | 63 | 11,175,882 | 11.176 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `deletion_backbone_sort` | 63 | 30,274,947 | 30.275 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `hybrid_inversion_gate` | 63 | 9,764,526 | 9.765 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `inversion_binsert` | 63 | 21,935,719 | 21.936 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `powersort` | 63 | 9,550,245 | 9.550 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
| `std_sort` | 63 | 29,004,235 | 29.004 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-route-v2` |
