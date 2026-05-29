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

        linalg::mat<3, 3, float> L;
        linalg::mat<3, 3, float> U;
        linalg::luf(m, L, U);

        assertEq(L, linalg::mat<3, 3, float> {
            {1, 0, 0},
            {2, 1, 0},
            {3, 4, 1}
        });

        assertEq(U, linalg::mat<3, 3, float> {
            {1, 1, 0},
            {0, -1, -1},
            {0, 0, 0}
        });
    }
}
