#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "mat.h"

namespace linalg
{
    // inverts a matrix
    template<size_t Dim, typename T>
    mat<Dim, Dim, T> inv(const mat<Dim, Dim, T>& m)
    {
        // create the agumented matrix
        mat<Dim, Dim * 2, T> a = aug(m);
        // get the matrix in row-echelon form
        mat<Dim, Dim * 2, T> u = gje(a);

        // use back substitution to find inverse
        for (size_t c = Dim - 1; c > 0; --c)
        {
            T pivot = u[c][c];

            if (pivot == 0)
                // matrix has no inverse; return a zero matrix to indicate failure
                return mat<Dim, Dim, T>();

            // make the pivot 1
            u[c] /= pivot;

            for (size_t r = c; r-- > 0;)
                u[r] -= u[c] * u[r][c];
        }

        // extract the inverse matrix from u
        mat<Dim, Dim, T> inverted_matrix;

        for (size_t r = 0; r < Dim; ++r)
            for (size_t c = 0; c < Dim; ++c)
                inverted_matrix[r][c] = u[r][c + Dim];

        return inverted_matrix;
    }

    // Augments the matrix m with the identity matrix
    template<size_t Dim, typename T>
    linalg::mat<Dim, Dim * 2, T> aug(const linalg::mat<Dim, Dim, T>& m)
    {
        mat<Dim, 2 * Dim, T> aug;

        for (size_t r = 0; r < Dim; ++r)
            for (size_t c = 0; c < 2 * Dim; ++c)
                if (c < Dim)
                    // we're in the left half of the augmented matrix; copy from m
                    aug[r][c] = m[r][c];
                else
                    // we're in the right half; set to identity matrix
                    if (r == c - Dim)
                        aug[r][c] = 1;
                    else
                        aug[r][c] = 0;
        
        return aug;
    }

    // Performs Gauss-Jordan elimination to reduce m into row-echelon form
    template<size_t Rows, size_t Cols, typename T>
    linalg::mat<Rows, Cols, T> gje(const linalg::mat<Rows, Cols, T>& m)
    {
        linalg::mat<Rows, Cols, T> ret = m;

        for (size_t c = 0; c < Cols - 1 && c < Rows; ++c)
        {
            if (ret[c][c] == 0)
            {
                // look for a nonzero pivot
                for (size_t r = c + 1; r < Rows; ++r)
                {
                    if (ret[r][c] != 0)
                    {
                        // swap the rows
                        auto temp = ret[c];
                        ret[c] = ret[r];
                        ret[r] = temp;
                    }
                }

                // if a nonzero pivot could not be found, skip this column 
                if (ret[c][c] == 0)
                    continue;
            }

            T pivot = ret[c][c];

            // eliminate the elements under the pivot
            for (size_t r = c + 1; r < Rows; ++r)
                ret[r] = ret[r] - (ret[c] / pivot) * ret[r][c];
        }

        return ret;
    }
}

#endif