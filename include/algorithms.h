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
            T det = m[0][0] * m[1][1] - m[0][1] * m[1][0];

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
}

#endif