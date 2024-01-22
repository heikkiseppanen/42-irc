/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:04:54 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/23 16:21:47 by emajuri          ###   ########.fr       */
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
: m_ClientDatabase(ClData), m_ChannelDatabase(ChData),
  m_reply(m_ClientDatabase)
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
    m_commands["CAP"] = CAP;
}

command CommandParser::get_command_type(std::string const& message)
{
    std::size_t pos = message.find(" ");
    std::string cmd;
    if (pos == std::string::npos)
        cmd = message.substr(0, message.length());
    else
        cmd = message.substr(0, pos);
    std::map<std::string, command>::iterator it = m_commands.find(cmd);
    if (it == m_commands.end())
        return ERR_NO_CMD;
    return it->second;
}

void    CommandParser::parser(std::string const& message, unsigned int user_id)
{
    command cmd = get_command_type(message);
    if (cmd < 100)
    {
        if (!m_ClientDatabase.get_client(user_id).is_registered())
            return;
    }
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
        case QUIT:
            quit_server(message, user_id);
            break;
        case KICK:
            kick_user(message, user_id);
            break;
        case INVITE:
            invite_user(message, user_id);
            break;
        case TOPIC:
            change_topic(message, user_id);
            break;
        case MODE:
            change_mode(message, user_id);
            break;
        case NICK:
            change_nick(message,user_id);
            break;
        case USER:
            user_register(message, user_id);
            break;
        case PASS:
            connection_password(message, user_id);
            break;
        case PING:
            receive_ping(message, user_id);
            break;
        case PONG:
            receive_pong(message, user_id);
            break;
        case CAP:
            answer_cap(message, user_id);
            break;
    }
}

std::string remove_prefix(std::string const&message, unsigned int size)
{
    return (message.substr(size + 1, message.length() - size - 1));
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

std::vector<std::string> split_string_to_vector(std::string string, std::string delim)
{
    std::vector<std::string> vec;
    std::string::size_type pos = string.find(delim);
    while (pos != std::string::npos)
    {
        vec.push_back(string.substr(0, pos));
        string.erase(0, string.find(delim) + 1);
        pos = string.find(delim);
    }
    vec.push_back(string.substr(pos + 1, string.length() - pos - 1));
    return (vec);
}

void CommandParser::send_privmsg(std::string const& message, unsigned int user_id)
{
    (void)user_id;
    //TODO add these checks
    // else
    // {
    //     //TODO IF TARGET(S) EXISTS IN DATABASE
    //         //return (ERR_NORECIPIENT);
    //     //TODO IF NICK EXISTS IN DATABASE
    //         //return (ERR_NOSUCHNICK);
    // std::string text;
    // if (!create_text(message, text))
    //         std::cout << "ERR_NOTEXTTOSEND\n"; // return (ERR_NOTEXTTOSEND);
    // std::cout << "TEXT:[" << text << "]\n";  //delete
    //     //TODO IF TOO MANY TARGETS
    //         // return (ERR_TOOMANYTARGETS);
    // //TODO SEND TEXT TO ALL TARGETS
    // }
    if (message.length() < 9)
    {
        m_reply.reply_to_sender(ERR_NORECIPIENT, user_id, {":No recipient given (" + message + ")"});
        return;
    }
    std::vector<std::string> targets = get_targets(message, 7);
    if (targets.size() == 0)
    {
        m_reply.reply_to_sender(ERR_NORECIPIENT, user_id, {":No recipient given (" + message + ")"});
        return;
    }
    for (auto& target : targets)
    {
        if (target[0] == '#')
        {
            if (!m_ChannelDatabase.is_channel(target))
            {
                m_reply.reply_to_sender(ERR_CANNOTSENDTOCHAN, user_id, {target, " :Cannot sent to channel"});
            }
            else
            {
                for (auto user : m_ChannelDatabase.get_channel(target).get_users())
                {
                    //TODO remove multiple targets
                    m_ClientDatabase.get_client(user).add_message(":" + m_ClientDatabase.get_client(user_id).get_nickname() + " " + message);
                }
            }
        }
        else if (m_ClientDatabase.is_nick_in_use(target))
        {
            m_ClientDatabase.get_client(m_ClientDatabase.get_user_id(target)).add_message(":" + m_ClientDatabase.get_client(user_id).get_nickname() + " " + message);
        }
        else
        {
            //TODO remove multiple targets
            //TODO change to nosuchnick
            m_reply.reply_to_sender(ERR_NORECIPIENT, user_id, {":No recipient given (" + message + ")"});
        }
    }
}

// ERR_NEEDMOREPARAMS "<command> :Not enough parameters"
// ERR_NOSUCHCHANNEL "<channel> :No such channel" 
// ERR_CHANNELISFULL  "<channel> :Cannot join channel (+l)"
// ERR_INVITEONLYCHAN "<channel> :Cannot join channel (+i)"
// ERR_BADCHANNELKEY "<channel> :Cannot join channel (+k)"
// RPL_TOPIC
void CommandParser::join_channel(std::string const& message, unsigned int user_id)
{
    if (message.length() <= 4)
    {
        std::cout << "ERR_NEEDMOREPARAMS\n";
        return;
    }
    std::string args = remove_prefix(message, 4);
    std::string::size_type pos = args.find(" ");
    std::string first_arg = args.substr(0, pos);
    std::string second_arg = args.substr(pos + 1, args.length() - pos - 1);
    std::vector<std::string> vec;
    std::stringstream ss(first_arg);
    std::string item;
    while (getline (ss, item, ','))
        vec.push_back(item);
    std::stringstream ss2(second_arg);
    std::vector<std::string> vec2;
    while (getline (ss2, item, ','))
        vec2.push_back(item);
    if (vec.size() != vec2.size())
    {
        std::cout << "ERR_NEEDMOREPARAMS\n";
        return;
    }
    for (unsigned int i = 0; i < vec.size();)
    {
        if (!m_ChannelDatabase.is_channel(vec[i]))
        {
            std::cout << "Channel doesn't exist\n"; //ERR NOSUCHCHANNEL
            m_reply.reply_to_sender(ERR_NOSUCHCHANNEL, user_id, {vec[i], " :No such channel"});
            i++;
            continue;
        }
        Client& client = m_ClientDatabase.get_client(user_id);
        Channel& channel = m_ChannelDatabase.get_channel(vec[i]);
        //TODO make sure that vec2 has something and no out of bounds accessing
        //TODO add return value handling
        channel.join_channel(user_id, vec2[i]);
        client.add_message(":localhost " + client.get_nickname() + " JOIN " + vec[i]);
        m_reply.reply_to_sender(RPL_TOPIC, user_id, {vec[i], " :", channel.get_topic()});
        //TODO rpl_namreply
        for (auto user : channel.get_users())
        {
            //TODO remove multiple targets
            m_ClientDatabase.get_client(user).add_message(":" + m_ClientDatabase.get_client(user_id).get_nickname() + " " + message);
        }
        i++;
    }
}

// ERR_NONICKNAMEGIVEN ":No nickname given"
// ERR_ERRONEUSNICKNAME "<nick> :Erroneous nickname"
// ERR_NICKNAMEINUSE "<nick> :Nickname is already in use"
void CommandParser::change_nick(std::string const& message, unsigned int user_id)
{
    Client& client = m_ClientDatabase.get_client(user_id);
    //if (server_has_no_password)
    client.password_received();
    if (!client.has_password())
    {
        std::cout << "User has not used PASS message\n";
        //TODO ERR
        return;
    }
    std::string nick = remove_prefix(message, 4);
    std::cout << "nick:[" << nick << "]\n";
    if (nick.empty())
    {
        m_reply.reply_to_sender(ERR_NONICKNAMEGIVEN, user_id, {":No nickname given"});
        return;
    }
    if (nick.size() > 9)
    {
        m_reply.reply_to_sender(ERR_ERRONEUSNICKNAME, user_id, {nick, " :Erroneous nickname"});
        return;
    }
    if (m_ClientDatabase.is_nick_in_use(nick))
    {
        m_reply.reply_to_sender(ERR_NICKNAMEINUSE, user_id, {nick, " :Nickname is already in use"});
        return;
    }
    std::string first_set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ[]\''_^{|}";
    std::string second_set = "-0123456789" + first_set;
    std::string::size_type pos;
    for (unsigned int i = 0; i < nick.size(); i++)
    {
        if (i == 0)
        {
            pos = first_set.find(nick[i]);
            if (pos == std::string::npos)
            {
                m_reply.reply_to_sender(ERR_ERRONEUSNICKNAME, user_id, {nick, " :Erroneous nickname"});
                return;
            }
        }
        else
        {
            pos = second_set.find(nick[i]);
            if (pos == std::string::npos)
            {
                m_reply.reply_to_sender(ERR_ERRONEUSNICKNAME, user_id, {nick, " :Erroneous nickname"});
                return;
            }
        }
    }
    client.set_nickname(nick);
    if (!client.has_nick() && client.has_user() && client.has_password())
        m_reply.reply_welcome(user_id, m_ChannelDatabase.count_channels());
    client.nick_received();
}

// ERR_NEEDMOREPARAMS
// ERR_ALREADYREGISTERED
void CommandParser::user_register(std::string const& message, unsigned int user_id)
{
    Client& client = m_ClientDatabase.get_client(user_id);
    //if (server_has_no_password)
    client.password_received();
    if (!client.has_password())
    {
        std::cout << "User has not used PASS message\n";
        //TODO ERR
        return;
    }
    if (message.length() == 4)
    {
        m_reply.reply_to_sender(ERR_NEEDMOREPARAMS, user_id, {"USER :Not enough parameters"});
        return;
    }
    std::string args = remove_prefix(message, 4);
    std::vector<std::string> vec;
    std::string::size_type pos = args.find(" ");
    for (unsigned int i = 0; pos != std::string::npos && i < 3; i++)
    {
        vec.push_back(args.substr(0, pos));
        args.erase(0, args.find(" ") + 1);
        pos = args.find(" ");
    }
    vec.push_back(args);
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        std::cout << "arg " << i << ":[" << vec[i] << "]\n"; //delete
    }
    if (vec.size() < 4)
    {
        m_reply.reply_to_sender(ERR_NEEDMOREPARAMS, user_id, {"USER :Not enough parameters"});
        return;
    }
    if (client.is_registered())
    {
        m_reply.reply_to_sender(ERR_ALREADYREGISTRED, user_id, {":Unauthorized command (already registered)"});
        return;
    }
    if (!client.has_user() && client.has_nick() && client.has_password())
        m_reply.reply_welcome(user_id, m_ChannelDatabase.count_channels());
    client.user_received();
}

// ERR_NEEDMOREPARAMS
// ERR_ALREADYREGISTRED

//NEEDS TO BE DONE BEFORE SENDING NICK/USER COMBINATION
void CommandParser::connection_password(std::string const& message, unsigned int user_id)
{
    if (message.length() <= 4)
    {
        std::cout << "ERR_NEEDMOREPARAMS\n";
        return;
    }
    if (m_ClientDatabase.is_client(user_id))
    {
        std::cout << "ERR_ALREADYREGISTRED\n"; //TODO ERR
        return;
    }
    std::string args = remove_prefix(message, 4);
    //TODO CHECK IF SERVER HAS PASSWORD
    //TODO CHECK IF PASSWORD MATCHES SERVER PASSWORD
    m_ClientDatabase.get_client(user_id).password_received();
}

void CommandParser::quit_server(std::string const& message, unsigned int user_id)
{
    (void)user_id;

    std::string args;
    if (message.length() > 4)
        args = remove_prefix(message, 4);
    else
        args = message.substr(0, 4);
    // m_ChannelDatabase.remove_user(user_id);
    if (args.size() > 0)
    {
        std::cout << "QUITTING SERVER\nReason:[" << args << "]\n";
        // TODO ERR_QUIT with quit message
        return;
    }
    else
    {
        std::cout << "QUITTING SERVER\n";
        // TODO ERR_QUIT
        return;
    }
}

// ERR_NEEDMOREPARAMS
// ERR_NOTONCHANNEL
// ERR_CHANOPRIVSNEEDED
// ERR_NOSUCHCHANNEL
// ERR_USERNOTINCHANNEL
// "KICK #finnish,#english heikki,crisplake :Bye noobs"
void CommandParser::kick_user(std::string const& message, unsigned int user_id)
{
    if (message.length() <= 4)
    {
        std::cout << "ERR_NEEDMOREPARAMS\n";
        return;
    }
    std::string args = remove_prefix(message, 4);
    std::string::size_type pos = args.find(" ");
    if (pos == std::string::npos || !message[pos + 1] || message.empty())
    {
        std::cout << "ERR_NEEDMOREPARAMS\n"; // TODO ERR
        return;
    }
    std::string channels = args.substr(0, pos);
    // std::cout << "Channels:[" << channels << "]\n"; // delete
    args.erase(0, args.find(" ") + 1);
    pos = args.find(" ");
    std::string users = args.substr(0, pos);
    // std::cout << "Users:[" << users << "]\n"; //delete
    args.erase(0, args.find(" ") + 1);
    // std::cout << "Args:[" << args << "]\n"; //delete
    std::vector<std::string> channel_vec = split_string_to_vector(channels, ",");
    std::vector<std::string> users_vec = split_string_to_vector(users, ",");
    // for (unsigned int i = 0; i < channel_vec.size(); i++) //delete
    //     std::cout << "channel " << i << ":[" << channel_vec[i] << "]\n";  //delete
    // for (unsigned int i = 0; i < users_vec.size(); i++) //delete
    //     std::cout << "user " << i << ":[" << users_vec[i] << "]\n";  //delete
    if (channel_vec.size() > 1 && channel_vec.size() != users_vec.size())
    {
        std::cout << "ERR_NEEDMOREPARAMS\n"; // TODO ERR
        return;
    }
    if (channel_vec.size() == 1)
    {
        if (!m_ChannelDatabase.is_channel(channel_vec[0])) 
        {
            std::cout << "ERR_NOSUCHCHANNEL\n"; //TODO ERR
            return;
        }
        Channel& channel_ref = m_ChannelDatabase.get_channel(channel_vec[0]);
        for (std::vector<std::string>::iterator user = users_vec.begin(); user != users_vec.end(); ++user)
        {
            if (!m_ClientDatabase.is_client(m_ClientDatabase.get_user_id(*user)))
            {
                std::cout << *user << ":User doesn't exist\n"; //TODO ERR
                continue;
            }
            std::cout << "Kicking:" << *user << " Reason:[" << args << "]\n";
            channel_ref.kick(user_id, m_ClientDatabase.get_user_id(*user));
            //TODO catch return value
        }
    }
    else
    {
        for (unsigned int i = 0; i < channel_vec.size(); i++)
        {
            if (!m_ChannelDatabase.is_channel(channel_vec[i]))
            {
                std::cout << "ERR_NOSUCHCHANNEL\n"; //TODO ERR
                continue;
            }
            Channel& channel_ref = m_ChannelDatabase.get_channel(channel_vec[i]);
            std::cout << "Kicking:" << users_vec[i] << " | Reason:[" << args << "]\n";
            channel_ref.kick(user_id, m_ClientDatabase.get_user_id(users_vec[i]));
            //TODO get return value
        }
    }
}

// RPL_INVITING "<channel> <nick>"
// ERR_NOSUCHNICK
// ERR_NEEDMOREPARAMS
// ERR_NOTONCHANNEL
// ERR_CHANOPRIVSNEEDED
// ERR_USERONCHANNEL
void CommandParser::invite_user(std::string const& message, unsigned int user_id)
{
    user_id++; //delete
    user_id--; //delete
    if (message.length() <= 4)
    {
        std::cout << "ERR_NEEDMOREPARAMS\n";
        return;
    }
    std::string args = remove_prefix(message, 6);
    std::string::size_type pos = args.find(" ");
    if (pos == std::string::npos || !message[pos + 1] || message.empty())
    {
        std::cout << "ERR_NEEDMOREPARAMS\n"; // TODO ERR
        return;
    }
    std::string nick = args.substr(0, pos);
    std::string channel_name = args.substr(pos + 1, args.size() - pos - 1);
    // std::cout << "nick:[" << nick << "]\n";
    // std::cout << "channel:[" << channel_name << "]\n";
    if (!m_ClientDatabase.is_nick_in_use(nick))
    {
        std::cout << "Invited doesn't exist\n"; //TODO ERR_NOSUCHNICK
        return;
    }
    if (!m_ChannelDatabase.is_channel(channel_name))
    {
        std::cout << "Channel doesn't exist, adding channel and inviting user\n"; //TODO?
        m_ChannelDatabase.add_channel(channel_name, user_id);
    }
    Channel& channel = m_ChannelDatabase.get_channel(channel_name);
    channel.invite(user_id, m_ClientDatabase.get_user_id(nick));
    //TODO check invite return value
}

//ERR_NEEDMOREPARAMS "<command> :Not enough parameters"
//RPL_NOTOPIC "<channel> :No topic is set"
//RPL_TOPIC "<channel> :<topic>"
//ERR_CHANOPRIVSNEEDED "<channel> :You're not channel operator"
//ERR_NOTONCHANNEL "<channel> :You're not on that channel"
void CommandParser::change_topic(std::string const& message, unsigned int user_id)
{
    user_id++; //delete
    user_id--; //delete
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

// ERR_NEEDMOREPPARAMS
// ERR_NOCHANMODES
// ERR_USERNOTINCHANNEL
// ERR_KEYSET
// ERR_CHANOPRIVSNEEDED
// ERR_UNKNOWNMODE
// RPL_BANLIST
// RPL_EXCEPTLIST
// RPL_INVITELIST
// RPL_UNIQOPIS
// RPL_ENDOFBANLIST
// RPL_ENDOFEXCEPTLIST
// RPL_ENDOFINVITELIST
void CommandParser::change_mode(std::string const& message, unsigned int user_id)
{
    (void)user_id;
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
        (void)ref; //delete
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
                    //check limit is int
                    // ref.set_user_limit(user_id, mode, user_limit);
                    break;
                }
            }
        }
    }
}

// ERR_NOORIGIN
// ERR_NOSUCHSERVER
void CommandParser::receive_ping(std::string const& message, unsigned int user_id)
{
    (void)message;
    (void)user_id;
    //TODO errors
    //TODO hostname
    m_ClientDatabase.get_client(user_id).add_message(":localhost PONG localhost :localhost");
}

void CommandParser::receive_pong(std::string const& message, unsigned int user_id)
{
    (void)message;
    (void)user_id;
    // std::string target = message.substr(5, message.length() - 5);
    // std::cout << "TYPE:PONG | ORIGIN:" << user_id << " | " << "TARGET:" << target << "\n"; // delete
    /*TODO IF TARGET EXISTS IN DATABASE*/
    //ERR_NOORIGIN
    //ERR_NOSUCHSERVER
}

void CommandParser::answer_cap(std::string const& message, unsigned int user_id)
{
    (void)message;
    (void)user_id;
    //TODO sanitize
    if (message != "CAP END")
        m_ClientDatabase.get_client(user_id).add_message("CAP * LS");
}