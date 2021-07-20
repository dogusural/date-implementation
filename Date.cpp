#include "Date.h"
#include <iostream>
#include <vector>

namespace project
{
    //////////////////////////////////////////////////////// STREAM OPERATORS ////////////////////////////////////////////////////////

    std::ostream &operator<<(std::ostream &os, const Date::Month &month)
    {
        switch (month)
        {
        case (Date::Month::January):
            os << "January";
            return os;
        case (Date::Month::February):
            os << "February";
            return os;
        case (Date::Month::March):
            os << "March";
            return os;
        case (Date::Month::April):
            os << "April";
            return os;
        case (Date::Month::May):
            os << "May";
            return os;
        case (Date::Month::June):
            os << "June";
            return os;
        case (Date::Month::July):
            os << "July";
            return os;
        case (Date::Month::August):
            os << "August";
            return os;
        case (Date::Month::September):
            os << "September";
            return os;
        case (Date::Month::October):
            os << "October";
            return os;
        case (Date::Month::November):
            os << "November";
            return os;
        case (Date::Month::December):
            os << "December";
            return os;

        default:
            os << "Error";
            return os;
        }
    }

    std::ostream &operator<<(std::ostream &os, const Date::Weekday &weekday)
    {
        switch (weekday)
        {
        case (Date::Weekday::Monday):
            os << "Monday";
            return os;
        case (Date::Weekday::Tuesday):
            os << "Tuesday";
            return os;
        case (Date::Weekday::Wednesday):
            os << "Wednesday";
            return os;
        case (Date::Weekday::Thursday):
            os << "Thursday";
            return os;
        case (Date::Weekday::Friday):
            os << "Friday";
            return os;
        case (Date::Weekday::Saturday):
            os << "Saturday";
            return os;
        case (Date::Weekday::Sunday):
            os << "Sunday";
            return os;

        default:
            os << "Error";
            return os;
        }
    }

    std::ostream &operator<<(std::ostream &os, const Date &date)
    {
        os << date.get_month_day() << " " << date.get_month_year() << " " << date.get_year() << " " << date.get_week_day() << "\n";
    }
    //////////////////////////////////////////////////////// STREAM OPERATORS ////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////// LOGICAL OPERATORS ////////////////////////////////////////////////////////
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
    //////////////////////////////////////////////////////// LOGICAL OPERATORS ////////////////////////////////////////////////////////

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
            size_t i = 0;
            for (auto &member : vec_date)
            {
                m_date.DATE[i++] = member;
            }
        }
    }
    //////////////////////////////////////////////////////// CONSTRUCTORS ////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////// GETTERS ////////////////////////////////////////////////////////

    unsigned int Date::get_month_day() const
    {
        return this->m_date.DATE[date_members::date_indice::DAY];
    }

    unsigned int Date::get_month() const
    {
        return this->m_date.DATE[date_members::date_indice::MONTH];
    }

    unsigned int Date::get_year() const
    {
        return this->m_date.DATE[date_members::date_indice::YEAR];
        ;
    }

    unsigned int Date::get_year_day() const
    {
        const int *tmp_month_days = nullptr;
        if (isleap(get_year()))
            tmp_month_days = leap_month_days;
        else
            tmp_month_days = month_days;

        size_t year_day = 0;

        for (unsigned int month = 1; month + 1 < get_month(); month++)
        {
            year_day += tmp_month_days[month];
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
        y = m_date.DATE[date_members::date_indice::YEAR];
        m = m_date.DATE[date_members::date_indice::MONTH];
        d = m_date.DATE[date_members::date_indice::DAY];
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
    //////////////////////////////////////////////////////// GETTERS ////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////// SETTERS ////////////////////////////////////////////////////////

    Date &Date::set_month_day(unsigned int day)
    {
        this->m_date.DATE[date_members::date_indice::DAY] = day;
        return *this;
    }
    Date &Date::set_month(unsigned int month)
    {
        this->m_date.DATE[date_members::date_indice::MONTH] = month;
        return *this;
    }
    Date &Date::set_year(unsigned int year)
    {
        this->m_date.DATE[date_members::date_indice::YEAR] = year;
        return *this;
    }
    Date &Date::set(unsigned int day, unsigned int month, unsigned int year)
    {
        this->m_date.DATE[date_members::date_indice::DAY] = day;
        this->m_date.DATE[date_members::date_indice::MONTH] = month;
        this->m_date.DATE[date_members::date_indice::YEAR] = year;

        return *this;
    }
    //////////////////////////////////////////////////////// SETTERS ////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////// ARITHMETIC OPERATORS ////////////////////////////////////////////////////////

    Date Date::operator-(unsigned int day) const
    {
        unsigned long current_date = date_to_integer(get_month_day(), get_month(), get_year()) - day;
        return Date{integer_to_date(current_date)};
    }

    // Date Date::operator+(unsigned int day) const
    // {
    //     unsigned long current_date = date_to_integer(get_month_day(), get_month(), get_year()) + day;
    //     return Date{integer_to_date(current_date)};
    // }

    Date &Date::operator+=(unsigned int day)
    {
        *this = operator+(*this,day);
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

    //////////////////////////////////////////////////////// ARITHMETIC OPERATORS ////////////////////////////////////////////////////////

    Date operator+(const Date &date, unsigned int n)
    {
        unsigned long current_date = date.date_to_integer(date.get_month_day(), date.get_month(), date.get_year()) + n;
        return Date{Date::integer_to_date(current_date)};
    }

    //////////////////////////////////////////////////////// HELPERS ////////////////////////////////////////////////////////

    constexpr inline unsigned long Date::date_to_integer(unsigned int d, unsigned int m, unsigned int y)  //https://web.archive.org/web/20131226174531/http://home.roadrunner.com/~hinnant/date_algorithms.html
    {
        y -= m <= 2;
        const unsigned int era = y / 400;
        const unsigned yoe = static_cast<unsigned>(y - era * 400);           // [0, 399]
        const unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1; // [0, 365]
        const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;          // [0, 146096]
        return era * 146097 + static_cast<int>(doe) - 719468;
    }

    inline Date Date::integer_to_date(unsigned long n)  //https://web.archive.org/web/20131226174531/http://home.roadrunner.com/~hinnant/date_algorithms.html
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
    //////////////////////////////////////////////////////// HELPERS ////////////////////////////////////////////////////////

}
