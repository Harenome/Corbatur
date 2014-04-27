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

const char client::_ORBINITREF[] = "-ORBInitRef";

client::client (void)
{
}

client::client (const client & c)
: _program_name (c._program_name)
{
    _client_infos.name = c._client_infos.name;
    _client_infos.address = c._client_infos.address;
    _contacts = c._contacts;
}

client::client (const char * program_name, const std::string & name, const std::string & address)
: _program_name (program_name)
{
    _client_infos.name = name.c_str ();
    _client_infos.address = address.c_str ();
}

client::client (const char * program_name, const std::string & name, const std::string & address, const contact_manager & contacts)
: _program_name (program_name)
{
    _client_infos.name = name.c_str ();
    _client_infos.address = address.c_str ();
    _contacts = contacts;
}

client::~client (void)
{
}

void client::read_contacts (const char * file_path)
{
    contact_manager cm;
    std::ifstream file;
    file.open (file_path, std::ifstream::in);
    file >> cm;
    _contacts = cm;
}

void client::_reset_contacted (void)
{
    _contacted.clear ();
    for (contact_manager_const_iterator it = _contacts.begin (); it != _contacts.end (); ++it)
    {
        std::pair<std::string, bool> element (it->second.name (), false);
        _contacted.insert (element);
    }
}

int client::send_message_to_contact (const char * name, const char * m)
{
    std::string contact_name (name);
    return send_message_to_contact (contact_name, m);
}

int client::send_message_to_contact (const std::string & name, const char * m)
{
    _reset_contacted ();
    return _send_message_to_contact (name, m);
}

int client::_send_message_to_contact (const char * name, const char * m)
{
    std::string contact_name (name);
    return _send_message_to_contact (contact_name, m);
}

int client::_send_message_to_contact (const std::string & name, const char * m)
{
    return _send_message_to_contact (_contacts[name], m);
}

int client::_send_message_to_contact (const contact & c, const char * m)
{
    _contacted[c.name ()] = true;
    std::vector<std::string> addresses = c.addresses ();
    for (std::vector<std::string>::const_iterator it = addresses.begin (); it != addresses.end (); ++it)
        _send_message_to_address (it->c_str (), m);

    std::vector<std::string> aliases = c.aliases ();
    for (std::vector<std::string>::const_iterator it = addresses.begin (); it != addresses.end (); ++it)
        if (! _contacted[*it])
            _send_message_to_contact (* it, m);

    return 0;
}

int client::_send_message_to_address (const char * address, const char * m)
{
    try
    {
        int fake_argc = 3;
        std::string corbaname_address ("NameService=corbaname::");
        corbaname_address += address;
        char * fake_argv[3] = { (char *) _program_name, (char *) _ORBINITREF, (char *) corbaname_address.c_str () };

        CORBA::ORB_var orb = CORBA::ORB_init (fake_argc, fake_argv);
        CORBA::Object_var obj = client::_get_object_reference (orb);
        corbatur::chat_var chat_ref = corbatur::chat::_narrow (obj);

        if (CORBA::is_nil (chat_ref))
            std::cerr << "The object reference is nil!" << std::endl;
        else
            chat_ref->message (_client_infos, m);
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

void client::swap (client & c)
{
    std::swap (_program_name, c._program_name);
    std::swap (_client_infos.name, c._client_infos.name);
    std::swap (_client_infos.address, c._client_infos.address);
    _contacts.swap (c._contacts);
}

client & client::operator= (client c)
{
    this->swap (c);
    return * this;
}
