namespace linalg
{
	template<typename T>
		template<typename U> requires std::convertible_to<U, T>
	vec<3, T>::vec(const vec<3, U>& other)
	{
		for (size_t i = 0; i < this->length; ++i)
			(*this)[i] = other[i];
	}

	template<typename T>
	vec<3, T>& vec<3, T>::operator=(const vec<3, T>& other)
	{
		for (size_t i = 0; i < this->length; ++i)
			(*this)[i] = other[i];

		return *this;
	}

	template<typename T>
	T& vec<3, T>::operator[](size_t idx) const
	{
		switch (idx)
		{
		case 0:
			return (value_type&)x;
			break;
		case 1:
			return (value_type&)y;
			break;
		case 2:
			return (value_type&)z;
			break;
		default:
			throw std::runtime_error("Index out of bounds");
		}
	}
}
