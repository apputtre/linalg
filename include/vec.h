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
	struct vec_base_storage {};

	template<typename T>
	struct vec_base_storage<1, T> {};

	template<typename T>
	struct vec_base_storage<2, T> {};

	template<typename T>
	struct vec_base_storage<3, T> {};

	template<typename T>
	struct vec_base_storage<4, T> {};

	template<size_t L, typename T> requires (L > 0)
	struct vec
	{
		typedef T value_type;


	public:
		const static size_t length = L;

		T x {value_type{}};

	private:
		T elems[L == 1? 0 : L - 1] {};

	public:
		vec() {}

		template<typename... TVals>
		vec(TVals... vals)
		{
			std::initializer_list<T> list {static_cast<T>(vals)...};

			if (list.size() != length)
				throw std::logic_error("Invalid initializer list size");
			
			for (size_t i = 0; i < list.size(); ++i)
			{
				if (i == 0)
					x = *list.begin();
				else
					elems[i - 1] = *(list.begin() + i);
			}
		}

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
			
			switch(idx)
			{
				case 0:
					return const_cast<value_type&>(x);
				default:
					return (value_type&)elems[idx - 1];
			}
		}


		T mag() const
		{
			T acc = 0;

			for (size_t i = 0; i < L; ++i)
				acc += std::pow((*this)[i], 2);

			T mag = std::sqrt(acc);

			return mag;
		}
	};

	template<typename T1, typename T2>
	using AdditionResult = decltype(std::declval<T1>() + std::declval<T2>());

	template<typename T1, typename T2>
	using SubtractionResult = decltype(std::declval<T1>() - std::declval<T2>());

	template<typename T1, typename T2>
	using MultiplicationResult = decltype(std::declval<T1>() * std::declval<T2>());

	template<typename T1, typename T2>
	using DivisionResult = decltype(std::declval<T1>() / std::declval<T2>());

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

	template<size_t L, typename T>
	vec<L, T> norm(vec<L, T> v)
	{
		T m = v.mag();

		if (m == 0)
			return v;

		vec<L, T> ret = v / m;

		return ret;
	}

	template<size_t L, typename T>
	std::ostream& operator<<(std::ostream& os, const linalg::vec<L, T>& v)
	{
		if (v.length == 0)
		{
			os << "<>";
			return os;
		}

		os << "<";
		for (size_t i = 0; i < v.length; ++i)
		{
			os << v[i];

			if (i != v.length - 1)
				os << ", ";
		}
		os << ">";

		return os;
	};

}

#endif