/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:51:27 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/31 16:05:18 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>
#include "Reply.hpp"

//Channel modes
#define ADD     true
#define REMOVE  false

class Channel
{
    public:
        Channel() {}
        Channel(unsigned int user_id);

        void join_channel(unsigned int user_id);

        ReplyEnum change_topic(unsigned int user_id, std::string const& topic);

        int leave_channel(unsigned int user_id);
        void remove_invite(unsigned int user_id);

        //Operator only
        ReplyEnum kick(unsigned int op_id, unsigned int kick_id);
        ReplyEnum invite(unsigned int op_id, unsigned int invite_id);

        //Channel modes
        ReplyEnum set_invite_only(unsigned int op_id, bool mode);
        ReplyEnum set_op_topic(unsigned int op_id, bool mode);
        ReplyEnum set_password(unsigned int op_id, bool mode, std::string const& pass);
        ReplyEnum set_op(unsigned int op_id, bool mode, unsigned int affect_id);
        ReplyEnum set_user_limit(unsigned int op_id, bool mode, unsigned int user_limit);

        //Getters
        inline std::vector<unsigned int> const& get_users() const { return m_users; }
        inline std::vector<unsigned int> const& get_operators() const { return m_operators; }
        inline std::string const& get_topic() const { return m_topic; }

        void print_channel();

        //
        bool is_invited(unsigned int user_id) const;
        bool is_valid_password(std::string const& password) const;
        bool is_operator(unsigned int user_id) const;
        bool is_not_full() const;
        bool is_subscribed(unsigned int user_id) const;
        inline bool is_channel_topic_empty() const { return m_topic.empty(); }
        inline bool is_invite_only() const { return m_has_invite_only; }
        inline bool is_topic_op_only() const { return m_has_op_topic; }
        inline bool has_password() const { return m_has_password; }

    private: 

        std::vector<unsigned int> m_users;
        std::vector<unsigned int> m_operators;
        std::vector<unsigned int> m_invited;

        std::string m_password;
        std::string m_topic;

        unsigned int m_user_limit;

        bool m_has_op_topic;
        bool m_has_password;
        bool m_has_invite_only;

};
