#pragma once
#include "bharatopt/model.hpp"
namespace bharatopt {
struct InteriorPointOptions {
  int max_iterations{100};
  double tolerance{1e-8};
  int max_variables{400};
  int max_constraints{400};
};
SolverResult solve_interior_point(const LPModel& model, const InteriorPointOptions& options = {});
}
struct InteriorPointDiagnostics {
    int iterations{0};
    double duality_gap{0.0};
    double primal_residual_norm{0.0};
    double dual_residual_norm{0.0};
    double barrier_parameter_mu{0.0};
    double cholesky_factorization_time_ms{0.0};
};
SolverResult solve_interior_point_verbose(const LPModel& model, const SolverOptions& options, InteriorPointDiagnostics* diag);
// Interior-Point Mehrotra predictor-corrector optimization step 5
// Interior-Point Mehrotra predictor-corrector optimization step 7
// Interior-Point Mehrotra predictor-corrector optimization step 9
// Interior-Point Mehrotra predictor-corrector optimization step 11
