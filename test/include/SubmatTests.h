#include "yUnit.h"

#include "submat.h"

SUITE(submatConstruction,
    {
        TEST(submatRow,
        {
            int elems[] = {11, 12, 21, 22};

            submat<2, int> s(&elems[2], 1);

            assertEq(s[0], 21);
            assertEq(s[1], 22);
        })

        TEST(submatCol,
        {
            int elems[] = {11, 12, 21, 22};

            submat<2, int> s(&elems[1], 2);

            assertEq(s[0], 12);
            assertEq(s[1], 22);
        })
    })

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

SUITE(submatComparison,
{
    TEST(test1,
    {
        int elems[] = {11, 12, 21, 22};

        submat<2, int> s(&elems[1], 2);
        
        assertEq(s, vec<2, int> {12, 22});
    })
})

/*
    }

    {
        tenv.beginTest("Equal vector comparison (int-int)");

        vec<2, int> v1(1, 3);
        vec<2, int> v2(1, 3);

        tenv.assert(v1 == v2, "Equal vectors considered unequal");
    }

    {
        tenv.beginTest("Equal vector comparison (double-double)");

        vec<4, double> v1(1, 2.5, -3, 137);
        vec<4, double> v2(1, 2.5, -3, 137);

        tenv.assert(v1 == v2, "Equal vectors considered unequal");
    }

    {
        tenv.beginTest("Unequal vector comparison (float-float)");

        vec<3, float> v1(1, 2.5, -3);
        vec<3, float> v2(4, 5.5, -6);

        tenv.assert(v1 != v2, "Unequal vectors considered equal");
    }

    {
        tenv.beginTest("Unequal vector comparison (int-int)");

        vec<2, float> v1(1, 3);
        vec<2, float> v2(5, 7);

        tenv.assert(v1 != v2, "Unequal vectors considered equal");
    }

    {
        tenv.beginTest("Unequal vector comparison (double-double)");

        vec<4, double> v1(1, 2.5, -3, 137);
        vec<4, double> v2(1, 3, 7.5, 9);

        tenv.assert(v1 != v2, "Unequal vectors considered equal");
    }
}
    */