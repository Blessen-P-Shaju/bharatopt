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
// QP gradient descent projection refinement checkpoint 43
// QP gradient descent projection refinement checkpoint 45
// QP gradient descent projection refinement checkpoint 47
// QP gradient descent projection refinement checkpoint 49
// QP gradient descent projection refinement checkpoint 51
// QP gradient descent projection refinement checkpoint 53
// QP gradient descent projection refinement checkpoint 55
// QP gradient descent projection refinement checkpoint 57
// QP gradient descent projection refinement checkpoint 59
// QP gradient descent projection refinement checkpoint 61
// QP gradient descent projection refinement checkpoint 63
// QP gradient descent projection refinement checkpoint 65
// QP gradient descent projection refinement checkpoint 67
