# Round-timing analysis: general_prefix_v3_train_20261022.csv

Build: `general-prefix-v3`.

Times are median nanoseconds per element. Regret compares the candidate's median with the fastest baseline median within each input/seed. Bootstrap intervals resample complete rounds and reselect the fastest baseline in every resample. They describe sampling uncertainty in this run; dependence between rounds, CPU frequency drift, and host differences are not covered. Prior/new differences do not isolate timing-order effects.

| Input | n | Seed | Best baseline | Candidate ns/item | Regret | Round-bootstrap 95% interval | Prior regret |
|---|---:|---:|---|---:|---:|---:|---:|
| sorted | 200000 | 191 | powersort | 0.38 | +3.71% | [-9.12%, +14.20%] | - |
| sorted | 1000000 | 191 | hybrid_descent_portfolio | 0.70 | +9.63% | [-2.12%, +21.70%] | - |
| reversed | 200000 | 191 | hybrid_descent_portfolio | 0.61 | -8.46% | [-12.95%, +12.97%] | - |
| reversed | 1000000 | 191 | hybrid_descent_portfolio | 1.01 | +2.43% | [-1.80%, +15.05%] | - |
| equal | 200000 | 191 | hybrid_general_portfolio | 0.67 | +20.13% | [-9.02%, +113.47%] | - |
| equal | 1000000 | 191 | hybrid_general_portfolio | 0.67 | +3.51% | [-5.05%, +17.14%] | - |
| organpipe | 200000 | 191 | hybrid_general_portfolio | 2.36 | +9.57% | [+2.25%, +19.83%] | - |
| organpipe | 1000000 | 191 | powersort | 1.82 | -3.52% | [-8.55%, +6.47%] | - |
| tail10 | 200000 | 191 | hybrid_general_portfolio | 9.87 | +2.21% | [-0.82%, +4.46%] | - |
| tail10 | 1000000 | 191 | powersort | 10.44 | +1.69% | [+0.68%, +4.79%] | - |
| runs1024 | 200000 | 191 | bl_quick | 24.31 | +1.33% | [-1.36%, +11.24%] | - |
| runs1024 | 1000000 | 191 | hybrid_general_portfolio | 26.89 | +1.90% | [-1.34%, +9.55%] | - |
| nearly1 | 200000 | 191 | hybrid_descent_portfolio | 3.44 | +0.15% | [-3.75%, +4.13%] | - |
| nearly1 | 1000000 | 191 | hybrid_descent_portfolio | 3.27 | +0.12% | [-9.75%, +3.28%] | - |
| random | 200000 | 191 | bl_quick | 24.11 | +1.12% | [-1.76%, +3.45%] | - |
| random | 1000000 | 191 | bl_quick | 29.28 | +0.79% | [-0.11%, +2.75%] | - |
| outpct1 | 200000 | 191 | hybrid_quantile_backbone | 1.56 | +1.02% | [-0.66%, +3.73%] | - |
| outpct1 | 1000000 | 191 | hybrid_quantile_backbone | 1.73 | +4.91% | [+2.02%, +7.05%] | - |
| dup16 | 200000 | 191 | bl_quick | 4.06 | +2.48% | [+1.05%, +6.25%] | - |
| dup16 | 1000000 | 191 | hybrid_general_portfolio | 4.47 | +0.19% | [-1.12%, +3.29%] | - |

Cases: 20; median regret +1.80%; mean +2.75%; nearest-rank p95 +9.63%; worst +20.13%; within 5%: 17; wins/ties: 2.
