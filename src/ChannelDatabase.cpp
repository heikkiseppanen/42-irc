/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelDatabase.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:21:47 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/20 15:04:29 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelDatabase.hpp"
#include <algorithm>
#include <iostream>

void    ChannelDatabase::add_channel(std::string const& channel_name, unsigned int user_id)
{
    Channel channel;

    channel.users.push_back(user_id);
    channel.operators.push_back(user_id);
    channel.user_limit = 0;
    channel.has_invite_only = false;
    channel.has_topic_op_only = false;
    channel.has_password = false;
    m_channels[channel_name] = channel;
    //TODO RPL_TOPIC
}

void    ChannelDatabase::join_channel(std::string const& channel_name, std::string const& password, unsigned int user_id)
{
    std::map<std::string, Channel>::iterator it = m_channels.find(channel_name);
    if (it == m_channels.end())
    {
        add_channel(channel_name, user_id);
        return;
    }

    Channel& channel = it->second;
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
    if (std::find(channel.users.begin(), channel.users.end(), user_id) != channel.users.end())
    {
        //TODO already on channel
        return;
    }
    //TODO tell everyone that user joined a channel
    channel.users.push_back(user_id);
}

void ChannelDatabase::change_topic(std::string const& channel_name, std::string const& topic, unsigned int user_id)
{
    Channel& channel = get_channel(channel_name);
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
    Channel& channel = get_channel(channel_name);
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
    Channel& channel = get_channel(channel_name);
    if (!is_operator(channel, user_id))
    {
        //TODO handle not op
        return;
    }
    //TODO remove from invite list or not?_?
    channel.invited.push_back(invite_id);
}

void    ChannelDatabase::mode(std::string const& channel_name, int mode, unsigned int user_limit, unsigned int user_id, std::string const& password)
{
    Channel& channel = get_channel(channel_name);
    bool add = mode & ADD;
    if (mode & INVITE_ONLY)
        channel.has_invite_only = add;

    if (mode & TOPIC_OP_ONLY)
        channel.has_topic_op_only = add;

    if (mode & PASSWORD)
    {
        channel.has_password = add;
        if (add)
            channel.password = password;
    }

    if (mode & OPERATOR)
    {
        std::vector<unsigned int>::iterator it = std::find(channel.operators.begin(), channel.operators.end(), user_id);
        if (add)
        {
            if (it == channel.operators.end())
                if (std::find(channel.users.begin(), channel.users.end(), user_id) != channel.users.end())
                    channel.operators.push_back(user_id);
        }
        else
        {
            if (it != channel.operators.end())
                channel.operators.erase(it);
        }
    }

    if (mode & USER_LIMIT)
    {
        if (add)
        {
            channel.user_limit = user_limit;
        }
        else
        {
            channel.user_limit = 0;
        }
    }
}

void    ChannelDatabase::print_all_channels()
{
    Channel channel;
    for (std::map<std::string, Channel>::iterator it = m_channels.begin(); it != m_channels.end(); it++)
    {
        std::cout << it->first << "\n";
        channel = it->second;
        std::cout << "Users: ";
        for (std::vector<unsigned int>::iterator it = channel.users.begin(); it != channel.users.end(); it++)
        {
            std::cout << *it << ", ";
        }
        std::cout << "\n";

        std::cout << "Operators: ";
        for (std::vector<unsigned int>::iterator it = channel.operators.begin(); it != channel.operators.end(); it++)
        {
            std::cout << *it << ", ";
        }
        std::cout << "\n";

        std::cout << "invited: ";
        for (std::vector<unsigned int>::iterator it = channel.invited.begin(); it != channel.invited.end(); it++)
        {
            std::cout << *it << ", ";
        }
        std::cout << "\n";

        std::cout << "Topic: " << channel.topic << "\n";

        std::cout << "Modes:\n";
        std::cout << std::boolalpha;
        std::cout << "\tInvite only: " << channel.has_invite_only << "\n";
        std::cout << "\tTopic op only: " << channel.has_topic_op_only << "\n";
        std::cout << "\tHas password: " << channel.has_password << " | " << channel.password << "\n";
        std::cout << "\tUser limit: " << channel.user_limit << "\n\n";
    }
}

Channel& ChannelDatabase::get_channel(std::string const& channel_name)
{
    std::map<std::string, Channel>::iterator it = m_channels.find(channel_name);
    if (it == m_channels.end())
    {
        //TODO handle missing channel
    }
    return it->second;
}

bool    ChannelDatabase::is_invited(Channel const& channel, unsigned int user_id) const
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

bool    ChannelDatabase::is_password_good(Channel const& channel, std::string const& password) const
{
    if (channel.has_password)
    {
        if (channel.password != password)
        {
            //TODO incorrect password
            return false;
        }
    }
    return true;
}

bool    ChannelDatabase::is_operator(Channel const& channel, unsigned int user_id) const
{
    if (std::find(channel.operators.begin(), channel.operators.end(), user_id) == channel.operators.end())
    {
        //TODO not operator
        return false;
    }
    return true;
}
