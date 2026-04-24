#ifndef MAT4_H
#define MAT4_H

#include "vec.h"

/*
namespace linalg
{
	template<size_t Rows, size_t Cols, typename T>
	class mat
	{
	private:
		vec<Rows, T> cols[Cols];

	public:
		const static int num_rows = 4;
		const static int num_cols = 4;
		const static int num_elements = num_rows * num_cols;

		mat() {};
	};
}
*/
namespace linalg
{
	template<size_t Rows, size_t Cols>
	class mat
	{
	public:

		mat() {};
	};
}

#endif
