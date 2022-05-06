#include "Hall.hpp"

Hall::Hall(unsigned int id, unsigned int rows, unsigned int sizeOfRow)
{
    this->id = id;
    this->rows = rows;
    this->sizeOfRow = sizeOfRow;
    this->sizeOfActs = 0;
    this->capacityActs = DEF_ACT_SIZE;
    this->acts = new Act *[capacityActs];
}

Hall::~Hall()
{
    for (int i = 0; i < sizeOfActs; ++i)
    {
        delete this->acts[i];
    }
    delete[] this->acts;
}

void Hall::addAct(Act act)
{
    if (sizeOfActs == capacityActs)
    {
        resize();
    }
    for (int i = 0; i < sizeOfActs; ++i)
    {
        if (acts[i]->getDate().cmp(act.getDate()))
        {
            throw std::invalid_argument("There is act on this day!");
        }
    }
    *this->acts[sizeOfActs] = act;
    sizeOfActs++;
}

void Hall::resize()
{
    capacityActs *= 2;
    Act **temp = new Act *[capacityActs];
    for (int i = 0; i < sizeOfActs; ++i)
    {
        *temp[i] = *acts[i];
        delete acts[i];
    }
    delete[] acts;
    this->acts = temp;
}

bool Hall::isFree(Date date) const
{
    for (int i = 0; i < sizeOfActs; ++i)
    {
        if (acts[i]->getDate().cmp(date))
        {
            return false;
        }
    }
    return true;
}

void Hall::findOnDate(char *actName, Date date)
{
    for (int i = 0; i < sizeOfActs; ++i)
    {
        if (strcmp(acts[i]->getName(), actName) == 0)
        {
            std::cout << "Hall: " << id << " Free places: " << acts[i]->getFreePlaces() << "\n";
        }
    }
}

int Hall::findAndReserve(char *actName, Date date, unsigned int row, unsigned int place, char *password, char *note = nullptr)
{
    int res = findAct(actName, date);
    acts[res]->reserveTicket(row, place, password, note);
    return res;
}

int Hall::removeReservation(char *actName, Date date, unsigned int row, unsigned int place, char *password)
{
    int res = findAct(actName, date);
    acts[res]->removeReservation(row, place, password);
    return res;
}

int Hall::buy(unsigned int row, unsigned int place, int actIndex = 0)
{
    acts[actIndex]->buyTicket(row, place);
    return 0;
}

int Hall::findAct(char *actName, Date date)
{
    int res = -1;
    for (int i = 0; i < sizeOfActs; ++i)
    {
        if ((acts[i]->getName(), actName) == 0 && acts[i]->getDate().cmp(date))
        {
            res = i;
            break;
        }
    }
    return res;
}
unsigned int Hall::getAllPlaces() const
{
    return this->rows * this->sizeOfRow;
}

int Hall::getId() const
{
    return this->id;
}

unsigned int Hall::getRows() const
{
    return this->rows;
}

unsigned int Hall::getSizeOfRow() const
{
    return this->sizeOfRow;
}

void Hall::printAllActs() const
{
    for (int i = 0; i < sizeOfActs; ++i)
    {
        std::cout << acts[i]->getName() << " - " << acts[i]->getDate().dateToStr() << " ";
        acts[i]->printAllReserved();
    }
}

void Hall::printSpecificAct(char *name) const
{
    for (int i = 0; i < sizeOfActs; ++i)
    {
        if (strcmp(name, acts[i]->getName()) == 0)
            std::cout << acts[i]->getName() << " - " << acts[i]->getDate().dateToStr() << " ";
        acts[i]->printAllReserved();
    }
}
void Hall::printOnSpecificDate(Date date) const
{
    for (int i = 0; i < sizeOfActs; ++i)
    {
        if (acts[i]->getDate().cmp(date))
            std::cout << acts[i]->getName() << " - " << acts[i]->getDate().dateToStr() << " ";
        acts[i]->printAllReserved();
    }
}
void Hall::print(char *name, Date date) const
{
    for (int i = 0; i < sizeOfActs; ++i)
    {
        if (strcmp(name, acts[i]->getName()) == 0 && acts[i]->getDate().cmp(date))
            std::cout << acts[i]->getName() << " - " << acts[i]->getDate().dateToStr() << " ";
        acts[i]->printAllReserved();
    }
}