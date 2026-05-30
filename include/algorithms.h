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

        // use forward-substitution get the matrix in row-echelon form
        for (size_t c = 0; c < Dim - 1; ++c)
        {
            if (a[c][c] == 0)
            {
                // look for a nonzero pivot
                for (size_t r = c + 1; r < Dim; ++r)
                {
                    if (a[r][c] != 0)
                    {
                        // swap the rows
                        vec<Dim * 2, T> temp = a[c];
                        a[c] = a[r];
                        a[r] = temp;
                    }
                }

                // if a nonzero pivot could not be found, matrix is singular; return zero matrix to indicate failure
                if (a[c][c] == 0)
                    return mat<Dim, Dim, T>();
            }

            T pivot = a[c][c];

            // eliminate the elements under the pivot
            for (size_t r = c + 1; r < Dim; ++r)
                a[r] = a[r] - (a[c] / pivot) * a[r][c];
        }

        // use back substitution to get u into reduced row-echelon form
        for (size_t c = Dim - 1; c > 0; --c)
        {
            T pivot = a[c][c];

            if (pivot == 0)
                // matrix has no inverse; return a zero matrix to indicate failure
                return mat<Dim, Dim, T>();

            // make the pivot 1
            a[c] /= pivot;

            for (size_t r = c; r-- > 0;)
                a[r] -= a[c] * a[r][c];
        }

        // extract the inverse matrix from u
        mat<Dim, Dim, T> inverted_matrix;

        for (size_t r = 0; r < Dim; ++r)
            for (size_t c = 0; c < Dim; ++c)
                inverted_matrix[r][c] = a[r][c + Dim];

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

    // perform LU factorization
    template<size_t Dim, typename T>
    void plu_factor(const mat<Dim, Dim, T>& m, mat<Dim, Dim, T>& P, mat<Dim, Dim, T>& L, mat<Dim, Dim, T>& U)
    {
        P = mat<Dim, Dim, T>(1);
        L = mat<Dim, Dim, T>(1);
        U = m;

        for (size_t i = 0; i < Dim - 1; ++i)
        {
            if (U[i][i] == 0)
            {
                // look for a nonzero pivot
                for (size_t r = i + 1; r < Dim; ++r)
                {
                    if (U[r][i] != 0)
                    {
                        // swap rows r and i
                        vec<Dim, T> temp = U[i];
                        U[i] = U[r];
                        U[r] = temp;
                        // record the swap in P
                        temp = P[i];
                        P[i] = P[r];
                        P[r] = temp;

                        break;
                    }
                }
            }

            T& pivot = U[i][i];

            for (size_t j = i + 1; j < Dim; j++)
            {
                L[j][i] = U[j][i] / pivot;
                U[j] -= L[j][i] * U[i];
            }
        }
    }
}

#endif