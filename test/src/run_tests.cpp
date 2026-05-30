#include <iostream>

#include "cppUnit.h"

#include "TestEnvironment.h"
#include "requirement_tests.h"
#include "development_tests.h"

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