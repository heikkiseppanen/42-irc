/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:21:48 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/08 21:23:44 by emajuri          ###   ########.fr       */
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
    RPL_WELCOME, // "Welcome to the Internet Relay Network <nick>!<user>@<host>"
    RPL_TOPIC, // "<channel> :<topic>" 
    RPL_NOTOPIC, // "<channel> :No topic is set"
    RPL_CHANNELMODEIS, // "<channel> <mode> <mode params>"
    RPL_INVITING, //"<channel> <nick>"
    RPL_NAMREPLY, //"( "=" / "*" / "@" ) <channel>
        //        :[ "@" / "+" ] <nick> *( " " [ "@" / "+" ] <nick> )
        //  - "@" is used for secret channels, "*" for private
        //    channels, and "=" for others (public channels).

    RPL_INVITELIST, // "<channel> <invitemask>"
    RPL_ENDOFINVITELIST, // "<channel> :End of channel invite list"

    ERR_NEEDMOREPARAMS, // "<command> :Not enough parameters"
    ERR_NOSUCHCHANNEL, // "<channel> :No such channel" 
    ERR_CHANNELISFULL, //  "<channel> :Cannot join channel (+l)"
    ERR_INVITEONLYCHAN, // "<channel> :Cannot join channel (+i)"
    ERR_BADCHANNELKEY, // "<channel> :Cannot join channel (+k)"
    ERR_NONICKNAMEGIVEN, // ":No nickname given"
    ERR_ERRONEUSNICKNAME, // "<nick> :Erroneous nickname"
    ERR_NICKNAMEINUSE, // "<nick> :Nickname is already in use"
    ERR_ALREADYREGISTRED, //":Unauthorized command (already registered)"
    ERR_NOTONCHANNEL, // "<channel> :You're not on that channel"
    ERR_CHANOPRIVSNEEDED, // "<channel> :You're not channel operator"
    ERR_USERNOTINCHANNEL, // "<nick> <channel> :They aren't on that channel"
    ERR_NOSUCHNICK, // "<nickname> :No such nick/channel"
    ERR_USERONCHANNEL, // "<user> <channel> :is already on channel"
    // ERR_NOCHANMODES, // "<channel> :Channel doesn't support modes"
    ERR_KEYSET, // "<channel> :Channel key already set"
    ERR_UNKNOWNMODE // "<char> :is unknown mode char to me for <channel>"
    // ERR_NOORIGIN, // ":No origin specified"
    // ERR_NOSUCHSERVER // "<server name> :No such server"
};

class Reply
{
    public:

        Reply() = delete;
        // Reply(ClientDatabase& clients);
        Reply(ClientDatabase& clients, ChannelDatabase& channels);

        void reply_to_sender(unsigned int user_id, ReplyEnum reply);
        void error_to_sender(unsigned int user_id, ReplyEnum error);
        void reply_to_channel(unsigned int user_id, ReplyEnum reply, std::vector<std::string> channels, std::string msg);
        void reply_to_target(unsigned int user_id, ReplyEnum reply, unsigned int target_id, std::string msg);

    private:

        ClientDatabase& clients;
        ChannelDatabase& channels;
        std::map<ReplyEnum, std::string> Replies;
};
