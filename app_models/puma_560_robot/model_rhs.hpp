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

	// x[0:2]	theta_vel[3]
	// x[3:5]	theta_pos[3]

	x_dot.theta_vel()=mid.angular_vec().subvec(0,2);
	x_dot.theta_vel()=Model::limit_D_states3(x.theta_vel(),x_dot.theta_vel(),10.0);

	x_dot.theta_pos()=x.theta_vel();
	x_dot.theta_pos()=Model::limit_D_states3(x.theta_pos(),x_dot.theta_pos(),10.0);

	// x_dot.theta_vel()=mid.angular_vec().subvec(0,2);
	// for(uint k=x.index_theta_vel_0;k<=x.index_theta_vel_end;k++)
	// 	if(std::abs(x(k))>=10.0 && x(k)*x_dot(k)>0)
	// 		x_dot(k)=0.0; // integral limit

	// x_dot.theta_pos()=x.theta_vel();
	// for(uint k=x.index_theta_pos_0;k<=x.index_theta_pos_end;k++)
	// 	if(std::abs(x(k))>=10.0 && x(k)*x_dot(k)>0)
	// 		x_dot(k)=0.0; // integral limit

}