/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:39:37 by emajuri           #+#    #+#             */
/*   Updated: 2024/02/13 12:50:43 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClientDatabase.hpp"
#include "ChannelDatabase.hpp"
#include "Reply.hpp"

#include <string>
#include <map>

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
    CAP
};

class CommandParser
{
    public:
        CommandParser() = delete;
        CommandParser(ClientDatabase& ClData, ChannelDatabase& ChData, std::string const& start_time, std::string const& password);

        command get_command_type(std::string const& message);
        void parser(std::string const& message, unsigned int user_id);

    private:
    
        std::map<std::string, command> m_commands;

        ClientDatabase& m_client_database;
        ChannelDatabase& m_channel_database;
        Reply m_reply;

        std::string const m_password;
        
        void send_privmsg(std::string const& arguments, unsigned int user_id);
        void join_channel(std::string const& arguments, unsigned int user_id);
        void change_nick(std::string const& arguments, unsigned int user_id);
        void user_register(std::string const& arguments, unsigned int user_id);
        void connection_password(std::string const& arguments, unsigned int user_id);
        void quit_server(std::string const& arguments, unsigned int user_id);
        void kick_user(std::string const& arguments, unsigned int user_id);
        void invite_user(std::string const& arguments, unsigned int user_id);
        void change_topic(std::string const& arguments, unsigned int user_id);
        void change_mode(std::string const& arguments, unsigned int user_id);
        void receive_ping(std::string const& arguments, unsigned int user_id);
        void answer_cap(std::string const& arguments, unsigned int user_id);
        void part_command(std::string const& arguments, unsigned int user_id);

        std::string get_current_modes(std::string channel_name);
};
