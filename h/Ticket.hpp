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
    /// Consturctor
    Ticket();
    /// Destructor
    ~Ticket();
    /// Copy operator
    Ticket& operator=(Ticket& other);
    /// Return ticket row
    unsigned int getRow() const;
    /// Return ticket seat
    unsigned int getColumn() const;
    /// Return ticket note\n
    /// Possible to return nullptr if there is no note added
    char* getNote() const;
    /// Return ticket password\n
    /// Possible to return nullptr if there is no password (Ticket is free or sold)
    char* getPass() const;
    /// Return ticket type
    int getType() const;
    /// Return change ticket status (type)
    void change(unsigned int row,unsigned int place,int newType,char* password=nullptr,char* note = nullptr);
};

#endif