/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelDatabase.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:20:47 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/30 12:53:34 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include "Channel.hpp"

class ChannelDatabase
{
    public:

        Channel& get_channel(std::string const& channel_name);
        void add_channel(std::string const& channel_name, unsigned int user_id);
        inline void remove_channel(std::string const& channel_name) { m_channels.erase(channel_name); }

        void print_all_channels();

        void remove_user(unsigned int user_id);

    private:

        std::map<std::string, Channel>    m_channels;
};