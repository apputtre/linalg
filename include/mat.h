#ifndef MAT_H
#define MAT_H

#include "vec.h"

namespace linalg
{
	template<size_t Rows, size_t Cols, typename T>
	class mat
	{
	private:
		vec<Cols, T> rows[Rows];

	public:
		constexpr static size_t num_rows = Rows;
		constexpr static size_t num_cols = Cols;
		constexpr static size_t num_elements = num_rows * num_cols;

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

		template<std::convertible_to<T> TOther>
		mat(const mat<Rows, Cols, TOther>& other)
		{
			//std::transform(&other[0], &other[0] + other.num_elements, cols[0], [](const TOther& t) {return static_cast<T>(t);});

			for (size_t r = 0; r < num_rows; ++r)
				for (size_t c = 0; c < num_cols; ++c)
					rows[r][c] = static_cast<T>(other[r][c]);
		}

		template<std::convertible_to<T> TOther>
		mat(const TOther& val)
		{
			std::fill(&rows[0], &rows[0] + num_rows, val);
		}

		vec<num_cols, T>& operator[](size_t idx) const
		{
			if (idx >= num_rows)
				throw std::runtime_error("Index out of bounds");
			
			return const_cast<vec<num_cols, T>&>(rows[idx]);
		}
	private:
		void set_row(const std::initializer_list<T>& row, size_t idx)
		{
			for (size_t c = 0; c < num_cols; ++c)
				rows[idx][c] = *(row.begin() + c);
		}

		void set_row(const vec<num_cols, T>& row, size_t idx)
		{
			rows[idx] = row;
		}
	};
}

#endif
