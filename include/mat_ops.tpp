namespace linalg
{

	// Scalar addition
	template<size_t L, typename T, typename U>
	mat<L, T> operator+(const U& val, const mat<L, T>& m) requires std::convertible_to<U, T>
	{
		return m + val;
	}

	// Matrix addition
	template<size_t L, typename T, typename U>
	mat<L, T>& operator+=(mat<L, T>& m1, const mat<L, U>& m2) requires std::convertible_to<U, T>
	{
		apply_elementwise(m1, [](T& val1, T& val2) {val1 += val2; }, (mat<L, U>&) m2);
		return m1;
	}

	// Matrix addition
	template<size_t L, typename T, typename U>
	mat<L, T> operator+(const mat<L, T>& m1, const mat<L, U>& m2) requires std::convertible_to<U, T>
	{
		mat new_mat(m1);
		new_mat += m2;
		return new_mat;
	}

	template<size_t L, typename T, typename U>
	mat<L, T>& operator-=(mat<L, T>& m, const U& val) requires std::convertible_to<U, T>
	{
		apply(m, [val](T& elem) {elem -= val; });

		return m;
	}

	template<size_t L, typename T, typename U>
	mat<L, T> operator-(const mat<L, T>& m, const U& val) requires std::convertible_to<U, T>
	{
		mat new_mat(m);
		new_mat -= val;
		return new_mat;
	}

	template<size_t L, typename T, typename U>
	mat<L, T> operator-(const U& val, const mat<L, T>& m) requires std::convertible_to<U, T>
	{
		mat<L, T> new_mat;
		return new_mat + val - m;
	}

	template<size_t L, typename T, typename U>
	mat<L, T>& operator-=(mat<L, T>& m1, const mat<L, U>& m2) requires std::convertible_to<U, T>
	{
		apply_elementwise(m1, [](T& val1, T& val2) {val1 -= val2; }, (mat<L, U>&) m2);
		return m1;
	}

	template<size_t L, typename T, typename U>
	mat<L, T> operator-(const mat<L, T>& m1, const mat<L, U>& m2) requires std::convertible_to<U, T>
	{
		mat new_mat(m1);
		new_mat -= m2;
		return new_mat;
	}

	template<size_t L, typename T, typename U>
	mat<L, T>& operator*=(mat<L, T>& m, const U& val) requires std::convertible_to<U, T>
	{
		apply(m, [val](T& elem) {elem *= val; });
		return m;
	}

	template<size_t L, typename T, typename U>
	mat<L, T> operator*(const mat<L, T>& m, const U& val) requires std::convertible_to<U, T>
	{
		mat new_mat(m);
		new_mat *= val;
		return new_mat;
	}

	template<size_t L, typename T, typename U>
	mat<L, T> operator*(const U& val, const mat<L, T>& m1) requires std::convertible_to<U, T>
	{
		return m1 * val;
	}

	template<size_t L, typename T, typename U>
	mat<L, T> operator*(const mat<L, T>& m1, const mat<L, U>& m2) requires std::convertible_to<U, T>
	{
		mat<L, T> result;

		for (int r = 0; r < m1.num_rows; ++r)
		{
			for (int c = 0; c < m1.num_cols; ++c)
			{
				T acc = 0;

				for (int offset = 0; offset < m1.num_cols; ++offset)
					acc += m1[offset][r] * m2[c][offset];

				result[c][r] = acc;
			}
		}

		return result;
	}

	template<size_t L, typename T, typename U>
	mat<L, T>& operator*=(mat<L, T>& m1, const mat<L, U>& m2) requires std::convertible_to<U, T>
	{
		m1 = m1 * m2;
		return m1;
	}

	template<size_t L, typename T, typename U>
	vec<L, T> operator*(const mat<L, T>& m, const vec<L, U>& v) requires std::convertible_to<U, T>
	{
		vec<L, T> result;

		for (int r = 0; r < m.num_rows; ++r)
		{
			T acc = 0;

			for (int offset = 0; offset < m.num_cols; ++offset)
				acc += m[offset][r] * v[offset];

			result[r] = acc;
		}

		return result;
	}


	template<size_t L, typename T, typename U>
	mat<L, T>& operator/=(mat<L, T>& m, const U& val) requires std::convertible_to<U, T>
	{
		apply(m, [val](T& elem) {elem /= val; });
		return m;
	}

	template<size_t L, typename T, typename U>
	mat<L, T> operator/(const mat<L, T>& m, const U& val) requires std::convertible_to<U, T>
	{
		mat new_mat(m);
		new_mat /= val;
		return new_mat;
	}

	// Apply a unary operation to every element in 'm'
	template<size_t L, typename T, typename F>
	void apply(mat<L, T>& m, F func)
	{
		for (int r = 0; r < m.num_rows; ++r)
			for (int c = 0; c < m.num_cols; ++c)
				func(m[c][r]);
	}

	// Apply a binary operation between every element of 'm1' and every element of 'm2'
	template<size_t L, typename T, typename U, typename F>
	void apply_elementwise(mat<L, T>& m1, F func, const mat<L, U>& m2) requires std::convertible_to<U, T>
	{
		for (int r = 0; r < m1.num_rows; ++r)
			for (int c = 0; c < m1.num_cols; ++c)
				func(m1[c][r], m2[c][r]);
	}

}
