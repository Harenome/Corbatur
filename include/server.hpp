/**
 * \file server.hpp
 * \brief Server.
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
#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <iostream>

#include "contact.hpp"
#include "contact_manager.hpp"
#include "corbatur_impl.hpp"

class server
{
public:
    server (void);
    ~server (void);
    int run (int argc, char ** argv);
private:
    contact_manager _manager;
    static CORBA::Boolean _bind_object_to_name (CORBA::ORB_ptr orb, CORBA::Object_ptr objref);
};

#endif /* __SERVER_HPP__ */
