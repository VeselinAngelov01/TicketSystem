#ifndef HALL_H
#define HALL_H

#include "Date.hpp"
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
    Hall(unsigned int id,unsigned int rows,unsigned int sizeOfRows);
    ~Hall();

    void addAct(Act act);
    bool isFree(Date date) const;
    void findOnDate(char* actName,Date date);
    int findAndReserve(char* actName,Date date,unsigned int row,unsigned int place,char* password,char* note = nullptr);
    int removeReservation(char* actName,Date date,unsigned int row,unsigned int place,char* password);
    int buy(unsigned int row,unsigned int place,int actIndex);

    unsigned int getAllPlaces() const;
    int getId() const;
    unsigned int getRows() const;
    unsigned int getSizeOfRow() const;
    
    
    int findAct(char* actName,Date date);
    void printAllActs() const;
    void printSpecificAct(char* name) const;
    void printOnSpecificDate(Date date) const;
    void print(char* name,Date date) const;
};

#endif