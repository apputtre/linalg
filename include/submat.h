#ifndef SUBMAT_H
#define SUBMAT_H

#include <format>

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

	template<typename... Indices>
	const T& operator()(Indices... indices) const
		requires (sizeof...(Indices) == sizeof...(Extents))
	{
		return (*const_cast<submat*>(this))(indices...);
	}

	submat& operator+=(const submat& other)
		requires (sizeof...(Extents) == 1)
	{
		for (size_t i = 0; i < extents[0]; ++i)
			(*this)(i) += other(i);
		
		return *this;
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

/*
2D non element owning submatrix

E0: extent of the first dimension (i.e. number of elements in each row)
E1: extent of the second dimension (i.e. number of elements in each column)
*/
/*
template<typename T, size_t... Extents>
struct submat : submat<T, Extents>
{
	}

	submat<T, E1, 1> operator()(size_t r)
	{
        if (r > E1)
            throw std::runtime_error("Index out of bounds");

        return submat<T, E1, 1>(&this->data[r * strides[0]], strides[1]);
	}

    submat<T, E1, 1> operator[](size_t r)
    {
		return (*this)(r);
    }
};

// 1D non element owning submatrix
template<typename T, size_t E0>
struct submat<T, E0, 1> : submat<T, E0, 1>
{
	size_t stride;

	submat(T* data, size_t stride) : submat_base<T, E0, 1>(data)
	{
		this->stride = stride;
	}

	T& operator()(size_t i)
	{
		if (i > E0)
			throw std::runtime_error("Index out of bounds");

		return this->data[i * stride];
	}

	T& operator[](size_t i)
	{
		return (*this)(i);
	}
};
*/

#endif