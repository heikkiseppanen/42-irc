/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientDatabase.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:47:27 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/27 12:56:54 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>
#include <stack>
#include "SharedPointer.hpp"

struct Client
{
    inline Client(std::string const& nick) : nickname(nick) {}

    std::string nickname;
    std::vector<SharedPointer<std::string> > message_queue;
};

class ClientDatabase
{
    public:

        unsigned int add_client(std::string const& nick);
        void remove_client(unsigned int id);
        void print_clients() const;

        inline bool is_client(unsigned int id) const { return m_clients.size() < id && !m_clients[id].nickname.empty(); }

        inline std::string const& get_nickname(unsigned int id) const { return m_clients[id].nickname; }

        //messages
        inline void add_message(unsigned int id, SharedPointer<std::string> const& msg) { m_clients[id].message_queue.push_back(msg); }
        inline SharedPointer<std::string> const& get_message(unsigned int id) const { return m_clients[id].message_queue[0]; }
        inline void remove_message(unsigned int id) { m_clients[id].message_queue.erase(m_clients[id].message_queue.begin()); }
        inline bool has_message(unsigned int id) { return m_clients[id].message_queue.size() != 0; }

    private:
        std::vector<Client> m_clients;
        std::stack<unsigned int> m_free_ids;

        void empty_client(Client& client);
};
