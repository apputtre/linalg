#include "yUnit.h"

#include "mat.h"

SUITE("Matrix inverse")
{
    TEST("Inverse of identity matrix")
    {
        linalg::mat<2, 2, float> m {
            {1, 0},
            {0, 1}
        };

        assertEq(m.inv(), linalg::mat<2, 2, float> {
            {1, 0},
            {0, 1}
        });
    }
}