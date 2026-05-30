#include "cppUnit.h"

#include "mat.h"

SUITE("LU Factorization")
{
    TEST("Test 1")
    {
        linalg::mat<3, 3, float> m = {
            {1, 1, 0},
            {2, 1, -1},
            {3, -1, -1}
        };

        linalg::mat<3, 3, float> P;
        linalg::mat<3, 3, float> L;
        linalg::mat<3, 3, float> U;
        linalg::plu_factor(m, P, L, U);

        assertEq(P, linalg::mat<3, 3, float>(1), "P is not correct");

        assertEq(L, linalg::mat<3, 3, float> {
            {1, 0, 0},
            {2, 1, 0},
            {3, 4, 1}
        }, "L is not correct");

        assertEq(U, linalg::mat<3, 3, float> {
            {1, 1, 0},
            {0, -1, -1},
            {0, 0, 3}
        }, "U is not correct");
    }

    TEST("Test 2")
    {
        linalg::mat<3, 3, float> m = {
            {1, 0, 0},
            {3, 0, -1},
            {2, 1, -1}
        };

        linalg::mat<3, 3, float> P;
        linalg::mat<3, 3, float> L;
        linalg::mat<3, 3, float> U;
        linalg::plu_factor(m, P, L, U);

        assertEq(P, linalg::mat<3, 3, float> {
            {1, 0, 0},
            {0, 0, 1},
            {0, 1, 0}
        }, "P is not correct");

        assertEq(L, linalg::mat<3, 3, float> {
            {1, 0, 0},
            {3, 1, 0},
            {2, 0, 1}
        }, "L is not correct");

        assertEq(U, linalg::mat<3, 3, float> {
            {1, 0, 0},
            {0, 1, -1},
            {0, 0, -1}
        }, "U is not correct");
    }
}
