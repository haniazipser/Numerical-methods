# Numerical Methods

This repository contains a collection of numerical algorithms implemented in C++ with a focus on performance, clarity, and extendability. The code is designed for educational and practical use in computational mathematics and engineering.

## Features

### 1. Gaussian Elimination with Iterative Refinement
- Solves systems of linear equations.
- Implements iterative refinement to improve numerical accuracy.
- Handles both well-conditioned and moderately ill-conditioned matrices.

### 2. Successive Over-Relaxation (SOR)
- Designed specifically for band (wstęgowe) matrices with non-zero elements near the diagonal.
- Efficient memory use through compact band matrix storage.
- Allows custom relaxation factor for convergence control.

### 3. Forward-Mode Automatic Differentiation
- Computes derivatives analytically at runtime.
- Handles functions of one or two variables.
- Computes first and second-order derivatives (including mixed partials).
- Implements arithmetic operations and common elementary functions (+, -, *, /, exp, sin, cos).
