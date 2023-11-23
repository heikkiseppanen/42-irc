/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:04:54 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/23 14:47:13 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandParser.hpp"
#include <iostream>
#include <vector>

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
: m_ClientData(ClData), m_ChannelData(ChData)
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
            send_privmsg(message, user_id);
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
            send_pong(message, user_id);
            break;
    }
}

//"PRIVMSG aaa,bbb,ccc :message to be sent"
std::vector<std::string> get_targets(std::string const& message, unsigned int skip)
{
    std::string::size_type pos = message.find(":");
    if (std::string::npos == pos)
        std::cout << "not found";
    std::cout << "found:" << message.substr(skip, pos);
    std::vector<std::string> vec;
    return vec;
}

void CommandParser::send_privmsg(std::string const& message, unsigned int user_id)
{
    user_id++; // delete
    std::cout << "TYPE: PRIVMSG | ORIGIN:" << user_id << '\n';
    std::vector<std::string> targets = get_targets(message, 7);
    //TODO IF CHANNEL EXISTS
        //return (ERR_CANNOTSENDTOCHAN);
    //TODO IF TARGET EXISTS IN DATABASE
        //return (ERR_NORECIPIENT);
    //TODO IF NICK EXISTS IN DATABASE
        //return (ERR_NOSUCHNICK);
    //TODO IF NO TEXT TO SEND
        // return (ERR_NOTEXTTOSEND);
    //TODO IF TOO MANY TARGETS
        // return (ERR_TOOMANYTARGETS);
    //ERR_WILDTOPLEVEL
    //ERR_NOTOPLEVEL
    //RPL_AWAY
}

void CommandParser::send_ping(std::string const& message, unsigned int user_id)
{
    user_id++; // delete
    std::string target = message.substr(5, message.length() - 5);
    std::cout << "TYPE:PING | ORIGIN:" << user_id << " | " << "TARGET:" << target << "\n"; // delete
    //ERR_NOORIGIN
    //ERR_NOSUCHSERVER
}

void CommandParser::send_pong(std::string const& message, unsigned int user_id)
{
    user_id++; // delete
    std::string target = message.substr(5, message.length() - 5);
    std::cout << "TYPE:PONG | ORIGIN:" << user_id << " | " << "TARGET:" << target << "\n"; // delete
    /*TODO IF TARGET EXISTS IN DATABASE*/
    //ERR_NOORIGIN
    //ERR_NOSUCHSERVER
}