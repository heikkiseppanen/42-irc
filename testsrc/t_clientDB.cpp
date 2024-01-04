/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_clientDB.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:26:14 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/04 14:40:04 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"
#include "ClientDatabase.hpp"
#include <vector>

//test adding and removing
void test1_cdb()
{
    ClientDatabase db;

    for (unsigned int i = 0; i < 10; i++)
    {
        if (db.add_client() != i)
            TEST_ERROR("Error adding client")
        if (db.is_client(i))
            TEST_ERROR("Client not empty after add")
    }

    for (unsigned int i = 0; i < 10; i++)
    {
        db.get_client(i).set_nickname("a");
        if (!db.is_client(i))
            TEST_ERROR("Error getting client")
        db.remove_client(i);
        if (db.is_client(i))
            TEST_ERROR("Error removing client")
    }
    print(true);
}

//Testing adding messages to a group
void    test2_cdb()
{
    ClientDatabase db;
    std::vector<unsigned int> ids;

    for (unsigned int i = 0; i < 10; i++)
    {
        unsigned int y = db.add_client();
        ids.push_back(y);
        if (y != i)
            TEST_ERROR("Error adding client")
        if (db.is_client(i))
            TEST_ERROR("Client not empty after add")
        db.get_client(i).set_nickname("name");
    }
    db.add_messages_to_group(ids, 0, std::make_shared<std::string>("Message"));
    if (db.get_client(0).has_message())
        TEST_ERROR("message to group exclude didn't work")
    for (unsigned int i = 1; i < 10; i++)
    {
        if (!db.get_client(i).has_message())
            TEST_ERROR("Didn't add message to all")
        if (db.get_client(i).get_message() != "Message")
            TEST_ERROR("Message added incorrectly")
    }
    print(true);
}

void test_clientDB()
{
    std::cout << "ClientDatabase:\n";
    test1_cdb();
    test2_cdb();
}