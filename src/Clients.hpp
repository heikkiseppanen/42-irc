/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Clients.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:40:24 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/16 13:27:37 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTS_HPP
# define CLIENTS_HPP

#include <vector>
#include <string>
#include <stack>

struct ClientInfo
{
    inline ClientInfo(int id, std::string const& nick) : m_id(id), m_nickname(nick) {}

    int m_id;
    std::string m_nickname;
};

class Clients
{
    public:

        int     add_client(std::string const& nick);
        void    remove_client(int id);
        void    print_clients() const;

    private:
        std::vector<ClientInfo> m_clients;
        std::stack<int>         m_free_ids;


        bool    is_empty(ClientInfo const& info) const;
        void    empty_client(ClientInfo& info);
};

#endif