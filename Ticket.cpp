#include "Ticket.hpp"

Ticket::Ticket()
{
    this->row = 0;
    this->place = 0;
    this->password = nullptr;
    this->note = nullptr;
    this->type = 0;
}
/*
Ticket::Ticket(unsigned int row,unsigned int place)
{
    this->row = row;
    this->place = place;
    this->password = nullptr;
    this->note = nullptr;
}

Ticket::Ticket(unsigned int row,unsigned int place,char* password)
{
    this->row = row;
    this->place = place;
    this->password = new char[strlen(password)+1];
    strcpy(this->password,password);
    this->note = nullptr;
}

Ticket::Ticket(unsigned int row,unsigned int place,char* password,char* note)
{
    this->row = row;
    this->place = place;
    this->password = new char[strlen(password)+1];
    strcpy(this->password,password);
    this->note = new char[strlen(note)+1];
    strcpy(this->note,note);
}
*/
Ticket::~Ticket()
{
    if(password) delete [] this->password;
    if(note) delete [] this->note;
}

unsigned int Ticket::getRow() const
{
    return this->row;
}

unsigned int Ticket::getColumn() const
{
    return this->place;
}

// possible to return nullptr
char* Ticket::getNote() const
{
    return this->note;
}
// possible to return nullptr
char* Ticket::getPass() const
{
    return this->password;
}

int Ticket::getType() const
{
    return this->type;
}

void Ticket::change(unsigned int row,unsigned int place,int newType,char* password=nullptr,char* note = nullptr)
{
    this->row =row;
    this->place = place;
    if(this->password) delete [] this->password;
    this->password = new char [strlen(password)+1];
    strcpy(this->password,password);
    if(note)
    {
        if(this->note) delete [] this->note;
        this->note = new char[strlen(note)+1];
        strcpy(this->note,note);
    }
    else if(this->note)
    {
        delete [] this->note;
    }
    this->type = newType;
}
/*
Ticket& Ticket::operator=(const Ticket& other)
{
    this->row=other.row;
    this->place = other.place;
    if(other.password)
    {
        if(this->password) delete [] this->password;
        this->password = new char[strlen(other.password)+1];
        strcpy(this->password,other.password);
    }
    else
    {
        if(this->password) delete [] this->password;
        this->password = nullptr;
    }
    if(other.note) 
    {
        if(this->note) delete [] this->note;
        this->note = new char[strlen(other.note)+1];
        strcpy(this->note,other.note);
    }
    else 
    {
        if(this->note) delete [] this->note;
        this->note = nullptr;
    }
}*/