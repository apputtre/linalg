#ifndef VEC4_H
#define VEC4_H

#include "vec_initializer.h"

namespace linalg
{
	template<typename T>
	class vec<4, T>
	{
		typedef T value_type;

	public:
		const static size_t length = 4;

		union { value_type x, r; };
		union { value_type y, g; };
		union { value_type z, b; };
		union { value_type w, a; };

		vec(value_type val = 0)
			: x{ val }, y{ val }, z{ val }, w{ val }
		{}

		vec(value_type x, value_type y, value_type z, value_type w)
			:x{ x }, y{ y }, z{ z }, w{ w }
		{}

		template<typename U> requires std::convertible_to<U, T>
		vec(const vec<4, U>& other);

		vec(const vec_initializer<4, T>& init);

		vec& operator=(const vec<4, T>& other);

		value_type& operator[](size_t idx) const;

	};
}

#include "vec4.tpp"

#endif