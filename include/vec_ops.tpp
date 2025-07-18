namespace linalg
{
	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T>& operator+=(vec<L, T>& v, const U& val)
	{
		apply(v, [val](T& elem) {elem += val; });
		return v;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T> operator+(const vec<L, T>& v, const U& val)
	{
		vec<L, T> new_vec(v);
		new_vec += val;
		return new_vec;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T> operator+(const U& val, const vec<L, T>& v)
	{
		return v + val;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T>& operator+=(vec<L, T>& v1, const vec<L, U>& v2)
	{
		apply_elementwise(v1, [v2](T& elem_1, const T& elem_2) {elem_1 += elem_2; }, v2);
		return v1;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T> operator+(const vec<L, T>& v1, const vec<L, U>& v2)
	{
		vec<L, T> new_vec(v1);
		new_vec += v2;
		return new_vec;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T>& operator-=(vec<L, T>& v, const U& val)
	{
		apply(v, [val](T& elem) {elem -= val; });
		return v;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T> operator-(const vec<L, T>& v, const U& val)
	{
		vec<L, T> new_vec(v);
		new_vec -= val;
		return new_vec;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T> operator-(const U& val, const vec<L, T>& v)
	{
		vec<L, T> new_vec;
		return new_vec + val - v;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T>& operator-=(vec<L, T>& v1, const vec<L, U>& v2)
	{
		apply_elementwise(v1, [v2](T& elem_1, const T& elem_2) {elem_1 -= elem_2; }, v2);
		return v1;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T> operator-(const vec<L, T>& v1, const vec<L, U>& v2)
	{
		vec<L, T> new_vec(v1);
		new_vec -= v2;
		return new_vec;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T>& operator*=(vec<L, T>& v1, const U& val)
	{
		apply(v1, [val](T& elem) {elem *= val; });
		return v1;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T> operator*(const vec<L, T>& v, const U& val)
	{
		vec<L, T> new_vec(v);
		new_vec *= val;
		return new_vec;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T> operator*(const U& val, const vec<L, T>& v)
	{
		return v * val;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	T operator*(const vec<L, T>& v1, const vec<L, U>& v2)
	{
		T acc = 0;

		for (size_t i = 0; i < L; ++i)
			acc += v1[i] * v2[i];

		return acc;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T>& operator/=(vec<L, T>& v1, const U& val)
	{
		apply(v1, [val](T& elem) {elem /= val; });
		return v1;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T> operator/(const vec<L, T>& v, const U& val)
	{
		vec<L, T> new_vec(v);
		new_vec /= val;
		return new_vec;
	}

	template<size_t L, typename T, typename U> requires std::convertible_to<U, T>
	vec<L, T> operator/(const U& val, const vec<L, T>& v)
	{
		vec<L, T> new_vec;
		apply_elementwise([val](T& elem1, const T& elem2) {elem1 = val / elem2; }, v);
		return new_vec;
	}

	template<size_t L, typename T>
	std::ostream& operator<<(std::ostream& os, const linalg::vec<L, T>& v)
	{
		for (int i = 0; i < v.length; ++i)
			std::cout << v[i] << "\t";

		return os;
	};

	// Apply a unary operation to every element in the vector
	template<size_t L, typename T, typename F>
	void apply(vec<L, T>& v, F func)
	{
		for (size_t i = 0; i < v.length; ++i)
			func(v[i]);
	}

	// Apply a binary operation between every element of this vector and every element of other
	template<size_t L, typename T, typename U, typename F>
	void apply_elementwise(vec<L, T>& v, F func, const vec<L, U>& other) requires std::convertible_to<U, T>
	{
		for (size_t i = 0; i < v.length; ++i)
			func(v[i], other[i]);
	}

	template<size_t L, typename T>
	T mag(vec<L, T> v)
	{
		T acc = 0;

		for (int i = 0; i < v.length; ++i)
			acc += std::pow(v[i], 2);

		T mag = std::sqrt(acc);

		return mag;
	}

	template<size_t L, typename T>
	vec<L, T> norm(vec<L, T> v)
	{
		T m = mag(v);

		if (m == 0)
			return v;

		vec<L, T> ret = v / m;

		return ret;
	}
}
