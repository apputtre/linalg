#ifndef VEC_OPS_H
#define VEC_OPS_H

#include "vec.h"

namespace linalg
{
	template<size_t L, typename T>
	std::ostream& operator<<(std::ostream& os, const linalg::vec<L, T>& v);

	// Apply a unary operation to every element in the vector
	template<size_t L, typename T, typename F>
	void apply(vec<L, T>& v, F func);

	// Apply a binary operation between every element of this vector and every element of other
	template<size_t L, typename T, typename U, typename F>
	void apply_elementwise(vec<L, T>& v, F func, const vec<L, U>& other) requires std::convertible_to<U, T>;
}

#include "vec_ops.tpp"

#endif
