#ifndef LINALG_COMMON_H
#define LINALG_COMMON_H

namespace linalg::impl
{
	template<typename T1, typename T2>
	using AdditionResult = decltype(std::declval<T1>() + std::declval<T2>());

	template<typename T1, typename T2>
	using SubtractionResult = decltype(std::declval<T1>() - std::declval<T2>());

	template<typename T1, typename T2>
	using MultiplicationResult = decltype(std::declval<T1>() * std::declval<T2>());

	template<typename T1, typename T2>
	using DivisionResult = decltype(std::declval<T1>() / std::declval<T2>());

	template<typename T1, typename T2>
	concept EqualityComparable = requires(T1 t1, T2 t2)
	{
		t1 == t2;
		t2 == t1;
	};

    template<typename T1, typename T2>
    concept Addable = requires(T1 t1, T2 t2)
    {
        t1 + t2;
    };
    
    template<typename T1, typename T2>
    concept Subtractable = requires(T1 t1, T2 t2)
    {
        t1 - t2;
    };

    template<typename T1, typename T2>
    concept Multipliable = requires(T1 t1, T2 t2)
    {
        t1 * t2;
    };

    template<typename T1, typename T2>
    concept Dividable = requires(T1 t1, T2 t2)
    {
        t1 / t2;
    };

    template<typename T>
    concept Negatable = requires(T t)
    {
        -t;
    };

    template<typename T1, typename T2>
    concept Insertable = requires(T1 t1, T2 t2)
    {
        t2 << t1;
    };
}

#endif