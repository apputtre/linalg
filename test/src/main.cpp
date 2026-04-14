#include <iostream>

#include "TestEnvironment.h"

int main()
{
    TestEnvironment tenv;

    tenv.beginSuite("Vector construction");
    {
        tenv.beginTest();
    }

    std::cout << tenv.getSummary();

    return 0;
}