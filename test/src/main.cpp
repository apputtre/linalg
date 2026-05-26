#include <iostream>

#include "yUnit.h"

#include "TestEnvironment.h"
#include "utils.h"
#include "requirement_tests/vector.h"
#include "requirement_tests/matrix.h"
#include "development_tests/matrix_inverse.h"
#include "development_tests/augmented_matrix.h"
#include "development_tests/gauss_jordan_elim.h"

using namespace linalg;

int main()
{
    std::cout << yUnit::getSummary();

    return 0;
}