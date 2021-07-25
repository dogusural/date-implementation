#include "Date.h"

#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"      // Header only library from
// https://web.archive.org/web/20170807171031/https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp

#include <iostream>

project::Date pre_increment(project::Date date)
{
    return ++date;
}

project::Date post_increment(project::Date date)
{
    return date++;
}

project::Date addition(project::Date date, int days)
{
    return date + days;
}

TEST_CASE("Pre increment test", "[pre_increment]")
{
    project::Date my_date{1, 1, 2020};

    REQUIRE(pre_increment(my_date) > my_date);
}

TEST_CASE("Post increment test", "[post_increment]")
{
    project::Date my_date{1, 1, 2020};

    REQUIRE(post_increment(my_date) == my_date);
}

TEST_CASE("Addition test", "[addition]")
{
    project::Date my_date{28, 2, 2020};

    REQUIRE(addition(my_date , 10) == (project::Date{9,3,2020}) );
}