#include "cppUnit.h"

#include "mat.h"
#include "algorithms.h"

SUITE("Solve")
{
    TEST("Test 1")
    {
        // 2x +  y = 3
        // -x + 2y = 1

        linalg::mat<2, 2, float> a {
            {2, 1},
            {-1, 2}
        };

        linalg::vec<2, float> b {3, 1};
        linalg::vec<2, float> x;

        assert(linalg::solve(a, b, x));

        assertEq(x, linalg::vec<2, float> {5, 3});
    }
}