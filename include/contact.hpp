/**
 * \file contact.hpp
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
#ifndef __CONTACT_HPP__
#define __CONTACT_HPP__

#include <string>
#include <cstdio>
#include <vector>
#include <iostream>
#include <ostream>
#include <sstream>
#include <istream>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////////
// Classe.
///////////////////////////////////////////////////////////////////////////////

/**
 * \brief Gestion d'un contact.
 */
class contact
{
public:
    /**
     * \brief Constructeur.
     */
    contact (void);

    /**
     * \brief Constructeur par copie.
     * \param c Contact.
     */
    contact (const contact & c);

    /**
     * \brief Constructeur.
     * \param name Nom.
     */
    contact (const std::string & name);

    contact (const std::string & name, const std::vector<std::string> & addresses, const std::vector<std::string> & aliases);

    /**
     * \brief Destructeur.
     */
    ~contact (void);

    /**
     * \brief Obtenir le nom.
     * \return Nom.
     */
    std::string name (void) const;

    /**
     * \brief Obtenir les adresses associées.
     * \return Adresses.
     */
    std::vector<std::string> addresses (void) const;

    /**
     * \brief Obtenir les alias associés.
     * \return Alias.
     */
    std::vector<std::string> aliases (void) const;

    /**
     * \brief Déterminer si le contact a au moins une adresse connue.
     * \retval true Si le contact a au moins une addresse.
     * \retval false Sinon.
     */
    bool has_address (void) const;

    /**
     * \brief Déterminer si une adresse est associée au contact.
     * \param address Adresse recherchée.
     * \retval true Si l'adresse correspond.
     * \retval false Sinon.
     */
    bool has_this_address (const std::string & address) const;

    /**
     * \brief Déterminer si un contact est associé à au moins un alias.
     * \retval true Si le contact est associé à au moins un alias.
     * \retval false Sinon.
     */
    bool has_alias (void) const;

    /**
     * \brief Déterminer si un alias est associé au contact.
     * \param alias Alias recherché.
     * \retval true Si l'alias correspond.
     * \retavl false Sinon.
     */
    bool has_this_alias (const std::string & alias) const;

    /**
     * \brief Changer le nom du contact.
     * \param name Nouveau nom.
     */
    void set_name (const std::string & name);

    /**
     * \brief Ajouter une adresse.
     * \param address Adresse.
     */
    void add_address (const std::string & address);

    /**
     * \brief Retirer une addresse.
     * \param address Addresse.
     */
    void remove_address (const std::string & address);

    /**
     * \brief Retirer une adresse.
     * \param index Index.
     */
    void remove_address (unsigned int index);

    /**
     * \brief Ajouter un alias.
     * \param alias Alias.
     */
    void add_alias (const std::string & alias);

    /**
     * \brief Retirer un alias.
     * \param alias Alias
     */
    void remove_alias (const std::string & alias);

    /**
     * \brief Retirer un alias.
     * \param index Index.
     */
    void remove_alias (unsigned int index);

    /**
     * \brief Échanger.
     * \param c Contact.
     */
    void swap (contact & c);

    /**
     * \brief Opérateur \c =
     * \param c Contact.
     */
    contact & operator= (contact c);

    /**
     * \brief Écrire dans un flux.
     * \param os Flux.
     * \return \c os.
     */
    std::ostream & write_to_stream (std::ostream & os) const;

private:
    std::string _name;                      /**<- Nom. */
    std::vector<std::string> _aliases;      /**<- Alias. */
    std::vector<std::string> _addresses;    /**<- Adresses. */

    /**
     * \brief Déterminer si une valeur est présente.
     * \param list Liste.
     * \param value Valeur.
     * \retval true Si la valeur se trouve dans la liste.
     * \retval false Sinon.
     */
    static bool _has_value (const std::vector<std::string> & list, const std::string & value);

    /**
     * \brief Retirer une valeur.
     * \param list Liste.
     * \param value Valeur.
     */
    static void _remove_from (std::vector<std::string> & list, const std::string & value);

    /**
     * \brief Retirer une valeur.
     * \param list Liste.
     * \param index Index.
     */
    static void _remove_from (std::vector<std::string> & list, unsigned int index);

    /**
     * \brief Écrire un vector dans un flux.
     * \param os Flux de sortie.
     * \param list Vector.
     */
    static std::ostream & _write_vector (std::ostream & os, const std::vector<std::string> & list);
};

///////////////////////////////////////////////////////////////////////////////
// Fonctions non membres.
///////////////////////////////////////////////////////////////////////////////

/**
 * \brief Écrire dans un flux.
 * \param[in,out] os Flux de sortie.
 * \param[in] c Contact.
 * \return \c os.
 * \relates contact
 */
std::ostream & operator<< (std::ostream & os, const contact & c);

std::istream & operator>> (std::istream & is, contact & c);

/**
 * \brief Échanger.
 * \param[in,out] a Contact.
 * \param[in,out] b Contact.
 * \return \c os.
 * \relates contact
 */
inline void swap (contact & a, contact & b)
{
    a.swap (b);
}

#endif /* __CONTACT_HPP__ */
