/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelDatabase.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:21:47 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/17 18:44:34 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelDatabase.hpp"
#include <algorithm>

void    ChannelDatabase::join_channel(std::string const& channel_name, std::string const& password, unsigned int user_id)
{
    Channel channel = get_channel(channel_name);

    if (!is_invited(channel, user_id))
        return;

    if (!is_password_good(channel, password))
        return;
    //TODO tell everyone that user joined a channel
    channel.users.push_back(user_id);
}

void    ChannelDatabase::invite(std::string const& channel_name, unsigned int user_id)
{
    get_channel(channel_name).invited.push_back(user_id);
}

Channel ChannelDatabase::get_channel(std::string const& channel_name)
{
    std::map<std::string, Channel>::iterator it = m_channels.find(channel_name);
    if (it == m_channels.end())
    {
        //TODO handle missing channel
        return;
    }
    return it->second;
}

void ChannelDatabase::change_topic(std::string const& channel_name, std::string const& topic)
{
    get_channel(channel_name).topic = topic;
}

bool    ChannelDatabase::is_invited(Channel channel, unsigned int user_id)
{
    if (channel.has_invite_only)
    {
        if (std::find(channel.invited.begin(), channel.invited.end(), user_id) == channel.invited.end())
        {
            //TODO handle not invited
            return false;
        }
    }
    return true;
}

bool    ChannelDatabase::is_password_good(Channel channel, std::string const& password)
{
    if (channel.has_password)
    {
        if (channel.password == password)
        {
            //TODO incorrect password
            return false;
        }
    }
    return true;
}