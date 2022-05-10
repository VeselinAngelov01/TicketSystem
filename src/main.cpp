#include "../h/Controller.hpp"

/// Main function to start program\n
/// Here can be specified file to be read
int main()
{
    Controller controller = Controller::instance();
    controller.Run();
    return 0;
}