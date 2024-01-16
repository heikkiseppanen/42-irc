/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientDatabase.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:47:27 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/23 16:12:56 by emajuri          ###   ########.fr       */
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
        bool is_nick_in_use(std::string const& nick);
        
        inline Client& get_client(unsigned int id) { return m_clients[id]; }
        inline int count_clients() { return m_clients.size(); }

        unsigned int get_user_id(std::string const& nick);

        inline unsigned int count_clients() const { return m_clients.size(); }
        unsigned int count_unknown_clients() const;


    private:
        std::vector<Client> m_clients;
        std::stack<unsigned int> m_free_ids;

        void empty_client(Client& client);
};
