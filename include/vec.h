#ifndef VEC_H
#define VEC_H

#include <memory>
#include <cmath>
#include <iostream>
#include <concepts>
#include <cstring>

#include "linalg_common.h"

namespace linalg
{
	using namespace impl;

	template<size_t L, typename T> requires (L > 0)
	struct vec_base_storage
	{
		T x {};
		T y {};
		T z {};
		T w {};
		T elems[L - 4] {};

		T& operator[](size_t idx) const
		{
			if (idx >= L)
				throw std::runtime_error("Index out of bounds");
			
			switch(idx)
			{
				case 0:
					return const_cast<T&>(x);
				case 1:
					return const_cast<T&>(y);
				case 2:
					return const_cast<T&>(z);
				case 3:
					return const_cast<T&>(w);
				default:
					return const_cast<T&>(elems[idx - 4]);
			}
		}
	};

	template<typename T>
	struct vec_base_storage<1, T>
	{
		T x {};

		T& operator[](size_t idx) const
		{
			switch(idx)
			{
				case 0:
					return const_cast<T&>(x);
				default:
					throw std::runtime_error("Index out of bounds");
			}
		}
	};

	template<typename T>
	struct vec_base_storage<2, T>
	{
		T x {};
		T y {};

		T& operator[](size_t idx) const
		{
			switch(idx)
			{
				case 0:
					return const_cast<T&>(x);
				case 1:
					return const_cast<T&>(y);
				default:
					throw std::runtime_error("Index out of bounds");
			}
		}
	};

	template<typename T>
	struct vec_base_storage<3, T>
	{
		T x {};
		T y {};
		T z {};

		T& operator[](size_t idx) const
		{
			
			switch(idx)
			{
				case 0:
					return const_cast<T&>(x);
				case 1:
					return const_cast<T&>(y);
				case 2:
					return const_cast<T&>(z);
				default:
					throw std::runtime_error("Index out of bounds");
			}
		}
	};

	template<size_t L, typename T> requires (L > 0)
	struct vec : public vec_base_storage<L, T>
	{
		typedef T value_type;
		const static size_t length = L;

		vec() {}

		template<typename... TVals>
			requires (sizeof...(TVals) == length)
		vec(TVals... vals)
		{
			size_t i = 0;
			(set(vals, i++), ...);
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

		value_type& operator[](size_t idx) const
		{
			try
			{
				return vec_base_storage<L, T>::operator[](idx);
			}
			catch(std::runtime_error& e)
			{
				throw e;
			}
		}

		vec& operator=(const vec<L, T>& other)
		{
			for (size_t i = 0; i < this->length; ++i)
				this->operator[](i) = static_cast<value_type>(other[i]);
			
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

		decltype(std::sqrt(T {})) mag()
		{
			T acc = 0;

			for (size_t i = 0; i < L; ++i)
				acc += (*this)[i] * (*this)[i];

			return std::sqrt(acc);
		}

		vec<L, decltype(T {} / std::sqrt(T {}))> norm()
		{
			if ((*this) == 0)
				return (*this);

			return (*this) / this->mag();
		}

		template<typename TOther>
			requires (Multipliable<T, TOther>) &&(Addable<MultiplicationResult<T, TOther>, MultiplicationResult<T, TOther>>)
		MultiplicationResult<T, TOther> dot(const vec<L, TOther>& v)
		{
			MultiplicationResult<T, TOther> acc = 0;

			for (size_t i = 0; i < L; ++i)
				acc += (*this)[i] * v[i];

			return acc;
		}

		template<typename TOther>
			requires (L == 3) &&
			(Multipliable<T, TOther>) &&
			(Subtractable<MultiplicationResult<T, TOther>, MultiplicationResult<T, TOther>>)
		vec<3, MultiplicationResult<T, TOther>> cross(const vec<L, TOther>& v)
		{
			return linalg::vec<3, MultiplicationResult<T, TOther>>(
				this->y * v.z - this->z * v.y,
				this->z * v.x - this->x * v.z,
				this->x * v.y - this->y * v.x
			);
		}

	private:
		void set(const T& val, size_t idx)
		{
			(*this)[idx] = val;
		}
	};

	template<size_t L, typename T1, typename T2>
		requires EqualityComparable<T1, T2>
	bool operator==(const vec<L, T1>& v1, const vec<L, T2>& v2)
	{
		for (size_t i = 0; i < L; ++i)
			if (v1[i] != v2[i])
				return false;

		return true;
	}

	template<size_t L, typename T1, typename T2>
		requires EqualityComparable<T1, T2>
	bool operator!=(vec<L, T1>& v1, const vec<L, T2>& v2)
	{
		return !(v1 == v2);
	}

	template<size_t L, typename TVector, typename TScalar>
		requires EqualityComparable<TVector, TScalar>
	bool operator==(const vec<L, TVector>& v, const TScalar& scalar)
	{
		for (size_t i = 0; i < v.length; ++i)
			if (v[i] != scalar)
				return false;

		return true;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires EqualityComparable<TVector, TScalar>
	bool operator!=(const vec<L, TVector>& v, const TScalar& scalar)
	{
		return !(v == scalar);
	}

	template<size_t L, typename TVector, typename TScalar>
		requires EqualityComparable<TVector, TScalar>
	bool operator==(const TScalar& scalar, const vec<L, TVector>& v)
	{
		return (v == scalar);
	}

	template<size_t L, typename TVector, typename TScalar>
		requires EqualityComparable<TVector, TScalar>
	bool operator!=(const TScalar& scalar, const vec<L, TVector>& v)
	{
		return !(v == scalar);
	}

	template<size_t L, typename T>
		requires Negatable<T>
	vec<L, T> operator-(const vec<L, T>& v)
	{
		vec<L, T> new_vec(v);

		for (size_t i = 0; i < L; ++i)
			new_vec[i] = -new_vec[i];
		
		return new_vec;
	}

	template<size_t L, typename T1, typename T2>
		requires Addable<T1, T2>
	vec<L, T1>& operator+=(vec<L, T1>& v1, const vec<L, T2>& v2)
	{
		for (size_t i = 0; i < L; ++i)
			v1[i] += v2[i];

		return v1;
	}

	template<size_t L, typename T1, typename T2>
		requires Addable<T1, T2>
	vec<L, AdditionResult<T1, T2>> operator+(const vec<L, T1>& v1, const vec<L, T2>& v2)
	{
		vec<L, AdditionResult<T1, T2>> new_vec(v1);
		new_vec += v2;
		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires Addable<TVector, TScalar>
	vec<L, TVector>& operator+=(vec<L, TVector>& v, const TScalar& val)
	{
		for (size_t i = 0; i < L; ++i)
			v[i] += val;
		
		return v;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires Addable<TVector, TScalar>
	vec<L, AdditionResult<TVector, TScalar>> operator+(const vec<L, TVector>& v, const TScalar& val)
	{
		vec<L, AdditionResult<TVector, TScalar>> new_vec(v);
		new_vec += val;
		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires Addable<TVector, TScalar>
	vec<L, AdditionResult<TVector, TScalar>> operator+(const TScalar& val, const vec<L, TVector>& v)
	{
		vec<L, AdditionResult<TVector, TScalar>> new_vec;

		for (size_t i = 0; i < L; ++i)
			new_vec[i] = val + v[i];

		return new_vec;
	}

	template<size_t L, typename T1, typename T2>
		requires Addable<T1, T2>
	vec<L, T1>& operator-=(vec<L, T1>& v1, const vec<L, T2>& v2)
	{
		for (size_t i = 0; i < L; ++i)
			v1[i] -= v2[i];

		return v1;
	}

	template<size_t L, typename T1, typename T2>
		requires Addable<T1, T2>
	vec<L, SubtractionResult<T1, T2>> operator-(const vec<L, T1>& v1, const vec<L, T2>& v2)
	{
		vec<L, SubtractionResult<T1, T2>> new_vec(v1);
		new_vec -= v2;
		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires Subtractable<TVector, TScalar>
	vec<L, TVector>& operator-=(vec<L, TVector>& v, const TScalar& val)
	{
		for (size_t i = 0; i < L; ++i)
			v[i] -= val;
		
		return v;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires Subtractable<TVector, TScalar>
	vec<L, SubtractionResult<TVector, TScalar>> operator-(const vec<L, TVector>& v, const TScalar& val)
	{
		vec<L, TVector> new_vec(v);
		new_vec -= val;
		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires Subtractable<TVector, TScalar>
	vec<L, SubtractionResult<TVector, TScalar>> operator-(const TScalar& val, const vec<L, TVector>& v)
	{
		vec<L, SubtractionResult<TVector, TScalar>> new_vec;

		for (size_t i = 0; i < L; ++i)
			new_vec[i] = val - v[i];

		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires Multipliable<TVector, TScalar>
	vec<L, TVector>& operator*=(vec<L, TVector>& v, const TScalar& val)
	{
		for (size_t i = 0; i < L; ++i)
			v[i] *= val;
		
		return v;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires Multipliable<TVector, TScalar>
	vec<L, MultiplicationResult<TVector, TScalar>> operator*(const vec<L, TVector>& v, const TScalar& val)
	{
		vec<L, MultiplicationResult<TVector, TScalar>> new_vec(v);
		new_vec *= val;
		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires Multipliable<TVector, TScalar>
	vec<L, MultiplicationResult<TVector, TScalar>> operator*(const TScalar& val, const vec<L, TVector>& v)
	{
		vec<L, MultiplicationResult<TVector, TScalar>> new_vec;

		for (size_t i = 0; i < L; ++i)
			new_vec[i] = val * v[i];

		return new_vec;
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
		requires Dividable<TVector, TScalar>
	vec<L, DivisionResult<TVector, TScalar>> operator/(const vec<L, TVector>& v, const TScalar& val)
	{
		if (val == 0)
			throw std::logic_error("Division by zero");

		vec<L, DivisionResult<TVector, TScalar>> new_vec(v);
		new_vec /= val;
		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar>
		requires Dividable<TVector, TScalar>
	vec<L, DivisionResult<TVector, TScalar>> operator/(const TScalar& val, const vec<L, TVector>& v)
	{
		vec<L, DivisionResult<TVector, TScalar>> new_vec;

		for (size_t i = 0; i < L; ++i)
			new_vec[i] = val / v[i];

		return new_vec;
	}

	template<size_t L, typename T>
		requires Insertable<T, std::ostream&>
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