#include "cppUnit.h"

#include "algorithms.h"

SUITE("Gauss-Jordan Elimination")
{
    TEST("Test 1")
    {
        // example taken from en.wikipedia.org/wiki/Gaussian_elimination
        linalg::mat<3, 4, float> m {
            {1, 3, 1, 9},
            {1, 1, -1, 1},
            {3, 11, 5, 35}
        };

        assertEq(linalg::gje(m), linalg::mat<3, 4, float> {
            {1, 3, 1, 9},
            {0, -2, -2, -8},
            {0, 0, 0, 0}
        });
    }

    TEST("Test 2")
    {
        linalg::mat<3, 3, float> m = {
            {1, 0, 0},
            {3, 0, -1},
            {2, 1, -1}
        };

        assertEq(linalg::gje(m), linalg::mat<3, 3, float> {
            {1, 0, 0},
            {0, 1, -1},
            {0, 0, -1}
        });
    }
}