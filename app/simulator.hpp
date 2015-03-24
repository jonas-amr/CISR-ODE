#pragma once

using namespace arma;

class CSimulator
{
public:

	static void rhs(
		const state_type 			&x,
		state_type 					&x_dot,
		const time_type				&t,
		const state_type 			&last_observed_x,
		// const direct_state_type 	&last_observed_direct_states,
		const time_type 			&last_observed_t
		)
	{
		// ******* system implementation *******
		input_type u;
		input(t,u);
		intermediate_type mid;
		intermediate_states(u,x,mid,t,last_observed_x,last_observed_t);

		// x0	surge_hp_x1
		// x1	surge_hp_x2
		// x2	surge_proposed_vel
		// x3	surge_kin_pos
		// x4	surge_lp_x1
		// x5	surge_lp_x2
		// x6	surgepitch_TCRL
		// x7	pitch_hp_x1
		// x8	pitch_kin_pos

		// washouts dynamics
		// x0, x1
		hp_surge(mid,x,x_dot);// influence hp surge x 1,2
		// x4, x5
		lp_surge(mid,x,x_dot);// influence lp surge x 1,2
		// x7
		hp_pitch(mid,x,x_dot);// influence hp pitch x 1

		// kinematics
		const double surge_vmax=platform::max_vel_surge;
		const double surge_xmax=platform::max_pos_surge;
		// x2, x3
		linear_dynamic_proposed(t,mid(mids::surge_proposed_acc),x,x_dot,surge_vmax,surge_xmax);

		// tilt rate limit
		// x6
		x_dot(states::surgepitch_TCRL)=mid(mids::surgepitch_TCRL_deriv);

		// x8
		x_dot(states::pitch_kin_pos)=mid(mids::pitch_kin_vel);
	}

	static void observer(
		const state_type 			&x ,
		const double 				&t,
		observer_type 				&ymat,
		const state_type 			&last_observed_x,
		const time_type 			&last_observed_t
		)
	{
		input_type u;
		intermediate_type mid;
		input(t,u);
		intermediate_states(u,x,mid,t,last_observed_x,last_observed_t);

		// surge_kin_acc
		// surge_kin_vel
		// surge_kin_pos
		// surge_hp_out
		// surge_input_acc
		// surgepitch_sp_force
		// x_proposed_vel //test
		// x_kin_pos //test
		// pitch_tilt_force

		ymat(outputs::surge_kin_acc)=mid(mids::surge_kin_acc);
		ymat(outputs::surge_kin_vel)=mid(mids::surge_kin_vel);
		ymat(outputs::surge_kin_pos)=mid(mids::surge_kin_pos);
		ymat(outputs::surge_hp_out)=mid(mids::surge_hp_out);
		ymat(outputs::surge_input_acc)=mid(mids::surge_input_acc_ref);

		ymat(outputs::pitch_tilt_force)=mid(mids::pitch_tilt_force); //test
		ymat(outputs::surgepitch_sp_force)=mid(mids::surgepitch_sp_force); //test

		const int x1=states::surge_proposed_vel; //test
		const int x2=states::surge_kin_pos; //test

		ymat(outputs::x_proposed_vel)=x(x1); //test
		ymat(outputs::x_kin_pos)=x(x2); //test
	}

	static void intermediate_states(
		const input_type &u,
		const state_type &x,
		intermediate_type &mid,
		const time_type &t,
		const state_type &last_observed_x,
		const time_type &last_observed_t
		)
	{
		// m0	surge_input_acc_ref
		// m1	surge_hp_out
		// m2	surge_proposed_acc
		// m3	surge_proposed_vel
		// m4	surge_kin_pos
		// m5	surge_kin_vel
		// m6	surge_kin_acc
		// m7	surge_lp_out
		// m8	surgepitch_TC
		// m9	surgepitch_TCRL
		// m10	surgepitch_TCRL_deriv
		// m11	pitch_input_vel_ref
		// m12	pitch_hp_out
		// m13	pitch_kin_vel
		// m14	pitch_kin_pos
		// m15	pitch_tilt_force
		// m16	surgepitch_sp_force

		_unused(t);
		_unused(last_observed_x);

		const double surge_vmax=platform::max_vel_surge;
		const double surge_xmax=platform::max_pos_surge;
		const double surge_amax=platform::max_acc_surge;
		const double surge_max_tilt_rate=platform::surge_tilt_threshold;

		// m0
		mid(mids::surge_input_acc_ref)=u(inputs::surge_acc);

		// m1
		mid(mids::surge_hp_out)=hp_surge_out(mid,x);

		// m2
		mid(mids::surge_proposed_acc)=bound(mid(mids::surge_hp_out),-surge_amax,+surge_amax); // dependant

		// m3
		mid(mids::surge_proposed_vel)=x(states::surge_proposed_vel);

		// m4
		mid(mids::surge_kin_pos)=x(states::surge_kin_pos);

		// m5, m6
		mid(mids::surge_kin_vel)=get_kinematic_surge_vel(x,surge_xmax);
		
		mid(mids::surge_kin_acc)=get_kinematic_surge_acc(x,mid(mids::surge_proposed_acc),surge_vmax,surge_xmax);

		// m7
		mid(mids::surge_lp_out)=lp_surge_out(x);
		const double surge_lp_out_old=lp_surge_out(last_observed_x);

		// m8
		mid(mids::surgepitch_TC)=mid(mids::surge_lp_out)/constants::g; // dependant
		const double surgepitch_TC_old=surge_lp_out_old/constants::g;

		// m9
		mid(mids::surgepitch_TCRL)=x(states::surgepitch_TCRL);

		// m10
		// rate limit
		mid(mids::surgepitch_TCRL_deriv)=// next line
			rate_limit_deriv(
				mid(mids::surgepitch_TC),
				surgepitch_TC_old,
				mid(mids::surgepitch_TCRL),
				t-last_observed_t,
				surge_max_tilt_rate
				);

		// m11
		mid(mids::pitch_input_vel_ref)=u(inputs::pitch_vel);

		// m12
		mid(mids::pitch_hp_out)=hp_pitch_out(mid,x);

		// m13
		mid(mids::pitch_kin_vel)=mid(mids::pitch_hp_out)+mid(mids::surgepitch_TCRL); // dependant

		// m14
		mid(mids::pitch_kin_pos)=x(states::pitch_kin_pos);

		// m15
		mid(mids::pitch_tilt_force)=mid(mids::pitch_kin_pos)*constants::g; // dependant

		// m16
		mid(mids::surgepitch_sp_force)=mid(mids::pitch_tilt_force)+mid(mids::surge_kin_acc); // dependant
	}

	static void input(const time_type t,input_type &u)
	{
		u(inputs::surge_acc)=(t>1?(t>7?0:1):0);
		u(inputs::pitch_vel)=0;
	}

protected:

 	static double rate_limit_deriv(
		const double &signal,
		const double &signal_last_observed,
		const double &rate_limited_signal,
		const double &dt,
		const double &rate
		)
	{
		if(dt==0)
			return 0;
		const double error_threshold=0.002;
		double current_rate=(signal-signal_last_observed)/dt;
		// is is correct to use last observed signal instead of current signal?
		double error=(signal_last_observed-rate_limited_signal);
		double proposed_derivative=current_rate+error*rate/error_threshold;
		return bound(proposed_derivative,-rate,+rate);
 	}

	static double bound(double val,double min,double max)
	{
		return std::min(std::max(val,min),max);
	}

	static void hp_surge(const intermediate_type &mid,const state_type &x,state_type &x_dot)
	{
		// observable form
		const double w=platform::omega_hp_x;
		const double z=platform::zeta_hp_x;
		const int x1=states::surge_hp_x1;
		const int x2=states::surge_hp_x2;
		x_dot(x1)=-w*w*x(x2)-w*w*mid(mids::surge_input_acc_ref);
		x_dot(x2)=x(x1)-2*z*w*x(x2)-2*z*w*mid(mids::surge_input_acc_ref);
	}

	static double hp_surge_out(const intermediate_type &mid,const state_type &x)
	{
		return x(states::surge_hp_x2)+mid(mids::surge_input_acc_ref);
	}

	static void lp_surge(const intermediate_type &mid,const state_type &x, state_type &x_dot)
	{
		// observable form
		const double w=platform::omega_lp_x;
		const double z=platform::zeta_lp_x;
		const int x1=states::surge_lp_x1;
		const int x2=states::surge_lp_x2;
		x_dot(x1)=-w*w*x(x2)+w*w*mid(mids::surge_input_acc_ref);
		x_dot(x2)=x(x1)-2*z*w*x(x2);
	}

	static double lp_surge_out(const state_type &x)
	{
		return x(states::surge_lp_x2);
	}

	static void hp_pitch(const intermediate_type &mid,const state_type &x, state_type &x_dot)
	{
		// observable form
		const double w=platform::omega_hp_pitch;
		const int x1=states::pitch_hp_x1;
		x_dot(x1)=-w*x(x1)-w*mid(mids::pitch_input_vel_ref);
	}

	static double hp_pitch_out(const intermediate_type &mid,const state_type &x)
	{
		return x(states::pitch_hp_x1)+mid(mids::pitch_input_vel_ref);
	}

	static void linear_dynamic_proposed(const time_type t,const double u,const state_type &x, state_type &x_dot,const double vmax,const double xmax)
	{
		// f(x) = d saturation(x) / dx
		// x1'=f(x1/amax)a
		// x2'=f(x2/vmax)x1
		_unused(t);
		const int x1=states::surge_proposed_vel;
		const int x2=states::surge_kin_pos;
		x_dot(x1)=proposed_velocity_derivative(u,x,vmax,xmax);
		x_dot(x2)=proposed_position_derivative(x,vmax,xmax);
	}

	static double proposed_position_derivative(
		const state_type &x,
		const double vmax,
		const double xmax)
	{
		_unused(vmax);
		const int x1=states::surge_proposed_vel;
		const int x2=states::surge_kin_pos;

		double pxd=sat_logistic(x(x2)/xmax)*x(x1);
		if(x(x1)*x(x2)<=0.0)
		{
			if(x(x2)>=0.0)
				return std::min(x(x1),pxd);
			else
				return std::max(x(x1),pxd);
		}
		else
		{
			return pxd;
		}
	}

	static double proposed_velocity_derivative(
		const double u,
		const state_type &x,
		const double vmax,
		const double xmax)
	{
		const int x1=states::surge_proposed_vel;
		// const int x2=states::surge_kin_pos;
		_unused(xmax);
		double pvd=sat_logistic(x(x1)/vmax)*u;

		if(u*x(x1)<=0.0)
		{
			if(x(x1)>=0.0)
				return std::min(u,pvd);
			else
				return std::max(u,pvd);
		}
		else
		{
			return pvd;
		}
	}

	static double get_kinematic_surge_acc(const state_type &x,const double u,const double vmax,const double xmax)
	{
		// x proposed velocity
		const auto xpv= x(states::surge_proposed_vel);
		// x kinematic position
		const auto xkp= x(states::surge_kin_pos);

		if(xkp*xpv>=0)
		{
			double xx_dot=proposed_position_derivative(x,vmax,xmax);
			double xv_dot=proposed_velocity_derivative(u,x,vmax,xmax);
			double result=xv_dot*sat_logistic(xkp/xmax)+sat_logistic_D1(xkp/xmax)*xpv/xmax*xx_dot;
			return result;
		}
		else
		{
			return proposed_velocity_derivative(u,x,vmax,xmax);
		}
	}

	static double get_kinematic_surge_vel(const state_type &x,const double xmax)
	{
		const int x1=states::surge_proposed_vel;
		const int x2=states::surge_kin_pos;
		return x(x1)*x(x2)<=0 ? x(x1) : sat_logistic(x(x2)/xmax)*x(x1);
	}

	// saturation logistic funciton
	static double sat_logistic(double x)
	{	// derivative of saturation function
		double xabs=std::abs(x);
		double threshold=0.95;
		if(xabs<threshold)
			return 1.0;
		if(xabs>=1)
			return 0.0;
		return (1.0-xabs)/(1.0-threshold);
	}

	static double sat_logistic_D1(double x)
	{	// second derivative of saturation function
		double xabs=std::abs(x);
		double threshold=0.95;
		if(xabs<threshold||xabs>=1)
			return 0.0;
		return -1.0/(1.0-threshold)*(x>0?1:-1);
	}
};