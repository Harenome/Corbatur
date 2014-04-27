/**
 * \file corbatur_impl.hpp
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
#ifndef __CORBATUR_IMPL_HPP__
#define __CORBATUR_IMPL_HPP__

#include <iostream>

#include "corbatur.hh"
#include "contact_manager.hpp"

class chat_impl: public POA_corbatur::chat
{
public:
    chat_impl (void);
    chat_impl (contact_manager & manager);
    virtual ~chat_impl (void);
    void set_manager (contact_manager & manager);
    void message (const corbatur::sender & s, const char * message);
private:
    contact_manager & _manager;
    std::string _last_contact;
};

#endif /* __CORBATUR_IMPL_HPP__ */
