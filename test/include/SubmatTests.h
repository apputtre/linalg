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

SUITE(submatAssignment,
    {
        TEST(submatAssignment,
        {
            int elems[] = {11, 12, 21, 22};

            submat<int, 2> s1(&elems[0], 1);
            submat<int, 2> s2(&elems[2], 1);

            s2 = s1;

            assertEq(elems[2], 11);
            assertEq(elems[3], 12);
        })
    })