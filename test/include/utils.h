#ifndef UTILS_H
#define UTILS_H

#include <concepts>
#include <float.h>
#include <bit>

template<typename TFloat>
    requires std::floating_point<typename std::remove_reference<TFloat>::type>
bool floatCompare(TFloat x, TFloat y)
{
    if (!(std::endian::native == std::endian::little))
        throw std::runtime_error("Not implemented");

    int diff_ulps = 0;
    for (size_t i = 0; i < sizeof(std::declval<TFloat>()); ++i)
    {
        uint8_t bx, by;

        memcpy(&bx, (uint8_t*) &x + i, 1);
        memcpy(&by, (uint8_t*) &y + i, 1);

        int diff = (int) bx - (int) by;
        diff *= pow(2, i*8);

        diff_ulps += diff;
    }

    if (abs(diff_ulps) <= 1)
        return true;
    
    return false;
}

template<typename T1, typename T2>
bool floatCompare(T1 x, T2 y)
    requires (
        std::floating_point<typename std::remove_reference<T1>::type> &&
        std::floating_point<typename std::remove_reference<T2>::type> &&
        !std::is_same<T1, T2>::value
    )
{
    if (sizeof(std::declval<T1>() > std::declval<T2>()))
        return floatCompare(x, (T1)y);
    else
        return floatCompare((T2)x, y);
}


#endif