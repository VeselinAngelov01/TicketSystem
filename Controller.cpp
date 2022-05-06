#include "Controller.hpp"

Controller::Controller()
{
    //this->halls = new Hall *[DEF_SIZE];
    this->hallsCount = 0;
    //this->capacity = DEF_SIZE;
}

Controller::~Controller()
{
    for (size_t i = 0; i < this->capacity; ++i)
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

void Controller::addEvent()
{
    try
    {
        unsigned int day, month, year, hallID;
        char actName[ACT_NAME_SIZE];
        std::cout << "Enter day: ";
        std::cin >> day;
        std::cout << "\nEnter month: ";
        std::cin >> month;
        std::cout << "\nEnter year: ";
        std::cin >> year;
        std::cout << "\nEnter name: ";
        std::cin >> actName;
        std::cout << "\nEnter hall: ";
        std::cin >> hallID;
        bool found = false;
        for (int i = 0; i < hallsCount; ++i)
        {
            if (halls[i]->getId() == hallID)
            {
                found = true;
                Date date(day, month, year);
                if (halls[i]->isFree(date))
                {
                    Act newAct(actName, hallID, halls[i]->getRows(), halls[i]->getSizeOfRow(), date);
                    halls[i]->addAct(newAct);
                }
                else
                    std::cout << "Hall is used on this day!\n";
            }
        }
        if (!found)
        {
            std::cout << "Invalid hall id!\n";
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
        unsigned int day, month, year;
        char actName[ACT_NAME_SIZE];
        std::cout << "\nEnter name of act: ";
        std::cin >> actName;
        std::cout << "Enter day: ";
        std::cin >> day;
        std::cout << "\nEnter month: ";
        std::cin >> month;
        std::cout << "\nEnter year: ";
        std::cin >> year;
        Date date(day, month, year);
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
        unsigned int day, month, year, row, place;
        char actName[ACT_NAME_SIZE];
        char password[PASS_SIZE];
        char note[NOTE_SIZE];
        std::cout << "\nEnter name of act: ";
        std::cin >> actName;
        std::cout << "Enter day: ";
        std::cin >> day;
        std::cout << "\nEnter month: ";
        std::cin >> month;
        std::cout << "\nEnter year: ";
        std::cin >> year;
        std::cout << "\nEnter row: ";
        std::cin >> row;
        std::cout << "\nEnter place: ";
        std::cin >> place;
        std::cout << "\nEnter pasword: ";
        std::cin >> password;
        std::cout << "Do you want to add note? (Y for yes,else no)";
        char ans;
        std::cin >> ans;
        if (ans == 'Y')
        {
            std::cout << "\nEnter note: ";
            std::cin >> note;
        }
        Date date(day, month, year);
        int res = -1;
        for (int i = 0; i < hallsCount; ++i)
        {
            if (ans == 'Y')
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
            std::cout << "Invalid act/date!\n";
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
        unsigned int day, month, year, row, place;
        char actName[ACT_NAME_SIZE];
        char password[PASS_SIZE];
        char note[NOTE_SIZE];
        std::cout << "\nEnter name of act: ";
        std::cin >> actName;
        std::cout << "Enter day: ";
        std::cin >> day;
        std::cout << "\nEnter month: ";
        std::cin >> month;
        std::cout << "\nEnter year: ";
        std::cin >> year;
        std::cout << "\nEnter row: ";
        std::cin >> row;
        std::cout << "\nEnter place: ";
        std::cin >> place;
        std::cout << "\nEnter pasword: ";
        std::cin >> password;
        Date date(day, month, year);
        int res = -1;
        for (int i = 0; i < hallsCount; ++i)
        {
            res = halls[i]->removeReservation(actName, date, row, place, password);
            if (res != -1)
                break;
        }
        if (res == -1)
        {
            std::cout << "Invalid reservation info!\n";
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
        unsigned int day, month, year, row, place;
        char actName[ACT_NAME_SIZE];
        char password[PASS_SIZE];
        char note[NOTE_SIZE];
        std::cout << "\nEnter name of act: ";
        std::cin >> actName;
        std::cout << "Enter day: ";
        std::cin >> day;
        std::cout << "\nEnter month: ";
        std::cin >> month;
        std::cout << "\nEnter year: ";
        std::cin >> year;
        std::cout << "\nEnter row: ";
        std::cin >> row;
        std::cout << "\nEnter place: ";
        std::cin >> place;
        Date date(day, month, year);
        int res = -1;
        for (int i = 0; i < hallsCount; ++i)
        {
            res = halls[i]->findAct(actName, date);
            if (res != -1)
            {
                halls[i]->buy(row, place, res);
                break;
            }
        }
        if (res == -1)
        {
            std::cout << "Invalid ticket info!\n";
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
        unsigned int day, month, year;
        char actName[ACT_NAME_SIZE];
        std::cout << "\nEnter name of act (if ALL - all acts): ";
        std::cin >> actName;
        int all = 0;
        std::cout << "\nSpecific date( number ) or all dates(0)";
        std::cin >> all;
        if (all != 0)
        {
            std::cout << "\nEnter day (if ALL - all possible dates): ";
            std::cin >> day;
            std::cout << "\nEnter month: ";
            std::cin >> month;
            std::cout << "\nEnter year: ";
            std::cin >> year;
            Date date(day, month, year);
            int res = strcmp(actName, "ALL");
            for (int i = 0; i < hallsCount; ++i)
            {
                if (res == 0)
                {
                    halls[i]->printOnSpecificDate(date);
                }
                else
                {
                    halls[i]->print(actName,date);
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


void Controller::loadHalls(char* fileName)
{
    std::ifstream reader(fileName);
    char buffer[32];
    char c;
    bool firstLine = true;
    int currIndex = 0;
    int sizeOfHallArr = 0;
    if(reader.is_open())
    {
        while(reader.getline(buffer,32))
        {
            if(firstLine)
            {
                try
                {
                    sizeOfHallArr=std::stoi(buffer);
                }
                catch(const std::exception& e)
                {
                    std::cerr << "Invalid value on line 1\n";
                }  
            }
            else
            {
                
            }
        }
    }
    else
    {
        throw std::invalid_argument("Can not open file to load halls!\nExiting...");
    }
}