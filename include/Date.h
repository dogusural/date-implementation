#ifndef DATE_H
#define DATE_H
#include <iosfwd>
#include <ctime>
#include <string>
#include <iostream>

namespace project
{

    class bad_date : public std::logic_error
    {
    public:
        bad_date(const std::string &msg) : logic_error{msg}, m_msg{msg}
        {
        }
        const char *what() const throw()
        {
            return m_msg.c_str();
        }

    private:
        std::string m_msg;
    };

    class Date
    {
        struct DATE
        {
            DATE(unsigned int day = 1, unsigned int month = 1, unsigned int year = 1900) : DAY{day}, MONTH{month}, YEAR{year}
            {
                if (!Date::is_valid_date(day, month, year))
                    throw bad_date{"Invalid date format. Use a valid value for Date and Month\n"};
            }
            unsigned int DAY;
            unsigned int MONTH;
            unsigned int YEAR;
        };
        DATE m_date;
        static constexpr unsigned int month_days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};      // gave an offset of "0" first element to match the first indice to 1
        static constexpr unsigned int leap_month_days[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // gave an offset of "0" first element to match the first indice to 1
        Date &set_month_day(unsigned int day);
        Date &set_month(unsigned int month);
        Date &set_year(unsigned int year);

    public:
        static constexpr int year_base = 1900;       //1
        static constexpr int random_min_year = 1940; //2
        static constexpr int random_max_year = 2020; //3
        enum class Weekday
        {
            Monday = 1,
            Tuesday,
            Wednesday,
            Thursday,
            Friday,
            Saturday,
            Sunday
        }; //4
        enum class Month
        {
            January = 1,
            February,
            March,
            April,
            May,
            June,
            July,
            August,
            September,
            October,
            November,
            December
        }; //4

        explicit Date();                                               //5
        explicit Date(unsigned int d, unsigned int m, unsigned int y); //6
        explicit Date(const char *p);                                  //7
        explicit Date(std::time_t timer);  
        Date(const Date &);
        unsigned int get_month_day() const;                            //9
        unsigned int get_month() const;                                //10
        unsigned int get_year() const;                                 //11
        unsigned int get_year_day() const;                             //12
        const unsigned int *get_day_each_month() const;
        Weekday get_week_day() const; //13
        Month get_month_year() const; //14

        Date &set(unsigned int day, unsigned int mon, unsigned int year); //17
        Date operator-(unsigned int day) const;                           //18
        Date& operator=(const Date&);                                   //8
        Date &operator+=(unsigned int day);                               //19
        Date &operator-=(unsigned int day);                               //20
        Date &operator++();                                               //21
        Date operator++(int);                                             //22
        Date &operator--();                                               //23
        Date operator--(int);                                             //24

        static constexpr inline unsigned long date_to_integer(unsigned int, unsigned int, unsigned int);
        static inline Date integer_to_date(unsigned long);
        static Date random_date();
        static inline constexpr bool isleap(unsigned int y);
        static inline bool is_valid_date(const Date &date);
        static bool is_valid_date(unsigned int day, unsigned int month, unsigned int year);
        static const unsigned int *get_day_each_month(const unsigned int);

        friend bool operator<(const Date &, const Date &);  //27
        friend bool operator>(const Date &, const Date &);  //27
        friend bool operator<=(const Date &, const Date &); //27
        friend bool operator>=(const Date &, const Date &); //27
        friend bool operator==(const Date &, const Date &); //27

        friend std::ostream &operator<<(std::ostream &os, const Date &date); //31
        friend std::istream &operator>>(std::istream &is, Date &date);       //32
    };
    std::ostream &operator<<(std::ostream &os, const Date::Weekday &day);
    std::ostream &operator<<(std::ostream &os, const Date::Month &month);
    bool operator<(const Date &, const Date &);  //27
    bool operator<=(const Date &, const Date &); //27
    bool operator>(const Date &, const Date &);  //27
    bool operator>=(const Date &, const Date &); //27
    bool operator==(const Date &, const Date &); //27
    bool operator!=(const Date &, const Date &); //27

    unsigned int operator-(const Date &d1, const Date &d2); //28
    Date operator+(const Date &date, unsigned int n);       //29
    Date operator+(unsigned int n, const Date &);           //29
    Date::Weekday &operator++(Date::Weekday &r);            //30
    Date::Weekday operator++(Date::Weekday &r, int);        //30
    Date::Weekday &operator--(Date::Weekday &r);            //30
    Date::Weekday operator--(Date::Weekday &r, int);        //30

}

#endif