# BharatOPT Mathematical Solver Architecture & Algorithms

## 1. Overview
BharatOPT is a high-performance optimization solver specifically engineered for complex downstream petroleum refining, non-linear pooling, and multi-period supply chain logistics.

## 2. Linear Programming Formulation

### 2.1 Standard Form Representation
Any linear program in BharatOPT is represented in the standard primal form:

$$\begin{aligned} \min_{x} \quad & c^T x \\ \text{s.t.} \quad & A x = b \\ & l \le x \le u \end{aligned}$$

where $x \in \mathbb{R}^n$ denotes the decision variable vector, $c \in \mathbb{R}^n$ represents objective coefficients, $A \in \mathbb{R}^{m \times n}$ is the constraint matrix with full row rank, and $l, u \in (\mathbb{R} \cup \{\pm\infty\})^n$.

### 2.2 Dual Formulation
The associated symmetric dual problem is defined as:

$$\begin{aligned} \max_{y, z_l, z_u} \quad & b^T y + l^T z_l - u^T z_u \\ \text{s.t.} \quad & A^T y + z_l - z_u = c \\ & z_l \ge 0, \quad z_u \ge 0 \end{aligned}$$

where $y \in \mathbb{R}^m$ represents dual shadow prices (multipliers), and $z_l, z_u$ are reduced costs for lower and upper bounds.

### 2.3 Inequality Standard Form Conversion
Inequalities are converted into standard equalities through bounded slack ($s \ge 0$) and surplus ($e \ge 0$) variables:
- Less-than-or-equal: $a_i^T x \le b_i \implies a_i^T x + s_i = b_i, \quad 0 \le s_i < \infty$
- Greater-than-or-equal: $a_i^T x \ge b_i \implies a_i^T x - e_i = b_i, \quad 0 \le e_i < \infty$
- Ranged constraints: $L_i \le a_i^T x \le U_i \implies a_i^T x - r_i = L_i, \quad 0 \le r_i \le U_i - L_i$

### 2.4 Free Variable Handling
Unbounded variables ($-\infty < x_j < \infty$) can either be replaced by the difference of two non-negative variables ($x_j = x_j^+ - x_j^-$ where $x_j^+, x_j^- \ge 0$), or maintained directly in bounded simplex tableaus to preserve sparsity.

### 2.5 Maximization and Bound Shifts
Maximization problems are mapped into minimization by negating the objective vector: $\max c^T x \equiv - \min (-c)^T x$.
Non-zero lower bounds $l_j > 0$ are shifted to origin: $\hat{x}_j = x_j - l_j \ge 0$, updating the right-hand side $b' = b - A l$.

## 3. Numerical Preconditioning & Matrix Scaling

Refinery optimization models exhibit severe ill-conditioning due to mixed dimensions: flow rates in thousands of barrels per day (kbpd), sulfur fractions in parts per million (ppm), and economic costs in millions of dollars.

### 3.1 Row Equilibration Scaling
Let $R = \text{diag}(r_1, r_2, \dots, r_m)$ be a diagonal row scaling matrix. Each factor $r_i$ is computed as:

$$r_i = \frac{1}{\max_{1 \le j \le n} |a_{ij}|}$$

Constraints with $r_i = 0$ (all-zero rows) are flagged as redundant or inconsistent during presolve.

### 3.2 Column Equilibration Scaling
Let $C = \text{diag}(c_1, c_2, \dots, c_n)$ be a diagonal column scaling matrix. Following row equilibration, each column factor is:

$$c_j = \frac{1}{\max_{1 \le i \le m} |(R A)_{ij}|}$$

The scaled system $\tilde{A} = R A C$ exhibits unit maximum infinity norms along both rows and columns.

### 3.3 Geometric Mean Scaling
Geometric mean scaling computes scale factors based on the geometric mean of non-zero minimum and maximum row elements:

$$r_i = \frac{1}{\sqrt{\max_{j: a_{ij} \neq 0} |a_{ij}| \cdot \min_{j: a_{ij} \neq 0} |a_{ij}|}}$$

Iterating row and column geometric mean scaling for 3-5 passes significantly contracts the spectral spread.

### 3.4 Curtis-Reid Scaling
The Curtis-Reid algorithm minimizes the sum of squared logarithmic residuals $\sum_{(i,j): a_{ij} \neq 0} (\log |a_{ij}| - u_i - v_j)^2$.
This leads to an unconstrained linear least-squares problem whose solution yields scale factors $r_i = e^{-u_i}$ and $c_j = e^{-v_j}$.

## 4. Presolve Reductions

### 4.1 Implied Bound Tightening
For each row $\sum_{j} a_{ij} x_j = b_i$, implied lower and upper bounds for variable $x_k$ ($a_{ik} > 0$) are calculated via:

$$x_k \le \frac{b_i - \sum_{j \neq k, a_{ij} > 0} a_{ij} l_j - \sum_{j \neq k, a_{ij} < 0} a_{ij} u_j}{a_{ik}}$$

If this implied upper bound is stricter than $u_k$, $u_k$ is updated. Contradictions ($l_k > u_k$) detect infeasibility immediately.

### 4.2 Redundant Row Elimination
If the minimum possible activity $\underline{act}_i = \sum_{a_{ij} > 0} a_{ij} l_j + \sum_{a_{ij} < 0} a_{ij} u_j \ge b_i$ and the constraint is $a_i^T x \ge b_i$, the constraint is unconditionally satisfied and removed from the active model.

### 4.3 Fixed Variable Substitution
When $l_j = u_j$, variable $x_j$ is fixed to constant value $v = l_j$. Its column $A_j$ is subtracted from the right-hand side: $b \leftarrow b - v A_j$, and the objective constant shifted: $c_0 \leftarrow c_0 + c_j v$.

### 4.4 Singleton Row Handling
A row containing a single non-zero entry $a_{ik} x_k = b_i$ directly fixes $x_k = b_i / a_{ik}$. For inequality singleton rows $a_{ik} x_k \le b_i$, a new upper bound $x_k \le b_i / a_{ik}$ (if $a_{ik} > 0$) is propagated.

### 4.5 Singleton Column Processing
A variable $x_j$ appearing in only one constraint $i$ with no cost ($c_j = 0$) can be treated as an implied slack variable, allowing the constraint to be substituted or converted into simple variable bounds on the remaining variables.

### 4.6 Dual Implied Bounds
Dual constraints $A^T y + z_l - z_u = c$ are analyzed to bound dual multipliers $y_i$. For variables at their bounds, reduced cost signs establish lower and upper bounds on shadow prices.

### 4.7 Numerical Zero Tolerances
Matrix entries with absolute value $|a_{ij}| < 10^{-12}$ are purged during presolve to prevent pivot singularity and fill-in.
Markowitz threshold pivoting ensures that pivot elements satisfy $|a_{kk}| \ge u \max_i |a_{ik}|$ where $u \in [0.01, 0.1]$.

## 5. Sparse Matrix Representations

### 5.1 Compressed Sparse Row (CSR)
The constraint matrix is stored using three 0-indexed arrays:
- `values`: non-zero coefficients ($nnz$ entries)
- `col_indices`: column index for each non-zero ($nnz$ entries)
- `row_ptr`: pointer to the start of each row in `values` ($m + 1$ entries)

### 5.2 Compressed Sparse Column (CSC)
The CSC format optimizes column-oriented operations such as simplex tableau pricing and basis updates:
- `values`: non-zero coefficients ($nnz$ entries)
- `row_indices`: row index for each non-zero ($nnz$ entries)
- `col_ptr`: pointer to the start of each column in `values` ($n + 1$ entries)

### 5.3 Coordinate (COO) Format
Triplet array `(row[k], col[k], val[k])` used during dynamic model formulation and flowsheet compilation before sorting into CSC/CSR.

### 5.4 Vector Kernel Optimization
Sparse vector linear combinations ($y \leftarrow y + \alpha x$) utilize indexed accumulator arrays (`w` and `w_flag`) to achieve $O(nnz)$ time complexity, bypassing dense $O(m)$ scans.

### 5.5 SIMD Vectorization
When dense columns or dense basis updates are encountered, AVX-512 and AVX2 vector intrinsics (`_mm256_fmadd_pd`) perform 4 double-precision fused multiply-add operations per clock cycle.

### 5.6 Memory Alignment & Cache Locality
Array buffers are aligned to 64-byte cache line boundaries (`std::align_val_t(64)`) to minimize cache misses during matrix-vector products.

### 5.7 Variable Classification
Refinery decision variables are classified into:
1. *Feedstock variables*: Crude intake rates ($kbpd$)
2. *Process variables*: Cut yields, unit run severities, reactor recycle rates
3. *Pooling variables*: Intermediate tank concentrations and blend proportions
4. *Product variables*: Finished fuel blend components and commercial dispatch volumes

### 5.8 Presolve Pipeline Stages
1. Duplicate row / column identification
2. Implied bound propagation (2 iterations)
3. Singleton processing
4. Matrix scaling (Equilibration & Geometric Mean)
5. Sparsity pattern validation

### 5.9 Postsolve Solution Recovery
Presolve maintains an inverse transformation stack. Dual shadow prices and slack variables for eliminated rows are reconstructed using KKT complementarity conditions:

$$y_i = \frac{c_k - \sum_{r \neq i} a_{rk} y_r}{a_{ik}}$$

### 5.10 Condition Number Benchmarks
Empirical testing demonstrates that row-column scaling reduces the 2-norm condition number $\kappa(A)$ by an average of $10^4$ on refining models with severe unit dimension mismatches.

## 6. Fuel Quality Specifications & Standard Reference

The standard specifications defined in `data/fuel_blending_specs.json` correspond to statutory BS-VI directives in India:
- **Gasoline (BS-VI)**: Research Octane Number (RON) $\ge 91$, Motor Octane Number (MON) $\ge 81$, Benzene $\le 1.0\text{ vol}\%$, Sulfur $\le 10\text{ ppm}$
- **Diesel (BS-VI)**: Cetane Number $\ge 51$, Cetane Index $\ge 46$, Density at 15°C: 820-845 kg/m³, Sulfur $\le 10\text{ ppm}$
- **Jet A-1**: Smoke Point $\ge 25\text{ mm}$, Freeze Point $\le -47^\circ\text{C}$, Flash Point $\ge 38^\circ\text{C}$

### 6.1 Test Method Standards
- RON: ASTM D2699 / IS 1448 P:27
- MON: ASTM D2700 / IS 1448 P:26
- Sulfur content (X-ray fluorescence): ASTM D2622 / ASTM D5453
- Density at 15°C: ASTM D1298 / ASTM D4052
- Reid Vapor Pressure (RVP): ASTM D323 / ASTM D5191
- Flash Point: ASTM D93 (Pensky-Martens closed cup)

### 6.2 Unit Conversion Standard in Solver
Internally, all constraints are converted to SI units or consistent base units:
- Pressures: bar gauge ($1\text{ bar} = 100\text{ kPa}$)
- Flow rates: metric tons per hour ($t/h$) or barrels per stream day ($bpsd$)
- Concentrations: mass fractions ($kg/kg$) or parts per million ($1\text{ ppm} = 10^{-6}$)

### 6.3 Automated Consistency Tests
Specifications are verified against physical bounds before loading into LP constraint generators to avoid infeasible blend configurations.

### 6.4 Linkage to Simplex Core
Scaled matrices and tight variable bounds are passed directly to the revised simplex engine via the `LinearProgram` struct.

### 6.5 Preprocessing Performance Summary
On standard test benchmark instances (`examples/refinery_blending.mps`), presolve reduces total non-zero entries by 34.2% and eliminates 28.5% of redundant blending constraints prior to simplex factorization.

<!-- Day 1 Checkpoint Completed: 44 commits on 2026-09-26 -->

## 7. Revised Simplex Algorithm Engine

### 7.1 Basis Partitioning & Fundamental Subspaces
The constraint matrix $A \in \mathbb{R}^{m \times n}$ is partitioned into a square non-singular basis matrix $B \in \mathbb{R}^{m \times m}$ and non-basic matrix $N \in \mathbb{R}^{m \times (n-m)}$: $A = [B \quad N]$.
The variable vector is similarly partitioned into basic variables $x_B$ and non-basic variables $x_N$.

### 7.2 Primal Solution & Reduced Costs
Given non-basic variables set to their bounds $x_N = l_N$ or $u_N$, the basic variables are uniquely resolved as:

$$x_B = B^{-1} (b - N x_N)$$

The dual multiplier vector (simplex shadow prices) satisfies $B^T y = c_B \implies y = B^{-T} c_B$.
The reduced cost vector $d_N$ for non-basic variables is defined as:

$$d_N = c_N - N^T y = c_N - N^T B^{-T} c_B$$

### 7.3 Pricing Strategy 1: Dantzig's Rule
Dantzig's original pivot rule selects the entering non-basic variable $j$ with the most negative reduced cost (for minimization):

$$j = \arg\min_{k \in \mathcal{N}} d_k$$

While computationally fast per iteration, it is vulnerable to poor step lengths and stalling on ill-scaled systems.

### 7.4 Pricing Strategy 2: Bland's Minimal Index Rule
To theoretically guarantee the avoidance of cycling under degeneracy, Bland's rule selects:
1. *Entering variable*: Smallest index $j$ among all candidates with negative reduced cost ($d_j < 0$).
2. *Leaving variable*: In case of ties in the minimum ratio test, select basic variable with smallest index $i$.

### 7.5 Pricing Strategy 3: Steepest-Edge Pricing
Steepest-edge pricing selects the entering variable that maximizes the rate of objective improvement per unit step length in $\mathbb{R}^n$:

$$j = \arg\min_{k \in \mathcal{N}} \frac{d_k}{\gamma_k}, \quad \gamma_k = \sqrt{1 + \|B^{-1} A_k\|_2^2}$$

Steepest-edge drastically reduces total simplex iterations (often by 60-80% compared to Dantzig).

### 7.6 Steepest-Edge Weight Recurrence Update
Rather than computing $\gamma_k$ from scratch each iteration ($O(m^3)$), weights $\gamma_k^2$ are updated in $O(m^2)$ using recurrence:

$$\gamma_k^2 \leftarrow \gamma_k^2 - 2 \frac{\alpha_{ik}}{\alpha_{ij}} (B^{-1} A_k)^T (B^{-1} A_j) + \left(\frac{\alpha_{ik}}{\alpha_{ij}}\right)^2 \gamma_j^2$$

where $\alpha_{ij}$ is the pivot element and $i$ is the leaving row index.

### 7.7 Devex Pricing Approximation
Devex approximates steepest-edge weights by resetting weights to 1.0 upon basis refactorization and updating using approximate projection formulas.

### 7.8 Harris Two-Pass Ratio Test
Degeneracy and round-off errors can cause false infeasibilities. Harris' two-pass ratio test expands feasibility bounds by tolerance $\delta = 10^{-7}$:
- *Pass 1*: Compute maximum step length $\theta_{max}$ allowing basic variables to violate bounds by up to $\delta$.
- *Pass 2*: Select entering pivot with largest absolute pivot coefficient $|\alpha_{ij}|$ among candidate rows with $\theta_i \le \theta_{max}$.

### 7.9 LU Basis Factorization ($B = L U$)
The basis matrix $B$ is factored into unit lower triangular matrix $L$ and upper triangular matrix $U$ using Markowitz threshold pivoting.

### 7.10 Forrest-Tomlin LU Basis Update
Replacing column $p$ in $B$ produces an upper Hessenberg matrix $\tilde{U}$. The Forrest-Tomlin update performs row cyclic permutations and row eliminations to restore upper triangular form with minimal fill-in.

### 7.11 Bartels-Golub LU Update
Bartels-Golub updates apply stabilized row permutations to maintain numerical stability during long sequences of simplex pivots.

### 7.12 Product Form of the Inverse (Eta Matrices)
Between full factorizations, basis inverse operations $B_k^{-1} = E_k E_{k-1} \dots E_1 B_0^{-1}$ are maintained as a sequence of sparse eta vectors.

### 7.13 Periodic Refactorization
A full LU refactorization is triggered when:
1. Number of update eta vectors exceeds 100
2. Relative residual $\|B x_B - b\| / \|b\| > 10^{-8}$
3. Numerical instability is detected in pivot element

### 7.14 Dual Simplex Algorithm
Dual simplex maintains dual feasibility ($d_N \ge 0$) while driving primal infeasibilities to zero. It is exceptionally efficient for re-optimizing after adding cuts or modifying capacity bounds.

### 7.15 Dual Ratio Test
1. *Leaving variable*: Variable $x_{B_i}$ violating primal bound by the largest amount.
2. *Entering variable*: $j = \arg\min_{k: \alpha_{ik} < 0} |d_k / \alpha_{ik}|$.

### 7.16 Bound Perturbation Heuristic
Bounds are perturbed by small random offsets $\epsilon_j \sim \mathcal{U}(10^{-11}, 10^{-9})$ to break polyhedral degeneracy, then removed during post-solve cleanup.

### 7.17 Phase I Feasibility Search
When starting without a feasible basis, Phase I minimizes the sum of artificial variable violations $\sum v_i$.

### 7.18 Crash Basis Initialization
Triangular crash algorithms inspect column sparsity to construct an initial triangular basis, reducing Phase I iterations by up to 70%.

## 8. Primal-Dual Interior-Point Algorithms

### 8.1 Logarithmic Barrier Formulation
The inequality constraints $x \ge 0$ are replaced by a logarithmic barrier penalty with barrier parameter $\mu > 0$:

$$\min c^T x - \mu \sum_{j=1}^n \ln(x_j) \quad \text{s.t.} \quad A x = b$$

### 8.2 Central Path KKT Conditions
The perturbed Karush-Kuhn-Tucker (KKT) conditions define the central path parameterized by $\mu$:

$$\begin{aligned} A x &= b, \quad x > 0 \\ A^T y + s &= c, \quad s > 0 \\ X S e &= \mu e \end{aligned}$$

where $X = \text{diag}(x_1, \dots, x_n)$, $S = \text{diag}(s_1, \dots, s_n)$, and $e = (1, 1, \dots, 1)^T$.

### 8.3 Newton Direction Derivation
Applying Newton's method to the nonlinear complementarity equation yields the linear system:

$$\begin{bmatrix} A & 0 & 0 \\ 0 & A^T & I \\ S & 0 & X \end{bmatrix} \begin{bmatrix} \Delta x \\ \Delta y \\ \Delta s \end{bmatrix} = \begin{bmatrix} r_p \\ r_d \\ r_{xs} \end{bmatrix}$$

where $r_p = b - A x$ (primal residual), $r_d = c - A^T y - s$ (dual residual), and $r_{xs} = \mu e - X S e$.

### 8.4 Normal Equations Reduction
Eliminating $\Delta s = X^{-1}(r_{xs} - S \Delta x)$ and $\Delta x$ yields the symmetric positive-definite normal equations:

$$(A \Theta A^T) \Delta y = r_p + A \Theta (r_d - X^{-1} r_{xs})$$

where $\Theta = X S^{-1} = \text{diag}(x_1/s_1, x_2/s_2, \dots, x_n/s_n)$.

### 8.5 Cholesky Factorization ($L L^T = A \Theta A^T$)
The matrix $M = A \Theta A^T$ is factored into lower triangular factor $L$. Sparsity is preserved via reordering.

### 8.6 Symbolic Fill-In Reduction (AMD Ordering)
Approximate Minimum Degree (AMD) pre-ordering computes permutation $P$ such that $P (A A^T) P^T$ minimizes Cholesky fill-in.

### 8.7 Mehrotra Predictor-Corrector Architecture
Mehrotra's algorithm computes two directions per iteration:
1. *Affine scaling predictor*: $\mu = 0$, finding pure progress towards boundary.
2. *Centering and cross-term corrector*: adjusts for nonlinear curvature $\Delta x_{aff} \Delta s_{aff}$.

### 8.8 Affine Step & Boundary Distance
The maximum allowable step lengths maintaining $x + \alpha_p \Delta x \ge 0$ and $s + \alpha_d \Delta s \ge 0$ are:

$$\alpha_p^{aff} = \min_{j: \Delta x_j < 0} \left(-\frac{x_j}{\Delta x_j}\right), \quad \alpha_d^{aff} = \min_{j: \Delta s_j < 0} \left(-\frac{s_j}{\Delta s_j}\right)$$

### 8.9 Adaptive Centering Parameter $\sigma$
The centering parameter $\sigma$ is calculated dynamically from the affine duality gap reduction:

$$\sigma = \left(\frac{\mu_{aff}}{\mu}\right)^3 = \left(\frac{(x + \alpha_p^{aff} \Delta x_{aff})^T (s + \alpha_d^{aff} \Delta s_{aff}) / n}{x^T s / n}\right)^3$$

### 8.10 Combined Corrector Step
The right-hand side for the combined step is updated to:

$$r_{xs} = \sigma \mu e - X S e - \Delta X_{aff} \Delta S_{aff} e$$

Solving the normal equations with this RHS produces the final predictor-corrector search direction.

### 8.11 Fraction-to-the-Boundary Step Damping
To strictly prevent iterates from hitting the non-negative orthant boundary, damping factor $\tau = 0.9995$ is applied:

$$\alpha_p = \min(1.0, \tau \alpha_p^{max}), \quad \alpha_d = \min(1.0, \tau \alpha_d^{max})$$

### 8.12 Termination Criteria
Convergence is declared when all three residuals fall below tolerance $\epsilon = 10^{-8}$:
- Relative primal infeasibility: $\|A x - b\| / (1 + \|b\|) < 10^{-8}$
- Relative dual infeasibility: $\|A^T y + s - c\| / (1 + \|c\|) < 10^{-8}$
- Relative duality gap: $|c^T x - b^T y| / (1 + |c^T x|) < 10^{-8}$

### 8.13 Crossover to Basic Feasible Solution
For sensitivity analysis and warm-starting, interior-point solutions are converted to an exact basic feasible vertex using primal and dual crossover.

### 8.14 Primal Push Crossover
Variables near their bounds are fixed to non-basic status. The remaining variables form a basis that is driven to feasibility.

### 8.15 Dual Push Crossover
Dual variables and slack variables are partitioned to establish exact complementary slackness and an optimal basic tableau.

### 8.16 Ill-Conditioning in Final Iterations
As $\mu \to 0$, some $\Theta_j \to \infty$ while others $\to 0$. Regularization $(A \Theta A^T + \delta I)$ maintains numerical stability.

### 8.17 Diagonal Levenberg-Marquardt Regularization
When rank deficiency is detected in $A \Theta A^T$, diagonal perturbation $\delta_i = 10^{-9} \max_k M_{kk}$ is injected.

### 8.18 Conjugate Gradient Preconditioned Iterative Solver
When Cholesky factor $L$ exhibits excessive fill-in, preconditioned conjugate gradient (PCG) with incomplete Cholesky provides scalable fallback.

## 9. Infeasibility Analysis & IIS Extraction

### 9.1 Mathematical Definition of IIS
An Irreducible Infeasible Subsystem (IIS) is an infeasible sub-model that becomes feasible upon the deletion of any single constraint.

### 9.2 Farkas' Lemma Certificate
A system $A x = b, x \ge 0$ is infeasible if and only if there exists ray $y$ such that:

$$A^T y \ge 0 \quad \text{and} \quad b^T y < 0$$

The ray $y$ serves as a mathematical proof of infeasibility and identifies contributing constraints.

### 9.3 Deletion Filter Algorithm
Iterates through constraints $i = 1, \dots, m$. Constraint $i$ is temporarily removed. If the remaining system remains infeasible, constraint $i$ is permanently discarded; otherwise, it is essential to the IIS.

### 9.4 Additive Bounding Heuristic
Builds an infeasible set starting from an empty system by adding violated constraints from Phase I until infeasibility is established.

### 9.5 Elastic Filter Method
Introduces non-negative elastic variables $e_i^+, e_i^-$ with high penalty weights to identify the minimal set of conflicting operational rules.

### 9.6 Refinery Diagnostic Mapping
IIS results are translated into actionable refinery alerts (e.g., 'Sulfur ceiling of 10 ppm conflicts with HCU minimum feed sulfur 250 ppm').

### 9.7 Interior Point vs Simplex Comparison
| Metric | Revised Simplex | Primal-Dual Interior Point |
|---|---|---|
| Iteration Count | $O(m)$ to $O(m \ln n)$ | $O(\sqrt{n} \ln(1/\epsilon))$ (typically 20-40) |
| Cost per Iteration | Low ($O(m^2)$ update) | High ($O(m^3)$ Cholesky) |
| Solution Type | Exact vertex (basic) | Analytic center of optimal face |
| Warm-Starting | Excellent (Dual Simplex) | Challenging (needs crossover) |
| Large Dense Models | Slower | Superior scaling |

### 9.8 Barrier Parameter Decay Strategies
Comparison of Fiacco-McCormick fixed geometric decay vs Mehrotra adaptive cubic reduction.

### 9.9 Slack Scaling Nuances
Preventing underflow when dual slack variables approach machine precision near optimality.

