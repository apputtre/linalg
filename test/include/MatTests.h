#include "yUnit.h"

#include "mat.h"
#include "utils.h"

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

            assert(verifyMatDims(m1));

            mat<2, 2, float> m2(m1);

            assert(verifyMatDims(m2));

            for (size_t r = 0; r < m1.num_rows; ++r)
                for (size_t c = 0; c < m1.num_cols; ++c)
                    assertEq(m1[r][c], m2[r][c]);
            
            // verify copy independence
            m1[0][0] = 137;
            assertNeq(m2[0][0], 137);

            mat<3, 3, float> m3 {
                {11.1, 12.2, 13.3},
                {21.4, 22.5, 23.6},
                {31.7, 32.8, 33.9},
            };

            assert(verifyMatDims(m3));

            mat<3, 3, int> m4(m3);

            assert(verifyMatDims(m4));

            for (size_t r = 0; r < m4.num_rows; ++r)
                for (size_t c = 0; c < m4.num_cols; ++c)
                    assertEq(m4[r][c], (int) m3[r][c]);
        })

        TEST(moveConstruction,
        {
            mat<3, 3, double> m1
            {
                {1, 3, 5},
                {-7, -9, -11},
                {13, 17, 19}
            };

            mat<3, 3, double> m2(std::move(m1));

            assertEq(m2[1][0], -7);
            assertEq(m2[2][1], 17);
        })

        TEST(copyAssignment,
        {
            mat<2, 2, float> m1 {
                {11.1, 12.2},
                {21.3, 22.4}
            };

            mat<2, 2, float> m2 = m1;

            assert(floatCompare(m2[0][0], 11.1));
            assert(floatCompare(m2[1][0], 21.3));
            assert(floatCompare(m2[0][1], 12.2));

            // verify copy independence
            m1[1][1] = 137;
            assertNeq(m2[1][1], 137);
        })

        TEST(moveAssignment,
        {
            mat<2, 2, char> m1
            {
                {'a', 'b'},
                {'c', 'd'}
            };

            mat<2, 2, char> m2 = std::move(m1);

            assertEq(m2[1][0], 'c');
            assertEq(m2[1][1], 'd');
        })

        TEST(scalarConstructor,
        {
            mat<2, 2, int> m(137);

            bool expected = true;

            for (size_t r = 0; r < m.num_rows; ++r)
                for (size_t c = 0; c < m.num_rows; ++c)
                    if (m[r][c] != 137)
                        expected = false;

            assert(expected);
        })

        TEST(elementAssignment,
        {
            mat<3, 3, float> m1;
            m1[1][2] = 15;
            assertEq(m1[1][2], 15);

            mat<2, 2, std::string> m2;
            m2[1][0] = "hello world";
            assertEq(m2[1][0], std::string("hello world"));

            mat<4, 3, int> m3;
            m3[2][1] = 137.5;
            assertEq(m3[2][1], 137);
        })
    }
)