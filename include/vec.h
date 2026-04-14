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

		vec(vec<L, T>&& other) = delete;

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

		vec& operator=(vec<L, T>&& other) = delete;

		value_type& operator[](size_t idx) const
		{
			if (idx >= length)
				throw std::runtime_error("Index out of bounds");
			
			return (value_type&)elems[idx];
		}
	};
}

#endif