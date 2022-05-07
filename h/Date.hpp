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
    /// Constructor
    Date(unsigned int day,unsigned int month,unsigned int year);
    /// Return day
    unsigned int getDay() const;
    /// Return month
    unsigned int getMonth() const;
    /// Return year
    unsigned int getYear() const;
    /// Return day in string format
    char* dateToStr() const;
    /// Compare if two dates are equal
    bool cmp(const Date& other);
    /// Return if date is early than other date
    friend bool less(Date first,Date second);
};

#endif