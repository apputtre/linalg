#include "yUnit.h"

#include "algorithms.h"
#include "mat.h"

SUITE("Augmented matrix")
{
    TEST("Test 1")
    {
        linalg::mat<2, 2, int> m {
            {1, 2},
            {3, 4}
        };

        assertEq(linalg::aug(m), linalg::mat<2, 4, int> {
            {1, 2, 1, 0},
            {3, 4, 0, 1}
        });
    }
}