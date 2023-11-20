/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelDatabase.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:20:47 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/20 13:34:32 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>
#include <map>

struct Channel
{
    std::vector<unsigned int>   operators;
    std::vector<unsigned int>   users;
    std::vector<unsigned int>   invited;

    bool    has_invite_only;
    bool    has_topic_op_only;
    bool    has_password;

    std::string password;

    int user_limit;

    std::string topic;
};

class ChannelDatabase
{
    public:

        void    add_channel(std::string const& channel_name, unsigned int user_id);
        void    join_channel(std::string const& channel_name, std::string const& password, unsigned int user_id);
        void    change_topic(std::string const& channel_name, std::string const& topic, unsigned int user_id);

        //Operator only
        void    kick(std::string const& channel_name, unsigned int user_id, unsigned int kick_id);
        void    invite(std::string const& channel_name, unsigned int user_id, unsigned int invite_id);

    private:

        std::map<std::string, Channel>    m_channels;

        Channel get_channel(std::string const& channel_name);
        bool    is_invited(Channel channel, unsigned int user_id);
        bool    is_password_good(Channel channel, std::string const& password);
        bool    is_operator(Channel channel, unsigned int user_id);
};