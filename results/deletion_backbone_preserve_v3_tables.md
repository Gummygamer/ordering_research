# Deletion-backbone prefix preservation v3

Aggregated 13,860 validated rows from 2 CSV file(s). Each row below is grouped by algorithm, distribution, n, and mode. Comparison and merge-span metrics are arithmetic means, timing metrics are medians, and memory bounds/peaks are maxima.

Build IDs: `backbone-preserve-v3`.

For random permutations, comparison excess is `100 * (mean comparisons - lg(n!)) / lg(n!)`; it is reported as `n/a` for other distributions. Timing metrics use only `time` rows, while comparison, heap, and merge metrics use only `count` rows.

## `disp16`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 3,911,372.7 | 19.556863 | 19.513850–19.578775 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 3,911,372.7 | 19.556863 | 19.513850–19.578775 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 3,911,372.7 | 19.556863 | 19.513850–19.578775 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 1,469,963 | 7.349815 | 7.347885–7.352460 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 1,467,659 | 7.338295 | 7.336365–7.340940 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 1,090,299.7 | 5.451498 | 5.449400–5.452685 | n/a | n/a | n/a | 2,648 | 0.013 | 0 | 0.930 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 3,780,340.3 | 18.901702 | 18.884185–18.928680 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 4,990,303 | 24.952 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 4,658,161 | 23.291 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 4,895,618 | 24.478 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 4,487,664 | 22.438 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 4,697,724 | 23.489 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 6,014,910 | 30.075 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 4,716,478 | 23.582 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `disp16`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 22,087,488.7 | 22.087489 | 22.034685–22.116918 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 22,087,488.7 | 22.087489 | 22.034685–22.116918 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 22,087,488.7 | 22.087489 | 22.034685–22.116918 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 11,985,426.3 | 11.985426 | 7.342203–21.269325 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 7,340,410 | 7.340410 | 7.338884–7.342447 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 5,543,057.3 | 5.543057 | 5.542122–5.543753 | n/a | n/a | n/a | 2,752 | 0.003 | 0 | 0.755 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 21,253,650.7 | 21.253651 | 21.241414–21.263932 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 27,977,716 | 27.978 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 28,901,912 | 28.902 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 29,392,093 | 29.392 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 24,979,152 | 24.979 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 25,785,938 | 25.786 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 31,534,448 | 31.534 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 27,594,126 | 27.594 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct1`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 454,907.3 | 2.274537 | 2.271250–2.280250 | n/a | n/a | n/a | 32,768 | 0.164 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 454,907.3 | 2.274537 | 2.271250–2.280250 | n/a | n/a | n/a | 32,768 | 0.164 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 454,907.3 | 2.274537 | 2.271250–2.280250 | n/a | n/a | n/a | 32,768 | 0.164 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 2,807,120.7 | 14.035603 | 1.688705–38.721960 | n/a | n/a | n/a | 10,256 | 0.051 | 0 | 3.581 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 3,229,583 | 16.147915 | 16.103295–16.190780 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 332,734 | 1.663670 | 1.656795–1.669950 | n/a | n/a | n/a | 10,576 | 0.053 | 0 | 5.364 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 7,771,625 | 38.858125 | 38.690085–39.010995 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 494,457 | 2.472 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 505,924 | 2.530 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 492,886 | 2.464 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 821,027 | 4.105 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 2,755,599 | 13.778 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 721,603 | 3.608 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 8,619,463 | 43.097 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct1`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 2,347,192.3 | 2.347192 | 2.338252–2.356011 | n/a | n/a | n/a | 393,216 | 0.393 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 2,347,192.3 | 2.347192 | 2.338252–2.356011 | n/a | n/a | n/a | 393,216 | 0.393 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 2,347,192.3 | 2.347192 | 2.338252–2.356011 | n/a | n/a | n/a | 393,216 | 0.393 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 15,813,290.7 | 15.813291 | 1.887845–43.661554 | n/a | n/a | n/a | 42,464 | 0.042 | 0 | 4.346 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 18,347,527.3 | 18.347527 | 18.336258–18.357904 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 1,885,071.3 | 1.885071 | 1.881465–1.890217 | n/a | n/a | n/a | 42,464 | 0.042 | 0 | 6.522 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 43,633,319 | 43.633319 | 43.551733–43.693046 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 3,035,933 | 3.036 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 3,140,959 | 3.141 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 3,169,047 | 3.169 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 4,500,423 | 4.500 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 15,235,375 | 15.235 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 4,343,017 | 4.343 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 48,176,746 | 48.177 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct10`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 1,219,819.3 | 6.099097 | 6.089580–6.112390 | n/a | n/a | n/a | 664,208 | 3.321 | 0 | 4.409 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 1,108,856.7 | 5.544283 | 5.270390–5.693230 | n/a | n/a | n/a | 497,872 | 2.489 | 0 | 5.502 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 4,648,077.7 | 23.240388 | 23.101610–23.507555 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 4,476,524 | 22.382620 | 22.321320–22.429205 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 3,362,549 | 16.812745 | 16.803495–16.818075 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 1,130,817 | 5.654085 | 5.639310–5.662750 | n/a | n/a | n/a | 83,120 | 0.416 | 0 | 6.580 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 4,470,314 | 22.351570 | 22.290255–22.398245 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 3,058,029 | 15.290 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 3,369,868 | 16.849 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 5,460,921 | 27.305 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 5,312,609 | 26.563 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 3,835,363 | 19.177 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 3,792,984 | 18.965 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 6,131,786 | 30.659 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct10`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 6,617,980 | 6.617980 | 6.560995–6.731723 | n/a | n/a | n/a | 3,167,608 | 3.168 | 0 | 5.148 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 6,112,032.3 | 6.112032 | 6.109037–6.115346 | n/a | n/a | n/a | 2,241,152 | 2.241 | 0 | 6.321 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 27,140,129.7 | 27.140130 | 27.071937–27.267141 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 26,061,354 | 26.061354 | 25.934248–26.202361 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 19,429,166 | 19.429166 | 19.426523–19.433613 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 6,177,164 | 6.177164 | 6.175215–6.178650 | n/a | n/a | n/a | 402,792 | 0.403 | 0 | 7.684 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 26,055,146.7 | 26.055147 | 25.928040–26.196159 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 17,280,906 | 17.281 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 19,026,592 | 19.027 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 32,946,815 | 32.947 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 35,257,338 | 35.257 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 22,759,019 | 22.759 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 19,096,329 | 19.096 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 34,746,992 | 34.747 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct2`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 519,277 | 2.596385 | 2.579010–2.628475 | n/a | n/a | n/a | 98,304 | 0.492 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 519,277 | 2.596385 | 2.579010–2.628475 | n/a | n/a | n/a | 98,304 | 0.492 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 519,277 | 2.596385 | 2.579010–2.628475 | n/a | n/a | n/a | 98,304 | 0.492 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 6,345,929 | 31.729645 | 31.578285–31.811065 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 3,255,950 | 16.279750 | 16.255975–16.303285 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 505,392.7 | 2.526963 | 2.521090–2.536490 | n/a | n/a | n/a | 18,712 | 0.094 | 0 | 5.831 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 6,339,569.7 | 31.697848 | 31.546535–31.779255 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 717,750 | 3.589 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 682,638 | 3.413 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 691,041 | 3.455 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 6,081,405 | 30.407 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 2,781,626 | 13.908 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 1,294,804 | 6.474 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 5,848,472 | 29.242 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct2`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 2,705,656.7 | 2.705657 | 2.681447–2.719210 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 2,705,656.7 | 2.705657 | 2.681447–2.719210 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 2,705,656.7 | 2.705657 | 2.681447–2.719210 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 25,101,969.7 | 25.101970 | 2.986848–36.195830 | n/a | n/a | n/a | 81,496 | 0.081 | 0 | 2.318 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 18,665,964.3 | 18.665964 | 18.657542–18.678960 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 2,977,438.3 | 2.977438 | 2.970198–2.986592 | n/a | n/a | n/a | 82,328 | 0.082 | 0 | 6.955 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 36,182,421 | 36.182421 | 36.116866–36.240928 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 4,026,420 | 4.026 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 4,242,874 | 4.243 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 4,049,011 | 4.049 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 34,036,982 | 34.037 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 16,257,606 | 16.258 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 7,328,930 | 7.329 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 31,699,698 | 31.700 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct3`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 591,566.3 | 2.957832 | 2.899760–3.005580 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 591,566.3 | 2.957832 | 2.899760–3.005580 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 591,566.3 | 2.957832 | 2.899760–3.005580 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 5,586,891.3 | 27.934457 | 27.877255–28.047315 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 3,278,867 | 16.394335 | 16.367345–16.411335 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 657,070 | 3.285350 | 3.265285–3.302495 | n/a | n/a | n/a | 26,480 | 0.132 | 0 | 6.053 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 5,580,553.7 | 27.902768 | 27.845610–28.015605 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 890,174 | 4.451 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 910,438 | 4.552 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 931,206 | 4.656 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 5,245,527 | 26.228 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 2,962,083 | 14.810 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 2,101,957 | 10.510 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 6,039,408 | 30.197 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct3`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 3,101,320 | 3.101320 | 3.078311–3.122762 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 3,101,320 | 3.101320 | 3.078311–3.122762 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 3,101,320 | 3.101320 | 3.078311–3.122762 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 22,881,286.7 | 22.881287 | 3.823244–32.477330 | n/a | n/a | n/a | 121,680 | 0.122 | 0 | 2.379 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 18,837,183.7 | 18.837184 | 18.831181–18.844084 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 3,815,974.7 | 3.815975 | 3.808194–3.822988 | n/a | n/a | n/a | 122,008 | 0.122 | 0 | 7.134 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 32,392,669 | 32.392669 | 32.336952–32.470982 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 5,259,522 | 5.260 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 4,730,805 | 4.731 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 5,162,147 | 5.162 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 25,333,714 | 25.334 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 18,588,789 | 18.589 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 9,516,539 | 9.517 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 28,836,457 | 28.836 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct4`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 692,858.7 | 3.464293 | 3.455170–3.478405 | n/a | n/a | n/a | 459,592 | 2.298 | 0 | 1.026 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 646,248.7 | 3.231243 | 3.215670–3.239950 | n/a | n/a | n/a | 539,408 | 2.697 | 0 | 2.623 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 5,372,536.7 | 26.862683 | 26.375895–27.652345 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 5,235,188 | 26.175940 | 26.065705–26.358900 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 3,297,794 | 16.488970 | 16.483275–16.494555 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 774,296.3 | 3.871482 | 3.863400–3.877840 | n/a | n/a | n/a | 34,584 | 0.173 | 0 | 6.174 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 5,228,869.3 | 26.144347 | 26.034075–26.327245 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 1,311,732 | 6.559 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 1,661,082 | 8.305 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 4,406,739 | 22.034 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 4,402,497 | 22.012 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 3,162,492 | 15.812 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 2,367,917 | 11.840 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 5,156,514 | 25.783 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct4`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 3,747,947.7 | 3.747948 | 3.730495–3.767848 | n/a | n/a | n/a | 2,147,784 | 2.148 | 0 | 1.239 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 3,410,122.7 | 3.410123 | 3.405416–3.414409 | n/a | n/a | n/a | 2,604,064 | 2.604 | 0 | 2.926 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 30,766,757.3 | 30.766757 | 29.611529–31.378794 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 30,951,938.7 | 30.951939 | 30.785435–31.232249 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 18,993,815.7 | 18.993816 | 18.986827–18.997730 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 4,414,065.3 | 4.414065 | 4.408904–4.418785 | n/a | n/a | n/a | 162,392 | 0.162 | 0 | 7.241 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 30,945,618.7 | 30.945619 | 30.779117–31.225926 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 6,653,471 | 6.653 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 8,997,777 | 8.998 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 26,161,122 | 26.161 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 28,812,418 | 28.812 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 17,403,063 | 17.403 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 11,917,343 | 11.917 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 28,335,475 | 28.335 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct5`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 791,082.3 | 3.955412 | 3.921900–4.006430 | n/a | n/a | n/a | 709,304 | 3.547 | 0 | 2.036 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 731,973 | 3.659865 | 3.656800–3.663350 | n/a | n/a | n/a | 805,872 | 4.029 | 0 | 3.642 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 5,165,132.3 | 25.825662 | 25.673305–25.980260 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 4,976,239 | 24.881195 | 24.805630–24.932565 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 3,313,781.3 | 16.568907 | 16.557325–16.577025 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 863,652.3 | 4.318262 | 4.303540–4.332530 | n/a | n/a | n/a | 42,872 | 0.214 | 0 | 6.260 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 4,969,938.7 | 24.849693 | 24.774215–24.901010 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 1,478,894 | 7.394 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 1,781,415 | 8.907 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 4,356,769 | 21.784 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 4,725,086 | 23.625 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 3,021,841 | 15.109 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 2,434,575 | 12.173 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 4,474,853 | 22.374 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct5`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 4,325,588.7 | 4.325589 | 4.293319–4.358945 | n/a | n/a | n/a | 3,396,856 | 3.397 | 0 | 2.428 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 3,918,164.7 | 3.918165 | 3.914705–3.920051 | n/a | n/a | n/a | 3,767,176 | 3.767 | 0 | 4.096 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 30,187,552 | 30.187552 | 29.762668–30.671313 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 29,566,150.3 | 29.566150 | 29.263308–29.718226 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 19,098,065.7 | 19.098066 | 19.092431–19.100939 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 4,849,320.7 | 4.849321 | 4.845302–4.854673 | n/a | n/a | n/a | 202,296 | 0.202 | 0 | 7.324 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 29,559,848 | 29.559848 | 29.257004–29.711920 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 10,004,349 | 10.004 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 11,954,236 | 11.954 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 30,934,304 | 30.934 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 30,192,038 | 30.192 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 18,521,603 | 18.522 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 15,070,267 | 15.070 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 32,614,890 | 32.615 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct6`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 923,675 | 4.618375 | 4.580450–4.656205 | n/a | n/a | n/a | 883,976 | 4.420 | 0 | 2.692 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 814,176.7 | 4.070883 | 4.062885–4.081550 | n/a | n/a | n/a | 651,792 | 3.259 | 0 | 4.456 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 5,180,869.7 | 25.904348 | 24.718935–27.678150 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 4,766,584 | 23.832920 | 23.777715–23.883510 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 3,326,910.3 | 16.634552 | 16.621195–16.642550 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 935,960 | 4.679800 | 4.668980–4.686945 | n/a | n/a | n/a | 50,936 | 0.255 | 0 | 6.333 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 4,760,301 | 23.801505 | 23.746260–23.852180 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 1,850,133 | 9.251 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 2,126,154 | 10.631 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 4,663,836 | 23.319 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 5,320,665 | 26.603 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 3,272,965 | 16.365 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 2,539,497 | 12.697 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 4,572,536 | 22.863 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct6`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 5,028,230.7 | 5.028231 | 5.010975–5.040527 | n/a | n/a | n/a | 4,240,640 | 4.241 | 0 | 3.177 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 4,396,593 | 4.396593 | 4.389119–4.400595 | n/a | n/a | n/a | 3,005,216 | 3.005 | 0 | 5.040 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 30,890,690.3 | 30.890690 | 30.260754–32.101013 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 27,790,831.3 | 27.790831 | 27.494658–27.983989 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 19,184,015.7 | 19.184016 | 19.179946–19.188792 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 5,205,712.3 | 5.205712 | 5.201021–5.211685 | n/a | n/a | n/a | 242,880 | 0.243 | 0 | 7.400 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 27,784,552 | 27.784552 | 27.488371–27.977712 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 12,899,939 | 12.900 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 13,591,135 | 13.591 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 34,006,270 | 34.006 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 32,266,840 | 32.267 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 19,748,178 | 19.748 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 15,945,174 | 15.945 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 29,757,737 | 29.758 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct7`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 1,120,969.3 | 5.604847 | 5.562815–5.640675 | n/a | n/a | n/a | 876,984 | 4.385 | 0 | 3.156 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 880,536.7 | 4.402683 | 4.388120–4.411050 | n/a | n/a | n/a | 295,808 | 1.479 | 0 | 4.588 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 4,873,115.7 | 24.365578 | 24.117290–24.649445 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 4,714,860.7 | 23.574303 | 23.415510–23.814320 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 3,337,841 | 16.689205 | 16.685430–16.693190 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 994,503 | 4.972515 | 4.958680–4.984890 | n/a | n/a | n/a | 58,976 | 0.295 | 0 | 6.396 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 4,708,595 | 23.542975 | 23.384150–23.782965 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 2,734,958 | 13.675 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 2,767,501 | 13.838 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 5,968,969 | 29.845 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 6,312,822 | 31.564 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 3,572,944 | 17.865 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 3,240,378 | 16.202 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 5,591,680 | 27.958 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct7`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 5,510,267.7 | 5.510268 | 5.465544–5.575209 | n/a | n/a | n/a | 4,236,536 | 4.237 | 0 | 3.993 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 4,765,371.7 | 4.765372 | 4.763879–4.766566 | n/a | n/a | n/a | 1,291,816 | 1.292 | 0 | 5.246 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 28,322,485 | 28.322485 | 28.071340–28.537088 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 27,524,368 | 27.524368 | 27.058250–27.842034 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 19,261,662.3 | 19.261662 | 19.257530–19.268056 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 5,494,286 | 5.494286 | 5.490885–5.496561 | n/a | n/a | n/a | 282,744 | 0.283 | 0 | 7.473 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 27,518,106.7 | 27.518107 | 27.051989–27.835774 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 14,304,736 | 14.305 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 13,839,816 | 13.840 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 27,611,116 | 27.611 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 34,832,260 | 34.832 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 21,894,011 | 21.894 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 18,103,483 | 18.103 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 34,376,708 | 34.377 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct8`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 1,197,653.7 | 5.988268 | 5.983350–5.997140 | n/a | n/a | n/a | 788,032 | 3.940 | 0 | 3.513 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 945,190.7 | 4.725953 | 4.719395–4.734030 | n/a | n/a | n/a | 373,552 | 1.868 | 0 | 4.982 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 5,030,394 | 25.151970 | 24.759490–25.834885 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 4,708,304 | 23.541520 | 23.286720–23.842750 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 3,346,924 | 16.734620 | 16.724215–16.742755 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 1,044,935.7 | 5.224678 | 5.205530–5.234795 | n/a | n/a | n/a | 67,064 | 0.335 | 0 | 6.460 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 4,702,059 | 23.510295 | 23.255540–23.811500 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 2,640,374 | 13.202 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 2,839,526 | 14.198 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 5,244,328 | 26.222 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 5,203,317 | 26.017 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 3,294,692 | 16.473 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 3,178,073 | 15.890 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 5,390,700 | 26.953 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct8`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 5,859,924 | 5.859924 | 5.838146–5.871188 | n/a | n/a | n/a | 3,788,224 | 3.788 | 0 | 4.463 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 5,102,513.3 | 5.102513 | 5.098374–5.105399 | n/a | n/a | n/a | 1,691,304 | 1.691 | 0 | 5.713 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 30,051,666.3 | 30.051666 | 29.598365–30.392651 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 27,260,691.7 | 27.260692 | 26.577161–27.803351 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 19,324,526.7 | 19.324527 | 19.321509–19.327997 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 5,743,839.3 | 5.743839 | 5.738819–5.750035 | n/a | n/a | n/a | 322,920 | 0.323 | 0 | 7.543 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 27,254,450.3 | 27.254450 | 26.570927–27.797109 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 18,203,446 | 18.203 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 16,750,498 | 16.750 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 36,520,229 | 36.520 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 34,799,257 | 34.799 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 19,976,191 | 19.976 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 19,514,836 | 19.515 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 37,378,244 | 37.378 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct9`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 1,269,952 | 6.349760 | 6.335980–6.367925 | n/a | n/a | n/a | 719,560 | 3.598 | 0 | 3.806 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 1,009,220.7 | 5.046103 | 5.018895–5.086605 | n/a | n/a | n/a | 435,008 | 2.175 | 0 | 5.275 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 4,896,487 | 24.482435 | 24.067225–24.795595 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 4,648,060.7 | 23.240303 | 23.082080–23.415965 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 3,355,107.3 | 16.775537 | 16.763070–16.781795 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 1,090,257.7 | 5.451288 | 5.448085–5.453280 | n/a | n/a | n/a | 74,824 | 0.374 | 0 | 6.522 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 4,641,832.7 | 23.209163 | 23.051025–23.384800 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 3,002,204 | 15.011 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 3,800,878 | 19.004 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 6,668,634 | 33.343 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 5,714,748 | 28.574 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 3,700,381 | 18.502 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 3,271,661 | 16.358 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 6,388,963 | 31.945 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `outpct9`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 6,243,126.3 | 6.243126 | 6.207436–6.284073 | n/a | n/a | n/a | 3,440,440 | 3.440 | 0 | 4.833 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 5,445,656.3 | 5.445656 | 5.437189–5.454786 | n/a | n/a | n/a | 1,998,920 | 1.999 | 0 | 6.049 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 29,041,658.7 | 29.041659 | 28.532396–29.880972 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 27,095,580 | 27.095580 | 26.898352–27.389507 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 19,380,076.3 | 19.380076 | 19.379101–19.381710 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 5,965,932 | 5.965932 | 5.963666–5.967154 | n/a | n/a | n/a | 363,120 | 0.363 | 0 | 7.613 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 27,089,355.7 | 27.089356 | 26.892129–27.383281 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 17,142,962 | 17.143 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 17,296,101 | 17.296 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 38,251,721 | 38.252 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 38,567,359 | 38.567 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 23,063,368 | 23.063 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 17,671,790 | 17.672 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 33,421,934 | 33.422 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `random`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 4,248,871.3 | 21.244357 | 20.728965–21.544210 | 16.166996 | 5.077361 | +31.406% | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 4,248,871.3 | 21.244357 | 20.728965–21.544210 | 16.166996 | 5.077361 | +31.406% | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 4,248,871.3 | 21.244357 | 20.728965–21.544210 | 16.166996 | 5.077361 | +31.406% | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 4,227,287 | 21.136435 | 20.655985–21.446585 | 16.166996 | 4.969439 | +30.738% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 3,441,501 | 17.207505 | 17.206150–17.208805 | 16.166996 | 1.040509 | +6.436% | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 3,257,659.7 | 16.288298 | 16.286620–16.289610 | 16.166996 | 0.121302 | +0.750% | 802,288 | 4.011 | 0 | 11.959 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 4,221,903.7 | 21.109518 | 20.629025–21.419665 | 16.166996 | 4.942522 | +30.572% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 12,964,510 | 64.823 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 12,856,852 | 64.284 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 13,079,754 | 65.399 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 13,072,434 | 65.362 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 15,456,346 | 77.282 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 15,848,323 | 79.242 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 12,590,905 | 62.955 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `random`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 24,283,476.3 | 24.283476 | 24.035727–24.565440 | 18.488885 | 5.794592 | +31.341% | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 24,283,476.3 | 24.283476 | 24.035727–24.565440 | 18.488885 | 5.794592 | +31.341% | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 24,283,476.3 | 24.283476 | 24.035727–24.565440 | 18.488885 | 5.794592 | +31.341% | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 24,000,723 | 24.000723 | 23.692164–24.319036 | 18.488885 | 5.511838 | +29.812% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 19,953,853 | 19.953853 | 19.952679–19.954767 | 18.488885 | 1.464968 | +7.924% | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 18,598,216.3 | 18.598216 | 18.597942–18.598468 | 18.488885 | 0.109332 | +0.591% | 4,002,304 | 4.002 | 0 | 13.968 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 23,995,339.3 | 23.995339 | 23.686762–24.313688 | 18.488885 | 5.506455 | +29.783% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 67,546,878 | 67.547 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 65,800,779 | 65.801 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 71,183,673 | 71.184 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 71,266,886 | 71.267 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 91,223,769 | 91.224 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 91,870,712 | 91.871 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 69,870,335 | 69.870 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `reversed`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 3,239,029 | 16.195145 | 16.195145–16.195145 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 3,239,029 | 16.195145 | 16.195145–16.195145 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 3,239,029 | 16.195145 | 16.195145–16.195145 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 204,351 | 1.021755 | 1.021755–1.021755 | n/a | n/a | n/a | 2,304 | 0.012 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 1,678,818 | 8.394090 | 8.394090–8.394090 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 199,999 | 0.999995 | 0.999995–0.999995 | n/a | n/a | n/a | 2,304 | 0.012 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 3,232,778 | 16.163890 | 16.163890–16.163890 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 1,380,650 | 6.903 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 1,381,725 | 6.909 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 1,392,166 | 6.961 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 155,582 | 0.778 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 2,857,913 | 14.290 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 123,664 | 0.618 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 1,328,149 | 6.641 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `reversed`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 18,162,333 | 18.162333 | 18.162333–18.162333 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 18,162,333 | 18.162333 | 18.162333–18.162333 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 18,162,333 | 18.162333 | 18.162333–18.162333 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 1,004,351 | 1.004351 | 1.004351–1.004351 | n/a | n/a | n/a | 2,304 | 0.002 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 9,413,019 | 9.413019 | 9.413019–9.413019 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 2,304 | 0.002 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 18,131,082 | 18.131082 | 18.131082–18.131082 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 7,802,264 | 7.802 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 7,455,572 | 7.456 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 7,089,113 | 7.089 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 1,025,940 | 1.026 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 16,176,082 | 16.176 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 909,983 | 0.910 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 7,546,701 | 7.547 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `sorted`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 199,999 | 0.999995 | 0.999995–0.999995 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 199,999 | 0.999995 | 0.999995–0.999995 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 199,999 | 0.999995 | 0.999995–0.999995 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 200,255 | 1.001275 | 1.001275–1.001275 | n/a | n/a | n/a | 2,304 | 0.012 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 199,999 | 0.999995 | 0.999995–0.999995 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 199,999 | 0.999995 | 0.999995–0.999995 | n/a | n/a | n/a | 2,304 | 0.012 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 4,526,699 | 22.633495 | 22.633495–22.633495 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 151,027 | 0.755 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 161,982 | 0.810 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 150,444 | 0.752 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 102,334 | 0.512 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 92,237 | 0.461 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 75,748 | 0.379 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 1,670,945 | 8.355 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `sorted`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 1,000,255 | 1.000255 | 1.000255–1.000255 | n/a | n/a | n/a | 2,304 | 0.002 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 2,304 | 0.002 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 25,604,781 | 25.604781 | 25.604781–25.604781 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 950,314 | 0.950 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 918,605 | 0.919 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 954,955 | 0.955 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 733,811 | 0.734 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 734,388 | 0.734 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 706,550 | 0.707 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 9,626,524 | 9.627 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `tail10`, n=200,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 932,734 | 4.663670 | 4.647910–4.675480 | n/a | n/a | n/a | 235,104 | 1.176 | 0 | 0.517 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 849,913.3 | 4.249567 | 4.230255–4.261290 | n/a | n/a | n/a | 321,784 | 1.609 | 0 | 2.186 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 5,420,109.7 | 27.100548 | 22.307845–29.995185 | n/a | n/a | n/a | 196,608 | 0.983 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 640,670 | 3.203350 | 3.183780–3.216960 | n/a | n/a | n/a | 146,768 | 0.734 | 0 | 1.872 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 2,206,525 | 11.032625 | 11.032230–11.033060 | n/a | n/a | n/a | 800,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 634,382.7 | 3.171913 | 3.152330–3.185535 | n/a | n/a | n/a | 146,768 | 0.734 | 0 | 1.872 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 5,258,606.7 | 26.293033 | 21.409620–29.264315 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 2,200,345 | 11.002 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 2,425,506 | 12.128 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 6,040,650 | 30.203 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 1,668,361 | 8.342 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 3,259,015 | 16.295 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 1,937,933 | 9.690 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 6,317,219 | 31.586 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

## `tail10`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 3 | 5,014,606.3 | 5.014606 | 5.001859–5.029133 | n/a | n/a | n/a | 1,044,832 | 1.045 | 0 | 0.648 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 3 | 4,504,276.3 | 4.504276 | 4.497620–4.509560 | n/a | n/a | n/a | 1,468,416 | 1.468 | 0 | 2.443 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 3 | 28,003,925 | 28.003925 | 26.239847–30.779727 | n/a | n/a | n/a | 786,432 | 0.786 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 3 | 3,440,648 | 3.440648 | 3.439851–3.441057 | n/a | n/a | n/a | 723,576 | 0.724 | 0 | 2.074 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 3 | 12,833,530.7 | 12.833531 | 12.833252–12.833787 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 3 | 3,434,353 | 3.434353 | 3.433552–3.434754 | n/a | n/a | n/a | 723,576 | 0.724 | 0 | 2.074 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 3 | 27,054,358.3 | 27.054358 | 25.310965–29.801984 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `deletion_backbone_preserve` | 63 | 10,629,701 | 10.630 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_route` | 63 | 12,016,668 | 12.017 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `deletion_backbone_sort` | 63 | 29,420,087 | 29.420 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `hybrid_inversion_gate` | 63 | 9,561,295 | 9.561 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `inversion_binsert` | 63 | 19,628,700 | 19.629 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `powersort` | 63 | 9,107,196 | 9.107 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
| `std_sort` | 63 | 30,822,900 | 30.823 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`backbone-preserve-v3` |
