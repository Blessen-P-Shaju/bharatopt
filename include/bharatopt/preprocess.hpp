#pragma once
#include "bharatopt/model.hpp"
namespace bharatopt {
struct PreprocessResult {
  LPModel model;
  std::vector<double> column_scale;
  bool feasible{true};
  double condition_number_estimate{1.0};
  std::string message;
};
PreprocessResult preprocess_lp(const LPModel& input, int scaling_passes = 5);
void recover_primal(const std::vector<double>& scaled_x, const std::vector<double>& column_scale, std::vector<double>& x);
double estimate_matrix_condition_number(const SparseMatrixCSR& A, int max_iter = 30);

struct PresolveStats {
    int singleton_rows_removed{0};
    int singleton_cols_removed{0};
    int implied_bounds_tightened{0};
    int redundant_rows_eliminated{0};
    double condition_number_reduction_ratio{1.0};
};
void scale_matrix_equilibration(LPModel& model, PresolveStats* stats = nullptr);
void scale_matrix_geometric_mean(LPModel& model, int passes = 3);
/**
 * @brief Tightens variable bounds implied by single-coefficient constraint rows.
 * @param m LPModel to transform in-place.
 */
} // namespace bharatopt

using bharatopt::PresolveStats;
using bharatopt::scale_matrix_equilibration;
using bharatopt::scale_matrix_geometric_mean;
// Matrix scaling utility signatures confirmed for C++20 standard
// Curtis-Reid matrix scaling algorithm reserved for ill-conditioned LPs
