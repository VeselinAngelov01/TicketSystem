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
    else if (month == 2)
    {
        if (leap && day > 29)
        {
            throw std::invalid_argument("Day must be between 1 and 29");
        }
        else if (!leap && day > 28)
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

bool Date::cmp(const Date &other)
{
    return (day == other.day && month == other.month && year == other.year);
}
char *Date::dateToStr() const
{
    
    char *str = new char[DATE_SIZE];
    int currentIndex = 0;
    if (day < exponent)
    {
        str[currentIndex++] = '0';
        str[currentIndex++] = day%exponent+48;
    }
    else
    {
        str[currentIndex++] = day/exponent+48;
        str[currentIndex++] = day%exponent+48;
    }
    str[currentIndex++] = '-';
    if(month<exponent)
    {
        str[currentIndex++] = '0';
        str[currentIndex++] = month%exponent+48;
    }
    else
    {
        str[currentIndex++] = month/exponent+48;
        str[currentIndex++] = month%exponent+48;
    }
    str[currentIndex++]='-';
    int del = std::pow(exponent,3);
    str[currentIndex++] = year/del + 48;
    str[currentIndex++] = (year%del)/(del/10) + 48;
    str[currentIndex++] = (year%(del/10))/(del/100)+48;
    str[currentIndex++] = year%exponent+48;
    str[currentIndex]='\0';
    return str;
}

bool less(Date first, Date second)
{
    if (first.year > second.year)
        return false;
    else if (first.year < second.year)
        return true;
    else
    {
        if (first.month > second.month)
            return false;
        else if (first.year < second.month)
            return true;
        else
        {
            if (first.day > second.day)
                return false;
            else return true;
        }
    }
}