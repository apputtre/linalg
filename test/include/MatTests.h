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

            mat<2, 2, float> m(v1, v2);

            assertEq(m[0][0], 11);
            assertEq(m[0][1], 12);
            assertEq(m[1][0], 21);
            assertEq(m[1][1], 22);
        })
    }
)