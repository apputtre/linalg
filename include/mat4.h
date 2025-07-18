#ifndef MAT4_H
#define MAT4_H

namespace linalg
{
	template<typename T>
	class mat<4, T>
	{
	private:
		vec<4, T> c0;
		vec<4, T> c1;
		vec<4, T> c2;
		vec<4, T> c3;

	public:
		const static int num_rows = 4;
		const static int num_cols = 4;
		const static int num_elements = num_rows * num_cols;

		mat()
			: c0{}, c1{}, c2{}, c3{}
		{}

		mat(T val);

		mat(const vec<4, T>& c0, const vec<4, T>& c1, const vec<4, T>& c2, const vec<4, T>& c3)
			: c0{ c0 }, c1{ c1 }, c2{ c2 }, c3 { c3 }
		{}

		mat(const mat& other);

		mat& operator=(const mat& other);

		vec<4, T>& operator[](size_t idx) const;
	};
}

#include "mat4.tpp"

#endif
