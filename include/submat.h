#ifndef SUBMAT_H
#define SUBMAT_H

#include "vec.h"

template<size_t Rows, size_t Cols, typename T>
struct submat_base
{
    T* data;

	submat_base(T* data)
		: data{data}
	{}
};

// 2D non element owning submatrix
template<size_t Rows, size_t Cols, typename T>
struct submat : submat_base<Rows, Cols, T>
{
	submat(T* data) : submat_base<Rows, Cols, T>(data) {}

	T& operator()(size_t r, size_t c)
	{
		if (r > Rows)
			throw std::runtime_error("Row index out of range");
		
		if (c > Cols)
			throw std::runtime_error("Column index out of range");

		return this->data[r * Cols + c];
	}

	submat<1, Cols, T> operator()(size_t r)
	{
        if (r > Rows)
            throw std::runtime_error("Index out of bounds");

        return submat<1, Cols, T>(&this->data[r * Cols]);
	}

    submat<1, Cols, T> operator[](size_t r)
    {
		return (*this)(r);
    }
};

// 1D non element owning submatrix
template<size_t Cols, typename T>
struct submat<1, Cols, T> : submat_base<1, Cols, T>
{
	submat(T* data) : submat_base<1, Cols, T>(data) {}

	T& operator()(size_t c)
	{
		if (c > Cols)
			throw std::runtime_error("Index out of bounds");

		return this->data[c];
	}

	T& operator[](size_t r)
	{
		return (*this)(r);
	}
};

#endif