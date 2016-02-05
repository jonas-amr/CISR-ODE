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
	_unused(x);
	_unused(u);
	_unused(mid);
	_unused(last_observed_t);
	_unused(last_observed_mids);

	// list of intermediates goes here

	// assigning intermediates

}