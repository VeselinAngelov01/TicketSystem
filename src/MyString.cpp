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
int MyString::find(char what, int startIndex)
{
    for(int i=startIndex;i<size;++i)
    {
        if(data[i]==what) return i;
    }
    return -1;
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
MyString MyString::subString(int startIndex, int endIndex)
{
    MyString result;
    for(int i=startIndex;i<=endIndex;++i)
    {
        result.append(data[i]);
    }
    return result;
}
unsigned int MyString::getSize() const
{
    return this->size;
}
char *MyString::getData() const
{
    return this->data;
}

MyString* MyString::splitString(char delimiter,int& sizeOfNewString)
{
    int cntOfDel = 0;
    for(int i=0;i<size;++i)
    {
        if(data[i]==delimiter) cntOfDel++;
    }
    MyString* arrOfMyStrings = new MyString[cntOfDel];
    int prevIndexDel = 0;
    int currIndexDel = find(delimiter);
    while(prevIndexDel!=-1)
    {
        if(currIndexDel==-1)
        {
            arrOfMyStrings[sizeOfNewString] = subString(prevIndexDel,size-1);
            prevIndexDel=-1;
        }
        else if(sizeOfNewString==0) arrOfMyStrings[sizeOfNewString++]=subString(prevIndexDel,currIndexDel-1);
        else
        {
            arrOfMyStrings[sizeOfNewString++]=subString(prevIndexDel+1,currIndexDel-1);
        }
        prevIndexDel = currIndexDel;
        currIndexDel = find(delimiter,prevIndexDel+1);
    }
    return arrOfMyStrings;
}

std::ostream &operator<<(std::ostream &out, const MyString &myString)
{
    out<<myString.getData();
    return out;
}