#ifndef VEC3_H
#define VEC3_H

#include "vec_initializer.h"

namespace linalg
{
	template<typename T>
	class vec<3, T>
	{
		typedef T value_type;

	public:
		const static size_t length = 3;

		union { value_type x, r; };
		union { value_type y, g; };
		union { value_type z, b; };

		vec(value_type val = 0)
			: x{ val }, y{ val }, z{ val }
		{}

		vec(value_type x, value_type y, value_type z)
			:x{ x }, y{ y }, z{ z }
		{}

		template<typename U> requires std::convertible_to<U, T>
		vec(const vec<3, U>& other);

		vec(const vec_initializer<3, T>& init);

		vec& operator=(const vec<3, T>& other);

		value_type& operator[](size_t idx) const;
	};

}

#include "vec3.tpp"

#endif