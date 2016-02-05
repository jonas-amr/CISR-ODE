#include <armadillo>
#include "model.hpp"

void Model::rhs(
	const states_type 	&x,
	states_type 		&x_dot,
	const time_type		&t,
	const mids_type 	&last_observed_mids,
	const time_type 	&last_observed_t,
	inputs_type			&u
	)
{
	// ******* system implementation *******
	mids_type mid;
	intermediates(u,x,mid,t,last_observed_mids,last_observed_t);

	_unused(t);
	_unused(x);
	_unused(last_observed_mids);
	_unused(last_observed_t);
	_unused(u);

	static arma::mat::fixed<2*N,2*N> A_mat=get_A();

	x_dot=A_mat*x.data;
	x_dot(x_dot.index_phi_0)+=mid.v_in();
}