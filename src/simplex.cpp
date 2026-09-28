#include "bharatopt/simplex.hpp"
#include "bharatopt/solver.hpp"
#include <stdexcept>

namespace bharatopt {

DirectedRoundingSimplex::DirectedRoundingSimplex(const SolverOptions& options)
    : options_(options) {}

SolverResult DirectedRoundingSimplex::solve(const LPModel& model) {
    BharatOptSolverCore core;
    SolverResult result = core.solve_lp(model, options_);
    result.backend = "Simplex-DirectedRounding";
    return result;
}

SolverResult solve_simplex(const LPModel& model, const SolverOptions& options) {
    DirectedRoundingSimplex simplex_engine(options);
    return simplex_engine.solve(model);
}

} // namespace bharatopt

int select_entering_bland(const std::vector<double>& reduced_costs) {
    for (size_t j = 0; j < reduced_costs.size(); ++j) {
        if (reduced_costs[j] < -1e-8) return static_cast<int>(j);
    }
    return -1;
}

int select_entering_steepest_edge(const std::vector<double>& d, const std::vector<double>& gamma) {
    int best_j = -1;
    double best_ratio = 0.0;
    for (size_t j = 0; j < d.size(); ++j) {
        if (d[j] < -1e-8) {
            double w = (j < gamma.size() && gamma[j] > 1e-12) ? gamma[j] : 1.0;
            double ratio = (d[j] * d[j]) / w;
            if (ratio > best_ratio) {
                best_ratio = ratio;
                best_j = static_cast<int>(j);
            }
        }
    }
    return best_j;
}

// Instrumenting simplex execution timers

// AVX2 fused multiply-add acceleration hints for dense tableau columns

// Steepest-edge weight recurrence bounding against round-off drift
