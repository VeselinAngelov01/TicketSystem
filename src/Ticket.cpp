#include "../h/Ticket.hpp"

Ticket::Ticket()
{
    this->row = 0;
    this->place = 0;
    this->type = 0;
}
Ticket::Ticket(unsigned int row, unsigned int place, int type)
{
    this->row = row;
    this->place = place;
    this->type = type;
}
Ticket::Ticket(unsigned int row, unsigned int place, int type, MyString password)
{
    this->row = row;
    this->place = place;
    this->type = type;
    this->password = password;
}
Ticket::Ticket(unsigned int row, unsigned int place, int type, MyString password, MyString note)
{
    this->row = row;
    this->place = place;
    this->type = type;
    this->password = password;
    this->note = note;
}
unsigned int Ticket::getRow() const
{
    return this->row;
}

unsigned int Ticket::getColumn() const
{
    return this->place;
}

MyString Ticket::getNote() const
{
    return this->note;
}
MyString Ticket::getPass() const
{
    return this->password;
}

int Ticket::getType() const
{
    return this->type;
}

void Ticket::changeType(unsigned int type)
{
    this->type=type;
}

std::ostream &operator<<(std::ostream &out, const Ticket &ticket)
{
    out << ticket.getRow() << " " << ticket.getColumn() << " " << ticket.getType();
    if (ticket.getPass().getSize() > 0)
        out << " " << ticket.getPass();
    if (ticket.getNote().getSize() > 0)
        out << " " << ticket.getNote();
    return out;
}