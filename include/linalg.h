#ifndef LINALG_H
#define LINALG_H

#include "vec.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "vec_ops.h"
#include "mat.h"
#include "mat2.h"
#include "mat3.h"
#include "mat4.h"
#include "mat_ops.h"
#include "quat.h"
#include "quat_ops.h"
#include "transformations.h"

#define LINALG_MAJOR_VERSION 0
#define LINALG_MINOR_VERSION 1

namespace linalg
{
	typedef vec<2, int> vec2i;
	typedef vec<3, int> vec3i;
	typedef vec<4, int> vec4i;
	typedef vec<2, float> vec2f;
	typedef vec<3, float> vec3f;
	typedef vec<4, float> vec4f;
	typedef vec<2, double> vec2d;
	typedef vec<3, double> vec3d;
	typedef vec<4, double> vec4d;

	typedef mat<2, int> mat2i;
	typedef mat<3, int> mat3i;
	typedef mat<4, int> mat4i;
	typedef mat<2, float> mat2f;
	typedef mat<3, float> mat3f;
	typedef mat<4, float> mat4f;
	typedef mat<2, double> mat2d;
	typedef mat<3, double> mat3d;
	typedef mat<4, double> mat4d;

	typedef quat<float> quatf;
	typedef quat<double> quatd;
}

#endif