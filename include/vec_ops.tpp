namespace linalg
{
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

}
