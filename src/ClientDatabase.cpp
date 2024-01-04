/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientDatabase.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:47:22 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/04 15:21:51 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ClientDatabase.hpp"
#include <iostream>

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
    return (id);
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

void ClientDatabase::add_messages_to_group(std::vector<unsigned int> const& users, unsigned int exclude, std::shared_ptr<std::string> const& msg)
{
    for (auto user_id : users)
    {
        if (user_id == exclude)
            continue;
        if (is_client(user_id))
        {
            Client& tmp = get_client(user_id);
            tmp.add_message(msg);
        }
        else
        {
            std::cerr << "ERROR: add_messages_to_group: User " << user_id << " not found\n";
        }
    }
}

void ClientDatabase::empty_client(Client& client)
{
    client.empty_client();
}
