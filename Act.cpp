#include "Act.hpp"

Act::Act(char *name, unsigned int hallID, unsigned int rows, unsigned int places, Date date)
{
    this->hallID = hallID;
    this->date = new Date(date);
    this->reservedCount = 0;
    this->soldCount = 0;
    this->rows = rows;
    this->places = places;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    this->tickets = new Ticket *[rows];
    for (int i = 0; i < rows; ++i)
    {
        this->tickets[i] = new Ticket[places];
    }
}

Act::~Act()
{
    for (int i = 0; i < this->rows; ++i)
    {
        delete[] this->tickets[i];
    }
    delete[] this->tickets;
    delete[] this->name;
}

unsigned int Act::getFreePlaces() const
{
    return rows * places - reservedCount - soldCount;
}

void Act::reserveTicket(unsigned int row, unsigned int place, char *password, char *note)
{
    int type = this->tickets[row][place].getType();
    if (type == 2)
    {
        throw std::invalid_argument("Ticket is sold!");
    }
    else if (type == 1)
    {
        throw std::invalid_argument("Ticket is already reserved!");
    }
    else
    {
        this->tickets[row][place].change(row, place, 1, password, note);
        this->reservedCount++;
    }
}

void Act::removeReservation(unsigned int row, unsigned int place, char *password)
{
    int type = this->tickets[row][place].getType();
    if (type == 2)
    {
        throw std::invalid_argument("Ticket is sold!");
    }
    else if (type == 0)
    {
        throw std::invalid_argument("Ticket is not reserved!");
    }
    else
    {
        if (strcmp(password, this->tickets[row][place].getPass()) == 0)
        {
            this->tickets[row][place].change(row, place, 0, password);
            this->reservedCount--;
        }
        else
            throw std::invalid_argument("Wrong password!");
    }
}

void Act::buyTicket(unsigned int row, unsigned int place,char* password)
{
    int type = this->tickets[row][place].getType();
    if (type == 2)
    {
        throw std::invalid_argument("Ticket is sold!");
    }
    else if (type == 1)
    {
        if(strcmp(this->tickets[row][place].getPass(),password)==0)
        {
            this->tickets[row][place].change(row, place, 2);
            this->soldCount++;
        }
        else throw std::invalid_argument("Invalid password!");
    }
    else
    {
        this->tickets[row][place].change(row, place, 2);
        this->soldCount++;
    }
}

void Act::printAllReserved() const
{
    int cnt = 0;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < places; ++j)
        {
            if (tickets[i][j].getType() == 1)
            {
                cnt++;
            }
        }
    }
    std::cout << cnt << "\n";
}

void Act::printAllSold() const
{
    int cnt = 0;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < places; ++j)
        {
            if (tickets[i][j].getType() == 2)
            {
                cnt++;
            }
        }
    }
    std::cout << cnt << "\n";
}

Act::Act(Act &other)
{

    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);
    this->date = new Date(other.getDate());

    this->hallID = other.hallID;
    this->rows = other.rows;
    this->places = other.places;
    this->reservedCount = other.reservedCount;
    this->soldCount = other.soldCount;
    this->tickets = new Ticket *[rows];
    for (int i = 0; i < rows; ++i)
    {
        this->tickets[i] = new Ticket[places];
        for (int j = 0; j < places; ++j)
        {
            this->tickets[i][j] = other.tickets[i][j];
        }
    }
}
Act &Act::operator=(Act &other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] this->name;
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);
    delete[] this->date;
    this->date = new Date(other.getDate());
    this->hallID = other.hallID;
    for (int i = 0; i < rows; ++i)
    {
        delete[] this->tickets[i];
    }
    delete[] this->tickets;
    this->rows = other.rows;
    this->places = other.places;
    this->reservedCount = other.reservedCount;
    this->soldCount = other.soldCount;
    this->tickets = new Ticket *[rows];
    for (int i = 0; i < rows; ++i)
    {
        this->tickets[i] = new Ticket[places];
        for (int j = 0; j < places; ++j)
        {
            this->tickets[i][j] = other.tickets[i][j];
        }
    }
    return *this;
}

Date Act::getDate() const
{
    return *this->date;
}

char *Act::getName() const
{
    return this->name;
}

int Act::viewTicketType(unsigned int row, unsigned int place) const
{
    return this->tickets[row][place].getType();
}