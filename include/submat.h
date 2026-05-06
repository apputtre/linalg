#ifndef SUBMAT_H
#define SUBMAT_H

#include "vec.h"

template<size_t L, typename T>
struct submat
{
    submat(T* data, const size_t& stride)
        : data{data}, stride{stride}
    {}

    T* data;
    const size_t stride;

    T& operator[](size_t idx)
    {
        if (idx > L)
            throw std::runtime_error("Index out of bounds");

        return data[idx * stride];
    }

    /*
		vec& operator=(const vec<L, T>& other)
		{
			for (size_t i = 0; i < this->length; ++i)
				this->operator[](i) = static_cast<value_type>(other[i]);
			
			return *this;
		}
            */

    template<typename TOther>
    submat& operator=(const vec<L, TOther>& v)
    {
        for (size_t i = 0; i < L; ++i)
            (*this)[i] = static_cast<T>(v[i]);
        
        return *this;
    }

    template<typename TOther>
    submat& operator=(const TOther& scalar)
    {
        for (size_t i = 0; i < L; ++i)
            (*this)[i] = static_cast<T>(scalar);
        
        return *this;
    }

    /*
	private:
		void set(const T& val, size_t idx)
		{
			(*this)[idx] = val;
		}
	};
    */

    /*
	template<size_t L, typename T1, typename T2>
		requires requires (T1 x, T2 y) {x == y;}
	bool operator==(const vec<L, T1>& v1, const vec<L, T2>& v2)
	{
		for (size_t i = 0; i < L; ++i)
			if (v1[i] != v2[i])
				return false;

		return true;
	}

	template<size_t L, typename T1, typename T2>
		requires requires (T1 x, T2 y) {x == y;}
	bool operator!=(vec<L, T1>& v1, const vec<L, T2>& v2)
	{
		return !(v1 == v2);
	}

	template<size_t L, typename TVector, typename TScalar>
		requires std::convertible_to<TScalar, TVector>
	bool operator==(const vec<L, TVector>& v, const TScalar& scalar)
	{
		for (size_t i = 0; i < v.length; ++i)
			if (v[i] != scalar)
				return false;

		return true;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires std::convertible_to<TScalar, TVector>
	bool operator!=(const vec<L, TVector>& v, const TScalar& scalar)
	{
		return !(v == scalar);
	}

	template<size_t L, typename TVector, typename TScalar>
		requires std::convertible_to<TScalar, TVector>
	bool operator==(const TScalar& scalar, const vec<L, TVector>& v)
	{
		return (v == scalar);
	}

	template<size_t L, typename TVector, typename TScalar>
		requires std::convertible_to<TScalar, TVector>
	bool operator!=(const TScalar& scalar, const vec<L, TVector>& v)
	{
		return !(v == scalar);
	}

	template<size_t L, typename T>
		requires requires (T x) {-x;}
	vec<L, T> operator-(const vec<L, T>& v)
	{
		vec<L, T> new_vec(v);

		for (size_t i = 0; i < L; ++i)
			new_vec[i] = -new_vec[i];
		
		return new_vec;
	}

	template<size_t L, typename T1, typename T2>
		requires requires (T1 x, T2 y) {x + y;}
	vec<L, T1>& operator+=(vec<L, T1>& v1, const vec<L, T2>& v2)
	{
		for (size_t i = 0; i < L; ++i)
			v1[i] += v2[i];

		return v1;
	}

	template<size_t L, typename T1, typename T2>
		requires requires (T1 x, T2 y) {x + y;}
	vec<L, AdditionResult<T1, T2>> operator+(const vec<L, T1>& v1, const vec<L, T2>& v2)
	{
		vec<L, AdditionResult<T1, T2>> new_vec(v1);
		new_vec += v2;
		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar>
	vec<L, TVector>& operator+=(vec<L, TVector>& v, const TScalar& val)
	{
		for (size_t i = 0; i < L; ++i)
			v[i] += val;
		
		return v;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires requires (TVector x, TScalar y) {x + y;}
	vec<L, AdditionResult<TVector, TScalar>> operator+(const vec<L, TVector>& v, const TScalar& val)
	{
		vec<L, AdditionResult<TVector, TScalar>> new_vec(v);
		new_vec += val;
		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires requires (TVector x, TScalar y) {x + y;}
	vec<L, AdditionResult<TVector, TScalar>> operator+(const TScalar& val, const vec<L, TVector>& v)
	{
		vec<L, AdditionResult<TVector, TScalar>> new_vec;

		for (size_t i = 0; i < L; ++i)
			new_vec[i] = val + v[i];

		return new_vec;
	}

	template<size_t L, typename T1, typename T2>
		requires requires (T1 x, T2 y) {x + y;}
	vec<L, SubtractionResult<T1, T2>>& operator-=(vec<L, T1>& v1, const vec<L, T2>& v2)
	{
		for (size_t i = 0; i < L; ++i)
			v1[i] -= v2[i];

		return v1;
	}

	template<size_t L, typename T1, typename T2>
		requires requires (T1 x, T2 y) {x + y;}
	vec<L, SubtractionResult<T1, T2>> operator-(const vec<L, T1>& v1, const vec<L, T2>& v2)
	{
		vec<L, SubtractionResult<T1, T2>> new_vec(v1);
		new_vec -= v2;
		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires requires (TVector x, TScalar y) {x - y;}
	vec<L, TVector>& operator-=(vec<L, TVector>& v, const TScalar& val)
	{
		for (size_t i = 0; i < L; ++i)
			v[i] -= val;
		
		return v;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires requires (TVector x, TScalar y) {x - y;}
	vec<L, SubtractionResult<TVector, TScalar>> operator-(const vec<L, TVector>& v, const TScalar& val)
	{
		vec<L, TVector> new_vec(v);
		new_vec -= val;
		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires requires (TVector x, TScalar y) {x - y;}
	vec<L, SubtractionResult<TVector, TScalar>> operator-(const TScalar& val, const vec<L, TVector>& v)
	{
		vec<L, SubtractionResult<TVector, TScalar>> new_vec;

		for (size_t i = 0; i < L; ++i)
			new_vec[i] = val - v[i];

		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires requires (TVector x, TScalar y) {x * y;}
	vec<L, TVector>& operator*=(vec<L, TVector>& v, const TScalar& val)
	{
		for (size_t i = 0; i < L; ++i)
			v[i] *= val;
		
		return v;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires requires (TVector x, TScalar y) {x * y;}
	vec<L, MultiplicationResult<TVector, TScalar>> operator*(const vec<L, TVector>& v, const TScalar& val)
	{
		vec<L, MultiplicationResult<TVector, TScalar>> new_vec(v);
		new_vec *= val;
		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires requires (TVector x, TScalar y) {x * y;}
	vec<L, MultiplicationResult<TVector, TScalar>> operator*(const TScalar& val, const vec<L, TVector>& v)
	{
		vec<L, MultiplicationResult<TVector, TScalar>> new_vec;

		for (size_t i = 0; i < L; ++i)
			new_vec[i] = val * v[i];

		return new_vec;
	}

	template<size_t L, typename T1, typename T2>
		requires requires (T1 x, T2 y) {x * y;} // TODO: missing requirement: MultiplicationResult<T1, T2> + MultiplicationResult<T1, T2>
	MultiplicationResult<T1, T2> operator*(const vec<L, T1>& v1, const vec<L, T2>& v2)
	{
		MultiplicationResult<T1, T2> acc = 0;

		for (size_t i = 0; i < L; ++i)
			acc += v1[i] * v2[i];

		return acc;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires requires (TVector x, TScalar y) {x / y;}
	vec<L, TVector>& operator/=(vec<L, TVector>& v1, const TScalar& val)
	{
		if (val == 0)
			throw std::logic_error("Division by zero");

		for (size_t i = 0; i < L; ++i)
			v1[i] /= val;

		return v1;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires requires (TVector x, TScalar y) {x / y;}
	vec<L, DivisionResult<TVector, TScalar>> operator/(const vec<L, TVector>& v, const TScalar& val)
	{
		if (val == 0)
			throw std::logic_error("Division by zero");

		vec<L, DivisionResult<TVector, TScalar>> new_vec(v);
		new_vec /= val;
		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires requires (TVector x, TScalar y) {x / y;}
	vec<L, DivisionResult<TVector, TScalar>> operator/(const TScalar& val, const vec<L, TVector>& v)
	{
		vec<L, DivisionResult<TVector, TScalar>> new_vec;

		for (size_t i = 0; i < L; ++i)
			new_vec[i] = val / v[i];

		return new_vec;
	}
        */
};

#endif