/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:21:52 by emajuri           #+#    #+#             */
/*   Updated: 2024/02/12 15:07:52 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reply.hpp"

#include <sstream>
#include <iomanip>
#include <string>
#include <vector>

std::stringstream Reply::create_start(ReplyEnum reply, unsigned int user_id)
{
    std::stringstream msg;
    msg << ":ircserv";
    msg << " ";
    msg << std::right << std::setfill('0') << std::setw(3) << std::to_string(reply);
    msg << " ";

    std::string nick = m_clients.get_client(user_id).get_nickname();
    if (nick.empty())
        nick = "*"; //For cases when nick is not yet set but need to reply error

    msg << nick;
    return msg;
}

std::string Reply::create_string(ReplyEnum reply, unsigned int user_id, std::vector<std::string> const& params)
{
    std::stringstream msg = create_start(reply, user_id);
    msg << ' ';
    for (auto& param : params)
        msg << param;
    return msg.str();
}

void Reply::reply_to_sender(ReplyEnum reply, unsigned int user_id, std::vector<std::string> const& params)
{
    Client& client = m_clients.get_client(user_id);
    std::string msg = create_string(reply, user_id, params);
    client.add_message(std::move(msg));
}

void Reply::reply_to_other(ReplyEnum reply, unsigned int user_id, unsigned int sender, std::vector<std::string> const& params)
{
    Client& client = m_clients.get_client(user_id);
    std::string msg = create_string(reply, sender, params);
    client.add_message(std::move(msg));
}

void Reply::reply_welcome(unsigned int user_id, unsigned int channel_count)
{
    //TODO variables
    std::string nick = m_clients.get_client(user_id).get_nickname();
    reply_to_sender(RPL_WELCOME, user_id, {":Welcome to the Internet Relay Network ", nick});
    reply_to_sender(RPL_YOURHOST, user_id, {":Your host is ", "<hostname> ", ", running version ", "1.0.1"});
    reply_to_sender(RPL_CREATED, user_id, {":This server was created ", m_start_time});
    reply_to_sender(RPL_MYINFO, user_id, {"<hostname> ", "1.0.1", " * ", "iklot"});
    reply_to_sender(RPL_ISUPPORT, user_id, {"CHANMODES=,o,kl,it", " MODES=3", " :are supported by this server"});
    reply_to_sender(RPL_LUSERCLIENT, user_id, {":There are ", std::to_string(m_clients.count_clients()), " users and 0 invisible on 1 servers"});
    reply_to_sender(RPL_LUSEROP, user_id, {"0 operator(s) online"});
    reply_to_sender(RPL_LUSERUNKNOWN, user_id, {std::to_string(m_clients.count_unknown_clients()), " unknown connection(s)"});
    reply_to_sender(RPL_LUSERCHANNELS, user_id, {std::to_string(channel_count), " channels formed"});
    reply_to_sender(RPL_LUSERME, user_id, {":I have, ", std::to_string(m_clients.count_clients()), " clients and 1 servers"});
    reply_to_sender(ERR_NOMOTD, user_id, {":MOTD File is missing"});
}
