# BharatOPT Benchmarking Guide & Performance Validation

## 1. Overview
This document outlines standard benchmarking methodologies for measuring BharatOPT simplex, interior point, and refinery flowsheet solvers against industry-standard benchmarks.

### Netlib Linear Programming Benchmark Suite
Standard collection of 98 real-world LP problems from industry and operations research.

### AFIRO Benchmark Profile
Small LP model (28 rows, 32 cols) validating Phase I/Phase II basic transition correctness.

### SHARE2B Benchmark Profile
Refinery-adjacent LP problem (97 rows, 79 cols) testing sparse pivot selection stability.

### ADLITTLE Benchmark Profile
Dynamic multi-period production model (57 rows, 97 cols) testing bounded variable simplex.

### SC205 Benchmark Profile
Sparse structural problem (206 rows, 203 cols) benchmarking LU update fill-in rates.

### ISRAEL Benchmark Profile
Ill-conditioned constraint system (175 rows, 142 cols) testing numerical scaling stability.

### E226 Benchmark Profile
Deep degeneracy problem (224 rows, 282 cols) testing anti-cycling Bland and steepest-edge rules.

### SCTAP1 Benchmark Profile
Dynamic traffic and routing model (301 rows, 480 cols) benchmarking sparse matrix multiply kernels.

### PILOT Benchmark Profile
Large macroeconomic input-output model (1442 rows, 3652 cols) stress testing basis refactorization.

### STAIR Benchmark Profile
Staircase multi-period constraint structure (357 rows, 467 cols) benchmarking warm-start capability.

### GREENBEA Benchmark Profile
Dense basis LP problem (2393 rows, 5405 cols) benchmarking SIMD vector kernel performance.

### Refinery Flowsheet Benchmark Architecture
Proprietary BharatOPT synthetic refinery test instances simulating coastal and inland configurations.

### MRPL Phase-III Synthetic Benchmark
Full flowsheet simulation with 12 process units, 24 intermediate streams, and 18 finished product tanks.

### CPCL Manali Synthetic Benchmark
Heavy crude processing configuration testing vacuum distillation and delayed coking constraints.

### IOCL Paradip Benchmark Instance
Deep conversion refinery model featuring INDMAX FCC technology and polypropylene yield balance.

### BPCL Kochi Synthetic Flowsheet
Clean fuels blending benchmark testing Euro-VI / BS-VI diesel and gasoline compliance bounds.

### Bilinear Pooling Benchmark Protocol
Standard protocol for testing non-convex pooling instances with varying component numbers.

### Haverly 1 Benchmark Instance
Standard pooling test: 2 crude sources, 1 pool tank, 2 blended products, 1 sulfur component.

### Haverly 2 Benchmark Instance
Haverly instance with inverted cost structures testing local vs global optima trapping.

### Haverly 3 Benchmark Instance
Extended Haverly instance with product demand upper bounds testing economic shadow prices.

### Standat Pooling Instance
Three-pool, four-component blending network benchmarking Successive Linear Programming (SLP).

### Benchmark Metrics: Iteration Count
Recording total simplex iterations, Phase I iterations, and Phase II iterations.

### Benchmark Metrics: Wall-Clock Solve Time
High-resolution microsecond timing using `std::chrono::steady_clock`.

### Benchmark Metrics: Primal Infeasibility Norm
Maximum constraint violation $\max_i |a_i^T x - b_i|$ must satisfy $< 10^{-6}$.

### Benchmark Metrics: Dual Infeasibility Norm
Maximum reduced cost violation must satisfy $< 10^{-6}$.

### Benchmark Metrics: Objective Value Gap
Relative gap $|z_{calc} - z_{ref}| / (1 + |z_{ref}|) < 10^{-7}$ against HiGHS reference.

### Benchmark Metrics: Memory High-Water Mark
Peak RSS resident memory usage during basis refactorization and matrix allocation.

### Benchmark Metrics: Cache Miss Rates
L1/L3 cache misses measured via hardware performance counters during sparse pricing.

### Reference Solver Comparison: HiGHS
Comparing solve speed and iteration counts against HiGHS v1.7.0 C++ API.

### Reference Solver Comparison: GLPK
Comparing basis stability against GNU Linear Programming Kit simplex engine.

### Reference Solver Comparison: Clp (Coin-OR)
Benchmarking against Coin-OR Linear Programming simplex solver.

### Automated Regression Test Suite
Integration of benchmarks into continuous verification pipeline with automated failure alerts.

### Tolerance Thresholds for Floating Point
Tolerances for primal feasibility ($10^{-7}$), dual feasibility ($10^{-7}$), and pivot zero ($10^{-12}$).

### Benchmarking Execution Script
Documentation for `scripts/run_benchmarks.py` parameters and summary report output.

### MPS Format Validation Protocol
Verifying column, row, and bound headers in MPS benchmark files.

### Sensitivity Analysis Benchmark
Testing objective range and right-hand side tolerance intervals.

### Parallel Benchmark Execution
Multi-threaded benchmark runner evaluating thread scaling across batch problem sets.

### Cross-Platform Reproducibility
Verifying identical iteration counts across Linux x86_64 and Windows MSVC/Clang targets.

