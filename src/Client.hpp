/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:54:10 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/29 18:48:12 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "SharedPointer.hpp"
#include <vector>
#include <string>

class Client
{
    public:
        inline Client(std::string const& nick) : m_nickname(nick), m_sent_count(0) {}

        inline bool is_empty() const { return m_nickname.empty(); }

        inline std::string const& get_nickname() const { return m_nickname; }
        inline void set_nickname(std::string const& nick) { m_nickname = nick; }

        //messages
        inline void add_message(SharedPointer<std::string> const& msg) { m_message_queue.push_back(msg); }
        inline std::string const& get_message() const { return *m_message_queue[0].get(); }
        inline void remove_message() { m_message_queue.erase(m_message_queue.begin()); }
        inline bool has_message() const { return m_message_queue.size() != 0; }

        inline void empty_client() { m_nickname.clear(); m_message_queue.clear(); }

        //buffer
        inline void add_to_buffer(std::string const& read) { m_buffer += read; }
        inline std::string const& get_buffer() const { return m_buffer; }
        inline void remove_from_buffer(unsigned int len) { m_buffer.erase((m_buffer.begin(), m_buffer.begin() + len)); }

        //sent_count
        inline unsigned int get_sent_count() const { return m_sent_count; }
        inline void set_sent_count(unsigned int count) { m_sent_count = count; }

        void print_messages() const;

    private:
        std::string m_nickname;
        std::vector<SharedPointer<std::string> > m_message_queue;
        std::string m_buffer;
        unsigned int m_sent_count;
};