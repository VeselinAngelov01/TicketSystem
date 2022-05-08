#ifndef TICKET_H
#define TICKET_H

#include "MyString.hpp"

class Ticket
{
private:
    unsigned int row;
    unsigned int place;
    MyString password;
    MyString note;
    int type;
    // 0 - free
    // 1 - reserved
    // 2 - sold
public:
    /// Consturctor
    Ticket();
    Ticket(unsigned int row,unsigned int place,int type);
    Ticket(unsigned int row,unsigned int place,int type,MyString password);
    Ticket(unsigned int row,unsigned int place,int type,MyString password,MyString note);
    /// Return ticket row
    unsigned int getRow() const;
    /// Return ticket seat
    unsigned int getColumn() const;
    /// Return ticket note\n
    MyString getNote() const;
    /// Return ticket password\n
    MyString getPass() const;
    /// Return ticket type
    int getType() const;
    /// Change type of ticket
    void changeType(unsigned int type);
    /// Write to file    
    friend std::ostream &operator<<(std::ostream &out, const Ticket &ticket);
};

#endif