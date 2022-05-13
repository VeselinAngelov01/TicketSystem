#include "../h/Controller.hpp"

/// Main function to start program\n
/// Here can be specified file to be read
int main()
{
    /// Github: https://github.com/VeselinAngelov01/TicketSystem
    Controller* controller=Controller::getController();
    controller->Run();
    delete controller;
    return 0;
}