/**
 * \file parser.hpp
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
#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <string>
#include <cstdio>
#include <iostream>
#include <algorithm>

class parser
{
public:
    static bool is_command (const std::string & s);
    static bool is_message (const std::string & s);
    static bool message_has_destination (const std::string & s);
    static std::string message_destination (const std::string & s);
    static std::string message_content (const std::string & s);
};

#endif /* __PARSER_HPP__ */
