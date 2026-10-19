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

