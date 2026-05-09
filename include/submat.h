#ifndef SUBMAT_H
#define SUBMAT_H

#include "vec.h"

template<typename T, size_t... Extents>
struct submat
{
    T* data;
	size_t extents[sizeof...(Extents)];
	size_t strides[sizeof...(Extents)];

	template<typename... Strides>
	submat(T* data, Strides... strides)
		requires (sizeof...(Strides) == sizeof...(Extents))
		: data{data}
	{
		size_t idx = 0;
		(setExtent(Extents, idx++), ...);

		idx = 0;
		(setStride(strides, idx++), ...);
	}

	template<typename... Indices>
	T& operator()(Indices... indices)
		requires (sizeof...(Indices) == sizeof...(Extents))
	{
		size_t dim = 0;
		size_t offset = 0;
		(calculateOffset(dim++, Extents, indices, offset), ...);

		return data[offset];
	}

	T& operator[](size_t idx)
		requires (sizeof...(Extents) == 1)
	{
		return (*this)(idx);
	}

private:
	void setExtent(size_t extent, size_t idx)
	{
		extents[idx] = extent;
	}

	void setStride(size_t stride, size_t idx)
	{
		strides[idx] = stride;
	}

	void calculateOffset(size_t dim, size_t extent, size_t idx, size_t& offset)
	{
		if (idx > extent)
			throw std::runtime_error(std::format("Index {} out of bounds", dim + 1));
		
		offset += strides[dim] * idx;
	}
};

#endif