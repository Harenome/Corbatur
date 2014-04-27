#include "client.hpp"
#include "parser.hpp"

int main (int argc, char ** argv)
{
    std::string name (argv[argc-2]);
    std::string address (argv[argc-1]);

    client c (argv[0], name, address);
    c.read_contacts ("config.cfg");

    std::string last_contact;
    char buffer[2048];
    std::cout << "corbatur > ";
    while (std::cin.getline (buffer, 2048))
    {
        std::string line (buffer);
        if (parser::is_message (line))
        {
            if (parser::message_has_destination (line))
                last_contact = parser::message_destination (line);

            if (last_contact.size () > 0)
            {
                std::string message = parser::message_content (line);
                c.send_message_to_contact (last_contact.c_str (), message.c_str ());
            }
            else
                std::cerr << "Error : Sorry I did not understand whom to send your message." << std::endl;
        }
        else if (line == "bye")
            return 0;
        std::cout << "corbatur > ";
    }

    return 0;
}
