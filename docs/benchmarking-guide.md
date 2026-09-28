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

