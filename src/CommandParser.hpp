/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:39:37 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/25 14:22:38 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClientDatabase.hpp"
#include "ChannelDatabase.hpp"
#include <string>
#include <map>
#include "Reply.hpp"

enum command
{
    ERR_NO_CMD,
    PRIVMSG,
    JOIN,
    QUIT,
    KICK,
    INVITE,
    TOPIC,
    MODE,
    PART,
    NICK = 100,
    USER,
    PASS,
    PING,
    PONG,
    CAP
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
        Reply m_reply;
        

        void send_privmsg(std::string const& message, unsigned int user_id);
        void join_channel(std::string const& message, unsigned int user_id);
        void change_nick(std::string const& message, unsigned int user_id);
        void user_register(std::string const& message, unsigned int user_id);
        void connection_password(std::string const& message, unsigned int user_id);
        void quit_server(std::string const& message, unsigned int user_id);
        void kick_user(std::string const& message, unsigned int user_id);
        void invite_user(std::string const& message, unsigned int user_id);
        void change_topic(std::string const& message, unsigned int user_id);
        void change_mode(std::string const& message, unsigned int user_id);
        void receive_ping(std::string const& message, unsigned int user_id);
        void receive_pong(std::string const& message, unsigned int user_id);
        void answer_cap(std::string const& message, unsigned int user_id);
        void part_command(std::string const& message, unsigned int user_id);
};
