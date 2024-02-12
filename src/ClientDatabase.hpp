/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientDatabase.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:47:27 by emajuri           #+#    #+#             */
/*   Updated: 2024/02/12 13:05:50 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <stack>
#include "Client.hpp"

class ClientDatabase
{
    public:
        unsigned int add_client(std::string const& address);
        void remove_client(unsigned int id);
        void print_clients() const;

        inline bool is_client(unsigned int id) const { return id < m_clients.size() && !m_clients[id].is_empty(); }
        bool is_nick_in_use(std::string const& nick) const;
        
        inline Client& get_client(unsigned int id) { return m_clients[id]; }
        unsigned int get_user_id(std::string const& nick) const;

        inline unsigned int count_clients() const { return m_clients.size(); }
        unsigned int count_unknown_clients() const;

        inline void add_to_cleanup(int socket_id) { m_cleanup_socket_ids.push_back(socket_id); }
        inline std::vector<int> get_cleanup() { return m_cleanup_socket_ids; }
        inline void empty_cleanup() { m_cleanup_socket_ids.clear(); }

    private:
        std::vector<Client> m_clients;
        std::stack<unsigned int> m_free_ids;
        std::vector<int> m_cleanup_socket_ids;

        void empty_client(Client& client);
};
