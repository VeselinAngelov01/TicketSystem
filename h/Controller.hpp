#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Hall.hpp"


class Controller
{
private:
    Hall** halls;
    unsigned int hallsCount;

    Date readDate();

    void help() const;
    void addEvent();
    void freeSpaces();
    void reserve();
    void rejectReserve();
    void buy();
    void listReservations();
    void sold();

    MyString readString();
public:
    /// Constructor
    Controller();
    /// Destructor
    ~Controller();
    /// Starting function
    void Run();
    /// Write data to file
    void writeToFile();
    /// Read data from file
    void readFromFile();

};

#endif