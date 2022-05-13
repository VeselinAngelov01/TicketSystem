#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Hall.hpp"


class Controller
{
private:
    Hall** halls;
    unsigned int hallsCount;
    /// Default constructor
    Controller();
    /// Read day from standart input
    Date readDate();

    void help() const;
    void addEvent();
    void freeSpaces();
    void reserve();
    void rejectReserve();
    void buy();
    void listReservations();
    void sold();
    /// Read string from standart input
    MyString readString();
    /// Write data to file
    void writeToFile();
    /// Read data from file
    void readFromFile();
    /// Instance object
    static Controller* controller;
public:
    /// Return object
    static Controller* getController();
    /// Destructor
    ~Controller();
    /// Starting function
    void Run();
};

#endif