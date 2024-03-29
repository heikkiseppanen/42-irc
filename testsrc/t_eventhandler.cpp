/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_eventhandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:58:55 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/15 19:25:12 by emajuri          ###   ########.fr       */
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

    c.add_to_buffer("hello world!\r\n");
    if (!find_command(cmd, c))
        TEST_ERROR("Find command not finding command");
    if (cmd != "hello world!")
        TEST_ERROR("Incorrect command found");
    if (c.get_buffer().length() != 0)
        TEST_ERROR("Erased incorrectly");
    if (find_command(cmd, c))
        TEST_ERROR("Finding on empty buffer");


    c.add_to_buffer("hello world!");
    if (find_command(cmd, c))
        TEST_ERROR("Finding command when there is no end");
    c.add_to_buffer("\r");
    if (find_command(cmd, c))
        TEST_ERROR("Finding command when there is no end");
    c.add_to_buffer("\n");
    if (!find_command(cmd, c))
        TEST_ERROR("not finding command");
    if (cmd != "hello world!")
        TEST_ERROR("Incorrect command found");
    if (c.get_buffer().length() != 0)
        TEST_ERROR("Erased incorrectly");
    if (find_command(cmd, c))
        TEST_ERROR("Finding on empty buffer");


    c.add_to_buffer("Hello\r\nHello\r\nHello\r\nHello\r\nHello\r\nHello\r\nHello\r\nHello\r\nHello\r\nHello\r\nHello\r\n\n");
    while (find_command(cmd, c))
    {
        if (cmd != "Hello")
            TEST_ERROR("Incorrect command found")
    }
    if (c.get_buffer().length() != 1)
        TEST_ERROR("Erased incorrectly");
    c.add_to_buffer("\r\n");
    if (!find_command(cmd, c))
        TEST_ERROR("not finding command");
    if (c.get_buffer().length() != 0)
        TEST_ERROR("Erased incorrectly");
    
    c.add_to_buffer("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    size_t old_len = c.get_buffer().length();
    if (find_command(cmd, c))
        TEST_ERROR("Found command without end");
    if (c.get_buffer().length() != old_len - 512)
        TEST_ERROR("Doesnt erase the correct amount");
    ok();
}

void test_eventhandler()
{
    std::cout << "Eventhandler:\n";
    test1_handler();
}