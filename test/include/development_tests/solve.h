#include <iomanip>

#include "cppUnit.h"

#include "mat.h"
#include "algorithms.h"

int diffUlps(float f1, float f2)
{
    float x, y;
    if (f1 >= f2)
    {
        x = f1;
        y = f2;
    }
    else
    {
        x = f2;
        y = f1;
    }

    return std::bit_cast<unsigned long>(x) - std::bit_cast<unsigned long>(y);

}

SUITE("Solve")
{
    TEST("Test 1")
    {
        linalg::mat<2, 2, float> a {
            {2, 1},
            {-1, 2}
        };

        linalg::vec<2, float> b {3, 1};
        linalg::vec<2, float> x;

        linalg::solve(a, b, x);

        assertEq(x, linalg::vec<2, float> {1, 1});
    }

    TEST("Test 2")
    {
        linalg::mat<3, 3, float> a {
            {2, 3, -1},
            {4, 0, 8},
            {-3, 2, 6}
        };

        linalg::vec<3, float> b {5, 28, 19};
        linalg::vec<3, float> x;

        linalg::solve(a, b, x);

        assertLtEq(diffUlps(x.x, 1), 5);
        assertLtEq(diffUlps(x.y, 2), 5);
        assertLtEq(diffUlps(x.z, 3), 5);
    }
}