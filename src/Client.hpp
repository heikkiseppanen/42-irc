/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:54:10 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/03 20:52:27 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <vector>
#include <string>

class Client
{
    public:
        inline Client() : m_sent_count(0), m_registered(0) {}

        inline bool is_empty() const { return m_nickname.empty(); }

        inline std::string const& get_nickname() const { return m_nickname; }
        inline void set_nickname(std::string const& nick) { m_nickname = nick; }

        //messages
        inline void add_message(std::shared_ptr<std::string> const& msg) { m_message_queue.push_back(msg); }
        inline std::string const& get_message() const { return *m_message_queue[0]; }
        inline void remove_message() { m_message_queue.erase(m_message_queue.begin()); }
        inline bool has_message() const { return m_message_queue.size() != 0; }

        inline void empty_client() { *this = Client(); }

        //buffer
        inline void add_to_buffer(std::string const& read) { m_buffer += read; }
        inline std::string const& get_buffer() const { return m_buffer; }
        inline void remove_from_buffer(unsigned int len) { m_buffer.erase(m_buffer.begin(), m_buffer.begin() + len); }

        //sent_count
        inline unsigned int get_sent_count() const { return m_sent_count; }
        inline void set_sent_count(unsigned int count) { m_sent_count = count; }

        //register
        inline void nick_received() { m_registered = m_registered | 0x1; }
        inline void user_received() { m_registered = m_registered | 0x2; }
        inline bool is_registered() { return m_registered & 0x1 && m_registered & 0x2; }

        void print_messages() const;

    private:
        std::string m_nickname;
        std::vector<std::shared_ptr<std::string> > m_message_queue;
        std::string m_buffer;
        unsigned int m_sent_count;
        int m_registered;
};