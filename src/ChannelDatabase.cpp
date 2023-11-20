/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelDatabase.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:21:47 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/20 12:46:53 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelDatabase.hpp"
#include <algorithm>

void    ChannelDatabase::add_channel(std::string const& channel_name, Channel& channel)
{
    m_channels[channel_name] = channel;
}

void    ChannelDatabase::join_channel(std::string const& channel_name, std::string const& password, unsigned int user_id)
{
    Channel channel = get_channel(channel_name);

    if (!is_invited(channel, user_id))
        return;

    if (!is_password_good(channel, password))
        return;
    if (channel.user_limit != 0)
    {
        if (channel.users.size() == channel.user_limit)
        {
            //TODO handle full channel
            return;
        }
    }
    //TODO tell everyone that user joined a channel
    channel.users.push_back(user_id);
}

void ChannelDatabase::change_topic(std::string const& channel_name, std::string const& topic, unsigned int user_id)
{
    Channel channel = get_channel(channel_name);
    if (channel.has_topic_op_only)
    {
        if (!is_operator(channel, user_id))
        {
            //Todo handle not operator
        }
    }
    //TODO tell everyone that topic changed
    get_channel(channel_name).topic = topic;
}

void    ChannelDatabase::kick(std::string const& channel_name, unsigned int user_id, unsigned int kick_id)
{
    Channel channel = get_channel(channel_name);
    if (!is_operator(channel, user_id))
    {
        //TODO handle not op
        return;
    }

    std::vector<unsigned int>::iterator it = std::find(channel.users.begin(), channel.users.end(), kick_id);
    if (it == channel.users.end())
    {
        //TODO user not found
        return;
    }
    //TODO tell everyone user was kicked from the channel
    channel.users.erase(it);

    it = std::find(channel.operators.begin(), channel.operators.end(), kick_id);
    if (it != channel.operators.end())
    {
        channel.operators.erase(it);
    }
}

void    ChannelDatabase::invite(std::string const& channel_name, unsigned int user_id, unsigned int invite_id)
{
    Channel channel = get_channel(channel_name);
    if (!is_operator(channel, user_id))
    {
        //TODO handle not op
        return;
    }
    //TODO remove from invite list or not?_?
    channel.invited.push_back(user_id);
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

bool    ChannelDatabase::is_operator(Channel channel, unsigned int user_id)
{
    if (std::find(channel.operators.begin(), channel.operators.end(), user_id) == channel.invited.end())
    {
        //TODO not operator
        return false;
    }
    return true;
}