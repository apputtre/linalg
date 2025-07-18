#ifndef MAT3_H
#define MAT3_H

namespace linalg
{
	template<typename T>
	class mat<3, T>
	{
	private:
		vec<3, T> c0;
		vec<3, T> c1;
		vec<3, T> c2;

	public:
		const static int num_rows = 3;
		const static int num_cols = 3;
		const static int num_elements = num_rows * num_cols;

		mat()
			: c0{}, c1{}, c2{}
		{}

		mat(T val);

		mat(const vec<3, T>& c0, const vec<3, T>& c1, const vec<3, T>& c2)
			: c0{ c0 }, c1{ c1 }, c2{ c2 }
		{}

		mat(const mat& other);

		mat& operator=(const mat& other);

		vec<3, T>& operator[](size_t idx) const;
	};
}

#include "mat3.tpp"

#endif
