/*
Each suite in this file corresponds to a particular requirement listed in the file matrix_requirements.txt.

Each requirement in that file has a suite containing at least one test here.
*/

#include "cppUnit.h"

#include "mat.h"

SUITE("Matrix list construction") // [C.1], [DA.1]
{
    TEST("Test 1")
    {
        linalg::mat<2, 2, float> m {
            {11, 12},
            {21, 22}
        };

        assertEq(m[0][0], 11);
        assertEq(m[0][1], 12);
        assertEq(m[1][0], 21);
        assertEq(m[1][1], 22);
    }
}

SUITE("Matrix construction from matrix") // [C.2], [DA.1]
{
    TEST("Test 1")
    {
        linalg::mat<3, 2, double> m1 {
            {11, 12},
            {21, 22},
            {31, 32}
        };

        linalg::mat<3, 2, float> m2(m1);


        assertEq(m2[0][0], 11);
        assertEq(m2[0][1], 12);
        assertEq(m2[1][0], 21);
        assertEq(m2[1][1], 22);
        assertEq(m2[2][0], 31);
        assertEq(m2[2][1], 32);
    }
}

SUITE("Matrix construction from scalar") // [C.3], [DA.1]
{
    TEST("Test 1")
    {
        linalg::mat<3, 3, float> m(1);

        assertEq(m[0][0], 1);
        assertEq(m[1][1], 1);
        assertEq(m[2][2], 1);
    }
}

SUITE("Row and column access") // [DA.2]
{
    TEST("Test 1") // [DA.2.1]
    {
        linalg::mat<2, 2, int> m {
            {11, 12},
            {21, 22}
        };

        auto row_1 = m.row(0);
        auto row_2 = m.row(1);

        assertEq(row_1[0], 11);
        assertEq(row_1[1], 12);
        assertEq(row_2[0], 21);
        assertEq(row_2[1], 22);

        auto col_1 = m.col(0);
        auto col_2 = m.col(1);

        assertEq(col_1[0], 11);
        assertEq(col_1[1], 21);
        assertEq(col_2[0], 12);
        assertEq(col_2[1], 22);

        row_1 = -1;

        assertEq(m[0][0], -1);
        assertEq(m[0][1], -1);
    }

    TEST("Test 2") // [DA.2.2]
    {
        linalg::mat<2, 2, int> m {
            {11, 12},
            {21, 22}
        };

        m[0] += m[1];

        assertEq(m[0][0], 32);
        assertEq(m[0][1], 34);

        auto v = m[1] + linalg::vec<2, int>(5, 10); 

        assertEq(v[0], 26);
        assertEq(v[1], 32);
    }
}

SUITE("Matrix assignment") // [DA.3]
{
    TEST("Test 1")
    {
        linalg::mat<2, 2, float> m1(0);
        linalg::mat<2, 2, double> m2{
            {1, 3},
            {5, 7}
        };

        m1 = m2;

        assertEq(m1[0][0], 1);
        assertEq(m1[0][1], 3);
        assertEq(m1[1][0], 5);
        assertEq(m1[1][1], 7);
    }
}

SUITE("Matrix scalar assignment") // [DA.4]
{
    TEST("Test 1")
    {
        linalg::mat<2, 2, double> m {
            {11, 12},
            {21, 22}
        };

        m = -1;

        assertEq(m[0][0], -1);
        assertEq(m[0][1], -1);
        assertEq(m[0][0], -1);
        assertEq(m[1][1], -1);
    }
}

SUITE("Size of a matrix") // [DL.1]
{
    TEST("Test 1")
    {
        linalg::mat<2, 2, float> m {
            {11, 12},
            {21, 22}
        };

        assertEq(sizeof(m), sizeof(float) * 2 * 2);
    }
}

SUITE("Matrix data layout") // [DL.2]
{
    TEST("Test 1")
    {
        linalg::mat<3, 2, char> m {
            {'a', 'b'},
            {'c', 'd'},
            {'e', 'f'}
        };

        assertEq((*(char*) &m + 0), 'a');
        assertEq((*(char*) &m + 1), 'b');
        assertEq((*(char*) &m + 2), 'c');
        assertEq((*(char*) &m + 3), 'd');
        assertEq((*(char*) &m + 4), 'e');
        assertEq((*(char*) &m + 5), 'f');
    }
}

SUITE("Matrix comparison") // [CMP.1]
{
    TEST("Test 1")
    {
        linalg::mat<2, 2, int> m1 {
            {11, 12},
            {21, 22}
        };
        linalg::mat<2, 2, float> m2 {
            {11, 12},
            {21, 22}
        };

        assertEq(m1, m2);
    }

    TEST("Test 2")
    {
        linalg::mat<2, 2, int> m1 {
            {11, 12},
            {21, 22}
        };
        linalg::mat<2, 2, float> m2 {
            {11.5, 12},
            {21, 22}
        };

        assertNeq(m1, m2);
    }
}

SUITE("Matrix addition") // [A.1]
{
    FIXTURE()
    {
        linalg::mat<2, 2, float> m1;
        linalg::mat<2, 2, int> m2;

        SETUP()
        {
            m1 = {
                {1, 2},
                {3, 4}
            };

            m2 = {
                {2, 4},
                {6, 8}
            };
        }

        FTEST("Test 1")
        {
            auto m3 = m1 + m2;

            assert(std::is_same<decltype(m3), linalg::mat<2, 2, float>>::value);

            assertEq(m3, linalg::mat<2, 2, float>
            {
                {3, 6},
                {9, 12}
            });
        }

        FTEST("Test 2")
        {
            m1 += m2;

            assertEq(m1, linalg::mat<2, 2, float>
            {
                {3, 6},
                {9, 12}
            });
        }
    }
}

SUITE("Matrix scalar addition") // [A.2]
{
    FIXTURE()
    {
        linalg::mat<2, 2, float> m1;
        int x;

        SETUP()
        {
            m1 = {
                {1.5, 2},
                {3, 4.5}
            };

            x = 1;
        }

        FTEST("Test 1")
        {
            auto m2 = m1 + x;

            assert(std::is_same<decltype(m2), linalg::mat<2, 2, float>>::value);

            assertEq(m2, linalg::mat<2, 2, float>
            {
                {2.5, 3},
                {4, 5.5}
            });
        }

        FTEST("Test 2")
        {
            m1 += x;

            assertEq(m1, linalg::mat<2, 2, float>
            {
                {2.5, 3},
                {4, 5.5}
            });
        }
    }
}

SUITE("Matrix subtraction") // [A.3]
{
    FIXTURE()
    {
        linalg::mat<2, 2, float> m1;
        linalg::mat<2, 2, int> m2;

        SETUP()
        {
            m1 = {
                {1, 2},
                {3, 4}
            };

            m2 = {
                {2, 4},
                {6, 8}
            };
        }

        FTEST("Test 1")
        {
            auto m3 = m1 - m2;

            assert(std::is_same<decltype(m3), linalg::mat<2, 2, float>>::value);

            assertEq(m3, linalg::mat<2, 2, float>
            {
                {-1, -2},
                {-3, -4}
            });
        }

        FTEST("Test 2")
        {
            m1 -= m2;

            assertEq(m1, linalg::mat<2, 2, float>
            {
                {-1, -2},
                {-3, -4}
            });
        }
    }
}

SUITE("Matrix scalar subtraction") // [A.4]
{
    FIXTURE()
    {
        linalg::mat<2, 2, float> m1;
        int x;

        SETUP()
        {
            m1 = {
                {1.5, 2},
                {3, 4.5}
            };

            x = 1;
        }

        FTEST("Test 1")
        {
            auto m2 = m1 - x;

            assert(std::is_same<decltype(m2), linalg::mat<2, 2, float>>::value);

            assertEq(m2, linalg::mat<2, 2, float>
            {
                {0.5, 1},
                {2, 3.5}
            });
        }

        FTEST("Test 2")
        {
            m1 -= x;

            assertEq(m1, linalg::mat<2, 2, float>
            {
                {0.5, 1},
                {2, 3.5}
            });
        }
    }
}

SUITE("Matrix multiplication") // [A.5]
{
    TEST("Test 1")
    {
        linalg::mat<3, 2, float> m1 {
            {1, 2},
            {3, 4},
            {5, 6}
        };

        linalg::mat<2, 3, double> m2 {
            {7, 8, 9},
            {10, 11, 12}
        };

        auto m3 = m1 * m2;

        assert(std::is_same<decltype(m3), linalg::mat<3, 3, double>>::value);

        assertEq(m3, linalg::mat<3, 3, double>
        {
            {27, 30, 33},
            {61, 68, 75},
            {95, 106, 117}
        });
    }
}

SUITE("Matrix scalar multiplication") // [A.6]
{
    FIXTURE()
    {
        linalg::mat<2, 2, float> m1;
        int x;

        SETUP()
        {
            m1 = {
                {1.5, 2},
                {3, 4.5}
            };

            x = 2;
        }

        FTEST("Test 1")
        {
            auto m2 = m1 * x;

            assert(std::is_same<decltype(m2), linalg::mat<2, 2, float>>::value);

            assertEq(m2, linalg::mat<2, 2, float>
            {
                {3, 4},
                {6, 9}
            });
        }

        FTEST("Test 2")
        {
            m1 *= x;

            assertEq(m1, linalg::mat<2, 2, float>
            {
                {3, 4},
                {6, 9}
            });
        }
    }
}

SUITE("Matrix scalar division") // [A.7]
{
    FIXTURE()
    {
        linalg::mat<2, 2, float> m1;
        int x;

        SETUP()
        {
            m1 = {
                {3, 2},
                {5, 4}
            };

            x = 2;
        }

        FTEST("Test 1")
        {
            auto m2 = m1 / x;

            assert(std::is_same<decltype(m2), linalg::mat<2, 2, float>>::value);

            assertEq(m2, linalg::mat<2, 2, float>
            {
                {1.5, 1},
                {2.5, 2}
            });
        }

        FTEST("Test 2")
        {
            m1 /= x;

            assertEq(m1, linalg::mat<2, 2, float>
            {
                {1.5, 1},
                {2.5, 2}
            });
        }
    }
}

SUITE("Matrix transposition") // [S.1]
{
    TEST("Test 1")
    {
        linalg::mat<2, 2, int> m
        {
            {11, 12},
            {21, 22}
        };

        auto transposed = m.t();

        assertEq(transposed, linalg::mat<2, 2, int> {
            {11, 21},
            {12, 22}
        });
    }
}