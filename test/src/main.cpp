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

void SuiteVecCopyConstruction(TestEnvironment& tenv)
{
    tenv.beginSuite("Vector copy construction");

    {
        tenv.beginTest();

        vec<3, float> v1(1, 2.5, -3);
        vec<3, float> v2(v1);

        tenv.assert(v1 == v2, "Vector copy construction failed");
    }

    {
        tenv.beginTest();

        vec<2, double> v1(2.5, -300);
        vec<2, double> v2(v1);

        tenv.assert(v1 == v2, "Vector copy construction failed");
    }

    {
        tenv.beginTest();

        vec<5, std::string> v1("a", "b", "c", "d", "e");
        vec<5, std::string> v2(v1);

        tenv.assert(v1 == v2, "Vector copy assignment failed");
    }

    {
        tenv.beginTest("Vector copy dependence 1");

        vec<3, float> v1(1, 2.5, -3);
        vec<3, float> v2(v1);

        v1[1] = 137;

        tenv.assert(v2[1] == 2.5, "Vector copy dependence");
    }

    {
        tenv.beginTest("Vector copy dependence 2");

        vec<2, int> v1(1, 2);
        vec<2, int> v2(v1);

        v2[0] = 14;

        tenv.assert(v1[0] == 1, "Vector copy dependence");
    }

}

void SuiteVecCopyConstructionDifferentTypes(TestEnvironment& tenv)
{
    tenv.beginSuite("Vector copy construction - different types");

    {
        tenv.beginTest("vec3f -> vec3i");

        vec<3, float> v1(1, 2.5, -3);
        vec<3, int> v2(v1);

        tenv.assert(v2 == vec<3, int>(1, 2, -3), "Vector copy construction failed");
    }

    {
        tenv.beginTest("vec2i -> vec2f");

        vec<2, int> v1(137, 25000);
        vec<2, float> v2(v1);

        tenv.assert(v2 == vec<2, float>(137.0f, 25000.0f), "Vector copy construction failed");
    }

    {
        tenv.beginTest("vec<4, int> -> vec<4, char>");

        vec<4, int> v1(65, 66, 67, 68);
        vec<4, char> v2(v1);

        tenv.assert(v2 == vec<4, char>('A', 'B', 'C', 'D'), "Vector copy construction failed");
    }
}

void SuiteVecCopyAssignment(TestEnvironment& tenv)
{
    tenv.beginSuite("Vector copy assignment");

    {
        tenv.beginTest();

        vec<3, float> v1(1, 2.5, -3);
        vec<3, float> v2(4, 5.5, -6);

        v2 = v1;

        tenv.assert(v1 == v2, "Vector copy assignment failed");
    }

    {
        tenv.beginTest();

        vec<5, int> v1(2, 4, 6, 8, 10);
        vec<5, int> v2;

        v2 = v1;

        tenv.assert(v1 == v2, "Vector copy assignment failed");
    }

    {
        tenv.beginTest();

        vec<2, float> v1(2.5, -5);
        vec<2, float> v2;

        v2 = v1;

        tenv.assert(v1 == v2, "Vector copy assignment failed");
    }

    {
        tenv.beginTest("Copy independence 1");

        vec<3, float> v1(1, 2.5, -3);
        vec<3, float> v2;

        v2 = v1;

        v2[0] = 13;

        tenv.assert(v1[0] == 1, "Vector copy dependence");
    }

    {
        tenv.beginTest("Copy independence 2");

        vec<2, int> v1(1, 2);
        vec<2, int> v2;

        v2 = v1;

        v1[1] = 32;

        tenv.assert(v2[1] == 2, "Vector copy dependence");
    }

    {
        tenv.beginTest();

        vec<3, float> v1(1, 2.5, -3);
        vec<3, int> v2;

        v2 = v1;

        tenv.assert(v2 == vec<3, int>(1, 2, -3), "Vector copy assignment failed");
    }

    {
        tenv.beginTest();

        vec<6, int> v1(1, 3, 5, 7, 9);
        vec<6, double> v2;

        v2 = v1;

        tenv.assert(v2 == vec<6, double>(1, 3, 5, 7, 9), "Vector copy assignment failed");
    }
}

void SuiteVecScalarConstruction(TestEnvironment& tenv)
{
    tenv.beginSuite("Vector scalar value construction");

    {
        tenv.beginTest();

        vec<4, double> v(2.7);

        tenv.assert(v == vec<4, double>(2.7, 2.7, 2.7, 2.7), "Vector scalar construction failed");
    }

    {
        tenv.beginTest();

        vec<2, int> v(13);

        tenv.assert(v == vec<2, int>(13, 13), "Vector scalar construction failed");
    }

    {
        tenv.beginTest();

        vec<3, std::string> v("abc");

        tenv.assert(v == vec<3, std::string>("abc", "abc", "abc"), "Vector scalar construction failed");
    }
}

void SuiteVecScalarAssignment(TestEnvironment& tenv)
{
    tenv.beginSuite("Vector scalar assignment");

    {
        tenv.beginTest();

        vec<3, float> v;
        v = 1.3;

        tenv.assert(v == vec<3, float>(1.3, 1.3, 1.3), "Vector scalar assignment failed");
    }

    {
        tenv.beginTest();

        vec<2, std::string> v;
        v = std::string("hello world");

        tenv.assert(v == vec<2, std::string>("hello world", "hello world"), "Vector scalar assignment failed");
    }

    {
        tenv.beginTest();

        vec<4, int> v(1, 2, 3, 4);
        v = 14;

        tenv.assert(v == vec<4, int>(14, 14, 14, 14), "Vector scalar assignment failed");
    }

    {
        tenv.beginTest();

        vec<3, int> v(15, 16, 17);
        v = 2.5;

        tenv.assert(v == vec<3, int>(2, 2, 2), "Vector scalar assignment failed");
    }
}

void SuiteVecScalarComparison(TestEnvironment& tenv)
{
    tenv.beginSuite("Vector scalar comparison");

    {
        tenv.beginTest();

        vec<3, float> v(2.4, 2.4, 2.4);

        tenv.assert(v == 2.4f, "Vector scalar comparison failed");
    }

    {
        tenv.beginTest();

        vec<2, int> v(13, 13);

        tenv.assert(v == 13, "Vector scalar comparison failed");
    }

    {
        tenv.beginTest();

        vec<2, std::string> v("hello world", "hello world");

        tenv.assert(v == std::string("hello world"), "Vector scalar comparison failed");
    }

    {
        tenv.beginTest();

        vec<3, double> v(1, 2.5, -3);

        tenv.assert(!(v == 2.5), "Vector scalar comparison failed");
    }

    {
        tenv.beginTest();

        vec<3, float> v(2, 2.5, -3);

        tenv.assert(v != 7.0f, "Vector scalar comparison failed");
    }

    {
        tenv.beginTest();

        vec<2, int> v(1, 1);

        tenv.assert(v != 0, "Vector scalar comparison failed");
    }

    tenv.beginTest();

    vec<4, double> v(2.5, 2.5, 2.5, 2.5);

    tenv.assert(!(v != 2.5), "Vector scalar comparison failed");
}

void SuiteVecAddition(TestEnvironment& tenv)
{
    tenv.beginSuite("Vector-vector addition");

    {
        tenv.beginTest("Vector-vector addition - same types 1");

        vec<3, int> v1 {1, -2, 3};
        vec<3, int> v2 {3, 5, 7};

        tenv.assertEq(v1 + v2, vec<3, int>{4, 3, 10});
        // test commutativity
        tenv.assertEq(v1 + v2, v2 + v1, "Addition is not commutative");

        vec<3, int> v1_old = v1;
        v1 += v2;

        tenv.assertEq(v1, v1_old + v2);
    }

    {
        tenv.beginTest("Vector-vector addition - same types 2");

        vec<2, float> v1 {2.5, 3.7};
        vec<2, float> v2 {-1.5, 3};

        tenv.assertEq(v1 + v2, vec<2, float>{1, 6.7});
        // test commutativity
        tenv.assertEq(v1 + v2, v2 + v1, "Addition is not commutative");

        vec<2, float> v1_old = v1;
        v1 += v2;

        tenv.assertEq(v1, v1_old + v2);
    }

    {
        tenv.beginTest("Vector-vector addition - same types 3");

        vec<1, std::string> v1 {"Race"};
        vec<1, std::string> v2 {"car"};

        tenv.assertEq(v1 + v2, vec<1, std::string>{"Racecar"});
        // test non-commutativity
        tenv.assertNeq(v1 + v2, v2 + v1, "Addition is commutative");

        vec<1, std::string> v1_old = v1;
        v1 += v2;

        tenv.assertEq(v1, v1_old + v2);
    }

        // when two vectors of different types are added, the smaller type should be promoted to the larger
    {
        tenv.beginTest("Vector-vector addition - different types 1");

        vec<4, float> v1 {1.1, -2.2, 3.3, -4.4};
        vec<4, int> v2 {1, 1, 1, 1};

        tenv.assert(std::is_same<decltype(v1 + v2), vec<4, float>>::value);
        tenv.assertEq(v1 + v2, vec<4, float> {2.1, -1.2, 4.3, -3.4});
        // test commutativity
        tenv.assertEq(v1 + v2, v2 + v1);

        vec<4, float> v1_old = v1;
        v1 += v2;

        tenv.assertEq(v1, v1_old + v2);
    }

    {
        tenv.beginTest("Vector-vector addition - different types 2");

        vec<2, float> v1 {2.5, 5.25};
        vec<2, double> v2 {0.1, 0.1};

        tenv.assert(std::is_same<decltype(v1 + v2), vec<2, double>>::value);
        tenv.assertEq(v1 + v2, vec<2, double> {2.6, 5.35});
        // test commutativity
        tenv.assertEq(v1 + v2, v2 + v1);

        vec<2, float> v1_old = v1;
        v1 += v2;

        // cast to float vec to reduce precision and make comparison work as expected
        tenv.assertEq(v1, (vec<2, float>) (v1_old + v2));
    }
}

void SuiteVecScalarAddition(TestEnvironment& tenv)
{
    tenv.beginSuite("Vector-scalar addition");

    {
        tenv.beginTest("Vector-scalar addition 1 - same types 1");

        vec<3, float> v(1, -2.5, 3);
        float x = 3.2;

        tenv.assertEq(v + x, vec<3, float> (v[0] + x, v[1] + x, v[2] + x));

        // test commutativity
        tenv.assertEq(v + x, x + v);

        auto v_old = v;

        v += x;
        
        tenv.assertEq(v, v_old + x);
    }

    {
        tenv.beginTest("Vector-scalar addition 2 - same types 2");

        vec<2, std::string> v("Hello", "Hello");
        std::string x = " world";

        tenv.assertEq(v + x, vec<2, std::string> (v[0] + x, v[1] + x));
        // test non-commutativity
        tenv.assertEq(x + v, vec<2, std::string> (x + v[0], x + v[1]));

        auto v_old = v;

        v += x;

        tenv.assertEq(v, v_old + x);
    }

    {
        tenv.beginTest("Vector-scalar addition - different types 1");

        vec<3, float> v {0.1, -0.2, 0.3};
        double x = 2.5;

        auto result = v + x;

        tenv.assert(std::is_same<decltype(result), vec<3, double>>::value);

        tenv.assertEq(result, vec<3, double>(v[0] + x, v[1] + x, v[2] + x));

        // test commutativity
        tenv.assertEq(v + x, x + v);

        auto v_old = v;

        v += x;

        tenv.assertEq(v, (vec<3, float>) (v_old + x));
    }

    {
        tenv.beginTest("Vector-scalar addition - different types 2");

        vec<3, double> v {0.1, -0.2, 0.3};
        float x = 2.5;

        auto result = v + x;

        tenv.assert(std::is_same<decltype(result), vec<3, double>>::value);

        tenv.assertEq(result, vec<3, double>(v[0] + x, v[1] + x, v[2] + x));

        // test commutativity
        tenv.assertEq(v + x, x + v);

        auto v_old = v;

        v += x;

        tenv.assertEq(v, (vec<3, double>) (v_old + x));
    }
}

void SuiteVecNegation(TestEnvironment& tenv)
{
    tenv.beginSuite("Vector negation");

    {
        tenv.beginTest("Vector negation 1");

        vec<3, int> v {25, 50, 75};

        tenv.assertEq(-v, vec<3, int>(-v[0], -v[1], -v[2]));
    }

    {
        tenv.beginTest("Vector negation 2");

        vec<2, float> v {2.5, 4.7};

        tenv.assertEq(-v, vec<2, float>(-v[0], -v[1]));
    }

    {
        tenv.beginTest("Vector negation 3");

        vec<4, double> v {137, -12.5, 13, 3.14};

        tenv.assertEq(-v, vec<4, double>(-v[0], -v[1], -v[2], -v[3]));
    }

}

void SuiteVecSubtraction(TestEnvironment& tenv)
{
    tenv.beginSuite("Vector-vector subtraction");

    {
        tenv.beginTest("Vector-vector subtraction - same types 1");

        vec<3, int> v1 {1, -2, 3};
        vec<3, int> v2 {3, 5, 7};

        tenv.assert(std::is_same<decltype(v1 - v2), vec<3, int>>::value);
        tenv.assertEq(v1 - v2, vec<3, int>(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]));
        // test anti-commutativity
        tenv.assertEq(v1 - v2, -(v2 - v1));

        vec<3, int> v1_old = v1;
        v1 -= v2;

        tenv.assertEq(v1, v1_old - v2);
    }

    {
        tenv.beginTest("Vector-vector subtraction - same types 2");

        vec<2, float> v1 {2.5, -3.7};
        vec<2, float> v2 {13.6, 4.5};

        tenv.assert(std::is_same<decltype(v1 - v2), vec<2, float>>::value);
        tenv.assertEq(v1 - v2, vec<2, float>(v1[0] - v2[0], v1[1] - v2[1]));
        // test anti-commutativity
        tenv.assertEq(v1 - v2, -(v2 - v1));

        vec<2, float> v1_old = v1;
        v1 -= v2;

        tenv.assertEq(v1, v1_old - v2);
    }

    {
        tenv.beginTest("Vector-vector subtraction - same types 3");

        vec<4, double> v1 {2.5, -3.7, 3.14, 2.6};
        vec<4, double> v2 {13.6, 4.5, 14, 0};

        tenv.assert(std::is_same<decltype(v1 - v2), vec<4, double>>::value);
        tenv.assertEq(v1 - v2, vec<4, double>(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2], v1[3] - v2[3]));
        // test anti-commutativity
        tenv.assertEq(v1 - v2, -(v2 - v1));

        vec<4, double> v1_old = v1;
        v1 -= v2;

        tenv.assertEq(v1, v1_old - v2);
    }

    {
        tenv.beginTest("Vector-vector subtraction - different types 1");

        vec<3, double> v1 {1.1, -2.2, 3.3};
        vec<3, float> v2 {1.5, 2.5, 3.5};

        tenv.assert(std::is_same<decltype(v1 - v2), vec<3, double>>::value);
        tenv.assertEq(v1 - v2, vec<3, double> (v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]));
        // test anti - commutativity
        tenv.assertEq((vec<3, float>)(v1 - v2), -(vec<3, float>)(v2 - v1));

        vec<3, double> v1_old = v1;
        v1 += v2;

        tenv.assertEq(v1, v1_old + v2);
    }

    {
        tenv.beginTest("Vector-vector subtraction - different types 2");

        vec<2, float> v1 {1.5, -3.6};
        vec<2, double> v2 {3.14, 9.2};

        tenv.assert(std::is_same<decltype(v1 - v2), vec<2, double>>::value);
        tenv.assertEq(v1 - v2, vec<2, double> (v1[0] - v2[0], v1[1] - v2[1]));
        // test anti - commutativity
        tenv.assertEq((vec<2, float>)(v1 - v2), -(vec<2, float>)(v2 - v1));

        vec<2, float> v1_old = v1;
        v1 += v2;

        tenv.assertEq(v1, (vec<2, float>) (v1_old + v2));
    }
}

void SuiteVecScalarSubtraction(TestEnvironment& tenv)
{
    tenv.beginSuite("Vector-scalar subtraction");

    {
        tenv.beginTest("Vector-scalar subtraction - same types");

        vec<3, float> v(1, -2.5, 3);
        float x = 0.2;

        tenv.assertEq(v - x, vec<3, float> (v[0] - x, v[1] - x, v[2] - x));
        // test anti-commutativity
        tenv.assertEq(x - v, -(v - x));

        auto v_old = v;

        v -= x;

        tenv.assertEq(v, v_old - x);
    }

    {
        tenv.beginTest("Vector-scalar subtraction - different types 1");

        vec<2, float > v {0.1, -0.2};
        double x = 1.75;

        auto result = v - x;

        tenv.assert(std::is_same<decltype(result), vec<2, double>>::value);

        tenv.assertEq((vec<2, float>) result, vec<2, float>(v[0] - x, v[1] - x));

        // test anti-commutativity
        tenv.assertEq((vec<2, float>)(v - x), -(vec<2, float>)(x - v));

        auto v_old = v;

        v -= x;

        tenv.assertEq(v, (vec<2, float>) (v_old - x));
    }

    {
        tenv.beginTest("Vector-scalar subtraction - different types 2");

        vec<3, double> v(2.6, -3.5, 137);
        float x = 256;

        auto result = v - x;

        tenv.assert(std::is_same<decltype(result), vec<3, double>>::value);

        tenv.assertEq((vec<3, float>) result, vec<3, float>(v[0] - x, v[1] - x, v[2] - x));

        // test anti-commutativity
        tenv.assertEq((vec<3, float>)(v - x), -(vec<3, float>)(x - v));

        auto v_old = v;

        v -= x;

        tenv.assertEq((vec<3, float>)v, (vec<3, float>) (v_old - x));
    }
}

void SuiteVecScalarMultiplication(TestEnvironment& tenv)
{
    tenv.beginSuite("Vector scalar multiplication");

    {
        tenv.beginTest("Vector-scalar multiplication - same types");

        vec<3, float> v(1, -2.5, 3);
        float x = 0.2;

        tenv.assertEq(v * x, vec<3, float> (v[0] * x, v[1] * x, v[2] * x));
        // test commutativity
        tenv.assertEq(x * v, v * x);

        auto v_old = v;

        v *= x;

        tenv.assertEq(v, v_old * x);
    }

    {
        tenv.beginTest("Vector-scalar multiplication - different types 1");

        vec<2, float > v {0.1, -0.2};
        double x = 1.75;

        auto result = v * x;

        tenv.assert(std::is_same<decltype(result), vec<2, double>>::value);

        tenv.assertEq((vec<2, float>) result, vec<2, float>(v[0] * x, v[1] * x));

        // test commutativity
        tenv.assertEq((vec<2, float>)(v * x), (vec<2, float>)(x * v));

        auto v_old = v;

        v *= x;

        tenv.assertEq(v, (vec<2, float>) (v_old * x));
    }

    {
        tenv.beginTest("Vector-scalar multiplication - different types 2");

        vec<3, double> v(2.6, -3.5, 137);
        float x = 256;

        auto result = v * x;

        tenv.assert(std::is_same<decltype(result), vec<3, double>>::value);

        tenv.assertEq((vec<3, float>) result, vec<3, float>(v[0] * x, v[1] * x, v[2] * x));

        // test commutativity
        tenv.assertEq((vec<3, float>)(v * x), (vec<3, float>)(x * v));

        auto v_old = v;

        v *= x;

        tenv.assertEq((vec<3, float>)v, (vec<3, float>) (v_old * x));
    }
}

void SuiteVecDotProduct(TestEnvironment& tenv)
{
    tenv.beginSuite("Vector dot product");

    {
        tenv.beginTest("Dot product - same types 1");

        vec<2, int> v1(1, 2);
        vec<2, int> v2(3, 4);

        tenv.assertEq(v1 * v2, v1[0] * v2[0] + v1[1] * v2[1]);
        tenv.assertEq(v1 * v2, v2 * v1);

        tenv.assertNeq(v1 * v2, 0);
    }

    {
        tenv.beginTest("Dot product - same types 2");

        vec<3, float> v1(1.5, -2.5, 3.5);
        vec<3, float> v2(4.5, -5.5, 6.5);

        tenv.assertEq(v1 * v2, v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
        tenv.assertEq(v1 * v2, v2 * v1);

        tenv.assertNeq(v1 * v2, 0);
    }

    {
        tenv.beginTest("Dot product - same types 3");

        vec<3, double> v1(0.1, -0.2, 0.3);
        vec<3, double> v2(137.5, 3.14, 192);

        tenv.assertEq(v1 * v2, v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
        tenv.assertEq(v1 * v2, v2 * v1);

        tenv.assertNeq(v1 * v2, 0);
    }

    {
        tenv.beginTest("Dot product - different types 1");

        vec<2, float> v1(1.5, -2.5);
        vec<2, double> v2(3.5, 4.5);

        auto result = v1 * v2;

        tenv.assert(std::is_same<decltype(result), double>::value);
        tenv.assertEq(result, v1[0] * v2[0] + v1[1] * v2[1]);
        tenv.assertEq(v1 * v2, v2 * v1);
    }

    {
        tenv.beginTest("Dot product - different types 2");

        vec<2, float> v1(3.14, 137);
        vec<2, int> v2(2, 3);

        auto result = v1 * v2;

        tenv.assert(std::is_same<decltype(result), float>::value);
        tenv.assertEq(result, v1[0] * v2[0] + v1[1] * v2[1]);
        tenv.assertEq(v1 * v2, v2 * v1);
    }
}

void SuiteVecScalarDivision(TestEnvironment& tenv)
{
    tenv.beginSuite("Vector scalar division");

    {
        tenv.beginTest("Vector-scalar division - same types");

        vec<3, float> v(1.5, -2, 3.5);
        float x = 2;

        tenv.assertEq(v / x, vec<3, float> (v[0] / x, v[1] / x, v[2] / x));
        // test anti-commutativity
        tenv.assertEq(x / v, 1/(v / x));

        auto v_old = v;

        v /= x;

        tenv.assertEq(v, v_old / x);
    }

    {
        tenv.beginTest("Vector-scalar multiplication - different types 1");

        vec<2, double> v(-3.5, 137);
        float x = 256;

        auto result = v / x;

        tenv.assert(std::is_same<decltype(result), vec<2, double>>::value);

        tenv.assertEq((vec<2, float>) result, vec<2, float>(v[0] / x, v[1] / x));

        // test commutativity
        tenv.assertEq((vec<2, float>)(v / x), (vec<2, float>)(1/(x / v)));

        auto v_old = v;

        v /= x;

        tenv.assertEq((vec<2, float>)v, (vec<2, float>) (v_old / x));
    }

    {
        tenv.beginTest("Vector-scalar multiplication - different types 2");

        vec<2, float> v(-3.5, 137);
        double x = 256;

        auto result = v / x;

        tenv.assert(std::is_same<decltype(result), vec<2, double>>::value);

        tenv.assertEq((vec<2, float>) result, vec<2, float>(v[0] / x, v[1] / x));

        // test commutativity
        tenv.assertEq((vec<2, float>)(v / x), (vec<2, float>)(1/(x / v)));

        auto v_old = v;

        v /= x;

        tenv.assertEq((vec<2, float>)v, (vec<2, float>) (v_old / x));
    }
}

void SuiteVecMagnitude(TestEnvironment& tenv)
{
    tenv.beginSuite("Vector magnitude");

    {
        tenv.beginTest("Vector magnitude test 1");

        vec<3, float> v(1.5, -2, 3.75);

        tenv.assertEq(mag(v), sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]));
    }
}

int main()
{
    TestEnvironment tenv;

    SuiteVecElemAccessConstruction(tenv);
    SuiteVecSize(tenv);
    SuiteVecElementMutability(tenv);
    SuiteVecComparison(tenv);
    SuiteVecScalarConstruction(tenv);
    SuiteVecScalarComparison(tenv);
    SuiteVecListInitialization(tenv);
    SuiteVecCopyConstruction(tenv);
    SuiteVecCopyConstructionDifferentTypes(tenv);
    SuiteVecCopyAssignment(tenv);
    SuiteVecScalarAssignment(tenv);
    SuiteVecAddition(tenv);
    SuiteVecScalarAddition(tenv);
    SuiteVecNegation(tenv);
    SuiteVecSubtraction(tenv);
    SuiteVecScalarSubtraction(tenv);
    SuiteVecScalarMultiplication(tenv);
    SuiteVecDotProduct(tenv);
    SuiteVecScalarDivision(tenv);
    SuiteVecMagnitude(tenv);

    std::cout << tenv.getSummary();

    return 0;
}