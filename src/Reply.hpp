/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:21:48 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/23 16:02:54 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>
#include <vector>

#include "ClientDatabase.hpp"

enum ReplyEnum
{
    IGNORE, // Incase no reply is meant to be sent
    RPL_WELCOME = 1, // "Welcome to the Internet Relay Network <nick>!<user>@<host>"
    RPL_YOURHOST = 2, // "Your host is <servername>, running version <ver>"
    RPL_CREATED = 3, // "This server was created <date>"
    RPL_MYINFO = 4, // "<servername> <version> <available user modes> <available channel modes>"
    RPL_ISUPPORT = 5, // "<client> <1-13 tokens> :are supported by this server"

    RPL_LUSERCLIENT = 251, // ":There are <integer> users and <integer> services on <integer> servers"
    RPL_LUSEROP = 252, // "<integer> :operator(s) online"
    RPL_LUSERUNKNOWN = 253, // "<integer> :unknown connection(s)"
    RPL_LUSERCHANNELS = 254, // "<integer> :channels formed"
    RPL_LUSERME = 255, // ":I have <integer> clients and <integer> servers"

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
    ERR_CANNOTSENDTOCHAN = 404, // "<channel name> :Cannot send to channel"
    ERR_NORECIPIENT = 411, // ":No recipient given (<command>)"
    ERR_NOTEXTTOSEND = 412, //":No text to send"
    ERR_NOMOTD = 422, // "<client> :MOTD File is missing"
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
        Reply(ClientDatabase& clients) : m_clients(clients) {}

        std::stringstream create_start(ReplyEnum rpl, unsigned int user_id);
        std::string create_string(ReplyEnum rpl, unsigned int user_id, std::vector<std::string> const& params);
        void reply_to_sender(ReplyEnum reply, unsigned int user_id, std::vector<std::string> const& params);
        void reply_welcome(unsigned int user_id, unsigned int channel_count);

    private:

        ClientDatabase& m_clients;
};
