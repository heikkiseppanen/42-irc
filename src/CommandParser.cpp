/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:04:54 by emajuri           #+#    #+#             */
/*   Updated: 2024/02/07 14:01:23 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandParser.hpp"

#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>

CommandParser::CommandParser(ClientDatabase& ClData, ChannelDatabase& ChData, std::string const& start_time) 
: m_client_database(ClData), m_channel_database(ChData),
  m_reply(m_client_database, start_time)
{
    m_commands["PRIVMSG"] = PRIVMSG;
    m_commands["JOIN"] = JOIN;
    m_commands["NICK"] = NICK;
    m_commands["USER"] = USER;
    m_commands["PASS"] = PASS;
    m_commands["QUIT"] = QUIT;
    m_commands["PART"] = PART;
    m_commands["KICK"] = KICK;
    m_commands["INVITE"] = INVITE;
    m_commands["TOPIC"] = TOPIC;
    m_commands["MODE"] = MODE;
    m_commands["PING"] = PING;
    m_commands["CAP"] = CAP;
}

command CommandParser::get_command_type(std::string const& message)
{
    std::size_t pos = message.find(" ");
    std::string cmd = message.substr(0, pos);
    std::map<std::string, command>::iterator it = m_commands.find(cmd);
    if (it == m_commands.end())
        return ERR_NO_CMD;
    return it->second;
}

std::string get_command_args(std::string const& message)
{
    std::size_t pos = message.find(" ");
    if (pos == std::string::npos)
        return "";
    return message.substr(pos + 1);
}

void CommandParser::parser(std::string const& message, unsigned int user_id)
{
    command cmd = get_command_type(message);
    if (cmd < 100)
    {
        if (!m_client_database.get_client(user_id).is_registered())
            return;
    }
    std::string args = get_command_args(message);
    switch (cmd)
    {
        case ERR_NO_CMD:
            break;
        case PRIVMSG:
            send_privmsg(args, user_id);
            break;
        case JOIN:
            join_channel(args, user_id);
            break;
        case QUIT:
            quit_server(args, user_id);
            break;
        case KICK:
            kick_user(args, user_id);
            break;
        case INVITE:
            invite_user(args, user_id);
            break;
        case TOPIC:
            change_topic(args, user_id);
            break;
        case MODE:
            change_mode(args, user_id);
            break;
        case PART:
            part_command(args, user_id);
            break;
        case NICK:
            change_nick(args,user_id);
            break;
        case USER:
            user_register(args, user_id);
            break;
        case PASS:
            connection_password(args, user_id);
            break;
        case PING:
            receive_ping(args, user_id);
            break;
        case CAP:
            answer_cap(args, user_id);
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

void CommandParser::send_privmsg(std::string const& arguments, unsigned int user_id)
{
    std::stringstream stream(arguments);
    std::string targets;

    std::getline(stream, targets, ' ');

    if (targets.empty())
    {
        m_reply.reply_to_sender(ERR_NORECIPIENT, user_id, {":No recipient given (PRIVMSG)"});
        return;
    }

    std::string content;
    std::getline(stream, content, '\0');

    stream.str(targets);
    stream.clear();
    std::vector<std::string> target_list;
    std::string target;

    while (std::getline(stream, target, ','))
    {
        target_list.emplace_back(std::move(target));
    }

    auto& client = m_client_database.get_client(user_id);
    for (auto& target : target_list)
    {
        if (target[0] == '#')
        {
            if (!m_channel_database.is_channel(target))
            {
                m_reply.reply_to_sender(ERR_CANNOTSENDTOCHAN, user_id, {target, " :Cannot sent to channel"});
                continue;
            }
            for (unsigned int channel_user_id : m_channel_database.get_channel(target).get_users())
            {
                if (channel_user_id != user_id)
                {
                    auto& channel_client = m_client_database.get_client(channel_user_id);
                    channel_client.add_message(":" + client.get_nickname() + " PRIVMSG " + target + ' ' + content);
                }
            }
        }
        else if (m_client_database.is_nick_in_use(target))
        {
            auto& receiver_client = m_client_database.get_client(m_client_database.get_user_id(target));
            receiver_client.add_message(":" + client.get_nickname() + " PRIVMSG " + target + ' ' + content);
        }
        else
        {
            m_reply.reply_to_sender(ERR_NOSUCHNICK, user_id, {target, " :No such nick/channel"});
        }
    }
}

void CommandParser::join_channel(std::string const& arguments, unsigned int user_id)
{
    std::stringstream stream(arguments);
    std::string channel_argument;
    std::string key_argument;

    std::getline(stream, channel_argument, ' ');
    std::getline(stream, key_argument, '\0');

    if (channel_argument.empty())
    {
        m_reply.reply_to_sender(ERR_NEEDMOREPARAMS, user_id, {"JOIN ", arguments, " :Not enough parameters"});
        return;
    }

    stream.str(channel_argument);
    stream.clear();

    std::vector<std::string> channel_list;
    while (getline(stream, channel_argument, ','))
    {
        channel_list.emplace_back(std::move(channel_argument));
    }

    stream.str(key_argument);
    stream.clear();

    std::vector<std::string> key_list;
    while (getline(stream, key_argument, ','))
    {
        key_list.emplace_back(std::move(key_argument));
    }

    auto& client = m_client_database.get_client(user_id);

    auto key = key_list.begin();
    for (auto const& channel_name : channel_list)
    {
        if (channel_name.front() != '#')
        {
            m_reply.reply_to_sender(ERR_NOSUCHCHANNEL, user_id, {":No such channel"});
            continue;
        }

        bool const has_password_provided = (key != key_list.end());
        std::string const& password = (has_password_provided) ? *(key++) : "";

        if (!m_channel_database.is_channel(channel_name))
        {
            m_channel_database.add_channel(channel_name, user_id);
            auto& channel = m_channel_database.get_channel(channel_name);
            if (has_password_provided)
            {
                channel.set_password(ADD, password);
            }
            m_reply.reply_to_sender(RPL_NOTOPIC, user_id, {channel_name,  " :No topic set"});
            m_reply.reply_to_sender(RPL_NAMREPLY, user_id, {"= ", channel_name, " :@", client.get_nickname()});
            m_reply.reply_to_sender(RPL_ENDOFNAMES, user_id, {channel_name, " :End of /NAMES list"});
            continue;
        }

        auto& channel = m_channel_database.get_channel(channel_name);

        if (!channel.is_subscribed(user_id))
        {
            if (!channel.is_invited(user_id))
            {
                m_reply.reply_to_sender(ERR_INVITEONLYCHAN, user_id, {channel_name, " :Cannot join channel (+i)"});
                continue;
            }
            if (!channel.is_valid_password(password))
            {
                m_reply.reply_to_sender(ERR_BADCHANNELKEY, user_id, {channel_name, " :Cannot join channel (+k)"});
                continue;
            }
            if (!channel.is_not_full())
            {
                m_reply.reply_to_sender(ERR_CHANNELISFULL, user_id, {channel_name, " :Cannot join channel (+l)"});
                continue;
            }
            channel.join_channel(user_id);
        }

        for (unsigned int channel_user_id : channel.get_users())
        {
            auto& channel_client = m_client_database.get_client(channel_user_id);
            channel_client.add_message(":" + client.get_nickname() + " JOIN " + channel_name);
        }

        if (!channel.is_channel_topic_empty())
        {
            m_reply.reply_to_sender(RPL_TOPIC, user_id, {channel_name, " :", channel.get_topic()});
        }
        else
        {
            m_reply.reply_to_sender(RPL_NOTOPIC, user_id, {channel_name,  " :No topic set"});
        }

        for (unsigned int channel_user_id : channel.get_users())
        {
            auto& channel_client = m_client_database.get_client(channel_user_id);
            if (channel.is_operator(channel_user_id))
            {
                m_reply.reply_to_sender(RPL_NAMREPLY, user_id, {"= ", channel_name, " :@", channel_client.get_nickname()});
            }
            else
            {
                m_reply.reply_to_sender(RPL_NAMREPLY, user_id, {"= ", channel_name, " :", channel_client.get_nickname()});
            }
        }
        m_reply.reply_to_sender(RPL_ENDOFNAMES, user_id, {channel_name,  " :End of /NAMES list"});
    }
}

// ERR_NONICKNAMEGIVEN ":No nickname given"
// ERR_ERRONEUSNICKNAME "<nick> :Erroneous nickname"
// ERR_NICKNAMEINUSE "<nick> :Nickname is already in use"
void CommandParser::change_nick(std::string const& arguments, unsigned int user_id)
{
    Client& client = m_client_database.get_client(user_id);
    //if (server_has_no_password)
    client.password_received();
    if (!client.has_password())
    {
        std::cout << "User has not used PASS message\n";
        //TODO ERR
        return;
    }
    std::string nick = arguments;
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
    if (m_client_database.is_nick_in_use(nick))
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
        m_reply.reply_welcome(user_id, m_channel_database.count_channels());
    client.nick_received();
}

void CommandParser::user_register(std::string const& arguments, unsigned int user_id)
{
    //TODO alreadyregistered
    Client& client = m_client_database.get_client(user_id);
    //if (server_has_no_password)
    client.password_received();
    if (!client.has_password())
    {
        std::cout << "User has not used PASS message\n";
        //TODO ERR
        return;
    }
    if (arguments.empty())
    {
        m_reply.reply_to_sender(ERR_NEEDMOREPARAMS, user_id, {"USER :Not enough parameters"});
        return;
    }
    std::string args = arguments;
    std::vector<std::string> vec;
    std::string::size_type pos = args.find(" ");
    for (unsigned int i = 0; pos != std::string::npos && i < 3; i++)
    {
        vec.push_back(args.substr(0, pos));
        args.erase(0, args.find(" ") + 1);
        pos = args.find(" ");
    }
    vec.push_back(args);
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
        m_reply.reply_welcome(user_id, m_channel_database.count_channels());
    client.user_received();
}

void CommandParser::connection_password(std::string const& arguments, unsigned int user_id)
{
    if (arguments.empty())
    {
        m_reply.reply_to_sender(ERR_NEEDMOREPARAMS, user_id, {"PASS :Not enough parameters"});
        return;
    }
    if (m_client_database.is_client(user_id))
    {
        m_reply.reply_to_sender(ERR_ALREADYREGISTRED, user_id, {":Unauthorized command (already registered)"});
        return;
    }
    //TODO CHECK IF SERVER HAS PASSWORD
    //TODO CHECK IF PASSWORD MATCHES SERVER PASSWORD
    m_client_database.get_client(user_id).password_received();
}

void CommandParser::quit_server(std::string const& arguments, unsigned int user_id)
{
    m_channel_database.remove_user(user_id, arguments, m_client_database);
    Client& client = m_client_database.get_client(user_id);
    client.quit();
    while (client.has_message())
        client.remove_message();
    client.add_message("ERROR :Client quit");
}

void CommandParser::kick_user(std::string const& arguments, unsigned int user_id)
{
    std::stringstream stream(arguments);
    std::string channel_name;
    std::string targets;
    std::string reason;

    std::getline(stream, channel_name, ' ');
    std::getline(stream, targets, ' ');
    std::getline(stream, reason, '\0');

    if (reason == ":" || reason.size() == 0) //Irssi sends ":" as default kick, so default kick message is set here
    {
        reason = ":Get rekt kiddo"; //Default kick message
    }

    stream.str(targets);
    stream.clear();

    std::vector<std::string> target_list;
    while (std::getline(stream, targets, ','))
    {
        target_list.emplace_back(std::move(targets));
    }

    if (target_list.empty())
    {
        m_reply.reply_to_sender(ERR_NEEDMOREPARAMS, user_id, {"KICK :Not enough parameters"});
        return;
    }
    if (!m_channel_database.is_channel(channel_name))
    {
        m_reply.reply_to_sender(ERR_NOSUCHCHANNEL, user_id, {channel_name, " :No such channel"});
        return;
    }
    if (!m_channel_database.is_user_on_channel(channel_name, user_id))
    {
        m_reply.reply_to_sender(ERR_NOTONCHANNEL, user_id, {channel_name, " :You're not on that channel"});
        return;
    }

    auto& channel_ref = m_channel_database.get_channel(channel_name);

    if (!channel_ref.is_operator(user_id))
    {
        m_reply.reply_to_sender(ERR_CHANOPRIVSNEEDED, user_id, {channel_name, " :You're not channel operator"});
        return;
    }

    auto& kicker_ref = m_client_database.get_client(user_id);

    for (auto const& nick : target_list)
    {
        if (!m_client_database.is_nick_in_use(nick))
        {
            m_reply.reply_to_sender(ERR_USERNOTINCHANNEL, user_id, {nick, " ", channel_name, " :They aren't on that channel"});
            continue;
        }

        unsigned int kicked_id = m_client_database.get_user_id(nick);

        if (!channel_ref.is_subscribed(kicked_id))
        {
            m_reply.reply_to_sender(ERR_USERNOTINCHANNEL, user_id, {nick, " ", channel_name, " :They aren't on that channel"});
            continue;
        }
        for (unsigned int channel_user_id : channel_ref.get_users())
        {
            auto& channel_client = m_client_database.get_client(channel_user_id);
            channel_client.add_message(":" + kicker_ref.get_nickname() + " KICK " + channel_name + " " + nick + " " + reason);
        }
        channel_ref.remove_user_from_channel(kicked_id);
    }
    if (channel_ref.get_users().empty())
    {
        m_channel_database.remove_channel(channel_name);
    }
}

void CommandParser::invite_user(std::string const& arguments, unsigned int user_id)
{
    std::stringstream stream(arguments);
    std::string nickname;
    std::string channel_name;

    std::getline(stream, nickname, ' ');
    std::getline(stream, channel_name, '\0');

    if (channel_name.empty())
    {
        m_reply.reply_to_sender(ERR_NEEDMOREPARAMS, user_id, {"INVITE :Not enough parameters"});
        return;
    }
    if (!m_channel_database.is_channel(channel_name))
    {
        m_reply.reply_to_sender(ERR_NOSUCHCHANNEL, user_id, {channel_name, " :No such channel"});
        return;
    }
    if (!m_channel_database.is_user_on_channel(channel_name, user_id))
    {
        m_reply.reply_to_sender(ERR_NOTONCHANNEL, user_id, {channel_name, " :You're not on that channel"});
        return;
    }

    Channel& channel_ref = m_channel_database.get_channel(channel_name);

    if (channel_ref.is_invite_only() == true && !channel_ref.is_operator(user_id))
    {
        m_reply.reply_to_sender(ERR_CHANOPRIVSNEEDED, user_id, {channel_name, " :You're not channel operator"});
        return;
    }
    if (!m_client_database.is_nick_in_use(nickname))
    {
        m_reply.reply_to_sender(ERR_NOSUCHNICK, user_id, {nickname, " :No such nick/channel"});
        return;
    }

    unsigned int invited_id = m_client_database.get_user_id(nickname);    

    if (channel_ref.is_subscribed(invited_id))
    {
        m_reply.reply_to_sender(ERR_USERONCHANNEL, user_id, {nickname, " ", channel_name ," :is already on channel"});
        return;
    }
    channel_ref.invite(invited_id);
    m_reply.reply_to_sender(RPL_INVITING, user_id, {nickname, " ", channel_name});

    Client& invited_ref = m_client_database.get_client(invited_id);
    Client& inviter_ref = m_client_database.get_client(user_id);

    invited_ref.add_message(inviter_ref.get_nickname() + " INVITE " + nickname + " " + channel_name);
}

void CommandParser::change_topic(std::string const& arguments, unsigned int user_id)
{
    std::stringstream stream(arguments);
    std::string channel_name;
    std::string topic;

    std::getline(stream, channel_name, ' ');
    std::getline(stream, topic, '\0');

    if (channel_name.empty())
    {
        m_reply.reply_to_sender(ERR_NEEDMOREPARAMS, user_id, {"TOPIC :Not enough parameters"});
        return;
    }
    if (!m_channel_database.is_channel(channel_name))
    {
        m_reply.reply_to_sender(ERR_NOSUCHCHANNEL, user_id, {channel_name, " :No such channel"});
        return;
    }

    Channel& channel = m_channel_database.get_channel(channel_name);

    if (!channel.is_subscribed(user_id))
    {
        m_reply.reply_to_sender(ERR_NOTONCHANNEL, user_id, {channel_name, " :You're not on that channel"});
        return;
    }
    if (topic.empty())
    {
        if (channel.is_channel_topic_empty())
        {
            m_reply.reply_to_sender(RPL_NOTOPIC, user_id, {channel_name, " :No topic is set"});
        }
        else
        {
            m_reply.reply_to_sender(RPL_TOPIC, user_id, {channel_name, " :", channel.get_topic()});

            std::string const& nick = m_client_database.get_client(user_id).get_nickname();
            std::string const time = std::to_string(std::time(nullptr));

            m_reply.reply_to_sender(RPL_TOPICWHOTIME, user_id, {channel_name, nick, time});
        }
        return;
    }
    if (channel.is_topic_op_only())
    {
        if (!channel.is_operator(user_id))
        {
            m_reply.reply_to_sender(ERR_CHANOPRIVSNEEDED, user_id, {channel_name, " :You are not channel operator"});
            return;
        }
    }
    channel.topic_change(topic.substr(1));
    for (unsigned int user : channel.get_users())
    {
        m_reply.reply_to_other(RPL_TOPIC, user, user_id, {channel_name, " ", topic});
    }
}

std::string CommandParser::get_current_modes(std::string channel_name)
{
    std::string modestring;
    Channel& channel_ref = m_channel_database.get_channel(channel_name);

    if (channel_ref.is_invite_only())
        modestring += 'i';
    if (channel_ref.is_topic_op_only())
        modestring += 't';
    if (channel_ref.has_password())
        modestring += 'k';
    if (channel_ref.has_user_limit())
        modestring += 'l';
    modestring += " ";
    if (channel_ref.has_password())
        modestring += channel_ref.get_password();
    if (channel_ref.has_password() && channel_ref.has_user_limit())
        modestring += ", ";
    if (channel_ref.has_user_limit())
        modestring += channel_ref.get_user_limit(); 
    return (modestring);
}

//MODE #Finnish +il 100 Wiz
/* 
i - invite-only channel flag; TYPE D
t - topic settable by channel operator only flag; TYPE D
k - set a channel key (password). TYPE C
o - give/take channel operator privileges TYPE B
l - set the user limit to channel; TYPE C
*/

// ERR_NEEDMOREPPARAMS
// RPL_CHANMODEIS
// ERR_NOSUCHCHANNEL
// ERR_NOTONCHANNEL
// ERR_CHANOPRIVSNEEDED
// ERR_UNKNOWNMODE
// ERR_INVALIDKEY

//MODE #finnish +itk
void CommandParser::change_mode(std::string const& arguments, unsigned int user_id)
{
    std::stringstream stream(arguments);
    std::string channel_name;
    std::string modestring;
    std::string params;

    std::getline(stream, channel_name, ' ');
    std::getline(stream, modestring, ' ');
    std::getline(stream, params, '\0');

    if (channel_name.front() != '#')
        return;
    if (channel_name.empty())
    {
        m_reply.reply_to_sender(ERR_NEEDMOREPARAMS, user_id, {"MODE :Not enough parameters"});
        return;
    }
    if (!m_channel_database.is_channel(channel_name))
    {
        m_reply.reply_to_sender(ERR_NOSUCHCHANNEL, user_id, {channel_name, " :No such channel"});
        return;
    }
    if (modestring.empty())
    {
        m_reply.reply_to_sender(RPL_CHANNELMODEIS, user_id, {channel_name, " ", get_current_modes(channel_name)});
        return;
    }
    if (modestring.front() != '+' && modestring.front() != '-')
        return;
    if (!m_channel_database.is_user_on_channel(channel_name, user_id))
    {
        m_reply.reply_to_sender(ERR_NOTONCHANNEL, user_id, {channel_name, " :You're not on that channel"});
        return;
    }
    if (!m_channel_database.get_channel(channel_name).is_operator(user_id))
    {
        m_reply.reply_to_sender(ERR_CHANOPRIVSNEEDED, user_id, {channel_name, " :You're not channel operator"});
        return;
    }

    stream.str(params);
    stream.clear();
    std::vector<std::string> param_list;

    while (std::getline(stream, params, ','))
    {
        param_list.emplace_back(std::move(params));
    }

    Channel& channel_ref = m_channel_database.get_channel(channel_name);
    std::vector<std::string> passed_params_list;
    std::string events;
    bool mode_value;
    for (unsigned int i = 0, param_count = 0; modestring[i]; i++)
    {
        switch (modestring[i])
        {
            case '+':
            {
                mode_value = ADD;
                events += "+";
                break;
            }
            case '-':
            {
                mode_value = REMOVE;
                events += "-";
                break;
            }
            case 'i':
            {
                channel_ref.set_invite_only(mode_value);
                events += "i";
                break;
            }
            case 't':
            {
                channel_ref.set_op_topic(mode_value);
                events += "t";
                break;
            }
            case 'k':
            {
                //TODO? check valid keyset
                if (mode_value == ADD)
                {
                    if (param_count < param_list.size())
                        break;
                    channel_ref.set_password(mode_value, param_list[param_count]);
                    passed_params_list.emplace_back(param_list[param_count++]);
                }
                else
                    channel_ref.set_password(mode_value, "");
                events += "k";
                break;
            }
            case 'o':
            {
                if (param_count < param_list.size())
                    break;
                std::string const nick = param_list[param_count++];
                if (!m_client_database.is_nick_in_use(nick))
                    break;
                channel_ref.set_op(mode_value, m_client_database.get_user_id(nick));
                passed_params_list.emplace_back(nick);
                events += "o";
                break;
            }
            case 'l':
            {
                if (mode_value == ADD)
                {
                    if (param_count < param_list.size() || param_list[param_count].find_first_not_of("0123456789") != std::string::npos)
                        break;
                    channel_ref.set_user_limit(mode_value, std::stoul(param_list[param_count]));
                    passed_params_list.emplace_back(param_list[param_count++]);
                }
                else 
                    channel_ref.set_user_limit(mode_value, 0);
                events += "l";
                break;
            }
            default :
            {
                std::string unknown_char = {modestring[i], '\0'};
                m_reply.reply_to_sender(ERR_UNKNOWNMODE, user_id, {unknown_char, " :is unknown mode char to me for ", channel_name});
                break;
            }
        }
    }
    if (!events.empty())
    {
        std::string event_message = ":" + m_client_database.get_client(user_id).get_nickname() + " MODE " + channel_name + " " + events;
        for (auto& arg : passed_params_list)
        {
            if (&arg == &passed_params_list.front())
                event_message += " ";
            event_message += arg;
            if (&arg != &passed_params_list.back())
                event_message += ",";
        }

        for (unsigned int channel_user_id : channel_ref.get_users())
        {
            auto& channel_client = m_client_database.get_client(channel_user_id);
            channel_client.add_message(event_message);
        }
    } 
}

// ERR_NOORIGIN
// ERR_NOSUCHSERVER
void CommandParser::receive_ping(std::string const& arguments, unsigned int user_id)
{
    (void)arguments;
    (void)user_id;
    //TODO errors
    //TODO hostname
    m_client_database.get_client(user_id).add_message(":localhost PONG localhost :localhost");
}

void CommandParser::answer_cap(std::string const& arguments, unsigned int user_id)
{
    //TODO sanitize
    if (arguments != "END")
        m_client_database.get_client(user_id).add_message("CAP * LS");
}

void CommandParser::part_command(std::string const& arguments, unsigned int user_id)
{
    if (arguments.empty())
    {
        m_reply.reply_to_sender(ERR_NEEDMOREPARAMS, user_id, {"PART :Not enough parameters"});
        return;
    }
    std::string args = arguments;
    std::string::size_type pos = args.find(' ');
    std::string channel_args = args.substr(0, pos);
    std::string reason;

    if (pos != std::string::npos)
        reason = args.substr(pos + 1);

    std::vector<std::string> channels;
    std::stringstream ss(channel_args);
    std::string channel_name;

    while(getline(ss, channel_name, ','))
    {
        channels.emplace_back(std::move(channel_name));
    }

    std::string nick = m_client_database.get_client(user_id).get_nickname();

    for (auto& channel_name : channels)
    {
        if (!m_channel_database.is_channel(channel_name))
        {
            m_reply.reply_to_sender(ERR_NOSUCHCHANNEL, user_id, {channel_name, " :No such channel"});
            continue;
        }

        Channel& channel = m_channel_database.get_channel(channel_name);

        if (!channel.is_subscribed(user_id))
        {
            m_reply.reply_to_sender(ERR_NOTONCHANNEL, user_id, {channel_name, " :You're not on that channel"});
            continue;
        }
        for (auto user : channel.get_users())
        {
            m_client_database.get_client(user).add_message(":" + nick + " PART " + channel_name + " " + reason);
        }
        channel.remove_user_from_channel(user_id);
        if (channel.get_users().empty())
        {
            m_channel_database.get_channels().erase(channel_name);
        }
    }
}
