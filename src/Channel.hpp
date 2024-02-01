/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:51:27 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/31 18:48:26 by jole             ###   ########.fr       */
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

        inline void topic_change(std::string const& topic) { m_topic = topic; }
        inline void topic_clear() { m_topic.clear(); }

        int leave_channel(unsigned int user_id);
        void remove_invite(unsigned int user_id);

        //Operator only
        ReplyEnum kick(unsigned int op_id, unsigned int kick_id);
        ReplyEnum invite(unsigned int op_id, unsigned int invite_id);

        //Channel modes
        inline void set_invite_only(bool mode) { m_has_invite_only = mode; }
        inline void set_op_topic(bool mode) { m_has_op_topic = mode; }
        void set_password(bool mode, std::string const& pass);
        void set_op(bool mode, unsigned int affect_id);
        void set_user_limit(bool mode, unsigned int user_limit);

        //Getters
        inline std::vector<unsigned int> const& get_users() const { return m_users; }
        inline std::vector<unsigned int> const& get_operators() const { return m_operators; }
        inline std::string const& get_topic() const { return m_topic; }
        inline std::string const& get_password() const { return m_password; }
        inline unsigned int get_user_limit() const { return m_user_limit; }

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
        inline bool has_user_limit() const { return m_user_limit != 0; }

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
