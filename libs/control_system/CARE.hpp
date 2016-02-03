
// A C++ implementation of a Continuous-time Algebraic Riccati Equation (CARE) solver based on Schur vectors.

// Solves a CARE, A'X + XA - XBR^(-1)B'X + Q = 0, using Schur vectors method, with A and Q n-by-n, B n-by-m, and R m-by-m real matrices, and Q and R symmetric, R positive definite. It is assumed, e.g., that the matrix pair (A,B) is stabilizable, and the matrix pair (C,A) is detectable, where Q = C'C, and rank(C) = rank(Q).

// Main steps:

// 1. Construct the Hamiltonian matrix H, H = [ A -B*(R\B'); Q -A' ]; (in MATLAB notation).

// 2. Reduce H to a real Schur form S and accumulate the transformations in U, S = U'HU, U orthogonal.

// 3. Reorder the real Schur form S so that all n stable eigenvalues are moved to the leading part of S, accumulating the transformations in U.

// 4. Compute the unique positive-semidefinite stabilizing solution X, X = U(n+1:2n,1:n)*U(1:n,1:n)^(-1).

// 5. Symmetrize X, X = ( X + X' )/2.

