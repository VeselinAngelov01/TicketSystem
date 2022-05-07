#ifndef HALL_H
#define HALL_H

#include "Act.hpp"

const int DEF_ACT_SIZE = 10;
class Hall
{
private:
    unsigned int id;
    unsigned int rows;
    unsigned int sizeOfRow;
    Act** acts;
    int sizeOfActs;
    int capacityActs;

    void resize();
public:
    ///Constructor
    Hall(unsigned int id,unsigned int rows,unsigned int sizeOfRows);
    ///Destructor
    ~Hall();
    /// Add act to current hall
    void addAct(Act act);
    /// Return if there are no acts in current hall on this day
    bool isFree(Date date) const;
    /// Print all free places for specified act on daye
    void findOnDate(char* actName,Date date);
    /// Reserve ticket
    int findAndReserve(char* actName,Date date,unsigned int row,unsigned int place,char* password,char* note = nullptr);
    /// Remove reservation
    int removeReservation(char* actName,Date date,unsigned int row,unsigned int place,char* password);
    /// Buy ticket
    int buy(unsigned int row,unsigned int place,int actIndex,char* password=nullptr);
    /// Return all seats
    unsigned int getAllPlaces() const;
    /// Return hall id
    int getId() const;
    /// Return hall rows
    unsigned int getRows() const;
    /// Return hall length of row
    unsigned int getSizeOfRow() const;
    
    /// Return index of act in this hall\n
    /// (-1 if there is no act)
    int findAct(char* actName,Date date);
    /// Print all acts on all days
    void printAllActs() const;
    /// Print specified act on all days
    void printSpecificAct(char* name) const;
    /// Print all acts on specified day
    void printOnSpecificDate(Date date) const;
    /// Print act on date
    void print(char* name,Date date) const;
    /// Return ticket type\n
    /// (See more on Ticket.hpp)
    int specificTicketType(unsigned int row,unsigned int place,int actIndex);
    /// Print acts from date to date (inclusive)
    void printFromTo(Date firstDate,Date secondDate);
};

#endif