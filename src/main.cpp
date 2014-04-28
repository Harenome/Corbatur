#include <iostream>
#include <fstream>

#include "contact_manager.cpp"
#include "client.hpp"
#include "server.hpp"

int main (int argc, char ** argv)
{
    std::cout << "Corbatur" << argc << std::endl << std::endl;

    std::string name (argv[1]);
    std::string port (argv[2]);
    std::string address (argv[3]);

    contact_manager cm;
    std::ifstream file;
    file.open ("config.cfg", std::ifstream::in);
    file >> cm;
    file.close ();

    client * c = new client (argv[0], name, address, & cm);
    std::string local ("localhost:");
    local += port;
    c->set_self_address (local);

    char orb_init_ref[] = "-ORBInitRef";
    std::string localhost ("NameService=corbaname::localhost:");
    localhost += port;
    char * fake_argv[3] = { argv[0], orb_init_ref, (char *) localhost.c_str () };
    server * s = new server (3, fake_argv);
    s->set_contact_manager (& cm);

    c->start ();
    s->start ();

    std::cout << "Waiting." << std::endl;

    while (true)
        ;

    return 0;
}
