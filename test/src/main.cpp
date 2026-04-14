#include <iostream>

#include "vec.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "vec_ops.h"

#include "TestEnvironment.h"

using namespace linalg;

int main()
{
    TestEnvironment tenv;

    tenv.beginSuite("Vector element access and construction");

    {
        tenv.beginTest("vec3f default construction 1");
        vec<3, float> v;

        tenv.assert(v[0] == 0 && v[1] == 0 && v[2] == 0, "Vector not default constructed with expected values");
    }

    {
        tenv.beginTest("vec1i default construction");
        vec<3, int> v;

        tenv.assert(v[0] == 0, "Vector not default constructed with expected value");
    }

    {
        tenv.beginTest("vec4d default construction");
        vec<4, double> v;

        tenv.assert(v[0] == 0 && v[1] == 0 && v[2] == 0 && v[3] == 0, "Vector not default constructed with expected values");
    }

    {
        tenv.beginTest("vec3d construction");
        vec<3, float> v(1, 2.5, -3);

        tenv.assert(v[0] == 1 && v[1] == 2.5 && v[2] == -3, "Vector not constructed with expected values");
    }

    {
        tenv.beginTest("vec4i construction");
        vec<4, int> v(-10, 500, 3, 62);

        tenv.assert(v[0] == -10 && v[1] == 500 && v[2] == 3 && v[3] == 62, "Vector not constructed with expected values");
    }

    {
        tenv.beginTest("vec2i construction with float values");
        vec<2, int> v(2.5, 6);

        tenv.assert(v[0] == 2 && v[1] == 6, "Vector not constructed with expected values");
    }

    {
        tenv.beginTest("vec<2, size_t> construction");
        vec<2, size_t> v(14, 137);

        tenv.assert(v[0] == 14 && v[1] == 137, "Vector not constructed with expected values");
    }

    {
        tenv.beginTest("Invalid element access");
        vec<3, float> v(1, 2.5, 3);

        bool error_caught = false;
        try
        {
            v[3];
        }
        catch(std::runtime_error& e)
        {
            error_caught = true;
        }

        tenv.assert(error_caught, "Invalid access allowed");
    }

    tenv.beginSuite("Vector comparison");

    {
        tenv.beginTest("Equal vector comparison (float-float)");

        vec<3, float> v1(1, 2.5, -3);
        vec<3, float> v2(1, 2.5, -3);

        tenv.assert(v1 == v2, "Equal vectors considered unequal");
    }

    {
        tenv.beginTest("Equal vector comparison (int-int)");

        vec<2, int> v1(1, 3);
        vec<2, int> v2(1, 3);

        tenv.assert(v1 == v2, "Equal vectors considered unequal");
    }

    {
        tenv.beginTest("Equal vector comparison (double-double)");

        vec<4, double> v1(1, 2.5, -3, 137);
        vec<4, double> v2(1, 2.5, -3, 137);

        tenv.assert(v1 == v2, "Equal vectors considered unequal");
    }

    {
        tenv.beginTest("Unequal vector comparison (float-float)");

        vec<3, float> v1(1, 2.5, -3);
        vec<3, float> v2(4, 5.5, -6);

        tenv.assert(v1 != v2, "Unequal vectors considered equal");
    }

    {
        tenv.beginTest("Unequal vector comparison (int-int)");

        vec<2, float> v1(1, 3);
        vec<2, float> v2(5, 7);

        tenv.assert(v1 != v2, "Unequal vectors considered equal");
    }

    {
        tenv.beginTest("Unequal vector comparison (double-double)");

        vec<4, double> v1(1, 2.5, -3, 137);
        vec<4, double> v2(1, 3, 7.5, 9);

        tenv.assert(v1 != v2, "Unequal vectors considered equal");
    }

    std::cout << tenv.getSummary();

    return 0;
}