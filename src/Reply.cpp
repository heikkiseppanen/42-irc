/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:21:52 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/16 17:20:34 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reply.hpp"

//all of these come with rpl welcome
// :<hostname> <enum> <target> :<MSG> <hostname> <MSG> <ver> // rpl_yourhost
// :<hostname> <enum> <target> :<MSG> <date> // rpl_created
// :<hostname> <enum> <target> :<hostname> <ver> <usermodes> <channelmodes> // rpl_myinfo
// :<hostname> <enum> <target> :<MSG> <integer> <MSG> <integer> <MSG> <integer> <MSG> // RPL_LUSERCLIENT
// :<hostname> <enum> <target> <integer :<MSG> // RPL_LUSEROP
// :<hostname> <enum> <target> <integer :<MSG> // RPL_LUSERUNKNOWN
// :<hostname> <enum> <target> <integer :<MSG> // RPL_LUSERCHANNELS
// :<hostname> <enum> <target> :<MSG> <integer> <MSG> <integer> <MSG> // RPL_LUSERME


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


void Reply::reply_to_sender(unsigned int user_id, ReplyEnum reply)
{
    Client client = m_clients.get_client(user_id);
    switch (reply)
    {
        case RPL_WELCOME:
            client.add_message(std::make_shared<std::string>("Welcome to the Internet Relay Network " + client.get_nickname()));
        default:
            (void)1;
    }
}