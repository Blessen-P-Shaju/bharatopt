# BharatOPT Developer Onboarding & Technical Contribution Guide

## 1. Development Environment Setup
BharatOPT requires a modern C++20 compiler (Clang 15+, GCC 12+, MSVC 2022), CMake 3.22+, and Python 3.10+.

### C++20 Language Standards & Modern Dialect Rules
Enforcing strict adherence to C++20 standard: concepts, ranges, constexpr algorithms, and std::span.

### Clang-Format and Code Styling Conventions
Google C++ style guide with 4-space indentation, 100-character line limit, and PascalCase types.

### Clang-Tidy Static Analysis Rules & Linters
Mandatory static analysis checks: bugprone, performance, modernize, and cert-err rules.

### CMake Build Configuration Profiles
Standard build targets: `Debug`, `Release`, `RelWithDebInfo`, and `AddressSanitizer`.

### AddressSanitizer (ASan) & UndefinedBehaviorSanitizer (UBSan)
Compiling with `-fsanitize=address,undefined` for zero memory leaks and undefined behavior.

### CUDA GPU Backend Compilation Flags
NVCC compilation with compute capability architecture `sm_70`, `sm_80`, and `sm_90`.

### Memory Management Guidelines: Zero Heap Allocations in Inner Loops
Pre-allocating scratch workspace buffers to eliminate `malloc`/`free` during simplex pivots.

### Floating-Point Reproducibility & IEEE 754 Compliance
Compiler flags `-fno-fast-math` ensuring strictly reproducible floating-point arithmetic.

### Git Workflow & Conventional Commit Standards
Feature branching (`feat/`, `fix/`, `docs/`) and conventional commit messages.

### Unit Testing Guidelines with GoogleTest & Python unittest
Writing deterministic unit tests with bounded execution timeouts.

### Continuous Integration GitHub Actions Pipelines
Matrix testing across Ubuntu Linux, Windows MSVC, and macOS Apple Silicon.

### Benchmarking Methodology for Pull Requests
Automated performance regression testing against Netlib benchmark suite on every PR.

### Documentation Generation via Doxygen & Markdown
Generating API reference documentation using Doxygen and GitHub Pages.

### Profiling CPU Hotspots with Linux perf and VTune
Identifying cache bottlenecks and instruction stalls during sparse matrix-vector multiplication.

### Debugging SIMD Vectorization with Compiler Assembly Explorer
Inspecting compiler assembly output for effective AVX-512 FMA utilization.

### Handling Numerical Singularities & Ill-Conditioned Bases
Defensive recovery strategies when matrix condition numbers exceed $10^{12}$.

### Security Practices for Open-Source Contributions
Code scanning with CodeQL and dependabot for supply-chain vulnerability mitigation.

### Release Engineering & Semantic Versioning
Automated semantic tagging, changelog generation, and multi-platform wheel publishing.

### Issue Triage & Bug Reporting Templates
Standardized issue templates requesting minimal reproducible MPS test cases.

### Code Review Checklist for Maintainers
Peer review criteria focusing on mathematical soundness, algorithmic complexity, and test coverage.

