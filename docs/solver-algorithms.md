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

