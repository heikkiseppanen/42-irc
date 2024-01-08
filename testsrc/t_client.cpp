/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_client.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:56:33 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/16 14:31:05 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include "tests.hpp"
#include "Client.hpp"

void test1_client()
{
    Client c;

    if (!c.is_empty())
        TEST_ERROR("Client not empty on creation");
    ok();
}

//nickname
void test2_client()
{
    Client c;

    c.set_nickname("Hello");
    if (c.get_nickname() != "Hello")
        TEST_ERROR("Error setting nickname");
    ok();
}

//messageque
void test3_client()
{
    Client c;

    if (c.has_message())
        TEST_ERROR("Messages not empty on construction");
    c.add_message(std::make_shared<std::string>("Message1"));
    if (!c.has_message())
        TEST_ERROR("Can't add messages");
    if (c.get_message() != "Message1")
        TEST_ERROR("Message added incorrectly");
    c.remove_message();
    if (c.has_message())
        TEST_ERROR("Message removed incorrectly");
    ok();
}

//registered
void test4_client()
{
    Client c;

    if (c.is_registered())
        TEST_ERROR("Client registered on construction");
    c.nick_received();
    if (c.is_registered())
        TEST_ERROR("Client registered only with nick received");
    c.user_received();
    if (c.is_registered())
        TEST_ERROR("Client registered without pass received");
    c.password_received();
    if (!c.is_registered())
        TEST_ERROR("Client not registered when should be");

    c.empty_client();
    c.user_received();
    if (c.is_registered())
        TEST_ERROR("Client registered only with user received");

    ok();
}

//same msg on multiple clients
void test5_client()
{
    Client c;
    Client d;

    std::shared_ptr<std::string> pmsg = std::make_shared<std::string>("Message");
    c.add_message(pmsg);
    d.add_message(pmsg);
    if (!c.has_message())
        TEST_ERROR("Adding msg on c failed");
    if (!d.has_message())
        TEST_ERROR("Adding msg on d failed");
    if (c.get_message() != "Message")
        TEST_ERROR("Incorrect msg on c");
    if (d.get_message() != "Message")
        TEST_ERROR("Incorrect msg on d");
    c.remove_message();
    if (c.has_message())
        TEST_ERROR("Remove message failed");
    if (d.get_message() != "Message")
        TEST_ERROR("Removing message on another client affected other one");
    ok();
}

//buffer tests
void test6_client()
{
    Client c;

    c.add_to_buffer("Messa");
    c.add_to_buffer("ge1");
    c.add_to_buffer("\nseco");
    c.add_to_buffer("ndMessage");

    if (c.get_buffer() != "Message1\nsecondMessage")
        TEST_ERROR("Adding to buffer failed");
    c.remove_from_buffer(8);
    if (c.get_buffer() != "\nsecondMessage")
        TEST_ERROR("Removing from buffer failed");
    ok();
}

//sent count tests
void test7_client()
{
    Client c;

    c.set_sent_count(120);
    if (c.get_sent_count() != 120)
        TEST_ERROR("Set/Get sent_count failed");
    ok();
}

void test_client()
{
    std::cout << "Client:\n";
    test1_client();
    test2_client();
    test3_client();
    test4_client();
    test5_client();
    test6_client();
    test7_client();
}