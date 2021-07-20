#include "Date.h"
#include <iostream>

int main()
{

    // project::Date my_date{1, 1, 2020};
    // std::cout << my_date;
    // std::cout << "==========================================================="<<std::endl;

    // // try
    // // {
    // //     project::Date str_date{"1/092021"};
    // // }
    // // catch (const std::exception &e)
    // // {
    // //     std::cerr << e.what() << '\n';
    // // }

    // std::cout << my_date - 1;
    // std::cout << "==========================================================="<<std::endl;

    project::Date last_day{27, 2, 2020};
    std::cout << last_day;
    std::cout << "===========================================================" << std::endl;

    last_day += 1;
    std::cout << last_day;
    std::cout << "===========================================================" << std::endl;

    last_day -= 1;
    int i = 0;
    while (i++ < 10)
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

    return 0;
}