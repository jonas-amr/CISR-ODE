
// *** Warning:
// *** auto-generated file and subjected to be overwritten

// path: ./app_models/classical_washoutfilter/autogenerated/model_observer.hpp

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

	// y0	surge_input_acc_ref;
	// y1	surge_hp_out;
	// y2	surge_kin_acc;
	// y3	surge_kin_vel;
	// y4	surge_kin_pos;
	// y5	surge_lp_out;
	// y6	specific_force;

	ymat(outputs::surge_input_acc_ref)=mid(mid.index_surge_input_acc_ref);
	ymat(outputs::surge_hp_out)=mid(mid.index_surge_hp_out);
	ymat(outputs::surge_kin_acc)=mid(mid.index_surge_kin_acc);
	ymat(outputs::surge_kin_vel)=mid(mid.index_surge_kin_vel);
	ymat(outputs::surge_kin_pos)=mid(mid.index_surge_kin_pos);
	ymat(outputs::surge_lp_out)=mid(mid.index_surge_lp_out);
	ymat(outputs::specific_force)=mid(mid.index_specific_force);

}
