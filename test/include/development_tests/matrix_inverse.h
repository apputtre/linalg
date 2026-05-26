#include "yUnit.h"

#include "mat.h"
#include "algorithms.h"

SUITE("Matrix inverse")
{
    TEST("Inverse of identity matrix")
    {
        linalg::mat<2, 2, float> m {
            {1, 0},
            {0, 1}
        };

        assertEq(linalg::inv(m), linalg::mat<2, 2, float> {
            {1, 0},
            {0, 1}
        });
    }

    TEST("Inverse of non-identity matrix")
    {
        linalg::mat<2, 2, float> m {
            {1, 2},
            {3, 4}
        };

        assertEq(linalg::inv(m), linalg::mat<2, 2, float> {
            {-2, 1},
            {1.5, -0.5}
        });
    }
}