/*
Each suite in this file corresponds to a particular requirement listed in the file matrix_requirements.txt.

Each requirement in that file has a suite containing at least one test here.
*/

#include "yUnit.h"

#include "mat.h"

SUITE("Matrix list construction") // [C.1], [DA.1]
{
    TEST("Test 1")
    {
        linalg::mat<2, 2, float> m {
            {11, 12},
            {21, 22}
        };

        assertEq(m[0][0], 11);
        assertEq(m[0][1], 12);
        assertEq(m[1][0], 21);
        assertEq(m[1][1], 22);
    }
}

SUITE("Matrix construction from matrix") // [C.2], [DA.1]
{
    TEST("Test 1")
    {
        linalg::mat<3, 2, double> m1 {
            {11, 12},
            {21, 22},
            {31, 32}
        };

        linalg::mat<3, 2, float> m2(m1);


        assertEq(m2[0][0], 11);
        assertEq(m2[0][1], 12);
        assertEq(m2[1][0], 21);
        assertEq(m2[1][1], 22);
        assertEq(m2[2][0], 31);
        assertEq(m2[2][1], 32);
    }
}

SUITE("Matrix construction from scalar") // [C.3], [DA.1]
{
    TEST("Test 1")
    {
        linalg::mat<3, 3, float> m(1);

        assertEq(m[0][0], 1);
        assertEq(m[1][1], 1);
        assertEq(m[2][2], 1);
    }
}

SUITE("Row and column access") // [DA.2]
{
    TEST("Test 1") // [DA.2.1]
    {
        linalg::mat<2, 2, int> m {
            {11, 12},
            {21, 22}
        };

        auto row_1 = m.row(0);
        auto row_2 = m.row(1);

        assertEq(row_1[0], 11);
        assertEq(row_1[1], 12);
        assertEq(row_2[0], 21);
        assertEq(row_2[1], 22);

        auto col_1 = m.col(0);
        auto col_2 = m.col(1);

        assertEq(col_1[0], 11);
        assertEq(col_1[1], 21);
        assertEq(col_2[0], 12);
        assertEq(col_2[1], 22);
    }

    TEST("Test 2") // [DA.2.3]
    {
        linalg::mat<2, 2, float> m{
            {11, 12},
            {21, 22}
        };

        m[0][0] = -1;
        m[1][1] = -2;

        assertEq(m[0][0], -1);
        assertEq(m[1][1], -2);
    }
}

SUITE("Matrix assignment") // [DA.3]
{
    TEST("Test 1")
    {
        linalg::mat<2, 2, float> m1(0);
        linalg::mat<2, 2, double> m2{
            {1, 3},
            {5, 7}
        };

        m1 = m2;

        assertEq(m1[0][0], 1);
        assertEq(m1[0][1], 3);
        assertEq(m1[1][0], 5);
        assertEq(m1[1][1], 7);
    }
}

SUITE("Matrix scalar assignment") // [DA.4]
{
    TEST("Test 1")
    {
        linalg::mat<2, 2, double> m {
            {11, 12},
            {21, 22}
        };

        m = -1;

        assertEq(m[0][0], -1);
        assertEq(m[0][1], -1);
        assertEq(m[0][0], -1);
        assertEq(m[1][1], -1);
    }
}