/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:04:54 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/23 19:22:18by jole             ###   ########.fr       */
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
: m_ClientDatabase(ClData), m_ChannelDatabase(ChData)
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
    (void)m_ClientDatabase; //delete
    
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
            change_mode(message, user_id);
            break;
        case PING:
            send_ping(message, user_id);
            break;
        case PONG:
            send_pong(message, user_id);
            break;
    }
}

std::vector<std::string> get_targets(std::string const& message, unsigned int skip)
{
    std::string::size_type pos = message.find(":");
    std::string substr = message.substr(skip + 1, pos);
    pos = substr.find(" ");
    substr = substr.substr(0, pos);
    std::vector<std::string> vec;
    pos = substr.find(",");
    while (pos != std::string::npos)
    {
        vec.push_back(substr.substr(0, pos));     
        substr.erase(0, substr.find(",") + 1);
        pos = substr.find(",");
    }
    vec.push_back(substr);
    return (vec);
}

int check_if_channel(std::vector<std::string> targets)
{
    for (unsigned int i = 0; i < targets.size(); i++)
    {
        if (targets[i][0] == '#')
        {
            if (i + 1 == targets.size())
                return (1);
            continue;
        }
    }
    return 0;
}

int create_text(std::string const& message, std::string &text)
{
    std::string::size_type pos = message.find(" ");
    text = message.substr(pos + 1, message.length() - pos);
    pos = text.find(" ");
    text = text.substr(pos + 1, text.length() - pos);
    if (text[0] == ':')
        text = text.substr(1, text.length() - 1);
    if (text[0] == '\0')
        return (0);
    return (1);
}

void CommandParser::send_privmsg(std::string const& message, unsigned int user_id)
{
    user_id++; // delete
    std::cout << "MESSAGE:" << message << '\n'; //delete
    std::vector<std::string> targets = get_targets(message, 7);
    
    if (check_if_channel(targets) == 1)
    {
        for (unsigned int i = 0; i < targets.size(); i++)
        {
            if (m_ChannelDatabase.is_channel(targets[i]))
            {
                if (i == targets.size())
                    std::cout << "SEND MSG TO CHANNELS\n"; //TODO SEND MSG TO CHANNEL
                continue;            
            }
        }
        std::cout << "ERR_CANNOTSENDTOCHAN\n"; //return (ERR_CANNOTSENDTOCHAN);
    } 
    else
    {
        //TODO IF TARGET(S) EXISTS IN DATABASE
            //return (ERR_NORECIPIENT);
        //TODO IF NICK EXISTS IN DATABASE
            //return (ERR_NOSUCHNICK);
    std::string text;
    if (!create_text(message, text))
            std::cout << "ERR_NOTEXTTOSEND\n"; // return (ERR_NOTEXTTOSEND);
    std::cout << "TEXT:[" << text << "]\n";  //delete
        //TODO IF TOO MANY TARGETS
            // return (ERR_TOOMANYTARGETS);
    //ERR_WILDTOPLEVEL
    //ERR_NOTOPLEVEL
    }
}

void CommandParser::change_mode(std::string const& message, unsigned int user_id)
{
    // i set/remove invite only
    // t set/remove restrictions of topic command to operaators
    // k set/remove channel password
    // o give/take channel operator priviledge
}

void CommandParser::send_ping(std::string const& message, unsigned int user_id)
{
    user_id++; // delete
    std::string target = message.substr(5, message.length() - 5);
    std::cout << "TYPE:PING | ORIGIN:" << user_id << " | " << "TARGET:" << target << "\n"; // delete
    /*TODO IF TARGET EXISTS IN DATABASE*/
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