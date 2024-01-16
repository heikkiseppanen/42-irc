/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:21:48 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/09 14:19:59emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>
#include <vector>
#include "ClientDatabase.hpp"

class ChannelDatabase;

enum ReplyEnum
{
    IGNORE, // Incase no reply is meant to be sent
    RPL_WELCOME = 1, // "Welcome to the Internet Relay Network <nick>!<user>@<host>"
    RPL_CHANNELMODEIS = 324, // "<channel> <mode> <mode params>"
    RPL_NOTOPIC = 331, // "<channel> :No topic is set"
    RPL_TOPIC = 332, // "<channel> :<topic>" 
    RPL_INVITING = 341, //"<channel> <nick>"
    RPL_INVITELIST = 346, // "<channel> <invitemask>"
    RPL_ENDOFINVITELIST = 347, // "<channel> :End of channel invite list"
    RPL_NAMREPLY = 353, //"( "=" / "*" / "@" ) <channel>
        //        :[ "@" / "+" ] <nick> *( " " [ "@" / "+" ] <nick> )
        //  - "@" is used for secret channels, "*" for private
        //    channels, and "=" for others (public channels).

    ERR_NOSUCHNICK = 401, // "<nickname> :No such nick/channel"
    ERR_NOSUCHCHANNEL = 403, // "<channel> :No such channel" 
    ERR_NOTEXTTOSEND = 412, //":No text to send"
    ERR_NONICKNAMEGIVEN = 431, // ":No nickname given"
    ERR_ERRONEUSNICKNAME = 432, // "<nick> :Erroneous nickname"
    ERR_NICKNAMEINUSE = 433, // "<nick> :Nickname is already in use"
    ERR_USERNOTINCHANNEL = 441, // "<nick> <channel> :They aren't on that channel"
    ERR_NOTONCHANNEL = 442, // "<channel> :You're not on that channel"
    ERR_USERONCHANNEL = 443, // "<user> <channel> :is already on channel"
    ERR_NEEDMOREPARAMS = 461, // "<command> :Not enough parameters"
    ERR_ALREADYREGISTRED = 462, //":Unauthorized command (already registered)"
    ERR_KEYSET = 467, // "<channel> :Channel key already set"
    ERR_CHANNELISFULL = 471, //  "<channel> :Cannot join channel (+l)"
    ERR_UNKNOWNMODE = 472, // "<char> :is unknown mode char to me for <channel>"
    ERR_INVITEONLYCHAN = 473, // "<channel> :Cannot join channel (+i)"
    ERR_BADCHANNELKEY = 475, // "<channel> :Cannot join channel (+k)"
    ERR_CHANOPRIVSNEEDED = 482, // "<channel> :You're not channel operator"
};

class Reply
{
    public:

        Reply() = delete;
        Reply(ClientDatabase& clients, ChannelDatabase& channels) : m_clients(clients), m_channels(channels) {}

        void reply_to_sender(unsigned int user_id, ReplyEnum reply);
        void error_to_sender(unsigned int user_id, ReplyEnum error, std::string filler1, std::string filler2);
        void reply_to_channel(unsigned int user_id, ReplyEnum reply, std::vector<std::string> channels, std::string msg);
        void reply_to_target(unsigned int user_id, ReplyEnum reply, unsigned int target_id, std::string msg);

    private:

        ClientDatabase& m_clients;
        ChannelDatabase& m_channels;
};
