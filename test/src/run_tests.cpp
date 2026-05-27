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
    std::cout << "Running tests..." << std::endl;

    std::string summary = yUnit::getSummary();

    std::cout << yUnit::getSummary();

    if (summary == "\n")
        std::cout << "All tests passed." << std::endl;

    return 0;
}