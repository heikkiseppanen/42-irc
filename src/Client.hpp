/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:54:10 by emajuri           #+#    #+#             */
/*   Updated: 2024/02/12 13:11:35 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <vector>
#include <string>

class Client
{
    public:
        inline Client() : m_sent_count(0), m_registered(0), m_quitting(false) {}

        inline bool is_empty() const { return m_nickname.empty(); }

        inline std::string const& get_nickname() const { return m_nickname; }
        inline void set_nickname(std::string const& nick) { m_nickname = nick; }

        inline std::string const& get_address() const { return m_address; }
        inline void set_address(std::string const& address) { m_address = address; }

        //messages
        inline void add_message(std::string const& msg) { m_message_queue.push_back(msg + "\r\n"); }
        inline std::string const& get_message() const { return m_message_queue[0]; }
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
        inline void password_received() { m_registered = m_registered | 0x4; }
        inline bool is_registered() const { return m_registered & 0x1 && m_registered & 0x2 && m_registered & 0x4; }
        inline bool has_nick() const { return m_registered & 0x1; }
        inline bool has_user() const { return m_registered & 0x2; }
        inline bool has_password() const { return m_registered & 0x4; }
        
        inline void quit() { m_quitting = true; }
        inline bool is_quitting() const { return m_quitting; }

        void print_messages() const;

    private:
        std::string m_nickname;
        std::string m_address;
        std::string m_buffer;

        std::vector<std::string> m_message_queue;

        unsigned int m_sent_count;
        int m_registered;
        bool m_quitting;
};
