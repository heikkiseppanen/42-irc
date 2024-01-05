/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientDatabase.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:47:27 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/05 17:33:15 by jole             ###   ########.fr       */
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

        unsigned int get_user_id(std::string const& nick);

        bool is_nick_in_use(std::string const& nick);
        void add_messages_to_group(std::vector<unsigned int> const& users, unsigned int exclude, std::shared_ptr<std::string> const& msg);

    private:
        std::vector<Client> m_clients;
        std::stack<unsigned int> m_free_ids;

        void empty_client(Client& client);
};
