#include "Act.hpp"

Act::Act(char* name,unsigned int hallID,unsigned int rows,unsigned int places,Date date)
{
    this->hallID = hallID;
    this->date = new Date(date);
    this->reservedCount = 0;
    this->soldCount = 0;
    this->rows = rows;
    this->places = places;
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
    this->tickets = new Ticket*[rows];
    for(int i=0;i<places;++i)
    {
        this->tickets[i] = new Ticket();
    }
}

Act::~Act()
{
    for(int i=0;i<this->rows;++i)
    {
        delete this->tickets[i];
    }
    delete [] this->tickets;
    delete [] this->name;
}

unsigned int Act::getFreePlaces() const
{
    return rows*places-reservedCount-soldCount;
}

bool Act::reserveTicket(unsigned int row,unsigned int place,char* password,char* note = nullptr)
{
    int type = this->tickets[row][place].getType();
    if(type==2)
    {
        throw std::invalid_argument("Ticket is sold!");
    }
    else if(type==1)
    {
        throw std::invalid_argument("Ticket is already reserved!");
    }
    else
    {
        this->tickets[row][place].change(row,place,1,password,note);
    }
}

bool Act::removeReservation(unsigned int row,unsigned int place,char* password)
{
    int type = this->tickets[row][place].getType();
    if(type==2)
    {
        throw std::invalid_argument("Ticket is sold!");
    }
    else if(type==0)
    {
        throw std::invalid_argument("Ticket is not reserved!");
    }
    else
    {
        if(strcmp(password,this->tickets[row][place].getPass())==0)
        {
            this->tickets[row][place].change(row,place,0,password);
        }
        throw std::invalid_argument("Wrong password!");
    }
}

bool Act::buyTicket(unsigned int row,unsigned int place)
{
    int type = this->tickets[row][place].getType();
    if(type==2)
    {
        throw std::invalid_argument("Ticket is sold!");
    }
    else if(type==1)
    {
        throw std::invalid_argument("Ticket is reserved!");
    }
    else
    {
        this->tickets[row][place].change(row,place,2);
    }
}

void Act::printAllReserved() const
{
    int cnt = 0;
    for(int i=0;i<rows;++i)
    {
        for(int j=0;j<places;++j)
        {
            if(tickets[i][j].getType()==1)
            {
                cnt++;
            }
        }
    }
    std::cout<<cnt<<"\n";
}

Act& Act::operator=(const Act& other)
{
    if(this==&other)
    {
        return *this;
    }

    
}