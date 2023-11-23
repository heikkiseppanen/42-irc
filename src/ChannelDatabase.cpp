/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelDatabase.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:21:47 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/05 17:25:09 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelDatabase.hpp"
#include <algorithm>
#include <iostream>

void ChannelDatabase::add_channel(std::string const& channel_name, unsigned int user_id)
{
    Channel channel(user_id);

    m_channels[channel_name] = channel;
    //TODO RPL_TOPIC
}

void ChannelDatabase::print_all_channels()
{
    for (auto& channel : m_channels)
    {
        std::cout << channel.first << "\n";
        channel.second.print_channel();
    }
}

void ChannelDatabase::remove_user(unsigned int user_id)
{
    for (auto& channel : m_channels)
    {
        if (channel.second.is_subscribed(user_id))
        {
            channel.second.leave_channel(user_id);
        }
    }
    for (auto it = m_channels.begin(), ite = m_channels.end(); it != ite;)
    {
        if (it->second.get_users().empty())
            it = m_channels.erase(it);
        else
            ++it;
    }
}
