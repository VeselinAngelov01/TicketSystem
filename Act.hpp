#ifndef ACT_H
#define ACT_H

#include <cstring>
#include "Date.hpp"
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
    void reserveTicket(unsigned int row,unsigned int place,char* password,char* note = nullptr);
    void removeReservation(unsigned int row,unsigned int place,char* password);
    void buyTicket(unsigned int row,unsigned int place,char* password = nullptr);

    void printReserved() const;

    Date getDate() const;

    Act& operator=(Act& other);
    Act(Act& other);

    char* getName() const;
    //unsigned int getFreePlaces() const;
    void printAllReserved() const;
    void printAllSold() const;

    int viewTicketType(unsigned int row,unsigned int place) const;
};

#endif