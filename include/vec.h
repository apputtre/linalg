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
	struct vec;

	template<size_t L, typename T> requires (L > 0)
	struct submat;

	template<size_t L, typename T, typename TStorageImpl>
	struct vec_ops;

	template<typename T>
	struct is_vec_type : std::false_type {};

	template<size_t L, typename TElem, typename TStorage>
	struct is_vec_type<vec_ops<L, TElem, TStorage>> : std::true_type {};

	template<size_t L, typename TElem>
	struct is_vec_type<vec<L, TElem>> : std::true_type {};

	template<size_t L, typename TElem>
	struct is_vec_type<submat<L, TElem>> : std::true_type {};

	template<size_t L, typename T, typename TStorageImpl>
	struct vec_ops
	{
		typedef T value_type;
		const static size_t length = L;

		T& operator[](size_t idx)
		{
			return static_cast<TStorageImpl&>(*this)[idx];
		}

		const T& operator[](size_t idx) const
		{
			return const_cast<const T&>(static_cast<TStorageImpl&>(const_cast<vec_ops<L, T, TStorageImpl>&>(*this))[idx]);
		}

		template<typename TStorageOther>
		vec_ops& operator=(const vec_ops<L, T, TStorageOther>& other)
		{
			for (size_t i = 0; i < L; ++i)
				this->operator[](i) = static_cast<value_type>(other[i]);
			
			return *this;
		}

		template<typename TOther, typename TStorageOther>
		vec_ops& operator=(const vec_ops<L, TOther, TStorageOther>& other)
		{
			for (size_t i = 0; i < this->length; ++i)
				(*this)[i] = static_cast<value_type>(other[i]);
			
			return *this;
		}

		vec_ops& operator=(const T& scalar)
		{
			for (size_t i = 0; i < length; ++i)
				(*this)[i] = scalar;
			
			return *this;
		}

		template<typename TOther, typename TStorage>
			requires Addable<T, TOther>
		vec_ops& operator+=(const vec_ops<L, TOther, TStorage>& v)
		{
			for (size_t i = 0; i < L; ++i)
				(*this)[i] += v[i];

			return (*this);
		}

		template<typename TScalar>
			requires Addable<T, TScalar> && (!is_vec_type<TScalar>::value)
		vec_ops& operator+=(const TScalar& val)
		{
			for (size_t i = 0; i < L; ++i)
				(*this)[i] += val;
			
			return (*this);
		}

		template<typename TOther, typename TStorage>
			requires Subtractable<T, TOther>
		vec_ops& operator-=(const vec_ops<L, TOther, TStorage>& v2)
		{
			for (size_t i = 0; i < L; ++i)
				(*this)[i] -= v2[i];

			return (*this);
		}

		template<typename TScalar>
			requires Subtractable<T, TScalar> && (!is_vec_type<TScalar>::value)
		vec_ops& operator-=(const TScalar& val)
		{
			for (size_t i = 0; i < L; ++i)
				(*this)[i] -= val;
			
			return (*this);
		}

		template<typename TScalar>
			requires Multipliable<T, TScalar> && (!is_vec_type<TScalar>::value)
		vec_ops& operator*=(const TScalar& val)
		{
			for (size_t i = 0; i < L; ++i)
				(*this)[i] *= val;
			
			return (*this);
		}

		template<typename TScalar>
			requires Dividable<T, TScalar> && (!is_vec_type<TScalar>::value)
		vec_ops& operator/=(const TScalar& val)
		{
			if (val == 0)
				throw std::logic_error("Division by zero");

			for (size_t i = 0; i < L; ++i)
				(*this)[i] /= val;

			return (*this);
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
			if (this->zero())
				return vec<L, decltype(T {} / std::sqrt(T {}))>(0);

			return (*this) / this->mag();
		}

		template<typename TOther, typename TStorageOther>
			requires
				(Multipliable<T, TOther>) &&
				(Addable<MultiplicationResult<T, TOther>, MultiplicationResult<T, TOther>>)
		MultiplicationResult<T, TOther> dot(const vec_ops<L, TOther, TStorageOther>& v)
		{
			MultiplicationResult<T, TOther> acc = 0;

			for (size_t i = 0; i < L; ++i)
				acc += (*this)[i] * v[i];

			return acc;
		}

		template<typename TOther, typename TStorageOther>
			requires
				(L == 3) &&
				(Multipliable<T, TOther>) &&
				(Subtractable<MultiplicationResult<T, TOther>, MultiplicationResult<T, TOther>>)
		vec<3, MultiplicationResult<T, TOther>> cross(const vec_ops<L, TOther, TStorageOther>& v)
		{
			return vec<3, MultiplicationResult<T, TOther>>(
				(*this)[1] * v[2] - (*this)[2] * v[1],
				(*this)[2] * v[0] - (*this)[0] * v[2],
				(*this)[0] * v[1] - (*this)[1] * v[0]
			);
		}

		bool zero()
		{
			T default_val = T{};
			for (size_t i = 0; i < L; ++i)
				if ((*this)[i] != default_val)
					return false;
			return true;
		}
	};

	template<size_t L, typename T> requires (L > 0)
	struct vec_owning : public vec_ops<L, T, vec_owning<L, T>>
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
	struct vec_owning<1, T> : public vec_ops<1, T, vec_owning<1, T>>
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
	struct vec_owning<2, T> : public vec_ops<2, T, vec_owning<2, T>>
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
	struct vec_owning<3, T> : public vec_ops<3, T, vec_owning<3, T>>
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

	template<size_t L, typename T>
		requires (L > 0)
	struct submat : public vec_ops<L, T, submat<L, T>>
	{
		T* data;
		const size_t stride;

		submat(T* data, size_t stride)
			: data{data}, stride{stride}
		{}

		submat(const submat& other)
			: stride {other.stride}
		{
			for (size_t i = 0; i < this->length; ++i)
				(*this)[i] = static_cast<T>(other[i]);
		}

		submat& operator=(const submat& other)
		{
			for (size_t i = 0; i < this->length; ++i)
				(*this)[i] = static_cast<T>(other[i]);
			
			return *this;
		}

		template<std::convertible_to<T> TOther, typename TStorageOther>
		submat& operator=(const vec_ops<L, TOther, TStorageOther>& other)
		{
			for (size_t i = 0; i < this->length; ++i)
				(*this)[i] = static_cast<T>(other[i]);
			
			return *this;
		}

		submat& operator=(const T& scalar)
		{
			for (size_t i = 0; i < L; ++i)
				(*this)[i] = scalar;
			
			return *this;
		}

		T& operator[](size_t idx)
		{
			if (idx > L)
				throw std::runtime_error("Index out of bounds");
			
			return data[idx * stride];
		}

		T& operator[](size_t idx) const
		{
			return (const_cast<submat<L, T>&>(*this))[idx];
		}

	};

	template<size_t L, typename T> requires (L > 0)
	struct vec : public vec_owning<L, T>
	{
		vec() {}

		template<typename... TVals>
			requires (sizeof...(TVals) == L)
		vec(TVals... vals)
		{
			size_t i = 0;
			(set(vals, i++), ...);
		}

		template<typename TOther>
			requires (!is_vec_type<TOther>::value)
		vec(TOther scalar)
		{
			for (size_t i = 0; i < L; ++i)
				(*this)[i] = static_cast<T>(scalar);
		}

		vec(const vec<L, T>& other)
		{
			for (size_t i = 0; i < L; ++i)
				(*this)[i] = other[i];
		}

		vec<L, T>& operator=(const vec<L, T>& other)
		{
			for (size_t i = 0; i < L; ++i)
				(*this)[i] = other[i];

			return (*this);
		}

		template<typename TStorageOther>
		vec(const vec_ops<L, T, TStorageOther>& other)
		{
			for (size_t i = 0; i < L; ++i)
				(*this)[i] = other[i];
		}

		template<typename TOther>
		vec(const vec<L, TOther>& other)
		{
			for (size_t i = 0; i < L; ++i)
				(*this)[i] = static_cast<T>(other[i]);
		}

		template<typename TOther, typename TStorageOther>
		vec(const vec_ops<L, TOther, TStorageOther>& other)
		{
			for (size_t i = 0; i < L; ++i)
				(*this)[i] = static_cast<T>(other[i]);
		}

		T& operator[](size_t idx) const
		{
			try
			{
				return vec_owning<L, T>::operator[](idx);
			}
			catch(std::runtime_error& e)
			{
				throw e;
			}
		}

	private:
		void set(const T& val, size_t idx)
		{
			(*this)[idx] = val;
		}
	};

	template<size_t L, typename T1, typename T2, typename TStorage1, typename TStorage2>
		requires EqualityComparable<T1, T2>
	bool operator==(const vec_ops<L, T1, TStorage1>& v1, const vec_ops<L, T2, TStorage2>& v2)
	{
		for (size_t i = 0; i < L; ++i)
			if (v1[i] != v2[i])
				return false;

		return true;
	}

	template<size_t L, typename T1, typename T2, typename TStorage1, typename TStorage2>
		requires EqualityComparable<T1, T2>
	bool operator!=(vec_ops<L, T1, TStorage1>& v1, const vec_ops<L, T2, TStorage2>& v2)
	{
		return !(v1 == v2);
	}

	template<size_t L, typename T, typename TStorage>
		requires Negatable<T>
	vec<L, T> operator-(const vec_ops<L, T, TStorage>& v)
	{
		vec<L, T> new_vec(v);

		for (size_t i = 0; i < L; ++i)
			new_vec[i] = -new_vec[i];
		
		return new_vec;
	}

	template<size_t L, typename T1, typename T2, typename TStorage1, typename TStorage2>
		requires Addable<T1, T2>
	vec<L, AdditionResult<T1, T2>> operator+(const vec_ops<L, T1, TStorage1>& v1, const vec_ops<L, T2, TStorage2>& v2)
	{
		vec<L, AdditionResult<T1, T2>> new_vec(v1);
		new_vec += v2;
		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar, typename TStorage>
		requires Addable<TVector, TScalar> && (!is_vec_type<TScalar>::value)
	vec<L, AdditionResult<TVector, TScalar>> operator+(const vec_ops<L, TVector, TStorage>& v, const TScalar& val)
	{
		vec<L, AdditionResult<TVector, TScalar>> new_vec(v);
		new_vec += val;
		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar, typename TStorage>
		requires Addable<TVector, TScalar> && (!is_vec_type<TScalar>::value)
	vec<L, AdditionResult<TVector, TScalar>> operator+(const TScalar& val, const vec_ops<L, TVector, TStorage>& v)
	{
		vec<L, AdditionResult<TVector, TScalar>> new_vec;

		for (size_t i = 0; i < L; ++i)
			new_vec[i] = val + v[i];

		return new_vec;
	}

	template<size_t L, typename T1, typename T2, typename TStorage1, typename TStorage2>
		requires Subtractable<T1, T2>
	vec<L, SubtractionResult<T1, T2>> operator-(const vec_ops<L, T1, TStorage1>& v1, const vec_ops<L, T2, TStorage2>& v2)
	{
		vec<L, SubtractionResult<T1, T2>> new_vec(v1);
		new_vec -= v2;
		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar, typename TStorage>
		requires Subtractable<TVector, TScalar> && (!is_vec_type<TScalar>::value)
	vec<L, SubtractionResult<TVector, TScalar>> operator-(const vec_ops<L, TVector, TStorage>& v, const TScalar& val)
	{
		vec<L, TVector> new_vec(v);
		new_vec -= val;
		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar, typename TStorage>
		requires Subtractable<TVector, TScalar> && (!is_vec_type<TScalar>::value)
	vec<L, SubtractionResult<TVector, TScalar>> operator-(const TScalar& val, const vec_ops<L, TVector, TStorage>& v)
	{
		vec<L, SubtractionResult<TVector, TScalar>> new_vec;

		for (size_t i = 0; i < L; ++i)
			new_vec[i] = val - v[i];

		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar, typename TStorage>
		requires Multipliable<TVector, TScalar> && (!is_vec_type<TScalar>::value)
	vec<L, MultiplicationResult<TVector, TScalar>> operator*(const vec_ops<L, TVector, TStorage>& v, const TScalar& val)
	{
		vec<L, MultiplicationResult<TVector, TScalar>> new_vec(v);
		new_vec *= val;
		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar, typename TStorage>
		requires Multipliable<TVector, TScalar> && (!is_vec_type<TScalar>::value)
	vec<L, MultiplicationResult<TVector, TScalar>> operator*(const TScalar& val, const vec_ops<L, TVector, TStorage>& v)
	{
		vec<L, MultiplicationResult<TVector, TScalar>> new_vec;

		for (size_t i = 0; i < L; ++i)
			new_vec[i] = val * v[i];

		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar, typename TStorage>
		requires Dividable<TVector, TScalar> && (!is_vec_type<TScalar>::value)
	vec<L, DivisionResult<TVector, TScalar>> operator/(const vec_ops<L, TVector, TStorage>& v, const TScalar& val)
	{
		if (val == 0)
			throw std::logic_error("Division by zero");

		vec<L, DivisionResult<TVector, TScalar>> new_vec(v);
		new_vec /= val;
		return new_vec;
	}

	template<size_t L, typename TVector, typename TScalar, typename TStorage>
		requires Dividable<TVector, TScalar> && (!is_vec_type<TScalar>::value)
	vec<L, DivisionResult<TVector, TScalar>> operator/(const TScalar& val, const vec_ops<L, TVector, TStorage>& v)
	{
		vec<L, DivisionResult<TVector, TScalar>> new_vec;

		for (size_t i = 0; i < L; ++i)
			new_vec[i] = val / v[i];

		return new_vec;
	}

	template<size_t L, typename T, typename TStorage>
		requires Insertable<T, std::ostream&>
	std::ostream& operator<<(std::ostream& os, const linalg::vec_ops<L, T, TStorage>& v)
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