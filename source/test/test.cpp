#include "Date.h"

#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp" // Header only library from 
// https://web.archive.org/web/20170807171031/https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp

#include <iostream>


project::Date my_date{1, 1, 2020};
project::Date my_copy_date = my_date;
unsigned int Factorial(unsigned int number)
{
    return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]")
{
    REQUIRE(Factorial(1) == 1);
    REQUIRE(Factorial(2) == 2);
    REQUIRE(Factorial(3) == 6);
    REQUIRE(Factorial(10) == 3628800);
}