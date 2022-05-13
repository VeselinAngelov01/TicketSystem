#include "../h/MyString.hpp"

MyString::MyString()
{
    this->capacity = 1;
    this->size = 0;
    this->data = new char[capacity];
    this->data[size]='\0';
}
MyString::MyString(const char *data)
{
    this->size = strlen(data);
    this->capacity = this->size+1;
    this->data = new char[capacity];
    strcpy(this->data,data);
}
MyString::MyString(const MyString &other)
{
    this->size = other.size;
    this->capacity = other.capacity;
    this->data = new char[capacity];
    strcpy(this->data,other.data);
}
MyString &MyString::operator=(const MyString &other)
{
    if(this==&other)
    {
        return *this;
    }
    this->size = other.size;
    this->capacity = other.capacity;
    this->data = new char[capacity];
    strcpy(this->data,other.data);
    return *this;
}
MyString::~MyString()
{
    delete [] this->data;
}

void MyString::resize()
{
    this->capacity *=2;
    char* newData = new char[capacity];
    for(int i=0;i<size;++i)
    {
        newData[i]=data[i];
    }
    newData[size+1]='\0';
    delete [] data;
    this->data = newData;
}

void MyString::append(char c)
{
    if(size>=capacity-1)
    {
        resize();
    }
    data[size++]=c;
    data[size]='\0';
}

unsigned int MyString::getSize() const
{
    return this->size;
}
char *MyString::getData() const
{
    return this->data;
}


std::ostream &operator<<(std::ostream &out, const MyString &myString)
{
    out<<myString.getData();
    return out;
}