/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelDatabase.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:20:47 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/21 16:15:02 by emajuri          ###   ########.fr       */
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

        void print_all_channels();

    private:

        std::map<std::string, Channel>    m_channels;
};