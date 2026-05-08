#include "yUnit.h"

#include "submat.h"

SUITE(submatConstruction,
    {
        TEST(test_1,
        {
            int elems[] = {
                11, 12,
                21, 22
            };

            submat<2, 2, int> s(&elems[0]);

            assertEq(s(1, 0), 21);
            assertEq(s(1, 1), 22);

            s(1, 1) = 137;

            assertEq(s(1, 1), 137);
            assertEq(elems[3], 137);
        })
    })

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