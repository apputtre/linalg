#ifndef SUBMAT_H
#define SUBMAT_H

#include "vec.h"

/*
2-D non element owning submatrix
*/
template<size_t Rows, size_t Cols, typename T>
struct submat
{
    T* data;

	T& operator()(size_t r, size_t c)
	{
		if (r > Rows)
			throw std::runtime_error("Row index out of range");
		
		if (c > Cols)
			throw std::runtime_error("Column index out of range");

		return data[r * Cols + c];
	}

	/*
    submat<1, Cols, T>& operator[](size_t idx)
    {
        if (idx > Dim1)
            throw std::runtime_error("Index out of bounds");

        return submat<1, Dim1, T> {data[idx * strides[0]], strides[1]};
    }
	*/
};

// 1-D submatrix
/*
template<size_t L, typename T>
struct submat<1, L, T>
{
	T* data;
	const size_t stride;

	T& operator[](size_t idx)
	{
		if (idx > L)
			throw std::runtime_error("Index out of bounds");

		return data[idx * stride];
	}
};
*/

#endif