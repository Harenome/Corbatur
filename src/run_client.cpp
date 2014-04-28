#include "client.hpp"
#include "parser.hpp"

static char * help =
"Commands:\n"
"---------\n"
"* h, help\n"
"\tDisplay the help.\n"
"* ls, list\n"
"\tList contacts\n"
"* bye, exit, quit\n"
"\tQuit.\n"
"Special commands:\n"
"-----------------\n"
"* <id>:<message>\n"
"\tSend <message> to <id>. <id> and <message> must be separated with a column.\n"
":<message>\n"
"\tSend <message> to the last used <id>.\n";

int main (int argc, char ** argv)
{

    std::string name (argv[argc-2]);
    std::string address (argv[argc-1]);

    std::cout << "Welcome to corbatur, " << name << "!" << std::endl << std::endl;

    client c (argv[0], name, address);
    c.read_contacts ("config.cfg");

    std::string last_contact;
    char buffer[2048];
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
        else if (line == "ls" || line == "list")
            c.display_contacts ();
        else if (line == "help" || line == "h")
            std::cout << help;
        else if (line == "bye" || line == "quit" || line == "ragequit" || line == "exit")
            return 0;
    }

    return 0;
}
