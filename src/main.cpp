#include "../h/Controller.hpp"

/// Main function to start program\n
/// Here can be specified file to be read
int main()
{
    Controller controller;
    controller.loadHalls("Halls.txt");
    controller.Run();
    return 0;
}