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
#include <sstream>
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
            join_channel(message, user_id);
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
            change_topic(message, user_id);
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

// ERR_NEEDMOREPARAMS "<command> :Not enough parameters"
// ERR_NOSUCHCHANNEL "<channel> :No such channel" 
// ERR_BADCHANNELKEY "<channel> :Cannot join channel (+k)"
// ERR_CHANNELISFULL  "<channel> :Cannot join channel (+l)"
// ERR_INVITEONLYCHAN "<channel> :Cannot join channel (+i)"
// ERR_BANNEDFROMCHAN "<channel> :Cannot join channel (+b)" PROBABLY DONT NEED?
// RPL_TOPIC
void CommandParser::join_channel(std::string const& message, unsigned int user_id)
{
    std::string::size_type pos = message.find(" ");
    if (pos == std::string::npos || !message[pos + 1] || message.empty())
    {
        std::cout << "ERR_NEEDMOREPARAMS\n";
        return;
    }
    
}

//ERR_NEEDMOREPARAMS "<command> :Not enough parameters"
//RPL_NOTOPIC "<channel> :No topic is set"
//RPL_TOPIC "<channel> :<topic>"
//ERR_CHANOPRIVSNEEDED "<channel> :You're not channel operator"
//ERR_NOTONCHANNEL "<channel> :You're not on that channel"
void CommandParser::change_topic(std::string const& message, unsigned int user_id)
{
    std::string::size_type pos = message.find(" ");
    if (pos == std::string::npos || !message[pos + 1] || message.empty())
    {
        std::cout << "1 ERR_NEEDMOREPARAMS\n"; //TODO ERR
        return;
    }
    std::string channel = message.substr(pos + 1, message.length() - (pos + 1));
    pos = channel.find(" ");
    if (!channel[pos + 1])
    {
        std::cout << "2 ERR_NEEDMOREPARAMS\n"; //TODO ERR
        return;
    }
    std::string topic = channel.substr(pos + 1, channel.length() - (pos + 1));
    channel = channel.substr(0, pos);
    if (channel.empty())
    {
        std::cout << "3 ERR_NEEDMOREPARAMS\n"; //TODO ERR
        return;
    }
    std::cout << "CHANNEL:[" << channel << "]\n"; //delete
    std::cout << "TOPIC:[" << topic << "]\n"; //delete
    Channel& ref = m_ChannelDatabase.get_channel(channel);
    if (!ref.is_subscribed(user_id))
        std::cout << "ERR_NOTONCHANNEL\n"; //TODO ERR
    if (ref.if_channel_topic_empty())
        std::cout << "RPL_NOTOPIC\n"; //TODO RPL
    else if (!topic.empty())
        std::cout << "RPL_TOPIC\n"; //TODO RPL
    if (!ref.is_operator(user_id))
        std::cout << "ERR_CHANOPRIVSNEEDED\n"; // TODO ERR
    // ref.change_topic(user_id, topic);
}

//MODE #Finnish +il 100 Wiz
/* 
i - invite-only channel flag;
t - topic settable by channel operator only flag;
k - set a channel key (password).
o - give/take channel operator privileges
l - set the user limit to channel;
*/
void CommandParser::change_mode(std::string const& message, unsigned int user_id)
{
    user_id++; // delete
    std::string::size_type pos = message.find(" ");
    std::string split = message.substr(pos + 1, message.length() - (pos + 1));
    pos = split.find(" ");
    std::string channel = split.substr(0, pos);
    std::cout << "CHANNEL:[" << channel << "]\n";
    split.erase(0, split.find(" ") + 1);
    pos = split.find(" ");
    std::string flags = split.substr(0, pos);
    std::cout << "FLAGS:[" << flags << "]\n"; 
    split.erase(0, split.find(" ") + 1);
    std::vector<std::string> vec;
    pos = split.find(" ");
    while (pos != std::string::npos)
    {
        vec.push_back(split.substr(0, pos));
        split.erase(0, split.find(" ") + 1);
        pos = split.find(" ");
    }
    vec.push_back(split.substr(0, pos));
    for (unsigned int i = 0; i < vec.size(); i++)
        std::cout << "ARG" << i << ":[" << vec[i] << "]\n";
    if (1 || m_ChannelDatabase.is_channel(channel))
    {
        Channel& ref = m_ChannelDatabase.get_channel(channel);
        (void)ref;
        int mode = 0;
        for (unsigned int i = 0; i < flags.size(); i++)
        {
            switch (flags[i])
            {
                case '+':
                    mode = 1;
                    std::cout << "SETTING MODE TO 1\n";
                    break;
                case '-':
                    mode = -1;
                    std::cout << "SETTING MODE TO -1\n";
                    break;
                case 'i':
                    // ref.set_invite_only(user_id, mode);
                    std::cout << "SETTING INVITE ONLY TO MODE:" << mode << '\n';
                    break;
                case 't':
                    // ref.set_op_topic(user_id, mode);
                    std::cout << "SETTING OP_TOPIC TO MODE:" << mode << '\n';
                    break;
                case 'k':
                    std::cout << "SETTING KEY MODE TO:" << mode << "\nKEY WILL BE:" << vec[i - 1] << '\n';
                    // ref.set_password(user_id, mode, vec[i]);
                    break;
                case 'o':
                    std::cout << "SETTING OPERATOR TO:" << vec[i - 1] << '\n';
                    // ref.set_op(user_id, mode, vec[i]); //affect_id instead of vec[i]
                    break;
                case 'l':
                {
                    std::stringstream ss;
                    unsigned int user_limit;
                    ss << vec[i - 1];
                    ss >> user_limit;
                    std::cout << "SETTING USER LIMIT MODE:" << mode << "\nLIMIT:" << user_limit << "\n";
                    // ref.set_user_limit(user_id, mode, user_limit);
                    break;
                }
            }
        }
    }
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