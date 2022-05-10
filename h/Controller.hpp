#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Hall.hpp"


class Controller
{
private:
    Hall** halls;
    unsigned int hallsCount;
    /// Constructor
    Controller();
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

    /// Write data to file
    void writeToFile();
    /// Read data from file
    void readFromFile();
public:
    /// Function to initialize object
    static Controller& instance();
    /// Destructor
    ~Controller();
    /// Starting function
    void Run();
    

};

#endif