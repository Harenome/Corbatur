/**
 * \file contact_manager.hpp
 * \brief Contact manager.
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
#include "contact_manager.hpp"

contact_manager contact_manager::DEFAULT;

///////////////////////////////////////////////////////////////////////////////
// Constructeurs.
///////////////////////////////////////////////////////////////////////////////

contact_manager::contact_manager (void)
{
}

contact_manager::contact_manager (const contact_manager & cm)
: _contacts (cm._contacts)
{
}

///////////////////////////////////////////////////////////////////////////////
// Destructeurs.
///////////////////////////////////////////////////////////////////////////////

contact_manager::~contact_manager (void)
{
}

///////////////////////////////////////////////////////////////////////////////
// Sélecteurs.
///////////////////////////////////////////////////////////////////////////////

contact_manager_const_iterator contact_manager::begin (void) const
{
    return _contacts.begin ();
}

contact_manager_const_iterator contact_manager::end (void) const
{
    return _contacts.end ();
}

contact & contact_manager::operator[] (const std::string & name)
{
    return _contacts[name];
}

const contact & contact_manager::operator[] (const std::string & name) const
{
    return _contacts.find (name)->second;
}

bool contact_manager::exists (const std::string & name) const
{
    return _contacts.count (name) > 0;
}

///////////////////////////////////////////////////////////////////////////////
// Modificateurs.
///////////////////////////////////////////////////////////////////////////////

void contact_manager::add_contact (const std::string & name)
{
    if (! exists (name))
    {
        contact c (name);
        contact_manager_element pair (name, c);
        _contacts.insert (pair);
    }
}

void contact_manager::add_contact (const contact & c)
{
    if (! exists (c.name ()))
    {
        contact_manager_element pair (c.name (), c);
        _contacts.insert (pair);
    }
}

void contact_manager::add_address (const std::string & contact_name, const std::string & address)
{
    if (exists (contact_name) && ! _contacts[contact_name].has_this_address (address))
        _contacts[contact_name].add_address (address);
}

void contact_manager::add_alias (const std::string & contact_name, const std::string & alias)
{
    if (exists (contact_name) && ! _contacts[contact_name].has_this_alias (alias))
        _contacts[contact_name].add_alias (alias);
}

void contact_manager::remove_contact (const std::string & name)
{
    if (exists (name))
        _contacts.erase (name);
}

void contact_manager::remove_contact (const contact & c)
{
    remove_contact (c.name ());
}

void contact_manager::remove_address (const std::string & name, const std::string & address)
{
    if (exists (name) && _contacts[name].has_this_address (address))
        _contacts[name].remove_address (name);
}

void contact_manager::remove_alias (const std::string & name, const std::string & alias)
{
    if (exists (name) && _contacts[name].has_this_alias (alias))
        _contacts[name].remove_alias (name);
}

std::ostream & contact_manager::write_to_stream (std::ostream & os) const
{
    for (contact_manager_const_iterator it = _contacts.begin (); it != _contacts.end (); ++it)
        os << it->second << std::endl;
    return os;
}

void contact_manager::swap (contact_manager & cm)
{
    _contacts.swap (cm._contacts);
}

contact_manager & contact_manager::operator= (contact_manager cm)
{
    this->swap (cm);
    return * this;
}

///////////////////////////////////////////////////////////////////////////////
// Fonctions non membres.
///////////////////////////////////////////////////////////////////////////////

std::ostream & operator<< (std::ostream & os, const contact_manager & c)
{
    return c.write_to_stream (os);
}

std::istream & operator>> (std::istream & is, contact_manager & cm)
{
    bool error = false;
    contact_manager new_cm;

    char buffer[2048];
    while (is.getline (buffer, 2048))
    {
        std::string line (buffer);
        std::string::size_type column = line.find_first_of (':');
        if (column != std::string::npos && column != 0)
        {
            std::replace (line.begin (), line.end (), ',', ' ');
            std::replace (line.begin () + column, line.begin () + column + 1, ':', ' ');

            std::stringstream stream (line, std::ios_base::in | std::ios_base::out);
            contact new_contact;
            stream >> new_contact;

            error = ! stream.fail ();
            if (error)
                is.setstate (std::ios::failbit);
            else
                new_cm.add_contact (new_contact);
        }
        else
        {
            error = true;
            is.setstate (std::ios::failbit);
        }
    }

    if (! error)
        cm = new_cm;

    return is;
}
