#include "Controller.hpp"

int main()
{
    Controller controller;
    controller.loadHalls("Halls.txt");
    controller.Run();
    return 0;
}