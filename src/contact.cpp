/**
 * \file contact.cpp
 * \brief Contact.
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
#include "contact.hpp"

///////////////////////////////////////////////////////////////////////////////
// Constructeurs.
///////////////////////////////////////////////////////////////////////////////

contact::contact (void)
{
}

contact::contact (const contact & c)
: _name (c._name)
{
    _addresses = c._addresses;
    _aliases = c._aliases;
}

contact::contact (const std::string & name)
: _name (name)
{
}

contact::contact (const std::string & name, const std::vector<std::string> & addresses, const std::vector<std::string> & aliases)
: _name (name)
{
    _addresses = addresses;
    _aliases = aliases;
}

///////////////////////////////////////////////////////////////////////////////
// Destructeur.
///////////////////////////////////////////////////////////////////////////////
contact::~contact (void)
{
}

///////////////////////////////////////////////////////////////////////////////
// Sélecteurs.
///////////////////////////////////////////////////////////////////////////////

std::string contact::name (void) const
{
    return _name;
}

std::vector<std::string> contact::addresses (void) const
{
    return _addresses;
}

std::vector<std::string> contact::aliases (void) const
{
    return _aliases;
}

bool contact::has_address (void) const
{
    return _addresses.size () > 0;
}

bool contact::has_alias (void) const
{
    return _aliases.size () > 0;
}

bool contact::_has_value (const std::vector<std::string> & list, const std::string & value)
{
    return list.end () != std::find (list.begin (), list.end (), value);
}

bool contact::has_this_alias (const std::string & alias) const
{
    return contact::_has_value (_aliases, alias);
}

bool contact::has_this_address (const std::string & address) const
{
    return contact::_has_value (_addresses, address);
}

///////////////////////////////////////////////////////////////////////////////
// Modificateurs.
///////////////////////////////////////////////////////////////////////////////

void contact::set_name (const std::string & name)
{
    _name = name;
}

void contact::add_address (const std::string & address)
{
    if (! has_this_address (address))
        _addresses.push_back (address);
}

void contact::add_alias (const std::string & alias)
{
    if (! has_this_alias (alias))
        _aliases.push_back (alias);
}

void contact::_remove_from (std::vector<std::string> & list, const std::string & value)
{
    std::vector<std::string>::iterator index = std::find (list.begin (), list.end (), value);
    if (index != list.end ())
        list.erase (index);
}

void contact::_remove_from (std::vector<std::string> & list, unsigned int index)
{
    if (index < list.size ())
        list.erase  (list.begin () + index);
}

void contact::remove_address (const std::string & address)
{
    contact::_remove_from (_addresses, address);
}

void contact::remove_alias (const std::string & alias)
{
    contact::_remove_from (_aliases, alias);
}

void contact::remove_address (unsigned int index)
{
    contact::_remove_from (_addresses, index);
}

void contact::remove_alias (unsigned int index)
{
    contact::_remove_from (_aliases, index);
}

///////////////////////////////////////////////////////////////////////////////
// Divers.
///////////////////////////////////////////////////////////////////////////////

void contact::swap (contact & c)
{
    _name.swap (c._name);
    _addresses.swap (c._addresses);
    _aliases.swap (c._aliases);
}

contact & contact::operator= (contact c)
{
    this->swap (c);
    return * this;
}

std::ostream & contact::_write_vector (std::ostream & os, const std::vector<std::string> & list)
{
    int size = list.size ();
    if (size > 0)
    {
        if (list.size () > 1)
            for (std::vector<std::string>::const_iterator it = list.begin (); it != list.end () - 1; ++it)
                os << * it << ", ";

        os << list.at (list.size () - 1);
    }
    return os;
}

std::ostream & contact::write_to_stream (std::ostream & os) const
{
    os << _name << " : ";
    if (has_address ())
    {
        contact::_write_vector (os, _addresses);
        if (has_alias ())
        {
            os << ", ";
            contact::_write_vector (os, _aliases);
        }
    }
    else if (has_alias ())
    {
        contact::_write_vector (os, _aliases);
    }
    else
    {
        os << "?";
    }

    return os;
}

///////////////////////////////////////////////////////////////////////////////
// Fonctions non membres.
///////////////////////////////////////////////////////////////////////////////

std::ostream & operator<< (std::ostream & os, const contact & c)
{
    c.write_to_stream (os);

    return os;
}

std::istream & operator>> (std::istream & is, contact & c)
{
    bool error = false;
    contact new_contact;
    std::string name;
    is >> name;

    char name_buffer[2048];
    if (sscanf (name.c_str (), "%[a-zA-Z]", name_buffer) == 1)
    {
        new_contact.set_name (name);
    }
    else
    {
        is.setstate (std::ios::failbit);
        error = true;
    }

    std::string thing;
    while (! error && is >> thing)
    {
        char thing_buffer[2048];

        /* Si la chaîne contient un ':'. */
        if (sscanf (thing.c_str (), "%*[a-zA-Z0-9]%[:]", thing_buffer) == 1)
            new_contact.add_address (thing);
        else
            new_contact.add_alias (thing);
    }

    if (! error)
        c = new_contact;

    return is;
}
