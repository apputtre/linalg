#include "yUnit.h"

#include "submat.h"

SUITE(submatConstruction,
{
    TEST(submat2DConstruction,
    {
        int elems[] = {
            11, 12,
            21, 22
        };

        submat<int, 2, 2> s(&elems[0], 2, 1);

        assertEq(s(1, 0), 21);
        assertEq(s(1, 1), 22);

        s(1, 1) = 137;

        assertEq(s(1, 1), 137);
        assertEq(elems[3], 137);
    })

    TEST(submatRowConstruction,
    {
        int elems[] = {
            11, 12,
            21, 22
        };

        submat<int, 2> s(&elems[2], 1);

        assertEq(s(0), 21);
        assertEq(s(1), 22);

        s(1) = 137;

        assertEq(s(1), 137);
        assertEq(elems[3], 137);
    })

    TEST(submatColConstruction,
    {
        int elems[] = {
            11, 12,
            21, 22
        };

        submat<int, 2> s(&elems[1], 2);

        assertEq(s(0), 12);
        assertEq(s(1), 22);

        s(1) = 137;

        assertEq(s(1), 137);
        assertEq(elems[3], 137);
    })
})

SUITE(submatArithmetic,
{
    TEST(submatAddition,
    {
        int elems[] = {
            11, 12,
            21, 22
        };

        // create submat that represents first row ({11, 12})
        submat<int, 2> s1(&elems[0], 1);

        // create submat that represents second row({21, 22})
        submat<int, 2> s2(&elems[2], 1);

        s1 += s2;

        assertEq(s1(0), 32);
        assertEq(s1(1), 34);
    })
})

SUITE(vecToSubmatConversion,
{
    TEST(test_1,
    {
        vec<3, int> v{1, 3, 5};

        submat<int, 3> s(v);

        assertEq(s(0), 1);
        assertEq(s(1), 3);
        assertEq(s(2), 5);

        s(1) = 137;

        assertEq(v[1], 137);
    })
})

/*
SUITE(submatRowAccess,
{
    TEST(test_1,
    {
        int elems[] = {
            11, 12,
            21, 22
        };

        submat<int, 2, 2> s(&elems[0], 2, 1);

        // access the second row of s ({21, 22})
        auto row = s[1];

        assertEq(row[0], 21);
        assertEq(row[1], 22);

        row[1] = 137;

        assertEq(row[1], 137);
        assertEq(s(1, 1), 137);
        assertEq(elems[3], 137);
    })
})
*/

/*
SUITE(submatAssignment,
    {
        TEST(submatElementAssignment,
        {
            int elems[] = {11, 12, 21, 22};

            submat<2, int> s(&elems[2], 1);

            s[1] = 137;

            assertEq(elems[3], 137);
        })

        TEST(submatScalarAssignment,
        {
            int elems[] = {11, 12, 21, 22};

            submat<2, int> s(&elems[1], 2);

            s = 137;

            assertEq(elems[1], 137);
            assertEq(elems[3], 137);
        })

        TEST(submatVectorAssignment,
        {
            int elems[] = {11, 12, 21, 22};

            submat<2, int> s(&elems[1], 2);
            vec<2, int> v = {137, 314};
            s = v;

            assertEq(elems[1], 137);
            assertEq(elems[3], 314);
        })
    })
*/