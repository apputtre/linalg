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
            /*
            mat<2, 2, float> m
            (
                {11, 12},
                {13, 14}
            );
            */
        })
    }
)