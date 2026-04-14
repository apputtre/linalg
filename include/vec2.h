#ifndef VEC2_H
#define VEC2_H

namespace linalg
{
	template<typename T>
	class vec<2, T>
	{
		typedef T value_type;

	public:
		const static size_t length = 2;

		union { value_type x, r; };
		union { value_type y, g; };

		vec(value_type val = 0)
			: x{ val }, y{ val }
		{}

		vec(value_type x, value_type y)
			:x{ x }, y{ y }
		{}

		template<typename U> requires std::convertible_to<U, T>
		vec(const vec<2, U>& other);

		vec& operator=(const vec<2, T>& other);

		/*
		template<typename U> requires std::convertible_to<U, T>
		vec<2, U> operator()(vec<2, U>);
		*/

		value_type& operator[](size_t idx) const;
	};
}

#include "vec2.tpp"

#endif
