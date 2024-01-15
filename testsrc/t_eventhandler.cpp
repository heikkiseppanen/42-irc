/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_eventhandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:58:55 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/15 17:13:27 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"
#include <iostream>
#include "EventHandler.hpp"

bool find_command(std::string& command, Client& client);

//find_command
void test1_handler()
{
    Client c;
    std::string cmd;

    //\r\n
    c.add_to_buffer("hello world!\r\n");
    if (find_command(cmd, c) != true)
        TEST_ERROR("Find command not finding command");
    if (cmd != "hello world!")
        TEST_ERROR("Incorrect command found");
    if (c.get_buffer().length() != 0)
        TEST_ERROR("Erased incorrectly");
    ok();
}

void test_eventhandler()
{
    std::cout << "Eventhandler:\n";
    test1_handler();
}