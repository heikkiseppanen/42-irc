/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientDatabase.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:47:22 by emajuri           #+#    #+#             */
/*   Updated: 2024/02/06 12:55:32 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ClientDatabase.hpp"
#include <iostream>
#include <algorithm>

unsigned int ClientDatabase::add_client()
{
    int id;
    if (m_free_ids.empty())
    {
        id = m_clients.size();
        m_clients.push_back(Client());
    }
    else
    {
        id = m_free_ids.top();
        m_free_ids.pop();
    }
    return id;
}

void ClientDatabase::remove_client(unsigned int id)
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

void ClientDatabase::print_clients() const
{
    std::cout << "Clients:\n";
    for (auto& client : m_clients)
    {
        if (client.is_empty())
            std::cout << "Empty\n";
        else
        {
            std::cout << "| " << client.get_nickname() << " |\n";
            client.print_messages();
        }
    }
    std::cout << "\n";
}

//To use: First check if nick is in use or get underflow
unsigned int ClientDatabase::get_user_id(std::string const& nick) const
{
    auto const pos = std::find_if(m_clients.begin(), m_clients.end(), [&](Client const& client) { return client.get_nickname() == nick; });
    if (pos != m_clients.end())
        return pos - m_clients.begin();
    return -1;
}

bool ClientDatabase::is_nick_in_use(std::string const& nick) const
{
    for (auto& client : m_clients)
    {
        if (client.get_nickname() == nick)
            return (true);
    }
    return (false);
}

void ClientDatabase::empty_client(Client& client)
{
    client.empty_client();
}

unsigned int ClientDatabase::count_unknown_clients() const 
{
    unsigned int count = 0;
    for (auto const& client : m_clients)
    {
        if (client.is_registered())
            count++;
    }
    return count;
}