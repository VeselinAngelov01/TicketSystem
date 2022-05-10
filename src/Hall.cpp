#include "../h/Hall.hpp"

Hall::Hall(unsigned int id, unsigned int rows, unsigned int sizeOfRow)
{
    this->id = id;
    this->rows = rows;
    this->sizeOfRow = sizeOfRow;
    this->sizeOfActs = 0;
    this->capacityActs = 1;
    this->acts = nullptr;
}

Hall::Hall(unsigned int id, unsigned int rows, unsigned int sizeOfRows, unsigned int sizeOfActs)
{
    this->id = id;
    this->rows = rows;
    this->sizeOfRow = sizeOfRows;
    this->sizeOfActs = sizeOfActs;
    this->capacityActs = sizeOfActs;
    this->acts = new Act*[sizeOfActs];
}

Hall::~Hall()
{
    for (int i = 0; i < sizeOfActs; ++i)
    {
        if(this->acts[i]) delete this->acts[i];
    }
    delete[] this->acts;
}

void Hall::addAct(Act act)
{
    if (!acts)
        this->acts = new Act *[capacityActs];
    else if (sizeOfActs == capacityActs)
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
    this->acts[sizeOfActs] = new Act(act);
    sizeOfActs++;
}

void Hall::resize()
{
    capacityActs *= 2;
    Act **temp = new Act *[capacityActs];
    for (int i = 0; i < sizeOfActs; ++i)
    {
        temp[i] = new Act(*acts[i]);
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

void Hall::findOnDate(MyString actName, Date date)
{
    for (int i = 0; i < sizeOfActs; ++i)
    {
        if (strcmp(acts[i]->getName().getData(), actName.getData()) == 0)
        {
            std::cout << "Hall: " << id << " Free places: " << rows * sizeOfRow - acts[i]->getTotal() << "\n";
        }
    }
}

int Hall::findAndReserve(MyString actName, Date date, unsigned int row, unsigned int place, MyString password, MyString note)
{
    if (row > rows || place > sizeOfRow)
        throw std::invalid_argument("Invalid row/place!");
    int res = findAct(actName, date);
    if (res != -1)
        acts[res]->reserveTicket(row, place, password, note);
    return res;
}

int Hall::findAndReserve(MyString actName, Date date, unsigned int row, unsigned int place, MyString password)
{
    if (row > rows || place > sizeOfRow)
        throw std::invalid_argument("Invalid row/place!");
    int res = findAct(actName, date);
    if (res != -1)
        acts[res]->reserveTicket(row, place, password);
    return res;
}

int Hall::removeReservation(MyString actName, Date date, unsigned int row, unsigned int place, MyString password)
{
    if (row > rows || place > sizeOfRow)
        throw std::invalid_argument("Invalid row/place!");
    int res = findAct(actName, date);
    if (res != -1)
        acts[res]->removeReservation(row, place, password);
    return res;
}

void Hall::buy(unsigned int actIndex, unsigned int row, unsigned int place)
{
    if (row > rows || place > sizeOfRow)
        throw std::invalid_argument("Invalid row/place!");
    acts[actIndex]->buyTicket(row, place);
}

int Hall::findAct(MyString actName, Date date)
{
    int res = -1;
    for (int i = 0; i < sizeOfActs; ++i)
    {
        if (strcmp(acts[i]->getName().getData(), actName.getData()) == 0 && acts[i]->getDate().cmp(date))
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
        std::cout << acts[i]->getName().getData() << " - " << acts[i]->getDate().dateToStr() << '\n';
        acts[i]->printAll(1);
    }
}

void Hall::printSpecificAct(MyString name) const
{
    for (int i = 0; i < sizeOfActs; ++i)
    {
        if (strcmp(name.getData(), acts[i]->getName().getData()) == 0)
        {
            std::cout << acts[i]->getName() << " - " << acts[i]->getDate().dateToStr() << '\n';
            acts[i]->printAll(1);
        }
    }
}
void Hall::printOnSpecificDate(Date date) const
{
    for (int i = 0; i < sizeOfActs; ++i)
    {
        if (acts[i]->getDate().cmp(date))
        {
            std::cout << acts[i]->getName() << " - " << acts[i]->getDate().dateToStr() << '\n';
            acts[i]->printAll(1);
        }
    }
}
void Hall::print(MyString name, Date date) const
{
    for (int i = 0; i < sizeOfActs; ++i)
    {
        if (strcmp(name.getData(), acts[i]->getName().getData()) == 0 && acts[i]->getDate().cmp(date))
        {
            std::cout << acts[i]->getName() << " - " << acts[i]->getDate().dateToStr() << '\n';
            acts[i]->printAll(1);
        }
    }
}

void Hall::printFromTo(Date firstDate, Date secondDate)
{
    for (int i = 0; i < sizeOfActs; ++i)
    {
        if (less(firstDate, acts[i]->getDate()) && less(acts[i]->getDate(), secondDate))
        {
            std::cout << acts[i]->getName() << '\n';
            acts[i]->printAll(2);
        }
    }
}

unsigned int Hall::getSizeOfActs() const
{
    return this->sizeOfActs;
}

std::ostream &operator<<(std::ostream &out, const Hall &hall)
{
    out << hall.getId() << " " << hall.getRows() << " " << hall.getSizeOfRow() << " " << hall.getSizeOfActs() << " ";
    MyString fileName((std::to_string(hall.getId())).c_str());
    fileName.append('.');
    fileName.append('t');
    fileName.append('x');
    fileName.append('t');
    out << fileName;
    std::ofstream writer(fileName.getData());
    if (writer.is_open())
    {
        writer << hall.getSizeOfActs()<<'\n';
        for (int i = 0; i < hall.getSizeOfActs(); ++i)
        {
            writer << *hall.acts[i] << '\n';
        }
        writer.close();
    }
    else
        throw std::invalid_argument("Can not open file Acts.txt");
    return out;
}


void Hall::readFromFile(MyString file)
{
    std::ifstream reader;
    try
    {
        reader.open(file.getData(), std::ios::in);
        char buffer[Act::BUFFER_SIZE];
        if (reader.is_open())
        {
            reader >> buffer;
            this->sizeOfActs = std::stoi(buffer);
            this->acts = new Act *[sizeOfActs];
            this->capacityActs = sizeOfActs;
            
            int currentAct = 0;
            char nameBuffer[Act::BUFFER_SIZE],nextFile[Act::BUFFER_SIZE];
            unsigned int ticketCapacity,ticketSize,reservedCount,soldCount;
            unsigned int day,month,year;
            while (reader >> nameBuffer >> day >> month >> year >> ticketCapacity >> ticketSize>> reservedCount>> soldCount>> nextFile)
            {
                if (currentAct >= sizeOfActs)
                    throw std::invalid_argument("Invalid data in file Act.txt");
                MyString name(nameBuffer),next(nextFile); 
                Date date(day,month,year);
                this->acts[currentAct] = new Act(name,date,reservedCount,soldCount,ticketSize,ticketCapacity);
                this->acts[currentAct++]->readFromFile(next);
            }
            reader.close();
        }
        else
            throw std::invalid_argument("Can not read from file!");
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
    }
}