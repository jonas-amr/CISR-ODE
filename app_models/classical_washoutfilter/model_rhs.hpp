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

	// x0	surge_hp_x1
	// x1	surge_hp_x2
	// x2	surge_kin_vel
	// x3	surge_kin_pos
	// x4	surge_lp_x1
	// x5	surge_lp_x2
	// x6	pitch_hp_x1

	// x_dot.surge_hp_x1()=...
	// x_dot.surge_hp_x2()=...
	hp_surge(mid,x,x_dot);

	x_dot.surge_kin_vel()=mid.surge_kin_acc();
	
	x_dot.surge_kin_pos()=mid.surge_kin_vel();

	// x_dot.surge_lp_x1()=...
	// x_dot.surge_lp_x2()=...
	lp_surge(mid,x,x_dot);

	// x_dot.pitch_hp_x1()=...
	hp_pitch(mid,x,x_dot);

}