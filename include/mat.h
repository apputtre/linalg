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

		template<std::convertible_to<vec<num_cols, T>>... Row>
		mat(Row... rows)
		{
			std::initializer_list<vec<num_cols, T>> list {rows...};

			for (size_t r = 0; r < num_rows; ++r)
				for (size_t c = 0; c < num_cols; ++c)
					cols[c][r] = (*(list.begin() + r))[c];
		}
	};
}

#endif
