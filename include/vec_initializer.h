#ifndef VEC_INITIALIZER_H
#define VEC_INITIALIZER_H

namespace linalg
{
	template<size_t L, typename T>
	class vec_initializer
	{
		std::unique_ptr<T> elems;

	public:
		vec_initializer();

		vec_initializer(std::initializer_list<T> vals);

		T& operator[](size_t idx);

		size_t size();
	};
}
#endif