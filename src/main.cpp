#include <iostream>
#include <fstream>

#include "contact_manager.cpp"

int main (int argc, char ** argv)
{
    std::cout << "Corbatur" << std::endl << std::endl;

    contact_manager cm;
    std::ifstream file;
    file.open ("test_config.cfg", std::ifstream::in);

    file >> cm;
    std::cout << cm << std::endl;

    return 0;
}
