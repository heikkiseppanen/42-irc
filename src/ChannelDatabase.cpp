/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelDatabase.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:21:47 by emajuri           #+#    #+#             */
/*   Updated: 2024/02/07 13:28:56 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelDatabase.hpp"
#include "ClientDatabase.hpp"

#include <algorithm>
#include <iostream>

void ChannelDatabase::add_channel(std::string const& channel_name, unsigned int user_id)
{
    Channel channel(user_id);

    m_channels[channel_name] = channel;
}

void ChannelDatabase::print_all_channels()
{
    for (auto& channel : m_channels)
    {
        std::cout << channel.first << "\n";
        channel.second.print_channel();
    }
}

void ChannelDatabase::remove_user(unsigned int user_id, std::string const& reason, ClientDatabase& client_database)
{
    for (auto& channel : m_channels)
    {
        if (channel.second.is_subscribed(user_id))
        {
            channel.second.remove_user_from_channel(user_id);
            for (unsigned int user : channel.second.get_users())
            {
                client_database.get_client(user).add_message(":" + client_database.get_client(user_id).get_nickname() + " QUIT :Quit: " + reason);
            }
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
