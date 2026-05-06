#include "yUnit.h"

#include "submat.h"

SUITE(submatConstruction,
    {
        TEST(submatRow,
        {
            int elems[] = {11, 12, 21, 22};

            submat s(&elems[2], 2, 1);

            assertEq(s[0], 21);
            assertEq(s[1], 22);
        })

        TEST(submatCol,
        {
            int elems[] = {11, 12, 21, 22};

            submat s(&elems[1], 2, 2);

            assertEq(s[0], 12);
            assertEq(s[1], 22);
        })
    })

SUITE(submatAssignment,
    {
        TEST(submatElementAssignment,
        {
            int elems[] = {11, 12, 21, 22};

            submat s(&elems[2], 2, 1);

            s[1] = 137;

            assertEq(elems[3], 137);
        })

        TEST(submatScalarAssignment,
        {
            int elems[] = {11, 12, 21, 22};

            submat s(&elems[1], 2, 2);

            s = 137;

            assertEq(elems[1], 137);
            assertEq(elems[3], 137);
        })

        TEST(submatVectorAssignment,
        {
            int elems[] = {11, 12, 21, 22};

            submat s(&elems[1], 2, 2);

            s = vec<2, int> {137, 314};

            assertEq(elems[1], 137);
            assertEq(elems[3], 314);
        })
    })