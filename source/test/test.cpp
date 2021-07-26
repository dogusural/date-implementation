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
int substraction(project::Date first_date, project::Date second_date)
{
    return first_date - second_date;
}
bool equal()
{
    bool result = false;
    project::Date date = project::Date::random_date();
    return result = (date + 1 == 1 + date);
}
bool greater_than()
{
    bool result = false;
    project::Date date = project::Date::random_date();
    return result = (date + 1 > date);
}
bool lesser_or_equal_to()
{
    bool result = false;
    project::Date date = project::Date::random_date();
    return result = (date - 3 <= date - 2);
}
bool greater_or_equal_to()
{
    bool result = false;
    project::Date date = project::Date::random_date();
    return result = (date + 3 >= date - 2);
}
bool lesser_than()
{
    bool result = false;
    project::Date date = project::Date::random_date();
    return result = (date - 100 < date - 99);
}

TEST_CASE("substraction test", "[substraction]")
{
    REQUIRE(substraction((project::Date{31, 12, 2020}), (project::Date{1, 1, 2020})) == 365);
    REQUIRE(substraction((project::Date{31, 12, 2021}), (project::Date{1, 1, 2021})) == 364);
}
TEST_CASE("Pre increment test", "[pre_increment]")
{
    REQUIRE(pre_increment((project::Date{1, 1, 2020})) > (project::Date{1, 1, 2020}));
}

TEST_CASE("Post increment test", "[post_increment]")
{
    REQUIRE(post_increment((project::Date{1, 1, 2020})) == (project::Date{1, 1, 2020}));
}

TEST_CASE("Addition test", "[addition]")
{
    REQUIRE(addition((project::Date{28, 2, 2020}), 10) == (project::Date{9, 3, 2020}));
    REQUIRE(addition((project::Date{28, 2, 2021}), 10) == (project::Date{10, 3, 2021}));
    REQUIRE(addition((project::Date{28, 12, 2005}), 10) == (project::Date{7, 1, 2006}));
}

TEST_CASE("Comperative operators test", "[logic_operators]")
{
    REQUIRE(equal() == (true));
    REQUIRE(lesser_than() == (true));
    REQUIRE(greater_than() == (true));
    REQUIRE(lesser_or_equal_to() == (true));
    REQUIRE(greater_or_equal_to() == (true));
}