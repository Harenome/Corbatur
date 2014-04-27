#include "client.hpp"

int main (int argc, char ** argv)
{
    client c;
    c.send_message (argc, argv);
    return 0;
}
