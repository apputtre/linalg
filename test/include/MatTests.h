#include "yUnit.h"

#include "mat.h"

using namespace linalg;

SUITE(matConstruction,
    {
        TEST(listConstruction,
        {
            vec<2, float> v1, v2;

            v1 = {11, 12};
            v2 = {21, 22};

            mat<2, 2, float> m1(v1, v2);

            assertEq(m1[0][0], 11);
            assertEq(m1[0][1], 12);
            assertEq(m1[1][0], 21);
            assertEq(m1[1][1], 22);

            /*
            mat<4, 4, int> m2(
                {1, 2, 3, 4},
                {5, 6, 7, 8},
                {9, 10, 11, 12},
                {13, 14, 15, 16}
            );

            assertEq(m2[0][3], 4);
            assertEq(m2[3][1], 14);
            assertEq(m2[1][3], 8);
            */
        })
    }
)