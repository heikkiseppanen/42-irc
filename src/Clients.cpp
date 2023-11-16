/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Clients.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:40:29 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/16 13:06:03 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Clients.hpp"
#include <iostream>
#include <vector>
#include <string>

int    Clients::add_client(std::string const& nick)
{
    int id = find_next_id();
    if (id == -1)
    {
        id = m_clients.size();
        m_clients.push_back(ClientInfo(id, nick));
    }
    else
    {
        m_clients[id].m_nickname = nick;
        m_clients[id].m_id = id;
    }
    return (id);
}

void    Clients::remove_client(int id)
{
    if (m_clients.back().m_id == id)
        m_clients.pop_back();
    else
        empty_client(m_clients[id]);
}

void    Clients::print_clients() const
{
    for (std::vector<ClientInfo>::const_iterator it = m_clients.begin(); it != m_clients.end(); it++)
    {
        if (is_empty(*it))
            std::cout << "Empty\n";
        else
            std::cout << "| " << it->m_id << " | " << it->m_nickname << " |\n";
    }
}

bool    Clients::is_empty(ClientInfo const& info) const
{
    return info.m_id == -1;
}

void    Clients::empty_client(ClientInfo& info)
{
    info.m_id = -1;
    info.m_nickname.clear();
}

int Clients::find_next_id()
{
    for (std::vector<ClientInfo>::iterator it = m_clients.begin(); it != m_clients.end(); it++)
    {
        if (is_empty(*it))
            return it - m_clients.begin();
    }
    return -1;
}
