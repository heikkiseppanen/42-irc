/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:21:48 by emajuri           #+#    #+#             */
/*   Updated: 2024/02/13 12:52:23 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>
#include <vector>

#include "ClientDatabase.hpp"

enum ReplyEnum
{
    IGNORE, 
    RPL_WELCOME = 1, 
    RPL_YOURHOST = 2, 
    RPL_CREATED = 3, 
    RPL_MYINFO = 4, 
    RPL_ISUPPORT = 5, 

    RPL_LUSERCLIENT = 251, 
    RPL_LUSEROP = 252, 
    RPL_LUSERUNKNOWN = 253, 
    RPL_LUSERCHANNELS = 254, 
    RPL_LUSERME = 255, 

    RPL_CHANNELMODEIS = 324, 
    RPL_NOTOPIC = 331, 
    RPL_TOPIC = 332, 
    RPL_TOPICWHOTIME = 333, 
    RPL_INVITING = 341, 
    RPL_INVITELIST = 346, 
    RPL_ENDOFINVITELIST = 347, 
    RPL_NAMREPLY = 353, 
        
        
        
    RPL_ENDOFNAMES = 366, 

    ERR_NOSUCHNICK = 401, 
    ERR_NOSUCHCHANNEL = 403, 
    ERR_CANNOTSENDTOCHAN = 404, 
    ERR_NORECIPIENT = 411, 
    ERR_NOTEXTTOSEND = 412, 
    ERR_NOMOTD = 422, 
    ERR_NONICKNAMEGIVEN = 431, 
    ERR_ERRONEUSNICKNAME = 432, 
    ERR_NICKNAMEINUSE = 433, 
    ERR_USERNOTINCHANNEL = 441, 
    ERR_NOTONCHANNEL = 442, 
    ERR_USERONCHANNEL = 443, 
    ERR_NEEDMOREPARAMS = 461, 
    ERR_ALREADYREGISTRED = 462, 
    ERR_PASSWDMISMATCH = 464, 
    ERR_KEYSET = 467, 
    ERR_CHANNELISFULL = 471, 
    ERR_UNKNOWNMODE = 472, 
    ERR_INVITEONLYCHAN = 473, 
    ERR_BADCHANNELKEY = 475, 
    ERR_CHANOPRIVSNEEDED = 482, 

    ERR_INVALIDKEY = 525,  
};

class Reply
{
    public:

        Reply() = delete;
        Reply(ClientDatabase& clients, std::string const& start_time) : m_start_time(start_time), m_clients(clients) {}

        std::stringstream create_start(ReplyEnum rpl, unsigned int user_id);
        std::string create_string(ReplyEnum rpl, unsigned int user_id, std::vector<std::string> const& params);
        void reply_to_sender(ReplyEnum reply, unsigned int user_id, std::vector<std::string> const& params);
        void reply_welcome(unsigned int user_id, unsigned int channel_count);
        void reply_to_other(ReplyEnum reply, unsigned int user_id, unsigned int sender, std::vector<std::string> const& params);

    private:
        std::string const m_start_time;

        ClientDatabase& m_clients;
};
