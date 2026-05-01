#include "yUnit.h"

#include "mat.h"

using namespace linalg;

SUITE(matConstruction,
    {
        TEST(vecConstruction,
        {
            vec<2, float> v1, v2;

            v1 = {11, 12};
            v2 = {21, 22};

            mat<2, 2, float> m1(v1, v2);

            assertEq(m1[0][0], 11);
            assertEq(m1[0][1], 12);
            assertEq(m1[1][0], 21);
            assertEq(m1[1][1], 22);
        })

        TEST(listConstruction,
        {
            mat<4, 4, int> m2({
                {1, 2, 3, 4},
                {5, 6, 7, 8},
                {9, 10, 11, 12},
                {13, 14, 15, 16}
            });

            assertEq(m2[0][3], 4);
            assertEq(m2[3][1], 14);
            assertEq(m2[1][3], 8);
        })

        TEST(defaultConstruction,
        {
            mat<3, 3, float> m1;

            for (int r = 0; r < m1.num_rows; ++r)
                for (int c = 0; c < m1.num_cols; ++c)
                    assertEq(m1[r][c], 0);
                
            mat<2, 2, std::string> m2;

            for (int r = 0; r < m2.num_rows; ++r)
                for (int c = 0; c < m2.num_cols; ++c)
                    assertEq(m2[r][c], std::string{});

        })
    }
)