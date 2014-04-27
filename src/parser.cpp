/**
 * \file parser.cpp
 * \brief Parser.
 * \author RAZANAJATO RANAIVOARIVONY Harenome
 * \author MEYER Jérémy
 * \date 2014
 * \copyright WTFPL version 2
 */
/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */
#include "parser.hpp"

bool parser::is_command (const std::string & s)
{
    char buffer[2048];
    if (sscanf (s.c_str (), "%*[^:]%[:]", buffer) == 1
        || sscanf (s.c_str (), " %[:]", buffer) == 1)
        return false;
    else
        return true;
}

bool parser::is_message (const std::string & s)
{
    return ! parser::is_command (s);
}

bool parser::message_has_destination (const std::string & s)
{
    char buffer[2048];
    if (sscanf (s.c_str (), " %[:]", buffer) == 1)
        return false;
    else
        return true;
}

std::string parser::message_destination (const std::string & s)
{
    std::string result ("");
    if (message_has_destination (s))
    {
        std::string::size_type column = s.find_first_of (':');
        result = s.substr (0, column);
        result.erase (std::remove (result.begin (), result.end (), ' '), result.end ());
    }

    return result;
}

std::string parser::message_content (const std::string & s)
{
    std::string::size_type column = s.find_first_of (':');
    std::string result = s.substr (column+1, s.size ());
    return result;
}
