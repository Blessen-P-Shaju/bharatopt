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
