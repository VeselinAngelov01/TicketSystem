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
    MyString();
    MyString(const char* data);
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);
    ~MyString();
    void append(char c);
    int find(char what,int startIndex=0);
    MyString subString(int startIndex,int endIndex);
    unsigned int getSize() const;
    char* getData() const;

    friend std::ostream &operator<<(std::ostream &out, const MyString &myString);

};

#endif