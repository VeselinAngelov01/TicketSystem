#ifndef ACT_H
#define ACT_H

#include "Date.hpp"
#include "Ticket.hpp"


class Act
{
private:
    
    MyString name;
    Date* date;
    Ticket* tickets;
    unsigned int reservedCount;
    unsigned int soldCount;
    unsigned int ticketsCount;
    unsigned int ticketCapacity;
    int findTicketIndex(unsigned int row,unsigned int column);
    void resize();

    void removeTicket(unsigned int ticketIndex);
public:
    /// Constructors
    Act(MyString name,Date date);
    Act(MyString name,Date date,Ticket* tickets,unsigned int reserved,unsigned int sold,unsigned int count,unsigned int capacity);
    Act(MyString name,Date date,unsigned int reserved,unsigned int sold,unsigned int count,unsigned int capacity);
    /// Destructor
    ~Act();
    /// Copy operator
    Act& operator=(const Act& other);
    /// Copy constructor
    Act(const Act& other);
    /// Reserve a ticket
    void reserveTicket(unsigned int row,unsigned int place,MyString password);
    /// Reserve a ticket
    void reserveTicket(unsigned int row,unsigned int place,MyString password,MyString note);
    /// Remove already reserved ticket
    void removeReservation(unsigned int row,unsigned int place,MyString password);
    /// Buy a ticket
    void buyTicket(unsigned int row,unsigned int place);
    /// Return  all reserved tickets
    unsigned int getReserved() const;
    /// Return  all sold tickets
    unsigned int getSold() const;
    /// Return total tickets;
    unsigned int getTotal() const;
    /// Return date of act
    Date getDate() const;
    /// Return name of act
    MyString getName() const;
    /// Print all tickets of specified type
    void printAll(unsigned int type) const;

    /// Write to file
    friend std::ostream &operator<<(std::ostream &out, const Act &act);
    /// Read from file
    void readFromFile(MyString fileName);

    /// Buffer for reading from file
    static const unsigned int BUFFER_SIZE=1024;
};

#endif