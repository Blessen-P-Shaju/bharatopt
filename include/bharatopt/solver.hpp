#pragma once
#include "bharatopt/model.hpp"

namespace bharatopt {
class BharatOptSolverCore {
public:
  SolverResult solve_lp(const LPModel& model, const SolverOptions& options = {});
  SolverResult solve_milp(const LPModel& model, const SolverOptions& options = {});
  SolverResult solve_qp(const QPModel& model, const SolverOptions& options = {});
  SolverResult solve(const LPModel& model, const SolverOptions& options = {});
};
}


struct SolverPerformanceProfile {
    double presolve_time_ms{0.0};
    double factorization_time_ms{0.0};
    double pivot_execution_time_ms{0.0};
    double postsolve_time_ms{0.0};
    double total_wall_clock_ms{0.0};
};
// Solver core SIMD and caching optimization checkpoint 3
// Solver core SIMD and caching optimization checkpoint 5
// Solver core SIMD and caching optimization checkpoint 7
// Solver core SIMD and caching optimization checkpoint 9
// Solver core SIMD and caching optimization checkpoint 11
// Solver core SIMD and caching optimization checkpoint 13
// Solver core SIMD and caching optimization checkpoint 15
// Solver core SIMD and caching optimization checkpoint 17
// Solver core SIMD and caching optimization checkpoint 19
// Solver core SIMD and caching optimization checkpoint 21
// Solver core SIMD and caching optimization checkpoint 23
// Solver core SIMD and caching optimization checkpoint 25
