#ifndef MAT_H
#define MAT_H

#include "vec.h"

namespace linalg
{
	template<size_t Rows, size_t Cols, typename T>
	class mat
	{
	private:
		vec<Rows, T> cols[Cols];

		void set_row(const std::initializer_list<T>& row, size_t idx)
		{
			for (size_t c = 0; c < num_cols; ++c)
				cols[c][idx] = *(row.begin() + c);
		}

		void set_row(const vec<num_cols, T>& row, size_t idx)
		{
			for (size_t c = 0; c < num_cols; ++c)
				cols[c][idx] = *(row.begin() + c);
		}

	public:
		const static int num_rows = Rows;
		const static int num_cols = Cols;
		const static int num_elements = num_rows * num_cols;

		template<std::initializer_list<T>... Row>
		mat(Row... rows)
		{
			/*
			for (r in num_rows)	
				(set_row(rows), ...)
			*/

			std::initializer_list<std::initializer_list<T>> list {rows...};

			for (size_t r = 0; r < num_rows; ++r)
				for (size_t c = 0; c < num_cols; ++c)
					cols[c][r] = (*(list.begin() + r))[c];
		}

		template<std::convertible_to<vec<num_cols, T>>... Row>
		mat(Row... rows)
		{
			for (size_t r = 0; r < num_rows; ++r)
				(set_row(rows, r), ...);
		}

		vec<num_cols, T> operator[](size_t idx) const
		{
			if (idx >= num_rows)
				throw std::runtime_error("Index out of bounds");
			
			vec<num_cols, T> row;
			
			for (size_t c = 0; c < num_cols; ++c)
				row[c] = cols[c][idx];
			
			return vec<num_cols, T>(row);
		}
	};
}

#endif
