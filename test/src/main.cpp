#include <iostream>

#include "yUnit.h"

#include "vec.h"

#include "TestEnvironment.h"
#include "utils.h"
#include "requirement_tests/vector.h"
#include "requirement_tests/matrix.h"

using namespace linalg;

int main()
{
    std::cout << yUnit::getSummary();

    return 0;
}