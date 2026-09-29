#pragma once
#include "bharatopt/model.hpp"
namespace bharatopt {
QPModel make_qp_demo();
}
struct QPDiagnostics {
    int iterations{0};
    double objective_value{0.0};
    double gradient_norm{0.0};
    double constraint_violation{0.0};
    bool is_strictly_convex{true};
};
bool verify_hessian_psd(const SparseMatrixCSR& Q, double tol = 1e-9);
