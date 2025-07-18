#include "vec_initializer.h"

namespace linalg
{
	template<typename T>
		template<typename U> requires std::convertible_to<U, T>
	vec<4, T>::vec(const vec<4, U>& other)
	{
		for (size_t i = 0; i < this->length; ++i)
			(*this)[i] = other[i];
	}

	template<typename T>
	vec<4, T>::vec(const vec_initializer<4, T>& init)
	{
		for (size_t i = 0; i < init.size(); ++i)
			(*this)[i] = init[i];
	}

	template<typename T>
	vec<4, T>& vec<4, T>::operator=(const vec<4, T>& other)
	{
		for (size_t i = 0; i < this->length; ++i)
			(*this)[i] = other[i];
		
		return *this;
	}

	template<typename T>
	T& vec<4, T>::operator[](size_t idx) const
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
		case 3:
			return (value_type&)w;
			break;
		default:
			throw new std::exception("Index out of bounds");
			break;
		}
	}
}
