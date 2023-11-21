/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelDatabase.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:21:47 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/21 16:46:52 by emajuri          ###   ########.fr       */
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
    for (std::map<std::string, Channel>::iterator it = m_channels.begin(); it != m_channels.end(); it++)
    {
        std::cout << it->first << "\n";
        it->second.print_channel();
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
