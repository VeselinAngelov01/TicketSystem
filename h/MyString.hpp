#ifndef MY_STRING_H
#define MY_STRING_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>

class MyString
{
private:
    char* data;
    unsigned int size;
    unsigned int capacity;

    void resize();

public:
    /// Default constructor
    MyString();
    /// Constructor with parameter
    MyString(const char* data);
    /// Copy constructor
    MyString(const MyString& other);
    /// Copy operator
    MyString& operator=(const MyString& other);
    /// Destructor
    ~MyString();
    /// Add symbol to string
    void append(char c);
    /// Return size of string
    unsigned int getSize() const;
    /// Return data of string in char*
    char* getData() const;
    /// Write to file
    friend std::ostream &operator<<(std::ostream &out, const MyString &myString);

};

#endif