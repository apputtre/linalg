#ifndef MAT2_H
#define MAT2_H

namespace linalg
{
	template<typename T>
	class mat<2, T>
	{
	private:
		vec<2, T> c0;
		vec<2, T> c1;

	public:
		const static int num_rows = 2;
		const static int num_cols = 2;
		const static int num_elements = num_rows * num_cols;

		mat()
			: c0{}, c1{}
		{}

		mat(T val);

		mat(const vec<2, T>& c0, const vec<2, T>& c1)
			: c0{ c0 }, c1{ c1 }
		{}

		mat(const mat& other);

		mat& operator=(const mat& other);

		vec<2, T>& operator[](size_t idx) const;
	};
}

#include "mat2.tpp"

#endif
