#ifndef VEC_H
#define VEC_H

#include <memory>
#include <cmath>
#include <iostream>
#include <concepts>
#include <cstring>

namespace linalg
{
	template<size_t L, typename T> requires (L > 0)
	class vec
	{
		typedef T value_type;

	private:
		T elems[L] {value_type{}};

	public:
		const static size_t length = L;

		template<typename... TOther>
		vec(TOther... vals)
			: elems {static_cast<value_type>(vals)...}
		{}

		template<typename TOther>
		vec(TOther scalar)
		{
			for (size_t i = 0; i < length; ++i)
				(*this)[i] = static_cast<value_type>(scalar);
		}

		vec(const vec<L, T>& other)
		{
			for (size_t i = 0; i < this->length; ++i)
				(*this)[i] = other[i];
		}

		template<typename TOther>
		vec(const vec<L, TOther>& other)
		{
			for (size_t i = 0; i < this->length; ++i)
				(*this)[i] = static_cast<value_type>(other[i]);
		}

		vec& operator=(const vec<L, T>& other)
		{
			for (size_t i = 0; i < this->length; ++i)
				(*this)[i] = static_cast<value_type>(other[i]);
			
			return *this;
		}

		template<typename TOther>
		vec& operator=(const vec<L, TOther>& other)
		{
			for (size_t i = 0; i < this->length; ++i)
				(*this)[i] = static_cast<value_type>(other[i]);
			
			return *this;
		}

		vec& operator=(const value_type& scalar)
		{
			for (size_t i = 0; i < length; ++i)
				(*this)[i] = scalar;
			
			return *this;
		}

		value_type& operator[](size_t idx) const
		{
			if (idx >= length)
				throw std::runtime_error("Index out of bounds");
			
			return (value_type&)elems[idx];
		}
	};

	template<typename T1, typename T2>
	using AdditionResult = decltype(std::declval<T1>() + std::declval<T2>());

	template<typename T1, typename T2>
	using SubtractionResult = decltype(std::declval<T1>() - std::declval<T2>());

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

	template<size_t L, typename TVector, typename TScalar> requires std::convertible_to<TScalar, TVector>
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

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T>& operator-=(vec<L, T>& v, const U& val)
	{
		apply(v, [val](T& elem) {elem -= val; });
		return v;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T> operator-(const vec<L, T>& v, const U& val)
	{
		vec<L, T> new_vec(v);
		new_vec -= val;
		return new_vec;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T> operator-(const U& val, const vec<L, T>& v)
	{
		vec<L, T> new_vec;
		return new_vec + val - v;
	}
}

#endif