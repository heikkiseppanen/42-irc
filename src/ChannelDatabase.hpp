/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelDatabase.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:20:47 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/21 14:47:57 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>
#include <map>

//Channel modes

#define ADD     true
#define REMOVE  false

struct Channel
{
    std::vector<unsigned int>   operators;
    std::vector<unsigned int>   users;
    std::vector<unsigned int>   invited;

    std::string password;
    std::string topic;

    unsigned int user_limit;

    bool    has_invite_only;
    bool    has_topic_op_only;
    bool    has_password;
};

class ChannelDatabase
{
    public:

        Channel& get_channel(std::string const& channel_name);
        void add_channel(std::string const& channel_name, unsigned int user_id);
        void join_channel(std::string const& channel_name, std::string const& password, unsigned int user_id);
        void change_topic(std::string const& channel_name, std::string const& topic, unsigned int user_id);

        //Operator only
        void kick(std::string const& channel_name, unsigned int user_id, unsigned int kick_id);
        void invite(std::string const& channel_name, unsigned int user_id, unsigned int invite_id);

        //Channel modes
        void set_invite_only(Channel& channel, bool mode);
        void set_op_topic(Channel& channel, bool mode);
        void set_password(Channel& channel, bool mode, std::string const& pass);
        void set_op(Channel& channel, bool mode, unsigned int user_id);
        void set_user_limit(Channel& channel, bool mode, unsigned int user_limit);

        void print_all_channels();

    private:

        std::map<std::string, Channel>    m_channels;

        bool is_invited(Channel const& channel, unsigned int user_id) const;
        bool is_password_good(Channel const& channel, std::string const& password) const;
        bool is_operator(Channel const& channel, unsigned int user_id) const;
};