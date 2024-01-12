/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:21:52 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/12 14:21:25 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reply.hpp"

Reply::Reply(ClientDatabase& clients, ChannelDatabase& channels) : m_clients(clients), m_channels(channels)
{
    m_replies[RPL_WELCOME] = "Welcome to the Internet Relay Network <nick>!<user>@<host>";
}

void Reply::reply_to_sender(unsigned int user_id, ReplyEnum reply)
{
    Client client = m_clients.get_client(user_id);
    switch (reply)
    {
        case RPL_WELCOME:
            client.add_message(std::make_shared<std::string>("Welcome to the Internet Relay Network " + client.get_nickname() + "!" + "<user>" + "@" + "<host>")); // TODO <user> and <host>
        default:
            (void)1;
    }

}

void Reply::error_to_sender(unsigned int user_id, ReplyEnum reply, std::string filler1, std::string filler2)
{
    (void)filler2;
    Client client = m_clients.get_client(user_id);
    switch (reply)
    {
        case ERR_NEEDMOREPARAMS:
            client.add_message(std::make_shared<std::string>(filler1 + " :Not enough parameters"));
        case ERR_ALREADYREGISTRED:
            client.add_message(std::make_shared<std::string>(":Unauthorized command (already registered)"));
        case ERR_NONICKNAMEGIVEN:
            client.add_message(std::make_shared<std::string>(":No nickname given"));
        case ERR_ERRONEUSNICKNAME:
            client.add_message(std::make_shared<std::string>(filler1 + " :Erroneous nickname"));
        case ERR_NICKNAMEINUSE:
            client.add_message(std::make_shared<std::string>(filler1 + " :Nickname is already in use"));
        default:
            (void)1;
    }
}