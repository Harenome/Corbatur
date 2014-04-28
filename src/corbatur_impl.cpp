/**
 * \file corbatur_impl.cpp
 * \brief Corbatur impl.
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
#include "corbatur_impl.hpp"

chat_impl::chat_impl (void)
: _manager (contact_manager::DEFAULT), _last_contact ("")
{
}

chat_impl::chat_impl (const contact_manager & manager)
: _manager (manager), _last_contact ("")
{
}

chat_impl::~chat_impl (void)
{
}

void chat_impl::set_manager (contact_manager & manager)
{
    _manager = manager;
}

void chat_impl::message (const corbatur::sender & s, const char * message)
{
    std::string name (s.name);
    std::string address (s.address);

    _manager = contact_manager::read_contacts ("config.cfg");
    if (! _manager.exists (name))
        _manager.add_contact (name);
    _manager.add_address (name, address);
    contact_manager::save_contacts ("config.cfg", _manager);

    std::cout << "> ";
    if (_last_contact != name)
    {
        _last_contact = name;
        std::cout << name;
    }
    std::cout << ": " << message << std::endl;
}

char * chat_impl::ask_infos (const char * name)
{
    static const char * not_found = "";
    std::string contact_name (name);
    if (_manager.exists (contact_name))
    {
        contact c = _manager[contact_name];
        if (c.has_address ())
        {
            std::vector<std::string> addresses = c.addresses ();
            return CORBA::string_dup (addresses[0].c_str ());
        }
    }

    return CORBA::string_dup (not_found);
}
