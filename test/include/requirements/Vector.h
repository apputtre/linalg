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