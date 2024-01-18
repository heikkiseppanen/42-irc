/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_clientDB.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:26:14 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/17 18:09:48 by emajuri          ###   ########.fr       */
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
    ok();
}

void test_clientDB()
{
    std::cout << "ClientDatabase:\n";
    test1_cdb();
}