#ifndef MAT4_H
#define MAT4_H

#include "vec.h"

namespace linalg
{
	template<size_t Rows, size_t Cols, typename T>
	class mat
	{
	private:
		vec<Rows, T> cols[Cols];

	public:
		const static int num_rows = Rows;
		const static int num_cols = Cols;
		const static int num_elements = num_rows * num_cols;

		template<vec<num_cols, T>... Rows>
		mat(Rows... rows) {};
	};
}

#endif
