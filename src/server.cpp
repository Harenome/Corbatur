/**
 * \file server.cpp
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
#include "server.hpp"

server::server (void)
{
}

server::~server (void)
{
}

int server::run (int argc, char ** argv)
{
    try
    {
        CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);
        CORBA::Object_var obj = orb->resolve_initial_references ("RootPOA");
        PortableServer::POA_var poa = PortableServer::POA::_narrow (obj);
        chat_impl * server_chat = new chat_impl (_manager);
        PortableServer::ObjectId_var chat_id = poa->activate_object (server_chat);
        obj = server_chat->_this ();
        CORBA::String_var ior = orb->object_to_string (obj);
        std::cout << ior << std::endl << std::endl;

        if (! server::_bind_object_to_name (orb, obj))
            return 1;

        server_chat->_remove_ref ();
        PortableServer::POAManager_var poa_manager = poa->the_POAManager ();
        poa_manager->activate ();
        orb->run ();
    }
    catch (CORBA::SystemException & ex)
    {
        std::cerr << "Caught CORBA::" << ex._name () << std::endl;
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

CORBA::Boolean server::_bind_object_to_name (CORBA::ORB_ptr orb, CORBA::Object_ptr objref)
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
            return 0;
        }
    }
    catch (CORBA::NO_RESOURCES &)
    {
        std::cerr << "Caught NO_RESOURCES exception. You must configure omniORB with the location of the naming service." << std::endl;
        return 0;
    }
    catch (CORBA::ORB::InvalidName &)
    {
        std::cerr << "Service required is invalid [does not exist]." << std::endl;
        return 0;
    }

    try
    {
        CosNaming::Name context_name;
        context_name.length (1);
        context_name[0].id = (const char *) "corbatur";
        context_name[0].kind = (const char *) "context";

        CosNaming::NamingContext_var corbatur_context;
        try
        {
            corbatur_context = root_context->bind_new_context (context_name);
        }
        catch (CosNaming::NamingContext::AlreadyBound & ex)
        {
            CORBA::Object_var obj;
            obj = root_context->resolve (context_name);
            corbatur_context = CosNaming::NamingContext::_narrow (obj);
            if (CORBA::is_nil (corbatur_context))
            {
                std::cerr << "Failed to narrow naming context." << std::cerr;
                return 0;
            }
        }

        CosNaming::Name object_name;
        object_name.length (1);
        object_name[0].id = (const char *) "chat";
        object_name[0].kind = (const char *) "object";

        try
        {
            corbatur_context->bind (object_name, objref);
        }
        catch (CosNaming::NamingContext::AlreadyBound & ex)
        {
            corbatur_context->rebind (object_name, objref);
        }
    }
    catch (CORBA::TRANSIENT & ex)
    {
        std::cerr << "Caught system exception TRANSIENT -- unable to contact the naming service" << std::endl;
        std::cerr << "Mage sure the naming server is running and that omniORB is configured correctly." << std::endl;

        return 0;
    }
    catch (CORBA::SystemException & ex)
    {
        std::cerr << "Caught a CORBA::" << ex._name () << " while using the naming service." << std::endl;
        return 0;
    }

    return 1;
}
