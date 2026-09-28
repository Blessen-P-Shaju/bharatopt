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

