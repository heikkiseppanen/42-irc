/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:04:54 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/22 16:53:22 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandParser.hpp"
#include <iostream>

// CommandParser::CommandParser()
// {
//     m_commands["PRIVMSG"] = PRIVMSG;
//     m_commands["JOIN"] = JOIN;
//     m_commands["NICK"] = NICK;
//     m_commands["USER"] = USER;
//     m_commands["PASS"] = PASS;
//     m_commands["QUIT"] = QUIT;
//     m_commands["KICK"] = KICK;
//     m_commands["INVITE"] = INVITE;
//     m_commands["TOPIC"] = TOPIC;
//     m_commands["MODE"] = MODE;
//     m_commands["PING"] = PING;
//     m_commands["PONG"] = PONG;
// }

CommandParser::CommandParser(ClientDatabase& ClData, ChannelDatabase& ChData) 
: m_ClData(ClData), m_ChData(ChData)
{
    m_commands["PRIVMSG"] = PRIVMSG;
    m_commands["JOIN"] = JOIN;
    m_commands["NICK"] = NICK;
    m_commands["USER"] = USER;
    m_commands["PASS"] = PASS;
    m_commands["QUIT"] = QUIT;
    m_commands["KICK"] = KICK;
    m_commands["INVITE"] = INVITE;
    m_commands["TOPIC"] = TOPIC;
    m_commands["MODE"] = MODE;
    m_commands["PING"] = PING;
    m_commands["PONG"] = PONG;
}

command CommandParser::get_command_type(std::string const& message)
{
    std::size_t pos = message.find(" ");
    if (pos == std::string::npos)
        return ERR_NO_CMD;
    std::string cmd = message.substr(0, pos);
    std::map<std::string, command>::iterator it = m_commands.find(cmd);
    if (it == m_commands.end())
        return ERR_NO_CMD;
    return it->second;
}

void    CommandParser::parser(std::string const& message, unsigned int user_id)
{ 
    command cmd = get_command_type(message);
    switch (cmd)
    {
        case ERR_NO_CMD:
            //TODO
            break;
        case PRIVMSG:
            // send_privmsg(message, user_id);
            break;
        case JOIN:
            //TODO
            break;
        case NICK:
            //TODO
            break;
        case USER:
            //TODO
            break;
        case PASS:
            //TODO
            break;
        case QUIT:
            //TODO
            break;
        case KICK:
            //TODO
            break;
        case INVITE:
            //TODO
            break;
        case TOPIC:
            //TODO
            break;
        case MODE:
            //TODO
            break;
        case PING:
            send_ping(message, user_id);
            break;
        case PONG:
            // send_pong(message, user_id);
            break;
    }
}

void CommandParser::send_privmsg(std::string const& message, unsigned int user_id)
{
    if (message[6] != ' ')
        std::cout << "FAIL\n";
    std::cout << "SUCCESS\n";
}

void CommandParser::send_ping(std::string const& message, unsigned int user_id)
{
    std::string target = message.substr(5, message.length() - 5);
    /*TODO IF TARGET EXISTS IN DATABASE*/
}

void send_pong(std::string const& message, unsigned int user_id)
{
    std::string target = message.substr(5, message.length() - 5);
    /*TODO IF TARGET EXISTS IN DATABASE*/
}