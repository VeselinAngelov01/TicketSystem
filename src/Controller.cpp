#include "../h/Controller.hpp"

Controller::Controller()
{
    this->halls = nullptr;
    this->hallsCount = 0;
}

Controller::~Controller()
{
    for (size_t i = 0; i < this->hallsCount; ++i)
    {
        delete this->halls[i];
    }
    delete[] this->halls;
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
        char actName[ACT_NAME_SIZE];
        std::cout << "Enter name: ";
        std::cin >> actName;
        Date date=readDate();
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
                    Act newAct(actName, hallID, halls[i]->getRows(), halls[i]->getSizeOfRow(), date);
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
        char actName[ACT_NAME_SIZE];
        std::cout << "Enter name of act: ";
        std::cin>>actName;
        Date date=readDate();
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
        char actName[ACT_NAME_SIZE];
        char password[PASS_SIZE];
        char note[NOTE_SIZE];
        std::cout << "Enter name of act: ";
        std::cin >> actName;
        Date date = readDate();
        std::cout << "Enter row: ";
        std::cin >> row;
        std::cout << "Enter place: ";
        std::cin >> place;
        std::cout << "Enter pasword: ";
        std::cin >> password;
        std::cout << "Do you want to add note? (0 for yes,else some num)";
        int ans;
        std::cin >> ans;
        if (ans == 0)
        {
            std::cout << "Enter note: ";
            std::cin >> note;
        }
        int res = -1;
        for (int i = 0; i < hallsCount; ++i)
        {
            if (ans == 0)
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
        char actName[ACT_NAME_SIZE];
        char password[PASS_SIZE];
        char note[NOTE_SIZE];
        std::cout << "\nEnter name of act: ";
        std::cin >> actName;
        Date date = readDate();
        std::cout << "\nEnter row: ";
        std::cin >> row;
        std::cout << "\nEnter place: ";
        std::cin >> place;
        std::cout << "\nEnter pasword: ";
        std::cin >> password;
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
        char actName[ACT_NAME_SIZE];
        char password[PASS_SIZE];
        char note[NOTE_SIZE];
        std::cout << "\nEnter name of act: ";
        std::cin >> actName;
        Date date=readDate();
        std::cout << "\nEnter row: ";
        std::cin >> row;
        std::cout << "\nEnter place: ";
        std::cin >> place;
        int res = -1;
        for (int i = 0; i < hallsCount; ++i)
        {
            res = halls[i]->findAct(actName, date);
            if (res != -1)
            {
                int ticketType = halls[i]->specificTicketType(row, place, res);
                if (ticketType == 1)
                {
                    std::cout << "Enter password: ";
                    std::cin >> password;
                    halls[i]->buy(row, place, res, password);
                }
                else
                    halls[i]->buy(row, place, res);
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
        char actName[ACT_NAME_SIZE];
        std::cout << "Enter name of act (if ALL - all acts): ";
        std::cin >> actName;
        int all = 0;
        std::cout << "Specific date( number ) or all dates(0)";
        std::cin >> all;
        if (all != 0)
        {
            Date date = readDate();
            std::cout << "Enter day (if ALL - all possible dates): ";
            int res = strcmp(actName, "ALL");
            for (int i = 0; i < hallsCount; ++i)
            {
                if (res == 0)
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
            int res = strcmp(actName, "ALL");
            for (int i = 0; i < hallsCount; ++i)
            {
                if (res == 0)
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

void Controller::loadHalls(char *fileName)
{
    std::ifstream reader(fileName);
    char buffer[32];
    char c;
    bool firstLine = true;
    int currIndex = 0;
    int sizeOfHallArr = 0;
    if (reader.is_open())
    {
        int indexToInsert = 0;
        while (reader.getline(buffer, 32))
        {
            if (firstLine)
            {
                try
                {
                    sizeOfHallArr = std::stoi(buffer);
                    this->halls = new Hall *[sizeOfHallArr];
                    this->hallsCount = sizeOfHallArr;
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Invalid value on line 1\n";
                }
                firstLine = false;
            }
            else
            {
                try
                {
                    int sizeOfBuff = strlen(buffer);
                    int delCount = 0;
                    int currIndex = 0;
                    char tempArr[sizeOfBuff];
                    unsigned int id, rows, sizeOfRow;
                    for (int i = 0; i < sizeOfBuff; ++i)
                    {
                        if (delCount > 2)
                        {
                            throw std::invalid_argument("Invalid data in file!");
                        }
                        if (buffer[i] == ' ')
                        {
                            tempArr[currIndex] = '\0';
                            currIndex = 0;
                            if (delCount == 0)
                            {
                                id = std::stoi(tempArr);
                            }
                            else if (delCount == 1)
                            {
                                rows = std::stoi(tempArr);
                            }
                            delCount++;
                        }
                        else
                        {
                            tempArr[currIndex] = buffer[i];
                            currIndex++;
                        }
                    }
                    tempArr[currIndex] = '\0';
                    sizeOfRow = std::stoi(tempArr);
                    if (indexToInsert >= hallsCount)
                    {
                        throw std::invalid_argument("More halls than specified!");
                    }
                    this->halls[indexToInsert] = new Hall(id, rows, sizeOfRow);
                    indexToInsert++;
                }
                catch (const std::exception &e)
                {
                    std::cout << e.what() << '\n';
                }
            }
        }
    }
    else
    {
        throw std::invalid_argument("Can not open file to load halls!\nExiting...");
    }
}

void Controller::sold()
{
    try
    {
        unsigned int id;
        std::cout << "Enter specific id or ALL(0): ";
        std::cin >> id;
        Date firstDate = readDate();
        Date secondDate = readDate();
        int res = -1;
        if (id == 0)
            res = 0;
        for (int i = 0; i < hallsCount; ++i)
        {
            if (id == 0)
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