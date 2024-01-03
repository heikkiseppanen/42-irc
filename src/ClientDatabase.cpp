/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientDatabase.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:47:22 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/30 12:48:03 by emajuri          ###   ########.fr       */
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
    for (std::vector<Client>::const_iterator it = m_clients.begin(); it != m_clients.end(); it++)
    {
        if (it->is_empty())
            std::cout << "Empty\n";
        else
        {
            std::cout << "| " << it->get_nickname() << " |\n";
            it->print_messages();
        }
    }
    std::cout << "\n";
}

void ClientDatabase::add_messages_to_group(std::vector<unsigned int> const& users, unsigned int exclude, SharedPointer<std::string> const& msg)
{
    for (std::vector<unsigned int>::const_iterator it = users.begin(); it != users.end(); it++)
    {
        if (*it == exclude)
            continue;
        if (is_client(*it))
        {
            Client& tmp = get_client(*it);
            tmp.add_message(msg);
        }
        else
        {
            std::cerr << "ERROR: add_messages_to_group: User " << *it << " not found\n";
        }
    }
}

void ClientDatabase::empty_client(Client& client)
{
    client.empty_client();
}
