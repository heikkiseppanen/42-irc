/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Clients.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:40:24 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/16 13:01:52 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTS_HPP
# define CLIENTS_HPP

#include <vector>
#include <string>

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
        void    print_clients();

    private:
        std::vector<ClientInfo> m_clients;

        bool    is_empty(ClientInfo const& info);
        void    empty_client(ClientInfo& info);
        int     find_next_id();
};

#endif