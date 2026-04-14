#include <iostream>

#include "vec.h"
#include "vec_ops.h"

#include "TestEnvironment.h"

using namespace linalg;

void SuiteVecElemAccessConstruction(TestEnvironment& tenv)
{
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
}

void SuiteVecElementMutability(TestEnvironment& tenv)
{
    tenv.beginSuite("Vector element mutability");

    {
        tenv.beginTest();

        vec<3, float> v(1, 2.5, -3);
        v[2] += 5;

        tenv.assert(v[2] == 2, "Vector element not mutable");
    }

    {
        tenv.beginTest();

        vec<4, int> v(1, 2, 4, 8);
        v[0] -= 4;
        v[2] += 3;

        tenv.assert(v[0] == -3 && v[2] == 7, "Vector elements not mutable");
    }

    {
        tenv.beginTest();

        vec<2, double> v(2.5, 4);
        v[0] *= 2;
        v[1] *= 1.5;

        tenv.assert(v[0] == 5 && v[1] == 6, "Vector elements not mutable");
    }
}

void SuiteVecSize(TestEnvironment& tenv)
{
    tenv.beginSuite("Vector size");

    {
        tenv.beginTest("vec3f size");

        vec<3, float> v(1, 2.5, -3);

        tenv.assert(sizeof(v) == sizeof(float) * 3, "Vector not expected size");
    }

    {
        tenv.beginTest("vec2d size");

        vec<2, double> v(3.5, 14);

        tenv.assert(sizeof(v) == sizeof(double) * 2, "Vector not expected size");
    }

    {
        tenv.beginTest("vec4i size");

        vec<4, int> v(1, 2, 3, 4);

        tenv.assert(sizeof(v) == sizeof(int) * 4, "Vector not expected size");
    }
}

void SuiteVecComparison(TestEnvironment& tenv)
{
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
}

void SuiteVecListInitialization(TestEnvironment& tenv)
{
    tenv.beginSuite("Vector list initialization");

    {
        tenv.beginTest("vec3f initialization");

        vec<3, float> v {4, 5.25, -6};

        tenv.assert(v[0] == 4 && v[1] == 5.25 && v[2] == -6, "Vector list intialization failed");
    }

    {
        tenv.beginTest("vec2i initialization");

        vec<2, int> v {1, 2};

        tenv.assert(v[0] == 1 && v[1] == 2, "Vector list initialization failed");
    }

    {
        tenv.beginTest("vec4d initialization");

        vec<4, double> v {3.25, 7.5, 1.2, 3.0};

        tenv.assert(v[0] == 3.25 && v[1] == 7.5 && v[2] == 1.2 && v[3] == 3.0, "Vector list initialization failed");
    }
}

int main()
{
    TestEnvironment tenv;

    SuiteVecElemAccessConstruction(tenv);
    SuiteVecSize(tenv);
    SuiteVecElementMutability(tenv);
    SuiteVecComparison(tenv);
    SuiteVecListInitialization(tenv);

    std::cout << tenv.getSummary();

    return 0;
}