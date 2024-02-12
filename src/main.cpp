/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:55:15 by emajuri           #+#    #+#             */
/*   Updated: 2024/02/12 12:55:17 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include <iostream>
#include <exception>

static bool is_valid_port(const std::string_view port)
{
    auto is_digit = [](char c)
    {
        return std::isdigit(static_cast<unsigned int>(c));
    };

    return port.size() == 4
        && std::find_if_not(port.begin(), port.end(), is_digit) == port.end();
}

static bool is_valid_password(const std::string_view port)
{
    std::size_t constexpr max_password_size = 32;

    auto is_valid_character = [](char c)
    {
        unsigned int cint = static_cast<unsigned int>(c);
        return std::isprint(cint) && !std::isspace(cint);
    };

    return port.size() <= max_password_size
        && std::find_if_not(port.begin(), port.end(), is_valid_character) == port.end();
}

int main(int argc, char *argv[])
{
    try
    {
        if (argc < 2 || 3 < argc)
        {
            throw std::runtime_error("Invalid argument count");
        }

        const char* port = argv[1];
        if (!is_valid_port(port))
        {
            throw std::runtime_error("Invalid port");
        }

        const char* password = (argc == 3) ? argv[2] : NULL;
        if (password && !is_valid_password(password))
        {
            throw std::runtime_error("Invalid password");
        }

        Server irc(port, password);
        irc.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "irc: " << e.what() << '\n'; 
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
