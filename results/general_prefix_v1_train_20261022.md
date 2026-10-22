# Round-timing analysis: general_prefix_v1_train_20261022.csv

Build: `general-prefix-v1`.

Times are median nanoseconds per element. Regret compares the candidate's median with the fastest baseline median within each input/seed. Bootstrap intervals resample complete rounds and reselect the fastest baseline in every resample. They describe sampling uncertainty in this run; dependence between rounds, CPU frequency drift, and host differences are not covered. Prior/new differences do not isolate timing-order effects.

| Input | n | Seed | Best baseline | Candidate ns/item | Regret | Round-bootstrap 95% interval | Prior regret |
|---|---:|---:|---|---:|---:|---:|---:|
| sorted | 200000 | 191 | powersort | 0.25 | +1.88% | [-0.49%, +4.67%] | - |
| sorted | 1000000 | 191 | hybrid_inversion_gate | 0.45 | +4.39% | [-3.46%, +30.16%] | - |
| reversed | 200000 | 191 | powersort | 0.37 | -1.90% | [-2.85%, +1.36%] | - |
| reversed | 1000000 | 191 | hybrid_descent_portfolio | 0.71 | +19.63% | [+10.13%, +25.03%] | - |
| equal | 200000 | 191 | hybrid_general_portfolio | 0.25 | +5.34% | [+3.35%, +15.12%] | - |
| equal | 1000000 | 191 | hybrid_general_portfolio | 0.42 | +14.77% | [+8.10%, +19.93%] | - |
| organpipe | 200000 | 191 | powersort | 1.00 | +3.62% | [+0.59%, +12.78%] | - |
| organpipe | 1000000 | 191 | hybrid_general_portfolio | 1.44 | +6.53% | [+3.30%, +9.23%] | - |
| tail10 | 200000 | 191 | hybrid_descent_portfolio | 7.29 | -0.10% | [-0.95%, +1.86%] | - |
| tail10 | 1000000 | 191 | hybrid_general_portfolio | 8.18 | +0.17% | [-0.25%, +1.40%] | - |
| runs1024 | 200000 | 191 | bl_quick | 22.25 | +0.64% | [-0.23%, +1.47%] | - |
| runs1024 | 1000000 | 191 | bl_quick | 24.30 | +0.46% | [-0.19%, +0.89%] | - |
| nearly1 | 200000 | 191 | hybrid_descent_portfolio | 2.73 | +1.84% | [+1.08%, +3.46%] | - |
| nearly1 | 1000000 | 191 | hybrid_descent_portfolio | 2.99 | +0.89% | [-0.74%, +2.68%] | - |
| random | 200000 | 191 | hybrid_general_portfolio | 21.55 | -2.05% | [-2.70%, +0.09%] | - |
| random | 1000000 | 191 | bl_quick | 24.02 | -0.42% | [-0.98%, +1.74%] | - |
| outpct1 | 200000 | 191 | hybrid_quantile_backbone | 1.48 | -0.29% | [-2.02%, +3.49%] | - |
| outpct1 | 1000000 | 191 | hybrid_quantile_backbone | 1.62 | +1.38% | [+0.37%, +10.24%] | - |
| dup16 | 200000 | 191 | bl_quick | 3.44 | -0.02% | [-1.03%, +1.96%] | - |
| dup16 | 1000000 | 191 | hybrid_general_portfolio | 3.79 | +1.90% | [+0.39%, +3.62%] | - |

Cases: 20; median regret +1.14%; mean +2.93%; nearest-rank p95 +14.77%; worst +19.63%; within 5%: 16; wins/ties: 6.
