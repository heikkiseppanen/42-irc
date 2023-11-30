/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientDatabase.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:47:27 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/30 12:47:55 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <stack>
#include "Client.hpp"

class ClientDatabase
{
    public:
        unsigned int add_client();
        void remove_client(unsigned int id);
        void print_clients() const;

        inline bool is_client(unsigned int id) const { return id < m_clients.size() && !m_clients[id].is_empty(); }
        inline Client& get_client(unsigned int id) { return m_clients[id]; }

        void add_messages_to_group(std::vector<unsigned int> const& users, unsigned int exclude, SharedPointer<std::string> const& msg);

    private:
        std::vector<Client> m_clients;
        std::stack<unsigned int> m_free_ids;

        void empty_client(Client& client);
};
