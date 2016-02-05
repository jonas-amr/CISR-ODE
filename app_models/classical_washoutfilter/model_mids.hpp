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
	_unused(last_observed_mids);
	_unused(last_observed_t);

	// m0	surge_input_acc_ref
	// m1	surge_hp_out
	// m2	surge_kin_acc
	// m3	surge_kin_vel
	// m4	surge_kin_pos
	// m5	surge_lp_out
	// m6	tilt_coordination
	// m7	pitch_input_angle_ref
	// m8	pitch_hp_out
	// m9	pitch_angle
	// m10	tilt_force
	// m11	specific_force

	const double max_acc=platform::max_acc;
	const double g=platform::g;

	mid.surge_input_acc_ref()=u.surge_acc();
	mid.surge_hp_out()=hp_surge_out(mid,x);
	mid.surge_kin_acc()=std::max(-max_acc,std::min(+max_acc,mid.surge_hp_out()));
	mid.surge_kin_vel()=x.surge_kin_vel();
	mid.surge_kin_pos()=x.surge_kin_pos();
	mid.surge_lp_out()=lp_surge_out(x);
	mid.tilt_coordination()=mid.surge_lp_out()/g;
	mid.pitch_input_angle_ref()=u.pitch_angle();
	mid.pitch_hp_out()=hp_pitch_out(mid,x);
	mid.pitch_angle()=mid.tilt_coordination()+mid.pitch_hp_out();
	mid.tilt_force()=mid.pitch_angle()*g;
	mid.specific_force()=mid.tilt_force()+mid.surge_kin_acc();
}
