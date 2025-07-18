#ifndef VEC_INITIALIZER_H
#define VEC_INITIALIZER_H

namespace linalg
{
	template<typename T>
	vec_initializer::vec_initializer()
	{
		elems = std::make_unique<T>(L);
	}

	template<typename T>
	vec_initializer::vec_initializer(std::initializer_list<T> vals)
	{
		if (vals.size() != L)
			throw new std::exception("Illegal initializer list size");

		elems = std::make_unique<T>(L);

		for (int i = 0; i < L; ++i)
			elems[i] = vals[i];
	}

	template<typename T>
	T& vec_initializer::operator[](size_t idx)
	{
		if (idx >= L)
			throw new std::exception("Index out of bounds");

		return elems[idx];
	}

	template<typename T>
	size_t vec_initializer::size()
	{
		return L;
	}
}

#endif