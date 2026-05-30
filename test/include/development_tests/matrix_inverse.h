#include "cppUnit.h"

#include "mat.h"
#include "algorithms.h"

SUITE("Matrix inverse")
{
    TEST("Inverse of identity matrix")
    {
        linalg::mat<2, 2, float> m {
            {1, 0},
            {0, 1}
        };

        linalg::mat<2, 2, float> m_inv;

        assert(linalg::inv(m, m_inv));

        assertEq(m_inv, linalg::mat<2, 2, float> {
            {1, 0},
            {0, 1}
        });
    }

    TEST("Inverse of 2x2 matrix")
    {
        linalg::mat<2, 2, float> m {
            {1, 2},
            {3, 4}
        };

        linalg::mat<2, 2, float> m_inv;

        assert(linalg::inv(m, m_inv));

        assertEq(m_inv, linalg::mat<2, 2, float> {
            {-2, 1},
            {1.5, -0.5}
        });
    }

    TEST("Inverse of 3x3 matrix")
    {
        linalg::mat<3, 3, float> m {
            {1, 0, 4},
            {0, 2, 0},
            {0, 0, 3}
        };

        linalg::mat<3, 3, float> m_inv;

        assert(linalg::inv(m, m_inv));

        assertEq(m_inv, linalg::mat<3, 3, float> {
            {1, 0, -4.0f/3},
            {0, 0.5, 0},
            {0, 0, 1.0f/3}
        });
    }

    TEST("Singular matrix")
    {
        linalg::mat<3, 3, float> m {
            {1, 0, 4},
            {0, 2, 0},
            {2, 0, 8}
        };

        linalg::mat<3, 3, float> m_inv;

        assert(!linalg::inv(m, m_inv));
    }
}