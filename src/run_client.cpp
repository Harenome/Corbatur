#include <algorithm>

#include "client.hpp"
#include "parser.hpp"

static char * help =
"Commands:\n"
"---------\n"
"* h, help\n"
"\tDisplay the help.\n"
"* ls, list, who\n"
"\tList contacts\n"
"* who am i, whoami\n"
"\tDisplay client info.\n"
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
    bool next_is_spam = false;

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
                if (next_is_spam)
                {
                    next_is_spam = false;
                    for (unsigned int i = 0; i < 100; ++i)
                        c.send_message_to_contact (last_contact.c_str (), message.c_str ());
                }
            }
            else
                std::cerr << "Error : Sorry I did not understand whom to send your message." << std::endl;
        }
        else
        {
            /* On supprime tous les espaces pour que les commandes soient toujours reconnues.
             * Du coup, certaines excentricités fonctionnent comme "w h o".
             */
            line.erase (std::remove (line.begin (), line.end (), ' '), line.end ());
            if (line == "ls" || line == "list" || line == "who")
                c.display_contacts ();
            else if (line == "help" || line == "h")
                std::cout << help;
            else if (line == "whoami")
                c.display_infos ();
            else if (line == "spam")
            {
                if (next_is_spam)
                    std::cout << "Oh you so crazy!" << std::endl;
                next_is_spam = true;
            }
            else if (line == "easteregg")
                std::cout << "NO." << std::endl;
            else if (line == "bye" || line == "quit" || line == "ragequit" || line == "exit")
                return 0;
        }
    }

    return 0;
}
