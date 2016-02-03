/**********************************************

This code file is available under LGPL (v 2.1)
GNU Lesser General Public License, version 2.1

http://www.gnu.org/licenses/lgpl-2.1.html

**********************************************/

/*
This file contains a continuous-time algebraic Riccati equation solver based on the explanations from Dr. Vasile Sima.
Further reference: Sima, Vasile. Algorithms for linear-quadratic optimization. Vol. 200. CRC Press, 1996.
*/

// A C++ implementation of a Continuous-time Algebraic Riccati Equation (CARE) solver based on Schur vectors.

// Solves a CARE, A'X + XA - XBR^(-1)B'X + Q = 0, using Schur vectors method, with A and Q n-by-n, B n-by-m, and R m-by-m real matrices, and Q and R symmetric, R positive definite. It is assumed, e.g., that the matrix pair (A,B) is stabilizable, and the matrix pair (C,A) is detectable, where Q = C'C, and rank(C) = rank(Q).

// Main steps:

// 1. Construct the Hamiltonian matrix H, H = [ A -B*(R\B'); Q -A' ]; (in MATLAB notation).

// 2. Reduce H to a real Schur form S and accumulate the transformations in U, S = U'HU, U orthogonal.

// 3. Reorder the real Schur form S so that all n stable eigenvalues are moved to the leading part of S, accumulating the transformations in U.

// 4. Compute the unique positive-semidefinite stabilizing solution X, X = U(n+1:2n,1:n)*U(1:n,1:n)^(-1).

// 5. Symmetrize X, X = ( X + X' )/2.


/*

C++ Implementation:

*/

#include "control_system_essential.hpp"

NS_CONTROL_SYSTEM_BEGIN

extern "C"
{
	void dtrexc_(
				const char *COMPQ,
				const int *N,
				double *T,
				const int *LDT,
				double *Q,
				const int *LDQ,
				int *IFST,
				int *ILST,
				double *WORK,
				int *INFO);
}

int reorder_schur(
	arma::mat U,
	arma::mat T,
	arma::mat &US,
	arma::mat &TS,
	arma::uvec newIndex
	)
{
	if(U.n_rows!=U.n_cols)
		throw std::runtime_error("Matrix U is not square! (reorder_schur)");
	if(T.n_rows!=T.n_cols)
		throw std::runtime_error("Matrix T is not square! (reorder_schur)");
	if(newIndex.n_rows!=U.n_rows)
		throw std::runtime_error("Vector newIndex does not have appropriate length");

	int N=U.n_rows;
	int info;


	std::vector<int> index_from;
	std::vector<int> index_to;
	index_from.reserve(N);
	index_to.reserve(N);
	arma::vec work=arma::zeros<arma::vec>(N);

	for(int i=0;i<N;i++)
	{
		// indices are 1 based
		index_from.push_back(i+1);
		index_to.push_back( (int)newIndex(i)+1 );
	}

	char COMPQ='V';
	US=U;
	TS=T;

	// call dtrexc from lapack 
	dtrexc_(
		&COMPQ,
		&N,
		TS.memptr(),
		&N,
		US.memptr(),
		&N,
		index_from.data(),
		index_to.data(),
		work.memptr(),
		&info
	);

	if (info<0)
		std::cerr<< "info = " << info << std::endl;
	if(info<0)
		throw std::runtime_error("Unsuccessful reordering Schur factorization!");
	return info;
}


class Riccati_Schvc
{
protected:
	arma::mat X;
	arma::cx_vec L;

public:

	const arma::mat& get_X() const
	{
		return X;
	}

	const arma::cx_vec& get_L() const
	{
		return L;
	}

	// Solves ARE  A'X + XA - XBR^(-1)B'X + Q = 0 using Schur vectors method.
	Riccati_Schvc (
		const arma::mat &A,
		const arma::mat &B,
		const arma::mat &Q,
		const arma::mat &R)
	{
		set(A,B,Q,R);
	}


	void set(
		const arma::mat &A,
		const arma::mat &B,
		const arma::mat &Q,
		const arma::mat &R)
	{

		const double eps10=2.22e-16*10.0;
		if(arma::norm(Q-Q.t(),1)/std::max(1.0,arma::norm(Q,1))>eps10)
			throw std::runtime_error("Q matrix is not symmetric");
		if(arma::norm(R-R.t(),1)/std::max(1.0,arma::norm(R,1))>eps10)
			throw std::runtime_error("R matrix is not symmetric");


		arma::uword N=A.n_rows;

		// 1. Construct the Hamiltonian matrix H.
		// 	  Ensure that BR^(-1)B' and Q are trully symmetric.
		arma::mat Rinv_BT=arma::solve(R,B.t());
		arma::mat H_row1=join_rows(A, -B*Rinv_BT);
		arma::mat H_row2=join_rows(-Q, -A.t());
		arma::mat H=join_cols(H_row1,H_row2);

		// 2. Reduce H to (real) Schur form and accumulate the transformations in U.
		arma::mat U;
		arma::mat T;
		arma::schur(U,T,H);

		// 3. Order (real) Schur form so that all stable eigenvalues are moved to the
		//  leading part of H, accumulating the transformations in U.
	 	// Reorder the Schur form according to sorted eigenvalues.
		arma::cx_vec E;
		arma::eig_gen(E,H);
		arma::mat E_real=arma::real(E);
		arma::uvec eigen_sort_indices = sort_index(E_real);

		arma::mat US;
		arma::mat TS;
		reorder_schur(U,T,US,TS,eigen_sort_indices);

		// US = [U11, U12]
		//      [U21, U22]

		arma::mat U11 = US.submat(0,0,N-1,N-1);
		arma::mat U21 = US.submat(N,0,2*N-1,N-1);

		if(arma::cond(U11)>1000.0)
			throw std::runtime_error("Condition number of U11 is too large");

		X = arma::solve(U11.t(),U21.t());
		X = ( X + X.t() )/2;

		arma::eig_gen(L, A-B*Rinv_BT*X);

	}

};

NS_CONTROL_SYSTEM_END

