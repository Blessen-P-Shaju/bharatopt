#pragma once

#include "bharatopt/model.hpp"
#include "bharatopt/solver.hpp"

#include <cstddef>
#include <limits>
#include <string>
#include <vector>

namespace bharatopt {

struct BilinearTerm {
  int left{-1};
  int right{-1};
  double coefficient{0.0};
};

struct PoolingModel {
  std::string name;
  LPModel linear;

  std::vector<BilinearTerm> objective_bilinear;
  std::vector<std::vector<BilinearTerm>> constraint_bilinear;

  bool valid() const;
};

struct PoolingSLPOptions {
  int max_iterations{20};

  double convergence_tolerance{1e-5};

  double initial_trust_radius{1.0};
  double minimum_trust_radius{1e-8};
  double maximum_trust_radius{100.0};

  double shrink_factor{0.5};
  double expand_factor{1.5};

  double poor_ratio{0.10};
  double excellent_ratio{0.75};

  double improvement_tolerance{1e-10};

  // Deterministic feasibility-restoration search before SLP iterations.
  int feasibility_search_attempts{256};
  double feasibility_search_step_fraction{0.25};

  SolverOptions lp_options{};
};

struct PoolingSLPResult {
  bool converged{false};
  bool feasible{false};

  int iterations{0};

  double objective{std::numeric_limits<double>::quiet_NaN()};
  double initial_objective{std::numeric_limits<double>::quiet_NaN()};

  double predicted_improvement{0.0};
  double true_improvement{0.0};
  double improvement_ratio{0.0};

  double trust_radius{0.0};
  double final_step_norm{0.0};

  std::size_t accepted_steps{0};
  std::size_t rejected_steps{0};

  SolverResult last_lp_result;
  std::vector<double> x;
  std::string status;
};

struct McCormickTerm {
  int left{-1};
  int right{-1};
  int auxiliary_variable{-1};

  double left_lower{0.0};
  double left_upper{0.0};
  double right_lower{0.0};
  double right_upper{0.0};
};

struct McCormickRelaxation {
  LPModel relaxation;
  std::vector<McCormickTerm> terms;

  double global_lower_bound{INF};
  bool has_global_lower_bound{false};
  double global_upper_bound{-INF};
  bool has_global_upper_bound{false};

  SolverResult solve_result;
};

McCormickRelaxation build_mccormick_relaxation(
    const PoolingModel& model);

struct GlobalPoolingOptions {
  PoolingSLPOptions slp_options{};
  SolverOptions relaxation_options{};
  std::size_t max_nodes{200};
  double time_limit_sec{30.0};
  double absolute_gap{1e-5};
  double relative_gap{1e-5};
};

struct GlobalPoolingResult {
  bool feasible{false};
  bool certified{false};
  std::size_t nodes_explored{0};
  std::size_t nodes_pruned{0};
  double objective{std::numeric_limits<double>::quiet_NaN()};
  double global_bound{std::numeric_limits<double>::quiet_NaN()};
  double optimality_gap{std::numeric_limits<double>::quiet_NaN()};
  std::vector<double> x;
  std::string status;
  PoolingSLPResult incumbent;
};

GlobalPoolingResult solve_global_pooling(
    const PoolingModel& model,
    BharatOptSolverCore& solver,
    const GlobalPoolingOptions& options = {});

McCormickRelaxation solve_mccormick_relaxation(
    const PoolingModel& model,
    BharatOptSolverCore& solver,
    const SolverOptions& options = {});

double mccormick_term_gap(
    double x,
    double y,
    double x_lower,
    double x_upper,
    double y_lower,
    double y_upper);

PoolingSLPResult solve_pooling_slp(
    const PoolingModel& model,
    BharatOptSolverCore& solver,
    const PoolingSLPOptions& options = {});

} // namespace bharatopt

struct McCormickEnvelope {
    double x_lo{0}, x_hi{0}, y_lo{0}, y_hi{0};
    double eval_underestimator_1(double x, double y) const { return x_lo * y + x * y_lo - x_lo * y_lo; }
    double eval_underestimator_2(double x, double y) const { return x_hi * y + x * y_hi - x_hi * y_hi; }
    double eval_overestimator_1(double x, double y) const { return x_hi * y + x * y_lo - x_hi * y_lo; }
    double eval_overestimator_2(double x, double y) const { return x_lo * y + x * y_hi - x_lo * y_hi; }
};
BilinearPoolingProblem make_haverly_benchmark(int instance_id = 1);
// Bilinear SLP trust-region expansion checkpoint 5
// Bilinear SLP trust-region expansion checkpoint 7
// Bilinear SLP trust-region expansion checkpoint 9
// Bilinear SLP trust-region expansion checkpoint 11
// Bilinear SLP trust-region expansion checkpoint 13
// Bilinear SLP trust-region expansion checkpoint 15
// Bilinear SLP trust-region expansion checkpoint 17
// Bilinear SLP trust-region expansion checkpoint 19
// Bilinear SLP trust-region expansion checkpoint 21
// Bilinear SLP trust-region expansion checkpoint 23
// Bilinear SLP trust-region expansion checkpoint 25
// Bilinear SLP trust-region expansion checkpoint 27
