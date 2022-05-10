#include "../h/Controller.hpp"

Controller::Controller()
{
    this->halls = new Hall *[2];
    this->hallsCount = 2;
    this->halls[0] = new Hall(1, 50, 50);
    this->halls[1] = new Hall(2, 10, 30);
}

Controller &Controller::instance()
{
    static Controller inst;
    inst.readFromFile();
    return inst;
}
Controller::~Controller()
{
    for (size_t i = 0; i < this->hallsCount; ++i)
    {
        delete this->halls[i];
    }
    delete[] this->halls;
}

MyString Controller::readString()
{
    char BUFFER[Act::BUFFER_SIZE];
    std::cin >> BUFFER;
    MyString res(BUFFER);
    return res;
}
void Controller::help() const
{
    std::cout << "Ticket system v0.1\nEnter:\n1.To add event\n2.To check free space\n3.To reserve ticket\n4.To revoke reservation\n5.To buy ticket\n6.See all reservations\n7.All sold tickets\n0.To exit\n";
}
void Controller::Run()
{
    help();
    int currentChoice;
    while (true)
    {
        std::cin >> currentChoice;
        if (currentChoice == 0)
        {
            writeToFile();
            std::cout << "Exiting!\n";
            break;
        }
        else if (currentChoice == 1)
        {
            addEvent();
        }
        else if (currentChoice == 2)
        {
            freeSpaces();
        }
        else if (currentChoice == 3)
        {
            reserve();
        }
        else if (currentChoice == 4)
        {
            rejectReserve();
        }
        else if (currentChoice == 5)
        {
            buy();
        }
        else if (currentChoice == 6)
        {
            listReservations();
        }
        else if (currentChoice == 7)
        {
            sold();
        }
        else
        {
            std::cout << "Invalid choice!\n";
        }
    }
}

Date Controller::readDate()
{
    unsigned int day, month, year, hallID;
    std::cout << "Enter day: ";
    std::cin >> day;
    std::cout << "Enter month: ";
    std::cin >> month;
    std::cout << "Enter year: ";
    std::cin >> year;
    Date date(day, month, year);
    return date;
}
void Controller::addEvent()
{
    try
    {
        unsigned int hallID;
        MyString actName;
        std::cout << "Enter name: ";
        actName = readString();
        Date date = readDate();
        std::cout << "Enter hall: ";
        std::cin >> hallID;
        bool found = false;
        for (int i = 0; i < hallsCount; ++i)
        {
            if (halls[i]->getId() == hallID)
            {
                found = true;

                if (halls[i]->isFree(date))
                {
                    Act newAct(actName, date);
                    halls[i]->addAct(newAct);
                }
                else
                    throw std::invalid_argument("Hall is used on this day!");
                break;
            }
        }
        if (!found)
        {
            throw std::invalid_argument("Invalid hall id!");
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
    }
}

void Controller::freeSpaces()
{
    try
    {
        MyString actName;
        std::cout << "Enter name of act: ";
        actName = readString();
        Date date = readDate();
        for (int i = 0; i < hallsCount; ++i)
        {
            halls[i]->findOnDate(actName, date);
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
    }
}

void Controller::reserve()
{
    try
    {
        unsigned int row, place;
        std::cout << "Enter name of act: ";
        MyString actName = readString();
        Date date = readDate();
        MyString note;
        std::cout << "Enter row: ";
        std::cin >> row;
        std::cout << "Enter place: ";
        std::cin >> place;
        std::cout << "Enter pasword: ";
        MyString password = readString();
        std::cout << "Do you want to add note?(Y/N)";
        MyString ans;
        ans = readString();
        bool toAdd = false;
        if (ans.getSize() == 1 && ans.getData()[0] == 'Y')
        {
            std::cout << "Enter note: ";
            note = readString();
            toAdd = true;
        }
        int res = -1;
        for (int i = 0; i < hallsCount; ++i)
        {
            if (toAdd)
            {
                res = halls[i]->findAndReserve(actName, date, row, place, password, note);
            }
            else
            {
                res = halls[i]->findAndReserve(actName, date, row, place, password);
            }

            if (res != -1)
                break;
        }
        if (res == -1)
        {
            throw std::invalid_argument("Invalid act/date!");
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
    }
}

void Controller::rejectReserve()
{
    try
    {
        unsigned int row, place;
        std::cout << "Enter name of act: ";
        MyString actName = readString();
        Date date = readDate();
        std::cout << "Enter row: ";
        std::cin >> row;
        std::cout << "Enter place: ";
        std::cin >> place;
        std::cout << "Enter pasword: ";
        MyString password = readString();
        int res = -1;
        for (int i = 0; i < hallsCount; ++i)
        {
            res = halls[i]->removeReservation(actName, date, row, place, password);
            if (res != -1)
                break;
        }
        if (res == -1)
        {
            throw std::invalid_argument("Invalid reservation info!");
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
    }
}

void Controller::buy()
{
    try
    {
        unsigned int row, place;
        std::cout << "Enter name of act: ";
        MyString actName = readString();
        Date date = readDate();
        std::cout << "Enter row: ";
        std::cin >> row;
        std::cout << "Enter place: ";
        std::cin >> place;
        int res = -1;
        for (int i = 0; i < hallsCount; ++i)
        {
            res = halls[i]->findAct(actName, date);
            if (res != -1)
            {
                halls[i]->buy(res, row, place);
                break;
            }
        }
        if (res == -1)
        {
            throw std::invalid_argument("Invalid ticket info!");
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
    }
}

void Controller::listReservations()
{
    try
    {

        std::cout << "Enter name of act (if ALL - all acts): ";
        MyString actName = readString();
        bool allActs = (strcmp(actName.getData(), "ALL") == 0) ? true : false;
        std::cout << "All dates?Y/N";
        MyString ans = readString();
        bool allDates = false;
        if (ans.getSize() == 1 && ans.getData()[0] == 'Y')
            allDates = true;
        if (!allDates)
        {
            Date date = readDate();
            for (int i = 0; i < hallsCount; ++i)
            {
                if (allActs)
                {
                    halls[i]->printOnSpecificDate(date);
                }
                else
                {
                    halls[i]->print(actName, date);
                }
            }
        }
        else
        {
            for (int i = 0; i < hallsCount; ++i)
            {
                if (allActs)
                {
                    halls[i]->printAllActs();
                }
                else
                {
                    halls[i]->printSpecificAct(actName);
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
    }
}

void Controller::sold()
{
    try
    {
        unsigned int id;
        std::cout << "Enter specific id or ALL: ";
        MyString stId = readString();
        bool specificHall = true;
        try
        {
            id = std::stoi(stId.getData());
        }
        catch (const std::exception &e)
        {
            specificHall = false;
        }

        Date firstDate = readDate();
        Date secondDate = readDate();
        int res = -1;
        if (!specificHall)
            res = 0;
        for (int i = 0; i < hallsCount; ++i)
        {
            if (!specificHall)
            {
                halls[i]->printFromTo(firstDate, secondDate);
            }
            else
            {
                res = halls[i]->getId();
                if (res == id)
                {
                    halls[i]->printFromTo(firstDate, secondDate);
                    break;
                }
            }
        }
        if (res == -1)
        {
            throw std::invalid_argument("Invalid hall id!");
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
    }
}

void Controller::writeToFile()
{
    std::ofstream writer("Halls.txt");
    try
    {
        if (writer.is_open())
        {
            writer << hallsCount << '\n';
            for (int i = 0; i < hallsCount; ++i)
            {
                writer << *halls[i] << '\n';
            }
            writer.close();
        }
        else
            throw std::invalid_argument("Can not open file Halls.txt!");
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
    }
}

void Controller::readFromFile()
{
    std::ifstream reader;
    try
    {
        reader.open("Halls.txt", std::ios::in);
        char buffer[Act::BUFFER_SIZE];
        if (reader.is_open())
        {
            reader >> buffer;
            this->hallsCount = std::stoi(buffer);
            this->halls = new Hall *[hallsCount];
            int currentHall = 0;
            unsigned int id, row, sizeOfRow, sizeOfActs;
            char fileName[Act::BUFFER_SIZE];
            while (reader >> id >> row >> sizeOfRow >> sizeOfActs >> fileName)
            {
                if (currentHall >= hallsCount)
                    throw std::invalid_argument("Invalid data in file Halls.txt");
                MyString file(fileName);

                this->halls[currentHall] = new Hall(id, row, sizeOfRow, sizeOfActs);
                this->halls[currentHall++]->readFromFile(fileName);
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