#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "mat.h"

namespace linalg
{
    template<size_t Dim, typename T>
    mat<Dim, Dim, T> inv(const mat<Dim, Dim, T>& m)
    {
        if (Dim == 2)
        {
            T det = m.det();

            if (det == 0)
            {
                // matrix has no inverse
                return mat<Dim, Dim, T>();
            }

            return {
                {1 / det * m[1][1], 1 / det * -m[0][1]},
                {1 / det * -m[1][0], 1 / det * m[0][0]}
            };
        }
        return m;
    }

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
}

#endif