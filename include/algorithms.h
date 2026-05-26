#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "mat.h"

namespace linalg
{
    template<size_t Dim, typename T>
    mat<Dim, Dim, T> inv(const mat<Dim, Dim, T>& m)
    {
        return m;
    }
}

#endif