# BharatOPT Bilinear Pooling Problem & Global Optimization Guide

## 1. Introduction
The pooling problem is a classic non-convex Non-Linear Program (NLP) that arises in petroleum refining.

### Bilinear Non-Convexities in Quality Blending
Product of total flow and pool quality creates bilinear terms.

### Haverly Pooling Problem Specification (Haverly 1)
Classic benchmark with 2 feed sources and 1 quality attribute.

### Haverly 2 Benchmark Instance with Reverse Economics
Inverted cost parameters creating multiple local optima.

### Haverly 3 Benchmark Instance with Capacity Bounds
Adding product demand bounds and pool volume constraints.

### Concentration-Based P-Formulation
Treating pool concentrations directly as continuous decision variables.

### Proportion-Based Q-Formulation (Ben-Tal et al.)
Reformulating using split fractions.

### Comparison: P-Formulation vs Q-Formulation Tightness
Q-formulation yields tighter linear relaxations.

### Hybrid PQ-Formulation (Tavallali et al.)
Combining both variable sets with redundant linking constraints.

### McCormick Convex Envelope Relaxation
Bounding bilinear term on rectangle using 4 linear inequalities.

### McCormick Underestimator 1
w >= xL*y + x*yL - xL*yL convex envelope.

### McCormick Underestimator 2
w >= xU*y + x*yU - xU*yU.

### McCormick Overestimator 1
w <= xU*y + x*yL - xU*yL concave envelope.

### McCormick Overestimator 2
w <= xL*y + x*yU - xL*yU.

### Successive Linear Programming (SLP) Core Algorithm
Iterative Taylor series first-order linearization.

### SLP Trust-Region Management
Dynamically adjusting step size bounds based on fidelity ratio.

### Feasibility-Based Bound Tightening (FBBT)
Propagating physical flow and quality bounds.

### Optimality-Based Bound Tightening (OBBT)
Solving auxiliary LPs to find tightest bounds.

### Piecewise Linear Relaxation of Bilinear Terms
Discretizing quality domain into K intervals.

### Multiplying Factor Formulation
Expressing pool exit flows as proportional fractions of inlet flows.

### Multi-Component Quality Tracking (Sulfur, Octane, Density)
Simultaneous tracking of multiple non-linear attributes.

### Crude Oil Blending at Atmospheric Distillation Inlets
Optimizing crude tank transfers to CDU desalter.

### FCCU Feedstock Pooling from Gasoil and Hydrocracker Bottoms
Blending gasoil fractions into FCCU feed.

### Reid Vapor Pressure (RVP) Non-Linearity in Gasoline Pools
Integrating Chevron RVP blending index into bilinear pool tracking.

### Viscosity Blending in Heavy Fuel Oil (HFO) Pools
Blending vacuum residue and cutter stock.

### Global Optimization Branch-and-Bound Architecture
Spatial branch-and-bound partitioning continuous domain.

### Branching Variable Selection Rules
Selecting variable with maximum McCormick violation.

### Duality Gap Closure in Spatial Branch and Bound
Convergence when NLP upper bound matches LP lower bound.

### Starting Point Heuristics for SLP
Generating initial feasible concentration guesses.

### Penalty Functions for Infeasible SLP Steps
L1-penalty formulations preventing solver stalling.

### Convergence Properties of SLP on Refinery Networks
Demonstrating quadratic local convergence.

### Standat 3-Pool Industrial Benchmark
Industrial-scale pooling network testing 3 intermediate pools.

### DeWitt Multi-Period Pooling Benchmark
Time-staged pooling model accounting for hold-up.

### RTG Industrial Refining Pooling Instance
Real-world European refinery pooling benchmark.

