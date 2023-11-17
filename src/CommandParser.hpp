/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:39:37 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/17 16:33:48 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>

enum command
{
    ERR_NO_CMD,
    PRIVMSG,
    JOIN,
    NICK,
    USER,
    PASS,
    QUIT,
    KICK,
    INVITE,
    TOPIC,
    MODE,
    PING,
    PONG
};

class CommandParser
{
    public:
        //Constructors
        CommandParser();

        command get_command_type(std::string const& message);

    private:

         std::map<std::string, command> m_commands;
};