namespace linalg
{
	template<typename T>
	mat<2, T>::mat(T val)
	{
		for (size_t i = 0; i < this->num_cols; ++i)
			(*this)[i][i] = val;
	}

	template<typename T>
	mat<2, T>::mat(const mat<2, T>& other)
	{
		for (int r = 0; r < this->num_cols; ++r)
			for (int c = 0; c < this->num_rows; ++c)
				(*this)[c][r] = other[c][r];
	}

	template<typename T>
	mat<2, T>& mat<2, T>::operator=(const mat<2, T>& other)
	{
		for (int r = 0; r < this->num_cols; ++r)
			for (int c = 0; c < this->num_rows; ++c)
				(*this)[c][r] = other[c][r];
		
		return *this;
	}

	template<typename T>
	vec<2, T>& mat<2, T>::operator[](size_t idx) const
	{
		switch (idx)
		{
		case 0:
			return (vec<2, T>&)c0;
			break;
		case 1:
			return (vec<2, T>&)c1;
			break;
		default:
			throw new std::exception("Index out of bounds");
		}
	}
}
