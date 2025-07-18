#ifndef MAT_H
#define MAT_H

#include <memory>
#include <iostream>
#include <concepts>

#include "vec.h"
#include "vec4.h"
#include "vec_ops.h"

namespace linalg
{
	template<size_t L, typename T>
	class mat
	{
	private:
		T elems[L];

	public:
		const static int num_rows = L;
		const static int num_cols = L;
		const static int num_elements = num_rows * num_cols;
	};
}

#endif
