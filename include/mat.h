#ifndef MAT_H
#define MAT_H

#include "vec.h"

namespace linalg
{
	template<typename T1, typename T2>
	concept EqualityComparable = requires(T1 t1, T2 t2)
	{
		t1 == t2;
		t2 == t1;
	};

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
			if (rows.size() != num_rows)
				throw std::runtime_error("Incorrect number of rows in initializer");

			size_t r = 0;
			for (auto row : rows)
			{
				if (row.size() != num_cols)
					throw std::runtime_error("Incorrect number of columns in initializer");
				set_row(row, r++);
			}
		}

		template<std::same_as<vec<num_cols, T>>... Row>
			requires (sizeof...(Row) == Rows)
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

		mat() = default;

		vec<num_cols, T>& operator[](size_t idx)
		{
			if (idx >= num_rows)
				throw std::runtime_error("Index out of bounds");
			
			return rows[idx];
		}

		const vec<num_cols, T>& operator[](size_t idx) const
		{
			return (*const_cast<mat*>(this))[idx];
		}

		template<typename TOther>
		mat<Rows, Cols, AdditionResult<T, TOther>>& operator+=(const mat<Rows, Cols, TOther>& m)
		{
			for (size_t r = 0; r < Rows; ++r)
				(*this)[r] += m[r];
			
			return *this;
		}

		template<typename TScalar>
		mat<Rows, Cols, AdditionResult<T, TScalar>>& operator+=(const TScalar& scalar)
		{
			for (size_t r = 0; r < Rows; ++r)
				(*this)[r] += scalar;
			
			return *this;
		}

		template<typename TOther>
		mat<Rows, Cols, SubtractionResult<T, TOther>>& operator-=(const mat<Rows, Cols, TOther>& m)
		{
			for (size_t r = 0; r < Rows; ++r)
				(*this)[r] -= m[r];
			
			return *this;
		}

		template<typename TScalar>
		mat<Rows, Cols, SubtractionResult<T, TScalar>>& operator-=(const TScalar& scalar)
		{
			for (size_t r = 0; r < Rows; ++r)
				(*this)[r] -= scalar;
			
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& os, const mat<Rows, Cols, T>& m)
		{
			os << "{";
			for (size_t r = 0; r < m.num_rows; ++r)
			{
				os << "{";
				for (size_t c = 0; c < m.num_cols; ++c)
				{
					os << m[r][c];

					if (c != m.num_cols - 1)
						os << ", ";
				}
				os << "}";

				if (r != m.num_rows - 1)
					os << ",";
			}
			os << "}";

			return os;
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

	template<size_t Rows, size_t Cols, typename T1, typename T2>
	bool operator==(const mat<Rows, Cols, T1>& m1, const mat<Rows, Cols, T2>& m2)
		requires EqualityComparable<T1, T2>
	{
		for (size_t r = 0; r < Rows; ++r)
			if (m1[r] != m2[r])
					return false;
		return true;
	}

	template<size_t Rows, size_t Cols, typename T1, typename T2>
	bool operator!=(const mat<Rows, Cols, T1>& m1, const mat<Rows, Cols, T2>& m2)
		requires EqualityComparable<T1, T2>
	{
		return !(m1 == m2);
	}

	template<size_t Rows, size_t Cols, typename T1, typename T2>
	mat<Rows, Cols, AdditionResult<T1, T2>> operator+(const mat<Rows, Cols, T1>& m1, const mat<Rows, Cols, T2>& m2)
	{
		mat<Rows, Cols, AdditionResult<T1, T2>> result = m1;
		result += m2;
		return result;
	}

	template<size_t Rows, size_t Cols, typename T, typename TScalar>
		requires (!std::is_same<TScalar, mat<Rows, Cols, T>>::value)
	mat<Rows, Cols, AdditionResult<T, TScalar>> operator+(const mat<Rows, Cols, T>& m, const TScalar& scalar)
	{
		mat<Rows, Cols, AdditionResult<T, TScalar>> result = m;
		result += scalar;
		return result;
	}

	template<size_t Rows, size_t Cols, typename T, typename TScalar>
		requires (!std::is_same<TScalar, mat<Rows, Cols, T>>::value)
	mat<Rows, Cols, AdditionResult<TScalar, T>> operator+(const TScalar& scalar, const mat<Rows, Cols, T>& m)
	{
		mat<Rows, Cols, AdditionResult<TScalar, T>> result;

		for (size_t r = 0; r < result.num_rows; ++r)
			result[r] = scalar + m[r];

		return result;
	}

	template<size_t Rows, size_t Cols, typename T1, typename T2>
	mat<Rows, Cols, SubtractionResult<T1, T2>> operator-(const mat<Rows, Cols, T1>& m1, const mat<Rows, Cols, T2>& m2)
	{
		mat<Rows, Cols, SubtractionResult<T1, T2>> result = m1;
		result -= m2;
		return result;
	}

	template<size_t Rows, size_t Cols, typename T, typename TScalar>
		requires (!std::is_same<TScalar, mat<Rows, Cols, T>>::value)
	mat<Rows, Cols, SubtractionResult<T, TScalar>> operator-(const mat<Rows, Cols, T>& m, const TScalar& scalar)
	{
		mat<Rows, Cols, AdditionResult<T, TScalar>> result = m;
		result -= scalar;
		return result;
	}

	template<size_t Rows, size_t Cols, typename T, typename TScalar>
		requires (!std::is_same<TScalar, mat<Rows, Cols, T>>::value)
	mat<Rows, Cols, SubtractionResult<TScalar, T>> operator-(const TScalar& scalar, const mat<Rows, Cols, T>& m)
	{
		mat<Rows, Cols, AdditionResult<TScalar, T>> result;

		for (size_t r = 0; r < result.num_rows; ++r)
			result[r] = scalar - m[r];

		return result;
	}

	template<size_t Rows, size_t Cols, typename T1, typename T2>
	mat<Rows, Rows, MultiplicationResult<T1, T2>> operator*(const mat<Rows, Cols, T1>& m1, const mat<Cols, Rows, T2>& m2)
	{
		mat<Rows, Rows, SubtractionResult<T1, T2>> result;

		return result;
	}

}

#endif
