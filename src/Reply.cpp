/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:21:52 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/16 22:32:21 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reply.hpp"
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>


// :<hostname> <enum> <target> :<MSG> <target> // rpl_welcome 1
// :<hostname> <enum> <target> <channel> <mode> <mode params> // rpl_channelmodeis 324
// :<hostname> <enum> <target> <channel> :<MSG> // rpl_notopic 331
// :<hostname> <enum> <target> <channel> :<topic> // rpl_topic 332
// :<hostname> <enum> <target> <channel> <nick> // rpl_inviting 341
// :<hostname> <enum> <target> <channel> <invitemask> // rpl_invitelist 346
// :<hostname> <enum> <target> <channel> :<MSG> // rpl_endofinvitelist 347
// :<hostname> <enum> <target> "( "=" / "*" / "@" ) <channel> :[ "@" / "+" ] <nick> *( " " [ "@" / "+" ] <nick> ) // rpl_namreply 353


// :<hostname> <enum> <target> <nick> :<MSG> // err_nosuchnick 401
// :<hostname> <enum> <target> <channel> :<MSG> // err_nosuchchannel 403
// :<hostname> <enum> <target> :<MSG> // err_notexttosend 412
// :<hostname> <enum> <target> :<MSG> // err_nonicknamegiven 431
// :<hostname> <enum> <target> <nick> :<MSG> // err_erroneusnickname 432
// :<hostname> <enum> <target> <nick> :<MSG> // err_nicknameinuse 433
// :<hostname> <enum> <target> <nick> <channel> :<MSG> // err_usernotinchannel 441
// :<hostname> <enum> <target> <channel> :<MSG> // err_notonchannel 442
// :<hostname> <enum> <target> <nick> <channel> :<MSG> // err_useronchannel 443
// :<hostname> <enum> <target> <command> :<MSG> // err_needmoreparams 461
// :<hostname> <enum> <target> :<MSG> // err_alreadyregistred 462
// :<hostname> <enum> <target> <channel> :<MSG> // err_keyset 467
// :<hostname> <enum> <target> <channel> :<MSG> // err_channelisfull 471
// :<hostname> <enum> <target> <char> :<MSG> <channel> // err_unknownmode 472
// :<hostname> <enum> <target> <channel> :<MSG> // err_inviteonlychan 473
// :<hostname> <enum> <target> <channel> :<MSG> // err_badchannelkey 475
// :<hostname> <enum> <target> <channel> :<MSG> // err_chanoprivsneeded 482

std::stringstream Reply::create_start(ReplyEnum reply, unsigned int user_id)
{
    std::stringstream msg;
    msg << "<hostname>";
    msg << " ";
    msg << std::right << std::setfill('0') << std::setw(3) << std::to_string(reply);
    msg << " ";
    msg << m_clients.get_client(user_id).get_nickname();
    return msg;
}

std::string Reply::create_string(ReplyEnum reply, unsigned int user_id, std::vector<std::string> const& params)
{
    std::stringstream msg = create_start(reply, user_id);
    for (auto param : params)
        msg << param;
    msg << "\r\n";
    return msg.str();
}

void Reply::reply_to_sender(ReplyEnum reply, unsigned int user_id, std::vector<std::string> const& params)
{
    Client client = m_clients.get_client(user_id);
    std::string msg = create_string(reply, user_id, params);
    client.add_message(std::make_shared<std::string>(msg));
}

//all of these come with rpl welcome
// :<hostname> <enum> <target> :<MSG> <hostname> <MSG> <ver> // rpl_yourhost 2
// :<hostname> <enum> <target> :<MSG> <date> // rpl_created
// :<hostname> <enum> <target> :<hostname> <ver> <usermodes> <channelmodes> // rpl_myinfo
// :<hostname> <enum> <target> :<MSG> <integer> <MSG> <integer> <MSG> <integer> <MSG> // RPL_LUSERCLIENT
// :<hostname> <enum> <target> <integer> :<MSG> // RPL_LUSEROP
// :<hostname> <enum> <target> <integer> :<MSG> // RPL_LUSERUNKNOWN
// :<hostname> <enum> <target> <integer> :<MSG> // RPL_LUSERCHANNELS
// :<hostname> <enum> <target> :<MSG> <integer> <MSG> <integer> <MSG> // RPL_LUSERME

void Reply::reply_welcome(unsigned int user_id)
{
    //TODO variables
    reply_to_sender(RPL_WELCOME, user_id, {":Welcome to the Internet Relay Network ", m_clients.get_client(user_id).get_nickname()});
    reply_to_sender(RPL_YOURHOST, user_id, {":Your host is ", "<servername> ", ", running version ", "1.0.1"});
    reply_to_sender(RPL_CREATED, user_id, {":This server was created ", "<date>"});
    reply_to_sender(RPL_MYINFO, user_id, {"<servername>", " ", "<ver>", " * ", "iklot"});
    reply_to_sender(RPL_LUSERCLIENT, user_id, {":There are ", std::to_string(m_clients.count_clients()), " and 0 services on 1 servers"});
    reply_to_sender(RPL_LUSEROP, user_id, {"<integer>", " operator(s) online"});
    reply_to_sender(RPL_LUSERUNKNOWN, user_id, {"<integer>", " unknown connection(s)"});
    reply_to_sender(RPL_LUSERCHANNELS, user_id, {std::to_string(m_channels.count_channels()), " channels formed"});
    reply_to_sender(RPL_LUSERME, user_id, {":I have, ", std::to_string(m_clients.count_clients()), " clients and 1 servers"});
}