#ifndef VEC_H
#define VEC_H

#include <memory>
#include <cmath>
#include <iostream>
#include <concepts>

namespace linalg
{
	template<size_t L, typename T>
	class vec
	{
	private:
		T elems[L];

	public:
		const static size_t length = L;
	};
}

#endif
