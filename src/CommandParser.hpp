/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:39:37 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/24 19:09:44 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClientDatabase.hpp"
#include "ChannelDatabase.hpp"
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
        // CommandParser(); // delete?
        CommandParser(ClientDatabase& ClData, ChannelDatabase& ChData);

        command get_command_type(std::string const& message);
        void parser(std::string const& message, unsigned int user_id);

    private:
    
        std::map<std::string, command> m_commands;
        ClientDatabase& m_ClientDatabase;
        ChannelDatabase& m_ChannelDatabase;
        

        void send_privmsg(std::string const& message, unsigned int user_id);
        void change_topic(std::string const& message, unsigned int user_id);
        void change_mode(std::string const& message, unsigned int user_id);
        void send_ping(std::string const& message, unsigned int user_id);
        void send_pong(std::string const& message, unsigned int user_id);
};