/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientDatabase.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:47:27 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/27 11:59:25 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>
#include <stack>
#include "SharedPointer.hpp"

struct ClientInfo
{
    inline ClientInfo(std::string const& nick) : nickname(nick) {}

    std::string nickname;
    std::vector<SharedPointer<std::string> > message_queue;
};

class ClientDatabase
{
    public:

        unsigned int add_client(std::string const& nick);
        void remove_client(unsigned int id);
        void print_clients() const;

        std::string const& get_nickname(unsigned int id);

        //messages
        inline void add_message(unsigned int id, SharedPointer<std::string> const& msg) { m_clients[id].message_queue.push_back(msg); }
        inline SharedPointer<std::string> const& get_message(unsigned int id) { return m_clients[id].message_queue[0]; }
        inline void remove_message(unsigned int id) { m_clients[id].message_queue.erase(m_clients[id].message_queue.begin()); }

    private:
        std::vector<ClientInfo> m_clients;
        std::stack<unsigned int> m_free_ids;

        void empty_client(ClientInfo& info);
};
