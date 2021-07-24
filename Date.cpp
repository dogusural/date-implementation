#include "Date.h"
#include <iostream>
#include <vector>
#include <random>

namespace project
{
    //////////////////////////////////////////////////////// STREAM OPERATOR OVERLOADS ////////////////////////////////////////////////////////

    std::ostream &operator<<(std::ostream &os, const Date::Month &month)
    {
        switch (month)
        {
        case (Date::Month::January):
            return os << "January";

        case (Date::Month::February):
            return os << "February";

        case (Date::Month::March):
            return os << "March";

        case (Date::Month::April):
            return os << "April";

        case (Date::Month::May):
            return os << "May";

        case (Date::Month::June):
            return os << "June";

        case (Date::Month::July):
            return os << "July";

        case (Date::Month::August):
            return os << "August";

        case (Date::Month::September):
            return os << "September";

        case (Date::Month::October):
            return os << "October";

        case (Date::Month::November):
            return os << "November";

        case (Date::Month::December):
            return os << "December";

        default:
            return os << "Error";
        }
    }

    std::ostream &operator<<(std::ostream &os, const Date::Weekday &weekday)
    {
        switch (weekday)
        {
        case (Date::Weekday::Monday):
            return os << "Monday";

        case (Date::Weekday::Tuesday):
            return os << "Tuesday";

        case (Date::Weekday::Wednesday):
            return os << "Wednesday";

        case (Date::Weekday::Thursday):
            return os << "Thursday";

        case (Date::Weekday::Friday):
            return os << "Friday";

        case (Date::Weekday::Saturday):
            return os << "Saturday";

        case (Date::Weekday::Sunday):
            return os << "Sunday";

        default:
            return os << "Error";
        }
    }

    std::ostream &operator<<(std::ostream &os, const Date &date)
    {
        os << date.get_month_day() << " " << date.get_month_year() << " " << date.get_year() << " " << date.get_week_day() << "\n";
    }

    std::istream &operator>>(std::istream &is, Date &date)
    {
        int day, month, year;
        char ch1, ch2;
        is >> day >> ch1 >> month >> ch2 >> year;
        if (ch1 != '/' || ch2 != '/')
        {
            throw bad_date{"Invalid date format. Use d/m/y\n"};
        }

        date.set(day, month, year);

        return is;
    }
    //////////////////////////////////////////////////////// STREAM OPERATOR OVERLOADS ////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////// LOGICAL OPERATOR OVERLOADS ////////////////////////////////////////////////////////
    bool operator<(const Date &left, const Date &right)
    {
        return (left.date_to_integer(left.get_month_day(), left.get_month(), left.get_year()) < right.date_to_integer(right.get_month_day(), right.get_month(), right.get_year()));
    }
    bool operator>(const Date &left, const Date &right)
    {
        return (left.date_to_integer(left.get_month_day(), left.get_month(), left.get_year()) > right.date_to_integer(right.get_month_day(), right.get_month(), right.get_year()));
    }
    bool operator<=(const Date &left, const Date &right)
    {
        return (left < right || left == right);
    }
    bool operator>=(const Date &left, const Date &right)
    {
        return (left > right || left == right);
    }
    bool operator==(const Date &left, const Date &right)
    {
        return (left.date_to_integer(left.get_month_day(), left.get_month(), left.get_year()) == right.date_to_integer(right.get_month_day(), right.get_month(), right.get_year()));
    }
    bool operator!=(const Date &left, const Date &right)
    {
        return !(left == right);
    }

    //////////////////////////////////////////////////////// LOGICAL OPERATOR OVERLOADS ////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////// CONSTRUCTORS ////////////////////////////////////////////////////////

    Date::Date() : m_date{}
    {
    }

    Date::Date(unsigned int day, unsigned int month, unsigned int year) : m_date{day, month, year}
    {
    }
    Date::Date(const char *str)
    {
        std::vector<int> vec_date;
        std::string temp_str{str};
        size_t pos = std::string::npos;
        while ((pos = temp_str.find('/')) != std::string::npos)
        {
            std::string token = temp_str.substr(0, pos);
            temp_str = temp_str.substr(pos + 1);
            vec_date.push_back(stoi(token));
        }
        vec_date.push_back(stoi(temp_str));
        if (vec_date.size() != 3)
        {
            throw bad_date{"Please use dd/mm/yyyy format!"};
        }
        else
        {
            set(vec_date[0], vec_date[1], vec_date[2]);
        }
    }
    Date::Date(std::time_t timer)
    {
        std::time_t t = timer;
        std::tm *now = std::localtime(&t);
        set(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
    }
    Date::Date(const Date &other) : m_date{other.m_date.DAY, other.m_date.MONTH, other.m_date.YEAR}
    {
    }
    //////////////////////////////////////////////////////// CONSTRUCTORS ////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////// GETTERS ////////////////////////////////////////////////////////

    unsigned int Date::get_month_day() const
    {
        return this->m_date.DAY;
    }

    unsigned int Date::get_month() const
    {
        return this->m_date.MONTH;
    }

    unsigned int Date::get_year() const
    {
        return this->m_date.YEAR;
        ;
    }

    unsigned int Date::get_year_day() const
    {
        const unsigned int *month_days = get_day_each_month();

        size_t year_day = 0;

        for (unsigned int month = 1; month + 1 < get_month(); month++)
        {
            year_day += month_days[month];
        }

        if (isleap(get_year()) && get_month() > static_cast<int>(Date::Month::February))
        {

            return year_day + 1;
        }

        else
        {
            return year_day;
        }
    }

    Date::Weekday Date::get_week_day() const // Copy-pasted from https://www.geeksforgeeks.org/find-day-of-the-week-for-a-given-date/
    {
        size_t y, m, d, day = 0;
        y = m_date.YEAR;
        m = m_date.MONTH;
        d = m_date.DAY;
        static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        y -= m < 3;
        day = ((y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7);
        day = (day == 0) ? 7 : day;
        return static_cast<Date::Weekday>(day);
    }

    Date::Month Date::get_month_year() const
    {
        return static_cast<Date::Month>(get_month());
    }

    const unsigned int *Date::get_day_each_month() const
    {
        if (isleap(get_year()))
            return leap_month_days;
        else
            return month_days;
    }

    //////////////////////////////////////////////////////// GETTERS ////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////// SETTERS ////////////////////////////////////////////////////////

    Date &Date::set_month_day(unsigned int day)
    {
        this->m_date.DAY = day;
        return *this;
    }
    Date &Date::set_month(unsigned int month)
    {
        this->m_date.MONTH = month;
        return *this;
    }
    Date &Date::set_year(unsigned int year)
    {
        this->m_date.YEAR = year;
        return *this;
    }
    Date &Date::set(unsigned int day, unsigned int month, unsigned int year)
    {
        if (!(Date::is_valid_date(day, month, year)))
        {
            throw bad_date{"Invalid date format. Use a valid value for Date and Month\n"};
        }
        set_month_day(day);
        set_month(month);
        set_year(year);

        return *this;
    }
    //////////////////////////////////////////////////////// SETTERS ////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////// OPERATOR OVERLOADS ////////////////////////////////////////////////////////
    Date &Date::operator=(const Date &other)
    {
        this->set(other.get_month_day(), other.get_month(), other.get_year());
        return *this;
    }

    //////////////////////////////////////////////////////// OPERATOR OVERLOADS ////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////// ARITHMETIC OPERATOR OVERLOADS ////////////////////////////////////////////////////////

    Date Date::operator-(unsigned int day) const
    {
        unsigned long current_date = date_to_integer(get_month_day(), get_month(), get_year()) - day;
        return integer_to_date(current_date);
    }

    Date &Date::operator+=(unsigned int day)
    {
        *this = operator+(*this, day);
        return *this;
    }

    Date &Date::operator-=(unsigned int day)
    {
        *this = this->operator-(day);
        return *this;
    }

    Date &Date::operator++()
    {
        this->operator+=(1);
        return *this;
    }

    Date Date::operator++(int)
    {
        Date tmp{*this};
        *this = this->operator++();
        return tmp;
    }

    Date &Date::operator--()
    {
        this->operator-=(1);
        return *this;
    }
    Date Date::operator--(int)
    {
        Date tmp{*this};
        *this = this->operator--();
        return tmp;
    }

    //////////////////////////////////////////////////////// ARITHMETIC OPERATOR OVERLOADS ////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////// GLOBAL ARITHMETIC OPERATOR OVERLOADS ////////////////////////////////////////////////////////

    Date operator+(const Date &date, unsigned int n)
    {
        unsigned long current_date = date.date_to_integer(date.get_month_day(), date.get_month(), date.get_year()) + n;
        return Date::integer_to_date(current_date);
    }

    Date operator+(unsigned int n, const Date &date)
    {
        return (date + n);
    }

    unsigned int operator-(const Date &d1, const Date &d2)
    {
        return Date::date_to_integer(d1.get_month_day(), d1.get_month(), d1.get_year()) - Date::date_to_integer(d2.get_month_day(), d2.get_month(), d2.get_year());
    }

    Date::Weekday &operator++(Date::Weekday &r)
    {
        size_t day = (static_cast<int>(r) + 1);
        day = day == 8 ? static_cast<int>(Date::Weekday::Monday) : day;
        r = static_cast<Date::Weekday>(day);
        return r;
    }
    Date::Weekday operator++(Date::Weekday &r, int)
    {
        Date::Weekday tmp{r};
        ++r;
        return tmp;
    }
    Date::Weekday &operator--(Date::Weekday &r)
    {
        size_t day = (static_cast<int>(r) - 1);
        day = day == 0 ? static_cast<int>(Date::Weekday::Sunday) : day;
        r = static_cast<Date::Weekday>(day);
        return r;
    }
    Date::Weekday operator--(Date::Weekday &r, int)
    {
        Date::Weekday tmp{r};
        --r;
        return tmp;
    }
    //////////////////////////////////////////////////////// GLOBAL ARITHMETIC OPERATOR OVERLOADS ////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////// HELPERS ////////////////////////////////////////////////////////

    constexpr inline unsigned long Date::date_to_integer(unsigned int d, unsigned int m, unsigned int y) //https://web.archive.org/web/20131226174531/http://home.roadrunner.com/~hinnant/date_algorithms.html
    {
        y -= m <= 2;
        const unsigned int era = y / 400;
        const unsigned yoe = static_cast<unsigned>(y - era * 400);           // [0, 399]
        const unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1; // [0, 365]
        const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;          // [0, 146096]
        return era * 146097 + static_cast<int>(doe) - 719468;
    }

    inline Date Date::integer_to_date(unsigned long n) //https://web.archive.org/web/20131226174531/http://home.roadrunner.com/~hinnant/date_algorithms.html
    {
        n += 719468;
        const int era = n / 146097;
        const unsigned doe = static_cast<unsigned>(n - era * 146097);               // [0, 146096]
        const unsigned yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365; // [0, 399]
        const unsigned int y = (yoe) + era * 400;
        const unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100); // [0, 365]
        const unsigned mp = (5 * doy + 2) / 153;                      // [0, 11]
        const unsigned d = doy - (153 * mp + 2) / 5 + 1;              // [1, 31]
        const unsigned m = mp + (mp < 10 ? 3 : -9);                   // [1, 12]
        return Date{d, m, y + (m <= 2)};
    }

    constexpr inline bool Date::isleap(unsigned int year)
    {
        return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

    inline bool Date::is_valid_date(const Date &date)
    {
        const unsigned int *month_days = date.get_day_each_month();
        if ((date.get_month_day() > month_days[date.get_month()]) || date.get_month_day() == 0)
            return false;
        if ((date.get_month() > 12) || date.get_month() == 0)
            return false;
        return true;
    }
    inline bool Date::is_valid_date(unsigned int day, unsigned int month, unsigned int year)
    {
        const unsigned int *month_days = get_day_each_month(year);
        if ((day > month_days[month]) || day == 0)
            return false;
        if ((month > 12) || month == 0)
            return false;
        return true;
    }

    Date Date::random_date()
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> month(static_cast<int>(Date::Month::January), static_cast<int>(Date::Month::December)); // distribution in range [1, 6]
        std::uniform_int_distribution<std::mt19937::result_type> year(random_min_year, random_max_year);
        unsigned int random_year = year(rng);
        unsigned int random_month = month(rng);
        const unsigned int *month_days = get_day_each_month(random_year);
        std::uniform_int_distribution<std::mt19937::result_type> day(1, month_days[random_month]);
        unsigned int random_day = day(rng);

        return Date{random_day, random_month, random_year};
    }

    const unsigned int *Date::get_day_each_month(const unsigned int year)
    {
        if (isleap(year))
            return leap_month_days;
        else
            return month_days;
    }
    //////////////////////////////////////////////////////// HELPERS ////////////////////////////////////////////////////////
}
