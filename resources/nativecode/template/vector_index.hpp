
#WARNING_COMMENTS#

// path: ./#TRACING_PATH#

#pragma once

class #TITLES#_type
{
public:

	// total size of #TITLE# vector
	static const uint #TITLES#_size=#TOTAL_SIZE#;

	#INDEX_NUMBERS_COMMENTS#

	#INDEX_CONSTANTS#

	typedef arma::vec::fixed<#TITLES#_size> vector_type;
	typedef arma::subview_col<double> subvector_type;
	vector_type data;

	#TITLES#_type()
	{}

	#TITLES#_type(vector_type data): data(data)
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

	#TITLES#_type operator= (const #TITLES#_type other)
	{
		data=other.data;
		return *this;
	}

	#TITLES#_type operator= (const vector_type other_data)
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
	// total size of #TITLE# vector

	#SUBVECTOR_FUNCTIONS#
};

inline #TITLES#_type::vector_type operator* (double scalar, #TITLES#_type vec)
{
	return scalar * vec.data;
}

inline #TITLES#_type::vector_type operator* (#TITLES#_type vec,double scalar)
{
	return vec.data * scalar;
}

inline #TITLES#_type::vector_type operator+ (double scalar, #TITLES#_type vec)
{
	return scalar + vec.data;
}

inline #TITLES#_type::vector_type operator+ (#TITLES#_type vec,double scalar)
{
	return vec.data + scalar;
}

inline #TITLES#_type::vector_type operator+ (#TITLES#_type vec1,#TITLES#_type vec2)
{
	return vec1.data + vec2.data;
}

inline #TITLES#_type::vector_type operator- (double scalar, #TITLES#_type vec)
{
	return scalar - vec.data;
}

inline #TITLES#_type::vector_type operator- (#TITLES#_type vec,double scalar)
{
	return vec.data - scalar;
}

inline #TITLES#_type::vector_type operator- (#TITLES#_type vec1,#TITLES#_type vec2)
{
	return vec1.data - vec2.data;
}

namespace arma
{
	inline #TITLES#_type::vector_type abs(#TITLES#_type vec)
	{
		return arma::abs(vec.data);
	}

	inline double max(#TITLES#_type vec)
	{
		return arma::max(vec.data);
	}
}