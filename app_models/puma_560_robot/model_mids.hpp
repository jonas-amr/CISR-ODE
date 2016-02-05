#include <armadillo>
#include "model.hpp"

using namespace arma;

void Model::intermediates(
	const inputs_type	&u,
	const states_type	&x,
	mids_type			&mid,
	const time_type 	&t,
	const mids_type		&last_observed_mids,
	const time_type		&last_observed_t
	)
{
	// m[0:2]	theta_desired[3]
	// m[3:5]	D_theta_desired[3]
	// m[6:8]	DD_theta_desired[3]
	// m[9:11]	theta[3]
	// m[12:14]	D_theta[3]
	// m[15:17]	theta_error[3]
	// m[18:20]	D_theta_error[3]
	// m[21:26]	DD_theta_controller[6]
	// m[27:32]	T[6]
	// m[33:38]	angular_vec[6]
	// m[39:41]	position[3]
	// m[42:44]	position_desired[3]
	// m[45]	error

	mid.theta_desired()=u();
	mid.D_theta_desired()=Model::derivative_range3(mid.theta_desired(),last_observed_mids.theta_desired(),t,last_observed_t);
	mid.DD_theta_desired()=Model::derivative_range3(mid.D_theta_desired(),last_observed_mids.D_theta_desired(),t,last_observed_t);
	mid.theta()=x.theta_pos();
	mid.D_theta()=x.theta_vel();

	// ********** CTC Control law **********
	mid.theta_error()=mid.theta_desired()-mid.theta();
	mid.D_theta_error()=Model::derivative_range3(mid.theta_error(),last_observed_mids.theta_error(),t,last_observed_t);

	mid.DD_theta_controller().subvec(0,2)=mid.DD_theta_desired()+15.0*mid.theta_error()+10.0*mid.D_theta_error();
	mid.DD_theta_controller().subvec(3,5).zeros();//={0,0,0};

	const double theta2=mid.theta()(1);
	const double theta3=mid.theta()(2);
	const arma::mat Inertia_mat=Model::kinetic_energy_mat(theta2,theta3);

	Model::coriolis_type B=Model::coriolis_mat(theta2,theta3);
	arma::mat C=Model::centrifugal_mat(theta2,theta3);
	arma::mat G=Model::gravity_mat(theta2,theta3);

	mid.T()=Model::to_T_vec(Inertia_mat,mid.DD_theta_controller(),B,C,G,mid.D_theta());

	// // ddtheta=....

	// // ********** 3-link Puma robot **********
	mid.angular_vec()=arma::solve(Inertia_mat, Model::to_angular_vec(mid.T(),B,C,G,mid.D_theta()));
	mid.position()=Model::angle_to_position(mid.theta());
	mid.position_desired()=Model::angle_to_position(mid.theta_desired());

	mid.error()=arma::norm(mid.position()-mid.position_desired());

}