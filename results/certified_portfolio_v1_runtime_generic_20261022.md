# Round-timing analysis: certified_portfolio_v1_runtime_20261022.csv

Build: `certified-runtime-v1-vqsort`.

Excluded baselines: `vqsort`, `x86_simd`.
The complete unfiltered round schedule was validated before this comparison filter.

Times are median nanoseconds per element. Regret compares the candidate's median with the fastest baseline median within each input/seed. Bootstrap intervals resample complete rounds and reselect the fastest baseline in every resample. They describe sampling uncertainty in this run; dependence between rounds, CPU frequency drift, and host differences are not covered. Prior/new differences do not isolate timing-order effects.

| Input | n | Seed | Best baseline | Candidate ns/item | Regret | Round-bootstrap 95% interval | Prior regret |
|---|---:|---:|---|---:|---:|---:|---:|
| random | 200000 | 321 | ips4o | 21.91 | -0.59% | [-5.44%, +4.11%] | - |
| random | 200000 | 322 | ips4o | 22.39 | +1.87% | [-1.11%, +3.70%] | - |
| random | 1000000 | 321 | ips4o | 25.95 | -1.71% | [-5.32%, +3.02%] | - |
| random | 1000000 | 322 | ips4o | 29.03 | -1.96% | [-9.42%, +11.71%] | - |
| uniform64 | 200000 | 321 | ips4o | 21.77 | +0.10% | [-5.86%, +7.32%] | - |
| uniform64 | 200000 | 322 | ips4o | 23.63 | -0.02% | [-6.51%, +7.30%] | - |
| uniform64 | 1000000 | 321 | ips4o | 26.36 | +0.49% | [-9.57%, +10.58%] | - |
| uniform64 | 1000000 | 322 | ips4o | 25.69 | +0.32% | [-4.02%, +7.49%] | - |
| uniform32 | 200000 | 321 | ips4o | 23.47 | +0.24% | [-2.06%, +0.99%] | - |
| uniform32 | 200000 | 322 | ips4o | 23.32 | +0.28% | [-2.21%, +4.00%] | - |
| uniform32 | 1000000 | 321 | ips4o | 26.50 | +2.21% | [-1.11%, +5.09%] | - |
| uniform32 | 1000000 | 322 | ips4o | 24.61 | -0.05% | [-3.24%, +3.87%] | - |
| highbits32 | 200000 | 321 | ips4o | 22.47 | +3.10% | [-1.37%, +7.38%] | - |
| highbits32 | 200000 | 322 | ips4o | 21.43 | +0.87% | [-4.74%, +4.74%] | - |
| highbits32 | 1000000 | 321 | ips4o | 22.38 | -1.73% | [-4.97%, +3.21%] | - |
| highbits32 | 1000000 | 322 | ips4o | 23.13 | +1.15% | [-1.12%, +5.17%] | - |
| sorted | 200000 | 321 | ips4o | 0.43 | +8.84% | [+0.12%, +24.66%] | - |
| sorted | 200000 | 322 | powersort | 0.40 | +5.43% | [-0.37%, +11.32%] | - |
| sorted | 1000000 | 321 | ips4o | 0.68 | +8.97% | [+4.77%, +17.03%] | - |
| sorted | 1000000 | 322 | ips4o | 0.74 | +9.77% | [-3.72%, +18.34%] | - |
| reversed | 200000 | 321 | powersort | 0.64 | +9.85% | [+3.07%, +15.00%] | - |
| reversed | 200000 | 322 | powersort | 0.61 | +6.32% | [+1.18%, +11.04%] | - |
| reversed | 1000000 | 321 | ips4o | 0.93 | +1.02% | [-3.27%, +11.12%] | - |
| reversed | 1000000 | 322 | powersort | 0.90 | +3.25% | [-1.81%, +7.45%] | - |
| equal | 200000 | 321 | ips4o | 0.37 | -3.48% | [-12.35%, +7.34%] | - |
| equal | 200000 | 322 | powersort | 0.35 | -4.17% | [-7.70%, -1.13%] | - |
| equal | 1000000 | 321 | powersort | 0.57 | -7.15% | [-12.08%, +2.35%] | - |
| equal | 1000000 | 322 | powersort | 0.59 | -10.14% | [-14.54%, -4.80%] | - |
| nearly1 | 200000 | 321 | pdqsort_branchless | 3.46 | -54.88% | [-55.71%, -53.84%] | - |
| nearly1 | 200000 | 322 | pdqsort_branchless | 3.53 | -54.43% | [-56.09%, -53.33%] | - |
| nearly1 | 1000000 | 321 | pdqsort_branchless | 3.98 | -57.62% | [-58.35%, -56.32%] | - |
| nearly1 | 1000000 | 322 | pdqsort_branchless | 4.18 | -55.99% | [-57.44%, -55.07%] | - |
| runs1024 | 200000 | 321 | ips4o | 21.18 | -0.37% | [-3.03%, +1.55%] | - |
| runs1024 | 200000 | 322 | ips4o | 21.39 | -0.24% | [-3.72%, +2.46%] | - |
| runs1024 | 1000000 | 321 | ips4o | 22.87 | +0.57% | [-1.82%, +2.41%] | - |
| runs1024 | 1000000 | 322 | ips4o | 23.87 | -0.44% | [-3.32%, +3.18%] | - |
| dup16 | 200000 | 321 | ips4o | 3.49 | -0.03% | [-1.96%, +6.09%] | - |
| dup16 | 200000 | 322 | ips4o | 3.53 | -0.31% | [-3.54%, +4.47%] | - |
| dup16 | 1000000 | 321 | ips4o | 3.76 | -1.38% | [-3.37%, +0.58%] | - |
| dup16 | 1000000 | 322 | ips4o | 3.84 | +0.78% | [-2.32%, +3.18%] | - |
| outpct1 | 200000 | 321 | hybrid_quantile_concat | 2.50 | +19.03% | [+15.35%, +22.96%] | - |
| outpct1 | 200000 | 322 | hybrid_quantile_concat | 2.48 | +29.71% | [+26.60%, +30.99%] | - |
| outpct1 | 1000000 | 321 | hybrid_quantile_concat | 2.29 | +13.07% | [+10.27%, +14.85%] | - |
| outpct1 | 1000000 | 322 | hybrid_quantile_concat | 2.43 | +13.56% | [+11.21%, +17.38%] | - |
| disp16 | 200000 | 321 | pdqsort_branchless | 23.96 | +29.10% | [+27.18%, +31.68%] | - |
| disp16 | 200000 | 322 | pdqsort_branchless | 24.58 | +29.22% | [+26.60%, +31.67%] | - |
| disp16 | 1000000 | 321 | pdqsort_branchless | 23.29 | +19.80% | [+16.18%, +22.99%] | - |
| disp16 | 1000000 | 322 | pdqsort_branchless | 23.73 | +21.14% | [+18.43%, +24.40%] | - |
| outpct5 | 200000 | 321 | hybrid_quantile_concat | 3.76 | -32.43% | [-33.23%, -31.27%] | - |
| outpct5 | 200000 | 322 | hybrid_quantile_concat | 3.70 | -39.44% | [-40.38%, -38.69%] | - |
| outpct5 | 1000000 | 321 | hybrid_quantile_concat | 3.51 | -30.79% | [-32.18%, -30.08%] | - |
| outpct5 | 1000000 | 322 | hybrid_quantile_concat | 3.68 | -35.68% | [-38.62%, -34.11%] | - |
| outpct14 | 200000 | 321 | hybrid_quantile_concat | 7.19 | -43.63% | [-44.58%, -42.45%] | - |
| outpct14 | 200000 | 322 | hybrid_quantile_concat | 6.94 | -43.66% | [-45.02%, -42.67%] | - |
| outpct14 | 1000000 | 321 | hybrid_quantile_concat | 6.96 | -42.02% | [-42.92%, -40.78%] | - |
| outpct14 | 1000000 | 322 | hybrid_quantile_concat | 6.75 | -45.60% | [-46.83%, -44.60%] | - |
| outpct26 | 200000 | 321 | ips4o | 11.25 | -31.47% | [-33.51%, -29.87%] | - |
| outpct26 | 200000 | 322 | ips4o | 15.67 | -0.66% | [-2.81%, +0.67%] | - |
| outpct26 | 1000000 | 321 | ips4o | 17.80 | +0.87% | [-0.25%, +2.28%] | - |
| outpct26 | 1000000 | 322 | ips4o | 17.82 | +1.12% | [+0.01%, +4.81%] | - |
| outpct36 | 200000 | 321 | ips4o | 16.52 | +1.74% | [-0.04%, +2.97%] | - |
| outpct36 | 200000 | 322 | ips4o | 17.52 | -0.63% | [-2.53%, +2.92%] | - |
| outpct36 | 1000000 | 321 | ips4o | 19.69 | +3.18% | [-1.14%, +7.37%] | - |
| outpct36 | 1000000 | 322 | ips4o | 18.46 | -2.54% | [-6.18%, +2.50%] | - |
| disp4 | 200000 | 321 | pdqsort_branchless | 12.76 | -12.31% | [-13.88%, -7.56%] | - |
| disp4 | 200000 | 322 | pdqsort_branchless | 14.52 | -12.42% | [-13.99%, -10.82%] | - |
| disp4 | 1000000 | 321 | pdqsort_branchless | 12.48 | -18.42% | [-19.81%, -17.56%] | - |
| disp4 | 1000000 | 322 | pdqsort_branchless | 12.21 | -20.14% | [-20.85%, -18.92%] | - |
| disp64 | 200000 | 321 | pdqsort_branchless | 18.07 | +4.95% | [+4.32%, +6.41%] | - |
| disp64 | 200000 | 322 | pdqsort_branchless | 17.84 | +3.54% | [+2.40%, +4.88%] | - |
| disp64 | 1000000 | 321 | pdqsort_branchless | 22.55 | +11.20% | [+10.26%, +11.94%] | - |
| disp64 | 1000000 | 322 | pdqsort_branchless | 20.02 | +11.68% | [+10.86%, +13.44%] | - |
| tail10 | 200000 | 321 | powersort | 7.67 | +2.03% | [+1.16%, +4.04%] | - |
| tail10 | 200000 | 322 | hybrid_quantile_concat | 7.49 | +1.97% | [+0.90%, +2.57%] | - |
| tail10 | 1000000 | 321 | powersort | 9.54 | +2.52% | [+0.21%, +3.89%] | - |
| tail10 | 1000000 | 322 | hybrid_quantile_concat | 8.41 | +0.61% | [-1.56%, +2.20%] | - |
| runs32 | 200000 | 321 | ips4o | 18.31 | +1.05% | [+0.01%, +2.89%] | - |
| runs32 | 200000 | 322 | ips4o | 18.15 | -1.16% | [-2.23%, +0.29%] | - |
| runs32 | 1000000 | 321 | ips4o | 20.21 | -0.07% | [-2.86%, +0.53%] | - |
| runs32 | 1000000 | 322 | ips4o | 22.62 | +0.70% | [-0.86%, +1.99%] | - |
| dup2 | 200000 | 321 | pdqsort_branchless | 2.47 | +111.99% | [+105.95%, +115.98%] | - |
| dup2 | 200000 | 322 | ips4o | 2.76 | +2.00% | [-0.06%, +4.21%] | - |
| dup2 | 1000000 | 321 | pdqsort_branchless | 2.87 | +67.96% | [+58.61%, +78.65%] | - |
| dup2 | 1000000 | 322 | pdqsort_branchless | 2.88 | +69.74% | [+63.71%, +78.93%] | - |
| dup256 | 200000 | 321 | ips4o | 6.22 | +0.43% | [-1.67%, +3.06%] | - |
| dup256 | 200000 | 322 | ips4o | 5.54 | +1.65% | [-0.15%, +3.70%] | - |
| dup256 | 1000000 | 321 | ips4o | 5.03 | -1.02% | [-2.64%, +1.31%] | - |
| dup256 | 1000000 | 322 | ips4o | 5.11 | +0.63% | [-1.35%, +3.84%] | - |
| organpipe | 200000 | 321 | powersort | 1.15 | +2.89% | [-4.56%, +11.64%] | - |
| organpipe | 200000 | 322 | powersort | 1.11 | +1.65% | [-2.32%, +7.90%] | - |
| organpipe | 1000000 | 321 | powersort | 1.49 | +0.47% | [-2.55%, +2.99%] | - |
| organpipe | 1000000 | 322 | powersort | 1.52 | +4.18% | [+0.57%, +6.35%] | - |

Cases: 92; median regret +0.53%; mean -1.30%; nearest-rank p95 +29.22%; worst +111.99%; within 5%: 73; wins/ties: 39.
