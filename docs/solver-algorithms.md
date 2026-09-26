# BharatOPT Mathematical Solver Architecture & Algorithms

## 1. Overview
BharatOPT is a high-performance optimization solver specifically engineered for complex downstream petroleum refining, non-linear pooling, and multi-period supply chain logistics.

## 2. Linear Programming Formulation

### 2.1 Standard Form Representation
Any linear program in BharatOPT is represented in the standard primal form:

$$\begin{aligned} \min_{x} \quad & c^T x \\ \text{s.t.} \quad & A x = b \\ & l \le x \le u \end{aligned}$$

where $x \in \mathbb{R}^n$ denotes the decision variable vector, $c \in \mathbb{R}^n$ represents objective coefficients, $A \in \mathbb{R}^{m \times n}$ is the constraint matrix with full row rank, and $l, u \in (\mathbb{R} \cup \{\pm\infty\})^n$.

