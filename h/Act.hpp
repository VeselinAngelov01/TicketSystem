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
    /// Constructor
    Act(char* name,unsigned int hallID,unsigned int rows,unsigned int places,Date date);
    /// Destructor
    ~Act();
    /// Copy operator
    Act& operator=(Act& other);
    /// Copy constructor
    Act(Act& other);
    /// Return all places that are not reserved and sold
    unsigned int getFreePlaces() const;
    /// Reserve a ticket
    void reserveTicket(unsigned int row,unsigned int place,char* password,char* note = nullptr);
    /// Remove already reserved ticket
    void removeReservation(unsigned int row,unsigned int place,char* password);
    /// Buy a ticket
    void buyTicket(unsigned int row,unsigned int place,char* password = nullptr);
    /// Prints all reserved tickets
    void printAllReserved() const;
    /// Prints all sold tickets
    void printAllSold() const;
    /// Return date of act
    Date getDate() const;
    /// Return name of act
    char* getName() const;
    /// Return type of specific ticket\n
    /// 0 - free\n
    /// 1 - reserved\n
    /// 2 - sold
    int viewTicketType(unsigned int row,unsigned int place) const;
};

#endif