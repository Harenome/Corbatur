/**
 * \file client.cpp
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
#include "client.hpp"

client::client (void)
{
}

client::~client (void)
{
}

int client::send_message (int argc, char ** argv)
{
    try
    {
        int fake_argc = argc - 2;
        CORBA::ORB_var orb = CORBA::ORB_init (fake_argc, argv);
        CORBA::Object_var obj = client::_get_object_reference (orb);
        corbatur::chat_var chat_ref = corbatur::chat::_narrow (obj);

        if (CORBA::is_nil (chat_ref))
            std::cerr << "The object reference is nil!" << std::endl;
        else
        {
            std::string temp_name (argv[argc-2]);
            std::string temp_address (argv[argc-1]);

            corbatur::sender s;
            s.name = temp_name.c_str ();
            s.address = temp_address.c_str ();

            chat_ref->message (s, (const char *) "Hi!");
        }
    }
    catch (CORBA::TRANSIENT &)
    {
        std::cerr << "Caught system exception TRANSIENT -- unable to contact the server." << std::endl;
    }
    catch (CORBA::SystemException & ex)
    {
        std::cerr << "Caught a CORBA::" << ex._name () << std::endl;
    }
    catch (CORBA::Exception & ex)
    {
        std::cerr << "Caught CORBA::Exception: " << ex._name () << std::endl;
    }
    catch (omniORB::fatalException & fe)
    {
        std::cerr << "Caught omniORB::fatalException:" << std::endl;
        std::cerr << "\tfile: " << fe.file () << std::endl;
        std::cerr << "\tline: " << fe.line () << std::endl;
        std::cerr << "\tmessage: " << fe.errmsg () << std::endl;
    }
    return 0;
}

CORBA::Object_ptr client::_get_object_reference (CORBA::ORB_ptr orb)
{
    CosNaming::NamingContext_var root_context;

    try
    {
        CORBA::Object_var obj;
        obj = orb->resolve_initial_references ("NameService");
        root_context = CosNaming::NamingContext::_narrow (obj);
        if (CORBA::is_nil (root_context))
        {
            std::cerr << "Failed to narrow the root naming context." << std::endl;
            return CORBA::Object::_nil ();
        }
    }
    catch (CORBA::NO_RESOURCES &)
    {
        std::cerr << "Caught NO_RESOURCES exception. You must configure omniORB with the location of the naming service." << std::endl;
        return 0;
    }
    catch (CORBA::ORB::InvalidName & ex)
    {
        std::cerr << "Service required is invalid [doex not exist]." << std::endl;
        return CORBA::Object::_nil ();
    }

    CosNaming::Name name;
    name.length (2);
    name[0].id = (const char *) "corbatur";
    name[0].kind = (const char *) "context";
    name[1].id = (const char *) "chat";
    name[1].kind = (const char *) "object";

    try
    {
        return root_context->resolve (name);
    }
    catch (CosNaming::NamingContext::NotFound & ex)
    {
        std::cerr << "Context not found." << std::endl;
    }
    catch (CORBA::TRANSIENT & ex)
    {
        std::cerr << "Caught system exception TRANSIENT -- unable to contact the naming service." << std::endl;
        std::cerr << "Make sure the naming server is running and that omniORB is configured correctly." << std::endl;
    }
    catch (CORBA::SystemException & ex)
    {
        std::cerr << "Caught a CORBA::" << ex._name () << " while using the naming service." << std::endl;
        return 0;
    }

    return CORBA::Object::_nil ();
}
