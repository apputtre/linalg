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

	public:
		const static int num_rows = Rows;
		const static int num_cols = Cols;
		const static int num_elements = num_rows * num_cols;

		mat(std::initializer_list<std::initializer_list<T>> rows)
		{
			size_t r = 0;
			for (auto row : rows)
				set_row(row, r++);
		}

		template<std::same_as<vec<num_cols, T>>... Row>
		mat(Row... rows)
		{
			size_t r = 0;
			(set_row(rows, r++), ...);
		}

		mat() = default;

		mat(const mat& other) = default;

		mat(mat&& other) = default;

		mat& operator=(const mat& other) = default;

		mat& operator=(mat&& other) = default;

		~mat() = default;

		vec<num_cols, T> operator[](size_t idx) const
		{
			if (idx >= num_rows)
				throw std::runtime_error("Index out of bounds");
			
			vec<num_cols, T> row;
			
			for (size_t c = 0; c < num_cols; ++c)
				row[c] = cols[c][idx];
			
			return vec<num_cols, T>(row);
		}
	private:
		void set_row(const std::initializer_list<T>& row, size_t idx)
		{
			for (size_t c = 0; c < num_cols; ++c)
				cols[c][idx] = *(row.begin() + c);
		}

		void set_row(const vec<num_cols, T>& row, size_t idx)
		{
			for (size_t c = 0; c < num_cols; ++c)
				cols[c][idx] = row[c];
		}
	};
}

#endif
