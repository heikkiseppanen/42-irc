/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientDB.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:56:33 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/03 18:53:53 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "tests.hpp"
#include "ClientDatabase.hpp"
#include <memory>
#include <string>

void test1_client()
{
    Client c;
    print(c.is_empty());
}

//nickname
void test2_client()
{
    Client c;

    c.set_nickname("Hello");
    print(c.get_nickname() == "Hello");
}

//messageque
void test3_client()
{
    Client c;

    if (c.has_message())
        return print(false);
    c.add_message(std::make_shared<std::string>("Message1"));
    if (c.has_message() == false)
        return print(false);
    std::string msg = c.get_message();
    if (msg != "Message1")
        return print(false);
    c.remove_message();
    if (c.has_message())
        return print(false);
    print(true);
}

//registered
void test4_client()
{
    Client c;

    if (c.is_registered() != false)
        return print(false);
    c.nick_received();
    if (c.is_registered() != false)
        return print(false);
    c.user_received();
    if (c.is_registered() == false)
        return print(false);
    print(true);
}

void test1_cdb()
{
    ClientDatabase db;
    // db.add_client("");
}

void test_clientDB()
{
    std::cout << "Client:\n";
    test1_client();
    test2_client();
    test3_client();
    test4_client();


    test1_cdb();
}