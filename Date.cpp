#include "Date.hpp"

Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
    if (year > 9999)
    {
        throw std::invalid_argument("Year must be between 0 and 9999");
    }
    bool leap = false;
    if (year % 4 == 0 || (year % 100 != 0 && year % 400 == 0))
    {
        leap = true;
    }
    if (month > 12)
    {
        throw std::invalid_argument("Month must be between 1 and 12");
    }
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        if (day > 31)
        {
            throw std::invalid_argument("Day must be between 1 and 31");
        }
    }
    else if(month == 2)
    {
        if(leap && day > 29)
        {
            throw std::invalid_argument("Day must be between 1 and 29");
        }
        else if(!leap && day > 28)
        {
            throw std::invalid_argument("Day must be between 1 and 28");
        }
    }
    else
    {
        if (day > 30)
        {
            throw std::invalid_argument("Day must be between 1 and 30");
        }
    }
    this->day = day;
    this->month = month;
    this->year = year;
}

unsigned int Date::getDay() const
{
    return this->day;
}

unsigned int Date::getMonth() const
{
    return this->month;
}

unsigned int Date::getYear() const
{
    return this->year;
}

bool Date::cmp(const Date& other)
{
    return (day==other.day && month == other.month && year == other.year);
}
// TO DO
char *Date::dateToStr() const
{
    char *str = new char[DATE_SIZE];
    str[DATE_SIZE] = '\0';
    int currentIndex = 0;
    if (day < 10)
        str[currentIndex++] = '0';

    str[currentIndex++] = day + '0';
}