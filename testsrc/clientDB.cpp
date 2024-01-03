/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientDB.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:56:33 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/03 17:27:56 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "tests.hpp"
#include "ClientDatabase.hpp"

void test1_client()
{
    std::cout << "Test1:\n";

    Client c;
    print(c.is_empty());
}

void test1_cdb()
{
    ClientDatabase db;
    // db.add_client("");
}

void test_clientDB()
{
    test1_client();
    test1_cdb();
}