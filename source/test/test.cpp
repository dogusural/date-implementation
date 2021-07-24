#include "Date.h"
#include <iostream>

int main()
{
    std::cout << project::Date{};

    project::Date my_date{1, 1, 2020};
    project::Date my_copy_date = my_date;
    my_date++;
    std::cout << my_copy_date;
    my_copy_date = my_date;
    std::cout << my_copy_date;
    std::cout << "===========================================================" << std::endl;

    try
    {
        project::Date str_date{"30/09/2022"};
        std::cout << str_date << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    project::Date last_day{27, 2, 2020};
    std::cout << last_day;
    std::cout << "===========================================================" << std::endl;
    last_day += 1;
    std::cout << last_day;
    std::cout << "===========================================================" << std::endl;

    last_day -= 1;
    int i = 0;
    while (++i < 10)
        std::cout << ++last_day;
    std::cout << "===========================================================" << std::endl;
    std::cout << last_day++;
    std::cout << ++last_day;
    std::cout << "===========================================================" << std::endl;
    ;

    std::cout << std::boolalpha << (last_day <= project::Date{last_day + 1}) << '\n';
    std::cout << std::boolalpha << (last_day >= project::Date{last_day - 1}) << '\n';
    std::cout << std::boolalpha << (last_day == project::Date{last_day + 1}) << '\n';
    std::cout << std::boolalpha << (last_day < project::Date{1 + last_day}) << '\n';
    std::cout << std::boolalpha << (last_day != project::Date{1 + last_day}) << '\n';
    std::cout << "===========================================================" << std::endl;

    project::Date::Weekday today = project::Date::Weekday::Monday;

    i = 0;
    while (i++ < 7)
        std::cout << ++today << std::endl;
    std::cout << "===========================================================" << std::endl;
    i = 0;

    while (i++ < 7)
        std::cout << --today << std::endl;

    project::Date input_date{};
    std::cin >> input_date;
    std::cout << input_date;
    std::cout << project::Date::random_date();
    std::cout << project::Date{std::time(0)};

    return 0;
}