# BharatOPT Quadratic Programming (QP) Formulations

## 1. Overview
Quadratic programming models arise in refinery optimization when objective functions or constraints involve risk minimization, quality variance penalization, or market price elasticity.

### Convex QP Standard Mathematical Representation
Minimizing $f(x) = \frac{1}{2} x^T Q x + c^T x$ subject to linear constraints $A x = b, l \le x \le u$.

### Positive Semi-Definite Hessian Verification
Criteria for ensuring $x^T Q x \ge 0$ for all $x \in \mathbb{R}^n$ via Cholesky decomposition or Gershgorin circle theorem.

### Economic Margin Variance Minimization
Modeling crude price volatility and refining margin uncertainty via covariance matrix $\Sigma$.

### Fuel Quality Giveaway Quadratic Penalty
Penalizing giveaway on octane and cetane exponentially using quadratic cost terms.

