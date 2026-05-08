#ifndef SUBMAT_H
#define SUBMAT_H

#include "vec.h"

template<typename T, size_t E0, size_t E1>
struct submat_base
{
    T* data;

	submat_base(T* data)
		: data{data}
	{}
};

/*
2D non element owning submatrix

E0: extent of the first dimension (i.e. number of elements in each row)
E1: extent of the second dimension (i.e. number of elements in each column)
*/
template<typename T, size_t E0, size_t E1>
struct submat : submat_base<T, E0, E1>
{
	size_t strides[2];

	submat(T* data, size_t stride_0, size_t stride_1) : submat_base<T, E0, E1>(data)
	{
		this->strides[0] = stride_0;
		this->strides[1] = stride_1;
	}

	T& operator()(size_t r, size_t c)
	{
		if (r > E1)
			throw std::runtime_error("Row index out of bounds");
		
		if (c > E0)
			throw std::runtime_error("Column index out of bounds");

		return this->data[r * strides[0] + c * strides[1]];
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
struct submat<T, E0, 1> : submat_base<T, E0, 1>
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

#endif