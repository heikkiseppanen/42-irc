/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientDatabase.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:47:22 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/27 12:06:24 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ClientDatabase.hpp"
#include <iostream>

unsigned int    ClientDatabase::add_client(std::string const& nick)
{
    int id;
    if (m_free_ids.empty())
    {
        id = m_clients.size();
        m_clients.push_back(Client(nick));
    }
    else
    {
        id = m_free_ids.top();
        m_free_ids.pop();
        m_clients[id].nickname = nick;
    }
    return (id);
}

void    ClientDatabase::remove_client(unsigned int id)
{
    if (m_clients.size() - 1 == id)
    {
        m_clients.pop_back();
    }
    else
    {
        empty_client(m_clients[id]);
        m_free_ids.push(id);
    }
}

void    ClientDatabase::print_clients() const
{
    for (std::vector<Client>::const_iterator it = m_clients.begin(); it != m_clients.end(); it++)
    {
        if (it->nickname.empty())
            std::cout << "Empty\n";
        else
            std::cout << "| " << it->nickname << " |\n";
    }
}

void    ClientDatabase::empty_client(Client& client)
{
    client.nickname.clear();
    client.message_queue.clear();
}
