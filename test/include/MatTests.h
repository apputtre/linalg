#include "yUnit.h"

#include "mat.h"

using namespace linalg;

SUITE(matConstruction,
    {
        TEST(listConstruction,
        {
            mat<2, 2> m
            {
                {1, 2},
                {3, 4}
            };

            assertEq(m[0][0], 1);
            assertEq(m[0][1], 2);
            assertEq(m[1][0], 3);
            assertEq(m[1][1], 4);
        })
    }
)