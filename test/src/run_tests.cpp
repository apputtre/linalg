#include <iostream>

#include "cppUnit.h"

#include "TestEnvironment.h"
#include "utils.h"
#include "requirement_tests/vector.h"
#include "requirement_tests/matrix.h"
#include "development_tests/matrix_inverse.h"
#include "development_tests/augmented_matrix.h"
#include "development_tests/gauss_jordan_elim.h"
#include "development_tests/LU_factorization.h"

using namespace linalg;

int main()
{
    std::cout << "Running tests..." << std::endl;

    std::string summary = cppUnit::getSummary();

    std::cout << cppUnit::getSummary();

    if (summary == "")
        std::cout << "All tests passed." << std::endl;

    return 0;
}