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

