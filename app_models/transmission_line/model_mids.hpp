#include <armadillo>
#include "model.hpp"

void Model::intermediates(
	const inputs_type	&u,
	const states_type	&x,
	mids_type			&mid,
	const time_type 	&t,
	const mids_type		&last_observed_mids,
	const time_type		&last_observed_t
	)
{
	_unused(t);
	_unused(u);
	_unused(last_observed_t);
	_unused(last_observed_mids);

	// m[0]	v_in
	// m[1]	v_end

	mid.v_in()=u.v_in();
	mid.v_end()=x(x.index_q_end)/physics::C;
}