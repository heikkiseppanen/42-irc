/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelDatabase.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:20:47 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/04 17:08:38 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include "Channel.hpp"

class ChannelDatabase
{
    public:

        inline bool is_channel(std::string const& channel_name) const { return m_channels.find(channel_name) != m_channels.end(); }
        inline Channel& get_channel(std::string const& channel_name) { return m_channels.find(channel_name)->second; }
        void add_channel(std::string const& channel_name, unsigned int user_id);
        inline void remove_channel(std::string const& channel_name) { m_channels.erase(channel_name); }

        void print_all_channels();

        bool is_user_on_channel(std::string const& channel_name, unsigned int user_id) { return get_channel(channel_name).is_subscribed(user_id); }
        void remove_user(unsigned int user_id);

    private:

        std::map<std::string, Channel>    m_channels;
};