/**
 * \file client.hpp
 * \brief Client.
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
#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include <iostream>

#include "corbatur.hh"

class client
{
public:
    client (void);
    ~client (void);
    int send_message (int argc, char ** argv);
private:
    static CORBA::Object_ptr _get_object_reference (CORBA::ORB_ptr orb);
};

#endif /* __CLIENT_HPP__ */
