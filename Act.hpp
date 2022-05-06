#ifndef ACT_H
#define ACT_H

#include <cstring>
#include "Hall.hpp"
#include "Ticket.hpp"
class Act
{
private:
    char* name;
    Date* date;
    int hallID;
    Ticket** tickets;
    unsigned int rows;
    unsigned int places;
    unsigned int reservedCount;
    unsigned int soldCount;
public:
    Act(char* name,unsigned int hallID,unsigned int rows,unsigned int places,Date date);
    ~Act();

    unsigned int getFreePlaces() const;
    bool reserveTicket(unsigned int row,unsigned int place,char* password,char* note = nullptr);
    bool removeReservation(unsigned int row,unsigned int place,char* password);
    bool buyTicket(unsigned int row,unsigned int place);

    void printReserved() const;

    Date getDate() const;

    Act& operator=(const Act& other);

    char* getName() const;
    //unsigned int getFreePlaces() const;
    void printAllReserved() const;
};

#endif