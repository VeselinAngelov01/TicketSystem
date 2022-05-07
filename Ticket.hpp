#ifndef TICKET_H
#define TICKET_H

#include <cstring>

class Ticket
{
private:
    unsigned int row;
    unsigned int place;
    char* password;
    char* note;
    int type;
    // 0 - free
    // 1 - reserved
    // 2 - sold
public:
    Ticket();
    ~Ticket();

    Ticket& operator=(Ticket& other);

    unsigned int getRow() const;
    unsigned int getColumn() const;
    char* getNote() const;
    char* getPass() const;
    int getType() const;

    void change(unsigned int row,unsigned int place,int newType,char* password=nullptr,char* note = nullptr);
};

#endif