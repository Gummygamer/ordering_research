# Round-timing analysis: certified_portfolio_v1_screen_20261022.csv

Build: `certified-portfolio-v1`.

Excluded baselines: `radix_lsd`, `x86_simd`.
The complete unfiltered round schedule was validated before this comparison filter.

Times are median nanoseconds per element. Regret compares the candidate's median with the fastest baseline median within each input/seed. Bootstrap intervals resample complete rounds and reselect the fastest baseline in every resample. They describe sampling uncertainty in this run; dependence between rounds, CPU frequency drift, and host differences are not covered. Prior/new differences do not isolate timing-order effects.

| Input | n | Seed | Best baseline | Candidate ns/item | Regret | Round-bootstrap 95% interval | Prior regret |
|---|---:|---:|---|---:|---:|---:|---:|
| random | 200000 | 311 | ips4o | 20.03 | +2.33% | [+0.30%, +4.13%] | - |
| random | 200000 | 312 | ips4o | 19.48 | +0.70% | [-2.49%, +2.27%] | - |
| random | 1000000 | 311 | ips4o | 23.98 | +0.85% | [-3.99%, +12.03%] | - |
| random | 1000000 | 312 | ips4o | 24.26 | +1.25% | [-3.62%, +3.82%] | - |
| uniform64 | 200000 | 311 | ips4o | 22.89 | -0.17% | [-1.25%, +1.02%] | - |
| uniform64 | 200000 | 312 | ips4o | 22.04 | +0.54% | [-0.96%, +3.19%] | - |
| uniform64 | 1000000 | 311 | ips4o | 24.27 | -0.47% | [-6.68%, +2.66%] | - |
| uniform64 | 1000000 | 312 | ips4o | 22.91 | -1.97% | [-10.24%, +7.21%] | - |
| uniform32 | 200000 | 311 | ips4o | 20.41 | -4.74% | [-7.48%, +2.87%] | - |
| uniform32 | 200000 | 312 | ips4o | 20.99 | +0.33% | [-2.00%, +2.73%] | - |
| uniform32 | 1000000 | 311 | ips4o | 23.98 | -0.05% | [-12.58%, +4.11%] | - |
| uniform32 | 1000000 | 312 | ips4o | 25.74 | -0.89% | [-4.09%, +3.54%] | - |
| highbits32 | 200000 | 311 | ips4o | 22.58 | +1.82% | [-3.71%, +3.54%] | - |
| highbits32 | 200000 | 312 | ips4o | 23.71 | -0.28% | [-2.86%, +4.72%] | - |
| highbits32 | 1000000 | 311 | ips4o | 25.97 | +2.31% | [-5.05%, +7.19%] | - |
| highbits32 | 1000000 | 312 | ips4o | 23.62 | -0.59% | [-2.85%, +1.93%] | - |
| sorted | 200000 | 311 | ips4o | 0.40 | +11.69% | [+4.23%, +22.34%] | - |
| sorted | 200000 | 312 | powersort | 0.37 | +7.71% | [+1.50%, +16.40%] | - |
| sorted | 1000000 | 311 | hybrid_quantile_backbone | 0.65 | +2.77% | [-5.27%, +12.24%] | - |
| sorted | 1000000 | 312 | hybrid_quantile_concat | 0.73 | +7.67% | [-2.42%, +26.20%] | - |
| reversed | 200000 | 311 | powersort | 0.50 | +4.28% | [+1.35%, +8.41%] | - |
| reversed | 200000 | 312 | powersort | 0.56 | +5.54% | [+1.76%, +14.59%] | - |
| reversed | 1000000 | 311 | hybrid_quantile_backbone | 0.89 | -0.16% | [-3.45%, +10.62%] | - |
| reversed | 1000000 | 312 | hybrid_general_portfolio | 1.03 | +13.47% | [+2.25%, +21.88%] | - |
| equal | 200000 | 311 | hybrid_general_portfolio | 0.34 | -2.98% | [-7.45%, +11.49%] | - |
| equal | 200000 | 312 | hybrid_general_portfolio | 0.33 | -1.67% | [-5.93%, +2.66%] | - |
| equal | 1000000 | 311 | hybrid_general_portfolio | 0.79 | -0.88% | [-9.56%, +14.42%] | - |
| equal | 1000000 | 312 | hybrid_quantile_concat | 0.95 | +14.86% | [-7.20%, +46.40%] | - |
| nearly1 | 200000 | 311 | hybrid_general_portfolio | 4.25 | -2.38% | [-10.59%, +1.05%] | - |
| nearly1 | 200000 | 312 | hybrid_general_portfolio | 6.16 | +7.71% | [-5.29%, +21.95%] | - |
| nearly1 | 1000000 | 311 | hybrid_general_portfolio | 4.16 | -3.03% | [-4.76%, +0.72%] | - |
| nearly1 | 1000000 | 312 | hybrid_general_portfolio | 4.21 | -10.78% | [-18.43%, -1.14%] | - |
| runs1024 | 200000 | 311 | ips4o | 20.90 | +0.41% | [-1.36%, +1.87%] | - |
| runs1024 | 200000 | 312 | ips4o | 20.91 | +1.00% | [-0.68%, +3.79%] | - |
| runs1024 | 1000000 | 311 | ips4o | 23.93 | -0.00% | [-2.19%, +2.10%] | - |
| runs1024 | 1000000 | 312 | ips4o | 24.09 | +0.30% | [-4.33%, +4.23%] | - |
| dup16 | 200000 | 311 | ips4o | 3.40 | +2.28% | [-0.98%, +5.82%] | - |
| dup16 | 200000 | 312 | ips4o | 5.75 | -5.07% | [-20.70%, +3.17%] | - |
| dup16 | 1000000 | 311 | ips4o | 3.76 | +0.35% | [-3.18%, +3.34%] | - |
| dup16 | 1000000 | 312 | ips4o | 3.79 | +1.81% | [+0.60%, +5.43%] | - |
| outpct1 | 200000 | 311 | hybrid_quantile_concat | 1.81 | -7.27% | [-9.15%, -5.76%] | - |
| outpct1 | 200000 | 312 | hybrid_quantile_concat | 1.85 | -9.05% | [-12.19%, -6.75%] | - |
| outpct1 | 1000000 | 311 | hybrid_quantile_concat | 1.65 | -20.37% | [-22.69%, -17.17%] | - |
| outpct1 | 1000000 | 312 | hybrid_quantile_concat | 4.35 | +131.05% | [+126.22%, +138.75%] | - |
| disp16 | 200000 | 311 | pdqsort_branchless | 22.34 | +26.62% | [+25.32%, +33.68%] | - |
| disp16 | 200000 | 312 | pdqsort_branchless | 21.37 | +25.68% | [+23.17%, +33.07%] | - |
| disp16 | 1000000 | 311 | pdqsort_branchless | 25.33 | +31.06% | [+27.95%, +35.89%] | - |
| disp16 | 1000000 | 312 | pdqsort_branchless | 22.31 | +17.60% | [+14.03%, +20.95%] | - |
| outpct5 | 200000 | 311 | hybrid_quantile_concat | 3.06 | -17.15% | [-19.17%, -15.40%] | - |
| outpct5 | 200000 | 312 | hybrid_quantile_concat | 3.07 | -40.97% | [-42.62%, -39.88%] | - |
| outpct5 | 1000000 | 311 | hybrid_quantile_concat | 3.14 | -42.05% | [-42.51%, -38.40%] | - |
| outpct5 | 1000000 | 312 | hybrid_quantile_concat | 3.06 | -39.94% | [-42.62%, -38.39%] | - |
| outpct14 | 200000 | 311 | hybrid_quantile_concat | 6.54 | -41.36% | [-43.78%, -39.08%] | - |
| outpct14 | 200000 | 312 | hybrid_quantile_concat | 5.55 | -43.29% | [-43.70%, -43.05%] | - |
| outpct14 | 1000000 | 311 | hybrid_quantile_concat | 6.02 | -48.04% | [-49.47%, -44.83%] | - |
| outpct14 | 1000000 | 312 | hybrid_general_portfolio | 6.69 | -44.89% | [-46.26%, -41.14%] | - |
| outpct26 | 200000 | 311 | ips4o | 15.09 | -1.12% | [-3.74%, +2.16%] | - |
| outpct26 | 200000 | 312 | ips4o | 15.27 | -1.83% | [-3.48%, +0.85%] | - |
| outpct26 | 1000000 | 311 | ips4o | 9.89 | -43.78% | [-46.39%, -41.89%] | - |
| outpct26 | 1000000 | 312 | ips4o | 10.67 | -38.71% | [-41.78%, -37.25%] | - |
| outpct36 | 200000 | 311 | ips4o | 16.68 | +3.83% | [+2.38%, +5.15%] | - |
| outpct36 | 200000 | 312 | ips4o | 16.30 | +0.93% | [-1.97%, +4.74%] | - |
| outpct36 | 1000000 | 311 | ips4o | 17.76 | -0.33% | [-2.95%, +3.78%] | - |
| outpct36 | 1000000 | 312 | ips4o | 18.31 | +0.04% | [-3.77%, +2.28%] | - |
| disp4 | 200000 | 311 | hybrid_general_portfolio | 14.63 | -2.14% | [-5.18%, +6.22%] | - |
| disp4 | 200000 | 312 | hybrid_general_portfolio | 14.51 | +0.31% | [-3.58%, +3.82%] | - |
| disp4 | 1000000 | 311 | hybrid_general_portfolio | 14.44 | +0.80% | [-1.94%, +3.95%] | - |
| disp4 | 1000000 | 312 | hybrid_general_portfolio | 13.78 | -1.53% | [-4.55%, +2.50%] | - |
| disp64 | 200000 | 311 | pdqsort_branchless | 18.58 | +3.93% | [+2.56%, +5.40%] | - |
| disp64 | 200000 | 312 | pdqsort_branchless | 20.10 | -1.02% | [-1.58%, -0.33%] | - |
| disp64 | 1000000 | 311 | pdqsort_branchless | 23.10 | +13.18% | [+9.50%, +22.00%] | - |
| disp64 | 1000000 | 312 | pdqsort_branchless | 22.66 | +12.14% | [+7.15%, +18.74%] | - |
| tail10 | 200000 | 311 | powersort | 7.62 | +2.65% | [+1.04%, +3.92%] | - |
| tail10 | 200000 | 312 | hybrid_quantile_concat | 7.60 | -0.43% | [-1.89%, +2.87%] | - |
| tail10 | 1000000 | 311 | hybrid_quantile_concat | 8.62 | +2.56% | [+0.91%, +3.75%] | - |
| tail10 | 1000000 | 312 | hybrid_quantile_concat | 8.55 | +1.31% | [+0.55%, +2.19%] | - |
| runs32 | 200000 | 311 | ips4o | 18.44 | +0.68% | [-2.21%, +2.08%] | - |
| runs32 | 200000 | 312 | ips4o | 18.04 | -0.54% | [-1.64%, +0.71%] | - |
| runs32 | 1000000 | 311 | ips4o | 20.41 | +0.50% | [-0.71%, +1.07%] | - |
| runs32 | 1000000 | 312 | ips4o | 20.19 | -0.41% | [-1.28%, +0.10%] | - |
| dup2 | 200000 | 311 | pdqsort_branchless | 2.45 | +144.91% | [+140.84%, +148.15%] | - |
| dup2 | 200000 | 312 | bl_quick | 2.41 | +45.20% | [+44.24%, +45.97%] | - |
| dup2 | 1000000 | 311 | pdqsort_branchless | 2.47 | +125.05% | [+120.91%, +128.78%] | - |
| dup2 | 1000000 | 312 | pdqsort_branchless | 2.57 | +71.83% | [+67.55%, +76.25%] | - |
| dup256 | 200000 | 311 | ips4o | 5.51 | +0.59% | [-0.90%, +3.85%] | - |
| dup256 | 200000 | 312 | ips4o | 5.35 | -0.64% | [-4.68%, +1.87%] | - |
| dup256 | 1000000 | 311 | ips4o | 5.90 | -0.73% | [-2.62%, +1.73%] | - |
| dup256 | 1000000 | 312 | ips4o | 5.73 | +1.77% | [-5.20%, +3.74%] | - |
| organpipe | 200000 | 311 | powersort | 1.02 | +1.60% | [-0.96%, +2.94%] | - |
| organpipe | 200000 | 312 | powersort | 1.02 | +0.34% | [-1.99%, +2.24%] | - |
| organpipe | 1000000 | 311 | powersort | 1.43 | -1.47% | [-3.12%, +2.29%] | - |
| organpipe | 1000000 | 312 | powersort | 1.45 | +2.05% | [-0.20%, +3.89%] | - |

Cases: 92; median regret +0.34%; mean +2.99%; nearest-rank p95 +45.20%; worst +144.91%; within 5%: 74; wins/ties: 42.
