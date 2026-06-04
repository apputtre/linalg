#ifndef LINALG_COMMON_H
#define LINALG_COMMON_H

#include <ostream>

namespace linalg::impl
{
	template<typename T1, typename T2>
	using t_sum = decltype(std::declval<T1>() + std::declval<T2>());

	template<typename T1, typename T2>
	using t_difference = decltype(std::declval<T1>() - std::declval<T2>());

	template<typename T1, typename T2>
	using t_product = decltype(std::declval<T1>() * std::declval<T2>());

	template<typename T1, typename T2>
	using t_quotient = decltype(std::declval<T1>() / std::declval<T2>());

    template<typename T>
    using t_sqrt = decltype(std::sqrt(std::declval<T>()));

	template<typename T>
	using t_norm = decltype(std::declval<T>() / t_sqrt<T>());

	template<typename T1, typename T2>
	using t_dot = decltype(std::declval<T1>() * std::declval<T2>() + std::declval<T1>() * std::declval<T2>());

	template<typename T1, typename T2>
	using t_cross = t_dot<T1, T2>();

    template<typename T>
    concept Printable = requires(T t, std::ostream& os)
    {
        os << t;
    };
}

#endif