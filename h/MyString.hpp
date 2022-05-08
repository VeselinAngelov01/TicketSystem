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
    /// Constructors
    MyString();
    MyString(const char* data);
    MyString(const MyString& other);
    /// Copy operator
    MyString& operator=(const MyString& other);
    /// Destructor
    ~MyString();
    /// Add symbol to string
    void append(char c);
    /// Return index of symbol in string
    /// If not exsist -> -1
    int find(char what,int startIndex=0);
    /// Return part of original string speicified by start and end index
    MyString subString(int startIndex,int endIndex);
    /// Return size of string
    unsigned int getSize() const;
    /// Return data of string in char*
    char* getData() const;
    /// Split string by delimiter
    MyString* splitString(char delimiter,int& sizeOfNewString);
    /// Write to file
    friend std::ostream &operator<<(std::ostream &out, const MyString &myString);

};

#endif