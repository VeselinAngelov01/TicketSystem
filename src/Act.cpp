#include "../h/Act.hpp"

Act::Act(MyString name, Date date)
{
    this->date = new Date(date);
    this->reservedCount = 0;
    this->soldCount = 0;
    this->ticketsCount = 0;
    this->tickets = nullptr;
    this->ticketCapacity = 1;
    this->name = name;
}

Act::Act(MyString name, Date date, Ticket *tickets, unsigned int reserved, unsigned int sold, unsigned int count, unsigned int capacity)
{
    this->name = name;
    this->date = new Date(date);
    this->reservedCount = reserved;
    this->soldCount = sold;
    this->ticketsCount = count;
    this->ticketCapacity = capacity;
    this->tickets = new Ticket[ticketsCount];
    for (int i = 0; i < ticketsCount; ++i)
    {
        this->tickets[i] = tickets[i];
    }
}

Act::Act(MyString name, Date date, unsigned int reserved, unsigned int sold, unsigned int count, unsigned int capacity)
{
    this->name = name;
    this->date = new Date(date);
    this->reservedCount = reserved;
    this->soldCount = sold;
    this->ticketsCount = count;
    this->ticketCapacity = capacity;
    this->tickets = new Ticket[ticketsCount];
}
Act::~Act()
{
    delete this->date;
    if (tickets)
        delete[] tickets;
}

void Act::resize()
{
    this->ticketCapacity *= 2;
    Ticket *newTickets = new Ticket[ticketCapacity];
    for (int i = 0; i < ticketsCount; ++i)
    {
        newTickets[i] = this->tickets[i];
    }
    delete[] this->tickets;
    this->tickets = newTickets;
}

int Act::findTicketIndex(unsigned int row, unsigned int column)
{
    for (int i = 0; i < ticketsCount; ++i)
    {
        if (tickets[i].getRow() == row && tickets[i].getColumn() == column)
            return i;
    }
    return -1;
}

void Act::reserveTicket(unsigned int row, unsigned int place, MyString password)
{
    int index = findTicketIndex(row, place);
    if (index == -1)
    {
        // seat if free -> reserve
        Ticket temp(row, place, 1, password);
        if (!tickets)
            tickets = new Ticket[ticketCapacity];
        else if (ticketsCount >= ticketCapacity)
            resize();

        this->tickets[ticketsCount++] = temp;
        this->reservedCount++;
    }
    else
    {
        int type = this->tickets[index].getType();
        if (type == 1)
            throw std::invalid_argument("Place is already reserved!");
        else if (type == 2)
            throw std::invalid_argument("Place is sold!");
        else
            throw std::logic_error("Act.cpp func reserveTicket");
    }
}

void Act::reserveTicket(unsigned int row, unsigned int place, MyString password, MyString note)
{
    int index = findTicketIndex(row, place);
    if (index == -1)
    {
        // seat if free -> reserve
        Ticket temp(row, place, 1, password, note);
        if (!tickets)
            tickets = new Ticket[ticketCapacity];
        else if (ticketsCount >= ticketCapacity)
            resize();
        this->tickets[ticketsCount++] = temp;
        this->reservedCount++;
    }
    else
    {
        int type = this->tickets[index].getType();
        if (type == 1)
            throw std::invalid_argument("Place is already reserved!");
        else if (type == 2)
            throw std::invalid_argument("Place is sold!");
        else
            throw std::logic_error("Act.cpp func reserveTicket");
    }
}

void Act::removeTicket(unsigned int ticketIndex)
{
    this->ticketsCount--;
    for (int i = ticketIndex; i < ticketsCount; ++i)
    {
        this->tickets[i] = this->tickets[i + 1];
    }
}
void Act::removeReservation(unsigned int row, unsigned int place, MyString password)
{
    int index = findTicketIndex(row, place);
    if (index == -1)
        throw std::invalid_argument("There is no reservation!");
    int type = this->tickets[index].getType();
    if (type == 2)
        throw std::invalid_argument("Ticket is sold!");
    else if (type == 1)
    {
        removeTicket(index);
        reservedCount--;
    }
    else
        throw std::logic_error("Act.cpp func removeReservation");
}

void Act::buyTicket(unsigned int row, unsigned int place)
{
    int index = findTicketIndex(row, place);
    if (index == -1)
    {
        Ticket temp(row, place, 2);
        if (!tickets)
            tickets = new Ticket[ticketCapacity];
        else if (ticketsCount >= ticketCapacity)
            resize();
        this->tickets[ticketsCount++] = temp;
        this->soldCount++;
    }
    else
    {

        int type = this->tickets[index].getType();
        if (type == 2)
            throw std::invalid_argument("Ticket is sold!");
        else if (type == 1)
        {
            std::cout << "Ticket is already reserved! Enter password: ";
            char buffer[BUFFER_SIZE];
            std::cin >> buffer;
            MyString pass(buffer);
            if (strcmp(pass.getData(), tickets[index].getPass().getData()) == 0)
            {
                reservedCount--;
                soldCount++;
                tickets[index].changeType(2);
            }
            else
            {
                std::cout << "Wrong password!\n";
            }
        }
        else
            throw std::logic_error("Act.cpp func buy ticket");
    }
}

unsigned int Act::getReserved() const
{
    return this->reservedCount;
}

unsigned int Act::getSold() const
{
    return this->soldCount;
}

Act::Act(const Act &other)
{
    this->name = other.name;
    this->date = new Date(other.getDate());
    this->reservedCount = other.reservedCount;
    this->soldCount = other.soldCount;
    this->tickets = new Ticket[other.ticketCapacity];
    this->ticketsCount = other.ticketsCount;
    this->ticketCapacity = other.ticketCapacity;
    for (int i = 0; i < ticketsCount; ++i)
    {
        this->tickets[i] = other.tickets[i];
    }
}
Act &Act::operator=(const Act &other)
{
    if (this == &other)
    {
        return *this;
    }
    this->name = other.name;
    delete this->date;
    this->date = new Date(other.getDate());
    this->reservedCount = other.reservedCount;
    this->soldCount = other.soldCount;
    if (tickets)
        delete[] this->tickets;
    this->tickets = new Ticket[other.ticketsCount];
    this->ticketsCount = other.ticketsCount;
    return *this;
}

Date Act::getDate() const
{
    return *this->date;
}

MyString Act::getName() const
{
    return this->name;
}
unsigned int Act::getTotal() const
{
    return this->ticketsCount;
}

std::ostream &operator<<(std::ostream &out, const Act &act)
{
    out << act.name << " " << act.getDate() << " " << act.ticketCapacity << " " << act.getTotal() << " " << act.getReserved() << " " << act.getSold() << " ";
    unsigned int ticketCount = act.getTotal();
    MyString fileName(act.getName());
    fileName.append('.');
    fileName.append('t');
    fileName.append('x');
    fileName.append('t');
    out << fileName;
    std::ofstream writer(fileName.getData());
    if (writer.is_open())
    {
        writer << act.getTotal() << '\n';
        for (int i = 0; i < ticketCount; ++i)
        {
            writer << act.tickets[i] << '\n';
        }
        writer.close();
    }
    else
        throw std::invalid_argument("Can not open Tickets.txt");
    return out;
}

void Act::printAll(unsigned int type) const
{
    for (int i = 0; i < ticketsCount; ++i)
    {
        if (tickets[i].getType() == type)
        {
            std::cout << tickets[i].getRow() << "-" << tickets[i].getColumn() << '\n';
        }
    }
}

void Act::readFromFile(MyString fileName)
{
    std::ifstream reader;
    try
    {
        reader.open(fileName.getData(), std::ios::in);
        char buffer[BUFFER_SIZE];
        char secondBuff[BUFFER_SIZE];
        if (reader.is_open())
        {
            reader >> buffer;
            this->ticketsCount = std::stoi(buffer);
            this->tickets = new Ticket[ticketsCount];
            this->ticketCapacity = ticketsCount;
            int currentTicket = 0;
            unsigned int row, place;
            int type;
            while (reader >> row >> place >> type)
            {
                if (currentTicket >= ticketsCount)
                    throw std::invalid_argument("Invalid data in file Ticket.txt");

                char c;
                reader.get(c);
                if (c != '\n')
                {
                    reader >> buffer;
                    reader.get(c);
                    MyString pass(buffer);
                    if (c != '\n')
                    {
                        reader >> secondBuff;
                        MyString note(secondBuff);
                        Ticket t(row, place, type, pass, note);
                        this->tickets[currentTicket++] = t;
                    }
                    else
                    {
                        Ticket t(row, place, type, pass);
                        this->tickets[currentTicket++] = t;
                    }
                }
                else
                {
                    Ticket t(row, place, type);
                    this->tickets[currentTicket++] = t;
                }
                
                    
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