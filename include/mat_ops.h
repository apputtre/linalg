#ifndef MAT_OPS_H
#define MAT_OPS_H

namespace linalg
{
	template<size_t L, typename T, typename U>
	mat<L, T>& operator+=(mat<L, T>& m, const U& val) requires std::convertible_to<U, T>;

	// Scalar addition
	template<size_t L, typename T, typename U>
	mat<L, T> operator+(const mat<L, T>& m, const U& val) requires std::convertible_to<U, T>;

	// Scalar addition
	template<size_t L, typename T, typename U>
	mat<L, T> operator+(const U& val, const mat<L, T>& m) requires std::convertible_to<U, T>;



	template<size_t L, typename T, typename U>
	mat<L, T>& operator-=(mat<L, T>& m, const U& val) requires std::convertible_to<U, T>;

	template<size_t L, typename T, typename U>
	mat<L, T> operator-(const mat<L, T>& m, const U& val) requires std::convertible_to<U, T>;

	template<size_t L, typename T, typename U>
	mat<L, T> operator-(const U& val, const mat<L, T>& m) requires std::convertible_to<U, T>;

	template<size_t L, typename T, typename U>
	mat<L, T>& operator-=(mat<L, T>& m1, const mat<L, U>& m2) requires std::convertible_to<U, T>;

	template<size_t L, typename T, typename U>
	mat<L, T> operator-(const mat<L, T>& m1, const mat<L, U>& m2) requires std::convertible_to<U, T>;

	template<size_t L, typename T, typename U>
	mat<L, T>& operator*=(mat<L, T>& m, const U& val) requires std::convertible_to<U, T>;

	template<size_t L, typename T, typename U>
	mat<L, T> operator*(const mat<L, T>& m, const U& val) requires std::convertible_to<U, T>;

	template<size_t L, typename T, typename U>
	mat<L, T> operator*(const U& val, const mat<L, T>& m1) requires std::convertible_to<U, T>;

	template<size_t L, typename T, typename U>
	mat<L, T> operator*(const mat<L, T>& m1, const mat<L, U>& m2) requires std::convertible_to<U, T>;

	template<size_t L, typename T, typename U>
	mat<L, T>& operator*=(mat<L, T>& m1, const mat<L, U>& m2) requires std::convertible_to<U, T>;

	template<size_t L, typename T, typename U>
	vec<L, T> operator*(const mat<L, T>& m, const vec<L, U>& v) requires std::convertible_to<U, T>;

	template<size_t L, typename T, typename U>
	mat<L, T>& operator/=(mat<L, T>& m, const U& val) requires std::convertible_to<U, T>;

	template<size_t L, typename T, typename U>
	mat<L, T> operator/(const mat<L, T>& m, const U& val) requires std::convertible_to<U, T>;

	template<size_t L, typename T, typename F>
	void apply(mat<L, T>& m, F func);

	template<size_t L, typename T, typename U, typename F>
	void apply_elementwise(mat<L, T>& m1, F func, const mat<L, U>& m2) requires std::convertible_to<U, T>;
}

#include "mat_ops.tpp"

#endif
