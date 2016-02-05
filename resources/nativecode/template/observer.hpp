
#WARNING_COMMENTS#

// path: ./#TRACING_PATH#

#pragma once

void Model::observer(
	const states_type 	&x ,
	const double 		&t,
	observer_type 		&ymat,
	const mids_type 	&last_observed_mids,
	const time_type 	&last_observed_t,
	inputs_type			&u
	)
{
	mids_type mid;
	intermediates(u,x,mid,t,last_observed_mids,last_observed_t);

	#INDEX_NUMBERS_COMMENTS#

	#OUTPUT_MATRIX#

}
