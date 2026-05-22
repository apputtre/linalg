/*
Each suite in this file corresponds to a particular requirement listed in the file vector_requirements.txt.

Each requirement in that file has a suite containing at least one test here.
*/

#include "yUnit.h"
#include "vec.h"

SUITE("Vector construction from list") // [C.1]
{
    TEST("Test 1")
    {
        linalg::vec<3, float> v(1, 3, 7);

        assertEq(v[0], 1);
        assertEq(v[1], 3);
        assertEq(v[2], 7);
    }

    TEST("Test 2")
    {
        linalg::vec<2, double> v(1.0f, 2.5f);

        assertEq(v[0], 1.0);
        assertEq(v[1], 2.5);
    }
}

SUITE("Vector construction from vector") // [C.2]
{
    FIXTURE()
    {
        linalg::vec<3, float> v1(1.0f, 2.5f, -3);
        linalg::vec<2, int> v2(3, 5);

        FTEST("Test 1")
        {
            linalg::vec<3, int> w(v1);

            assertEq(w[0], 1);
            assertEq(w[1], 2);
            assertEq(w[2], -3);
        }

        FTEST("Test 2")
        {
            linalg::vec<2, double> w(v2);

            assertEq(w[0], 3);
            assertEq(w[1], 5);
        }
    }
}

SUITE("Vector construction from scalar") // [C.3]
{
    TEST("Test 1")
    {
        linalg::vec<3, int> v(2.5);

        assertEq(v[0], 2);
        assertEq(v[1], 2);
        assertEq(v[2], 2);
    }
}

SUITE("Vector element access") // [DA.1]
{
    TEST("Test 1")
    {
        linalg::vec<3, float> v(1, 2, 3);

        assertEq(v[1], 2);

        v[1] = -1;

        assertEq(v[1], -1);
    }
}

SUITE("Vector assignment") // [DA.2]
{
    TEST("Test 1")
    {
        linalg::vec<3, float> v1(1.0f, 2.5f, 3.0f);
        linalg::vec<3, int> v2(0);

        v2 = v1;

        assertEq(v2[0], 1);
        assertEq(v2[1], 2);
        assertEq(v2[2], 3);
    }
}

SUITE("Vector scalar assignment") // [DA.3}]
{
    TEST("Test 1")
    {
        linalg::vec<3, float> v(0);

        v = 1;

        assertEq(v[0], 1);
        assertEq(v[1], 1);
        assertEq(v[2], 1);
    }
}

SUITE("Size of a vector") // [DL.1]
{
    TEST("Test 1")
    {
        linalg::vec<3, float> v1;

        assertEq(sizeof(float) * 3, sizeof(v1));
    }

    TEST("Test 2")
    {
        linalg::vec<2, char> v1;

        assertEq(sizeof(char) * 2, sizeof(v1));
    }
}

SUITE("Vector data layout") // [DL.2]
{
    TEST("Test 1")
    {
        linalg::vec<3, int> v(1, 2, 3);

        assertEq(v[0], *(&v[0] + 0));
        assertEq(v[1], *(&v[0] + 1));
        assertEq(v[2], *(&v[0] + 2));
    }
}

SUITE("Vector comparison") // [CMP.1]
{
    TEST("Test 1")
    {
        linalg::vec<3, float> v1(1.0f, 2.5f, 3.0f);
        linalg::vec<3, float> v2(1.0f, 2.5f, 3.0f);

        assertEq(v1, v2);
        assertEq(v2, v1);
    }

    TEST("Test 2")
    {
        linalg::vec<2, int> v1(3, 4);
        linalg::vec<2, int> v2(1, 7);

        assertNeq(v1, v2);
        assertNeq(v2, v1);
    }

    TEST("Test 3")
    {
        linalg::vec<2, float> v1(1.0f, 2.0f);
        linalg::vec<2, double> v2(1.0, 2.0);

        assertEq(v1, v2);
        assertEq(v2, v1);
    }
}

SUITE("Vector scalar comparison") // [CMP.2]
{
    TEST("Test 1")
    {
        linalg::vec<3, float> v(2.5, 2.5, 2.5);

        assertEq(v, 2.5);
    }
}

SUITE("Vector addition") // [A.1]
{
    FIXTURE()
    {
        linalg::vec<3, float> v1;
        linalg::vec<3, double> v2;

        SETUP()
        {
            v1 = linalg::vec<3, float>(1, 2, 3);
            v2 = linalg::vec<3, double>(0.5);
        }

        FTEST("Test 1")
        {
            auto v3 = v1 + v2;

            assert(std::is_same<decltype(v3), linalg::vec<3, double>>::value);
            assertEq(v3, linalg::vec<3, double>(1.5, 2.5, 3.5));
            assertEq(v3, v2 + v1);
        }

        FTEST("Test 2")
        {
            v1 += v2;

            assertEq(v1, linalg::vec<3, double>(1.5, 2.5, 3.5));
        }

        FTEST("Test 3")
        {
            v2 += v1;

            assertEq(v2, linalg::vec<3, double>(1.5, 2.5, 3.5));
        }
    }
}

SUITE("Vector scalar addition") // [A.2]
{
    FIXTURE()
    {
        linalg::vec<3, float> v;
        int x;
        
        SETUP()
        {
            v = linalg::vec<3, float>(1, 2.5, 3);
            x = 1;
        }

        FTEST("Test 1")
        {
            auto v2 = v + x;

            assert(std::is_same<decltype(v2), linalg::vec<3, float>>::value);
            assertEq(v2, linalg::vec<3, float>(2, 3.5, 4));
            assertEq(v2, x + v);
        }

        FTEST("Test 2")
        {
            v += x;

            assertEq(v, linalg::vec<3, float>(2, 3.5, 4));
        }
    }
}

SUITE("Vector subtraction") // [A.3]
{
    FIXTURE()
    {
        linalg::vec<3, float> v1;
        linalg::vec<3, double> v2;

        SETUP()
        {
            v1 = linalg::vec<3, float>(1, 2, 3);
            v2 = linalg::vec<3, double>(0.5);
        }

        FTEST("Test 1")
        {
            auto v3 = v1 - v2;

            assert(std::is_same<decltype(v3), linalg::vec<3, double>>::value);
            assertEq(v3, linalg::vec<3, double>(0.5, 1.5, 2.5));
            assertEq(v3, -(v2 - v1));
        }

        FTEST("Test 2")
        {
            v1 -= v2;

            assertEq(v1, linalg::vec<3, double>(0.5, 1.5, 2.5));
        }

        FTEST("Test 3")
        {
            v2 -= v1;

            assertEq(v2, linalg::vec<3, double>(-0.5, -1.5, -2.5));
        }
    }
}

SUITE("Vector scalar subtraction") // [A.4]
{
    FIXTURE()
    {
        linalg::vec<3, float> v;
        int x;

        SETUP()
        {
            v = linalg::vec<3, float>(1, 2.5, 3);
            x = 1;
        }

        FTEST("Test 1")
        {
            auto v2 = v - x;

            assert(std::is_same<decltype(v2), linalg::vec<3, float>>::value);
            assertEq(v2, linalg::vec<3, float>(0, 1.5, 2));
            assertEq(v2, -(x - v));
        }

        FTEST("Test 2")
        {
            v -= x;

            assertEq(v, linalg::vec<3, float>(0, 1.5, 2));
        }
    }
}

SUITE("Vector scalar multiplication") // [A.5]
{
    FIXTURE()
    {
        linalg::vec<3, float> v;
        int x;

        SETUP()
        {
            v = linalg::vec<3, float>(1, 2.5, 3);
            x = 2;
        }

        FTEST("Test 1")
        {
            auto v2 = v * x;

            assert(std::is_same<decltype(v2), linalg::vec<3, float>>::value);
            assertEq(v2, linalg::vec<3, float>(2, 5, 6));
            assertEq(v2, x * v);
        }

        FTEST("Test 2")
        {
            v *= x;

            assertEq(v, linalg::vec<3, float>(2, 5, 6));
        }
    }
}

SUITE("Vector scalar division") // [A.6]
{
    FIXTURE()
    {
        linalg::vec<3, float> v;
        int x;

        SETUP()
        {
            v = linalg::vec<3, float>(1, 2.5, 3);
            x = 2;
        }

        FTEST("Test 1")
        {
            auto v2 = v / x;

            assert(std::is_same<decltype(v2), linalg::vec<3, float>>::value);
            assertEq(v2, linalg::vec<3, float>(0.5, 1.25, 1.5));
            assertEq(v2, 1/(x / v));
        }

        FTEST("Test 2")
        {
            v /= x;

            assertEq(v, linalg::vec<3, float>(0.5, 1.25, 1.5));
        }
    }
}

SUITE("Vector mag") // [S.1]
{
    TEST("Test 1")
    {
        linalg::vec<2, float> v(1, 1);

        auto m = v.mag();

        assert(std::is_same<decltype(m), decltype(std::sqrt(float {}))>::value);
        assertEq(v.mag(), std::sqrt(2.0f));
    }

    TEST("Test 2")
    {
        linalg::vec<3, double> v(1, 2, 3);

        auto m = v.mag();

        assert(std::is_same<decltype(m), decltype(std::sqrt(double {}))>::value);
        assertEq(v.mag(), std::sqrt((double) 14));
    }
}

SUITE("Vector norm") // [S.2]
{
    TEST("Test 1")
    {
        linalg::vec<2, float> v(1, 1);

        auto n = v.norm();

        assert(std::is_same<decltype(n), linalg::vec<2, decltype(float{} / v.mag())>>::value);
        assertEq(v.norm(), linalg::vec<2, float>(1 / std::sqrt(2.0), 1 / std::sqrt(2.0)));
    }

    TEST("Test 2")
    {
        linalg::vec<3, double> v(0);

        auto n = v.norm();

        assertEq(n, linalg::vec<3, double>(0));
    }
}

SUITE("Vector dot product")
{
    TEST("Test 1")
    {
        linalg::vec<3, float> v1(1, 2.5, 3);
        linalg::vec<3, double> v2(4, 5, 6);

        auto n = v1.dot(v2);

        assert(std::is_same<decltype(n), double>::value);
        assertEq(n, 34.5);
    }
}

SUITE("Vector cross product")
{
    TEST("Test 1")
    {
        linalg::vec<3, float> v1(1, 0, 0);
        linalg::vec<3, double> v2(0, 1, 0);

        auto n = v1.cross(v2);

        assert(std::is_same<decltype(n), linalg::vec<3, double>>::value);
        assertEq(n, linalg::vec<3, double>(0, 0, 1));
    }
}