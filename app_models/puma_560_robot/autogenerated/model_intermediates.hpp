
// *** Warning:
// *** auto-generated file and subjected to be overwritten

// path: ./app_models/puma_560_robot/autogenerated/model_intermediates.hpp

#pragma once

class mids_type
{
public:

	// total size of mid vector
	static const uint mids_size=46;

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

	const uint index_theta_desired_0=0;
	const uint index_theta_desired_end=2;
	const uint index_D_theta_desired_0=3;
	const uint index_D_theta_desired_end=5;
	const uint index_DD_theta_desired_0=6;
	const uint index_DD_theta_desired_end=8;
	const uint index_theta_0=9;
	const uint index_theta_1=10;
	const uint index_theta_2=11;
	const uint index_theta_end=11;
	const uint index_D_theta_0=12;
	const uint index_D_theta_end=14;
	const uint index_theta_error_0=15;
	const uint index_theta_error_end=17;
	const uint index_D_theta_error_0=18;
	const uint index_D_theta_error_end=20;
	const uint index_DD_theta_controller_0=21;
	const uint index_DD_theta_controller_2=23;
	const uint index_DD_theta_controller_3=24;
	const uint index_DD_theta_controller_end=26;
	const uint index_T_0=27;
	const uint index_T_end=32;
	const uint index_angular_vec_0=33;
	const uint index_angular_vec_2=35;
	const uint index_angular_vec_3=36;
	const uint index_angular_vec_end=38;
	const uint index_position_0=39;
	const uint index_position_end=41;
	const uint index_position_desired_0=42;
	const uint index_position_desired_end=44;
	const uint index_error=45;

	typedef arma::vec::fixed<mids_size> vector_type;
	typedef arma::subview_col<double> subvector_type;
	vector_type data;

	mids_type()
	{}

	mids_type(vector_type data): data(data)
	{}

	inline const vector_type operator() () const
	{
		return data;
	}
	inline vector_type operator() ()
	{
		return data;
	}

	inline double operator() (const arma::uword n) const
	{
		return data(n);
	}
	inline double& operator() (const arma::uword n)
	{
		return data(n);
	}

	inline const subvector_type subvec(const arma::uword n,const arma::uword m) const
	{
		return data.subvec(n,m);
	}
	inline subvector_type subvec(const arma::uword n,const arma::uword m)
	{
		return data.subvec(n,m);
	}

	mids_type operator= (const mids_type other)
	{
		data=other.data;
		return *this;
	}

	mids_type operator= (const vector_type other_data)
	{
		data=other_data;
		return *this;
	}

	inline vector_type zeros()
	{
		return data.zeros();
	}

	// inline const vector_type operator*= (const double val)
	// {
	// 	return (data=val*data);
	// }

	// inline const vector_type operator* (const double val) const
	// {
	// 	return data*val;
	// }

	// inline const vector_type operator* (const double val) const
	// {
	// 	return val*data;
	// }

	// ****************************
	// total size of mid vector

	inline const subvector_type theta_desired() const
	{
	return data.subvec(0,2);
	}
	inline subvector_type theta_desired()
	{
	return data.subvec(0,2);
	}
	
	inline const subvector_type D_theta_desired() const
	{
	return data.subvec(3,5);
	}
	inline subvector_type D_theta_desired()
	{
	return data.subvec(3,5);
	}
	
	inline const subvector_type DD_theta_desired() const
	{
	return data.subvec(6,8);
	}
	inline subvector_type DD_theta_desired()
	{
	return data.subvec(6,8);
	}
	
	inline const subvector_type theta() const
	{
	return data.subvec(9,11);
	}
	inline subvector_type theta()
	{
	return data.subvec(9,11);
	}
	
	inline const subvector_type D_theta() const
	{
	return data.subvec(12,14);
	}
	inline subvector_type D_theta()
	{
	return data.subvec(12,14);
	}
	
	inline const subvector_type theta_error() const
	{
	return data.subvec(15,17);
	}
	inline subvector_type theta_error()
	{
	return data.subvec(15,17);
	}
	
	inline const subvector_type D_theta_error() const
	{
	return data.subvec(18,20);
	}
	inline subvector_type D_theta_error()
	{
	return data.subvec(18,20);
	}
	
	inline const subvector_type DD_theta_controller() const
	{
	return data.subvec(21,26);
	}
	inline subvector_type DD_theta_controller()
	{
	return data.subvec(21,26);
	}
	
	inline const subvector_type T() const
	{
	return data.subvec(27,32);
	}
	inline subvector_type T()
	{
	return data.subvec(27,32);
	}
	
	inline const subvector_type angular_vec() const
	{
	return data.subvec(33,38);
	}
	inline subvector_type angular_vec()
	{
	return data.subvec(33,38);
	}
	
	inline const subvector_type position() const
	{
	return data.subvec(39,41);
	}
	inline subvector_type position()
	{
	return data.subvec(39,41);
	}
	
	inline const subvector_type position_desired() const
	{
	return data.subvec(42,44);
	}
	inline subvector_type position_desired()
	{
	return data.subvec(42,44);
	}
	
	inline double error() const
	{
	return data(45);
	}
	inline double& error()
	{
	return data(45);
	}
	
};

inline mids_type::vector_type operator* (double scalar, mids_type vec)
{
	return scalar * vec.data;
}

inline mids_type::vector_type operator* (mids_type vec,double scalar)
{
	return vec.data * scalar;
}

inline mids_type::vector_type operator+ (double scalar, mids_type vec)
{
	return scalar + vec.data;
}

inline mids_type::vector_type operator+ (mids_type vec,double scalar)
{
	return vec.data + scalar;
}

inline mids_type::vector_type operator+ (mids_type vec1,mids_type vec2)
{
	return vec1.data + vec2.data;
}

inline mids_type::vector_type operator- (double scalar, mids_type vec)
{
	return scalar - vec.data;
}

inline mids_type::vector_type operator- (mids_type vec,double scalar)
{
	return vec.data - scalar;
}

inline mids_type::vector_type operator- (mids_type vec1,mids_type vec2)
{
	return vec1.data - vec2.data;
}

namespace arma
{
	inline mids_type::vector_type abs(mids_type vec)
	{
		return arma::abs(vec.data);
	}

	inline double max(mids_type vec)
	{
		return arma::max(vec.data);
	}
}