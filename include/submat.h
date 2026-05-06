#ifndef SUBMAT_H
#define SUBMAT_H

template<typename T>
struct submat
{
    T* data;
    const size_t size;
    const size_t stride;

    T& operator[](size_t idx)
    {
        if (idx > size)
            throw std::runtime_error("Index out of bounds");

        return data[idx * stride];
    }
};

#endif