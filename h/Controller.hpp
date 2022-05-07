#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include "Date.hpp"
#include "Hall.hpp"
#include "Act.hpp"
#include <fstream>

const size_t ACT_NAME_SIZE = 100;
const size_t PASS_SIZE = 16;
const size_t NOTE_SIZE = 128;
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
public:
    /// Constructor
    Controller();
    /// Destructor
    ~Controller();
    /// Function to load halls from file
    void loadHalls(char* fileName);
    /// Starting function
    void Run();

};

#endif