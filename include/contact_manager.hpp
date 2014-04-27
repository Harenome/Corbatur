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
#ifndef __CONTACT_MANAGER_HPP__
#define __CONTACT_MANAGER_HPP__

#include <ostream>
#include <map>

#include "contact.hpp"

///////////////////////////////////////////////////////////////////////////////
// Typedefs.
///////////////////////////////////////////////////////////////////////////////

typedef std::map<std::string, contact> contact_manager_map;
typedef std::pair<std::string, contact> contact_manager_element;
typedef contact_manager_map::iterator contact_manager_iterator;
typedef contact_manager_map::const_iterator contact_manager_const_iterator;

///////////////////////////////////////////////////////////////////////////////
// Classe.
///////////////////////////////////////////////////////////////////////////////

class contact_manager
{
public:
    static contact_manager DEFAULT;
    contact_manager (void);
    contact_manager (const contact_manager & cm);
    ~contact_manager (void);
    contact & operator[] (const std::string & name);
    const contact & operator[] (const std::string & name) const;
    contact_manager_const_iterator begin (void) const;
    contact_manager_const_iterator end (void) const;
    bool exists (const std::string & name) const;
    void add_contact (const std::string & name);
    void add_contact (const contact & c);
    void add_address (const std::string & contact_name, const std::string & address);
    void add_alias (const std::string & contact_name, const std::string & alias);
    void remove_contact (const std::string & name);
    void remove_contact (const contact & c);
    void remove_address (const std::string & contact_name, const std::string & address);
    void remove_alias (const std::string & contact_name, const std::string & alias);
    std::ostream & write_to_stream (std::ostream & os) const;
    void swap (contact_manager & cm);
    contact_manager & operator= (contact_manager cm);

private:
    std::map<std::string, contact> _contacts;
};

///////////////////////////////////////////////////////////////////////////////
// Fonctions non membres.
///////////////////////////////////////////////////////////////////////////////

std::ostream & operator<< (std::ostream & os, const contact_manager & cm);

inline void swap (contact_manager & a, contact_manager & b)
{
    a.swap (b);
}

#endif /* __CONTACT_MANAGER_HPP__ */
