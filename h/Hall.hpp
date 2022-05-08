#ifndef HALL_H
#define HALL_H

#include "Act.hpp"
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
    Hall(unsigned int id,unsigned int rows,unsigned int sizeOfRows,unsigned int sizeOfActs);
    ///Destructor
    ~Hall();
    /// Add act to current hall
    void addAct(Act act);
    /// Return if there are no acts in current hall on this day
    bool isFree(Date date) const;
    /// Print all free places for specified act on daye
    void findOnDate(MyString actName,Date date);
    /// Reserve ticket
    int findAndReserve(MyString actName,Date date,unsigned int row,unsigned int place,MyString password);
    int findAndReserve(MyString actName,Date date,unsigned int row,unsigned int place,MyString password,MyString note);
    /// Remove reservation
    int removeReservation(MyString actName,Date date,unsigned int row,unsigned int place,MyString password);
    /// Buy ticket
    void buy(unsigned int actIndex,unsigned int row,unsigned int place);
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
    int findAct(MyString actName,Date date);
    /// Print all acts on all days
    void printAllActs() const;
    /// Print specified act on all days
    void printSpecificAct(MyString name) const;
    /// Print all acts on specified day
    void printOnSpecificDate(Date date) const;
    /// Print act on date
    void print(MyString name,Date date) const;
    /// Return ticket type\n
    /// (See more on Ticket.hpp)
    /// Print acts from date to date (inclusive)
    void printFromTo(Date firstDate,Date secondDate);
    /// Write to file
    friend std::ostream &operator<<(std::ostream &out, const Hall &hall);
    /// Read from file
    void readFromFile(MyString file);
    /// Return size of all acts in current hall
    unsigned int getSizeOfActs() const;
};

#endif