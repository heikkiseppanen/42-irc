/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:51:27 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/21 16:57:20 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>

//Channel modes
#define ADD     true
#define REMOVE  false

class Channel
{
    public:
        Channel() {}
        Channel(unsigned int user_id);

        void join_channel(unsigned int user_id, std::string const& password);
        void change_topic(std::string const& topic);

        //Operator only
        void kick(unsigned int user_id);
        void invite(unsigned int user_id);

        //Channel modes
        void set_invite_only(bool mode);
        void set_op_topic(bool mode);
        void set_password(bool mode, std::string const& pass);
        void set_op(bool mode, unsigned int user_id);
        void set_user_limit(bool mode, unsigned int user_limit);

        void print_channel();

    private: 

        std::vector<unsigned int> m_users;
        std::vector<unsigned int> m_operators;
        std::vector<unsigned int> m_invited;

        std::string m_password;
        std::string m_topic;

        unsigned int m_user_limit;

        bool m_has_invite_only;
        bool m_has_topic_op_only;
        bool m_has_password;

        bool is_invited(unsigned int user_id) const;
        bool is_password_good(std::string const& password) const;
        bool is_operator(unsigned int user_id) const;
};
