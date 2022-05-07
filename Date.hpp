#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <cmath>
const unsigned int DATE_SIZE = 11;
const int exponent = 10;
class Date
{
private:
    unsigned int day;
    unsigned int month;
    unsigned int year;
public:
    Date(unsigned int day,unsigned int month,unsigned int year);

    unsigned int getDay() const;
    unsigned int getMonth() const;
    unsigned int getYear() const;

    char* dateToStr() const;

    bool cmp(const Date& other);

    friend bool less(Date first,Date second);
};

#endif