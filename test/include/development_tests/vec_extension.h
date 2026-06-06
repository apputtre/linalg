#include "cppUnit.h"

#include "vec.h"

SUITE("Vec extension")
{
    TEST("Test 1")
    {
        linalg::vec<3, float> v1 {1, 2, 3};
        linalg::vec<4, float> v2(v1, 4);

        assertEq(v2, linalg::vec<4, float> {1, 2, 3, 4});
    }
}