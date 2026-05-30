#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "mat.h"

namespace linalg
{
    // Inverts a matrix. Returns true is m is invertible, false otherwise
    template<size_t Dim, typename T>
    bool inv(mat<Dim, Dim, T>& m, mat<Dim, Dim, T>& result)
    {
        result = mat<Dim, Dim, T>(1);

        // use forward-substitution get the matrix in row-echelon form
        for (size_t c = 0; c < Dim; ++c)
        {
            if (m[c][c] == 0)
            {
                // look for a nonzero pivot
                for (size_t r = c + 1; r < Dim; ++r)
                {
                    if (m[r][c] != 0)
                    {
                        // swap the rows
                        vec<Dim, T> temp = m[c];
                        m[c] = m[r];
                        m[r] = temp;

                        // reflect the swap on the result matrix
                        temp = result[c];
                        result[c] = result[r];
                        result[r] = temp;
                    }
                }

                // if a nonzero pivot could not be found, matrix is singular
                if (m[c][c] == 0)
                    return false;
            }

            T pivot = m[c][c];

            // eliminate the elements under the pivot
            for (size_t r = c + 1; r < Dim; ++r)
            {
                T coefficient = m[r][c] / pivot;

                m[r] -= m[c] * coefficient;
                result[r] -= result[c] * coefficient;
            }
        }

        // use back substitution to turn result into m^-1
        for (size_t c = Dim - 1; c > 0; --c)
        {
            T pivot = m[c][c];

            result[c] /= pivot;

            for (size_t r = c; r-- > 0;)
                // we don't care about updating m anymore
                result[r] -= result[c] * m[r][c];   
        }

        return true;
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

    // Solves a system of Dim equations and Dim variables of the form LUx = Pb for x, storing the result in x
    template<size_t Dim, typename T>
    bool solve(mat<Dim, Dim, T>& p, mat<Dim, Dim, T>& L, mat<Dim, Dim, T>& u, vec<Dim, T>& b, vec<Dim, T>& x)
    {
        x = vec<Dim, T>();

        return false;
    }

    // Solves a system of Dim equations and Dim variables of the form Ax = b for x, storing the result in x
    template<size_t Dim, typename T>
    bool solve(mat<Dim, Dim, T>& a, vec<Dim, T>& b, vec<Dim, T>& x)
    {
        mat<Dim, Dim, T> p;
        mat<Dim, Dim, T> L;
        mat<Dim, Dim, T> u;
        plu_factor(p, L, u, a);
        
        return solve(p, L, u, b, x);
    }
}

#endif