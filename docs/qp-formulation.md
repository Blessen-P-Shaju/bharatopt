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

### Minimum Kinetic Energy Pipeline Scheduling
Minimizing pump power losses proportional to squared flow rate: $P \propto Q^2$.

### Active Set Algorithm for Quadratic Programming
Iterative active set strategy treating active constraints as equalities and updating basis.

### KKT Conditions for Quadratic Programs
First-order necessary and sufficient optimality conditions for convex QP.

### Null-Space Method for Equality-Constrained QP
Projecting the Hessian $Q$ onto the null space of constraint matrix $A$.

### Range-Space Method for Equality-Constrained QP
Dual approach solving for Lagrange multipliers via Schur complement.

### Dual Quadratic Programming Formulation
Formulating the Wolfe dual problem for efficient solution when $n \gg m$.

### Goldfarb-Idnani Dual Active-Set Algorithm
Solving strictly convex quadratic programs starting from unconstrained minimum.

### Interior-Point Method for Convex QP
Extending primal-dual Mehrotra predictor-corrector to quadratic objective terms.

### Linearized Complementarity System for QP
Incorporating Hessian $Q \Delta x$ directly into the Newton normal equations.

### Augmented System Formulation for QP
Solving the symmetric indefinite saddle-point system $\begin{bmatrix} Q + \Theta^{-1} & A^T \\ A & 0 \end{bmatrix}$.

### LDL^T Factorization of Indefinite Saddle System
Using Bunch-Parlett or symmetric indefinite pivoting for saddle-point stability.

### Refinery Blend Optimization QP Model
Balancing octane give-away penalty against component cost trade-offs.

### Nonlinear Viscosity Blending via QP Approximation
Refining Refutas viscosity index blending using local quadratic approximations.

### Emissions Abatement Cost Curve Modeling
Quadratic marginal abatement cost curves for refinery carbon capture investments.

### Thermal Efficiency & Furnace Heat Loss QP
Modeling non-linear radiative heat losses in atmospheric distillation furnaces.

### Crude Distillation Yield Deviation Penalties
Penalizing deviation from nominal cut temperatures in CDU and VDU operations.

### Hydrogen Network Pressure Drop QP
Quadratic hydraulic resistance across high-pressure hydrotreater piping loops.

### Tank Farm Working Ullage Safety Buffers
Quadratic penalty on tank levels approaching minimum heel or overflow limits.

### Multi-Period Demurrage Soft Constraint Penalties
Quadratic penalty on vessel waiting times beyond contracted laytime.

### Catalyst Deactivation Rate Minimization
Optimizing reformer severity to minimize exponential catalyst coking rates.

### Steam Header Venting & Letdown Penalties
Quadratic penalization of high-pressure to low-pressure steam letdown throttling.

### Cooling Water Temperature Rise Constraints
Environmental limits on heat discharge to coastal water bodies.

### Flare Gas Minimization Quadratic Model
Penalizing flaring events during unit upsets and mode transitions.

### Power Grid Demand Charge Peak Shaving
Quadratic penalty on peak electrical megawatt consumption from external grid.

### Desalter Salt Removal Efficiency Optimization
Optimizing wash water injection rate against downstream corrosion costs.

### FCCU Catalyst Regeneration Air Blower Limits
Quadratic fan power curves vs coke combustion kinetics in regenerator.

### Alkylation Acid Consumption Minimization
Balancing acid makeup rate against alkylate octane rating.

### Delayed Coker Cycle Time Optimization
Scheduling drum decoking cycles to maximize liquid yield vs coke formation.

### QP Model Verification & Solvability Checks
Automated validation of Hessian matrix symmetry and strict convexity.

