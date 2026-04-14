namespace linalg
{
	template<typename T>
		template<typename U> requires std::convertible_to<U, T>
	vec<2, T>::vec(const vec<2, U>& other)
	{
		for (size_t i = 0; i < this->length; ++i)
			(*this)[i] = other[i];
	}

	template<typename T>
	vec<2, T>& vec<2, T>::operator=(const vec<2, T>& other)
	{
		for (size_t i = 0; i < this->length; ++i)
			(*this)[i] = other[i];
	}

	/*
	template<typename T>
		template<typename U> requires std::convertible_to<U, T>
	vec<2, U> vec<2, T>::operator()(vec<2, U>)
	{
		return vec<2, U>(*this);
	}
	*/

	template<typename T>
	T& vec<2, T>::operator[](size_t idx) const
	{
		switch (idx)
		{
		case 0:
			return (value_type&)x;
			break;
		case 1:
			return (value_type&)y;
			break;
		default:
			throw std::runtime_error("Index out of bounds");
			break;
		}
	}
}
