#include "yUnit.h"

#include "mat.h"

using namespace linalg;

template<size_t Rows, size_t Cols, typename T>
bool verifyMatDims(const mat<Rows, Cols, T>& m)
{
    return(
        m.num_rows == Rows &&
        m.num_cols == Cols &&
        m.num_elements == Rows * Cols
    );
}

SUITE(matConstruction,
    {
        TEST(vecConstruction,
        {
            vec<2, float> v1, v2;

            v1 = {11, 12};
            v2 = {21, 22};

            mat<2, 2, float> m1(v1, v2);

            assert(verifyMatDims(m1));

            assertEq(m1[0][0], 11);
            assertEq(m1[0][1], 12);
            assertEq(m1[1][0], 21);
            assertEq(m1[1][1], 22);

            assertEq(m1.num_cols, (size_t) 2);
        })

        TEST(listConstruction,
        {
            mat<4, 4, int> m({
                {1, 2, 3, 4},
                {5, 6, 7, 8},
                {9, 10, 11, 12},
                {13, 14, 15, 16}
            });

            assert(verifyMatDims(m));

            assertEq(m[0][3], 4);
            assertEq(m[3][1], 14);
            assertEq(m[1][3], 8);
        })

        TEST(defaultConstruction,
        {
            mat<3, 3, float> m1;

            assert(verifyMatDims(m1));

            for (size_t r = 0; r < m1.num_rows; ++r)
                for (size_t c = 0; c < m1.num_cols; ++c)
                    assertEq(m1[r][c], 0);

            mat<2, 2, std::string> m2;

            assert(verifyMatDims(m2));

            for (size_t r = 0; r < m2.num_rows; ++r)
                for (size_t c = 0; c < m2.num_cols; ++c)
                    assertEq(m2[r][c], std::string{});
        })

        TEST(copyConstruction,
        {
            mat<2, 2, float> m1({
                {11.5f, 12.5f},
                {21.5f, 22.5f}
            });

            //assertEq(m1.num_cols, (size_t) 2);

            //mat<2, 2, double> m2(m1);

            /*
            assertEq(m1.num_rows, m2.num_rows);
            assertEq(m1.num_cols, m2.num_cols);
            */

            /*
            for (int r = 0; r < m1.num_rows; ++r)
                for (int c = 0; c < m1.num_cols; ++c)
                    assertEq(m1[r][c], m2[r][c]);
                    */
        })
    }
)