/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Clients.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:40:29 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/15 20:45:43 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Clients.hpp"
#include <iostream>
#include <vector>
#include <string>

void    Clients::add_user(std::string const& nick)
{
    int id = find_next_id();
    if (id == -1)
        m_nicknames.push_back(nick);
    else
        m_nicknames[id] = nick;
}

void    Clients::print_users()
{
    for (std::vector<std::string>::iterator it = m_nicknames.begin(); it != m_nicknames.end(); it++)
    {
        if (it->empty())
            std::cout << "Empty\n";
        else
            std::cout << *it << "\n";
    }
}

int Clients::find_next_id()
{
    for (std::vector<std::string>::iterator it = m_nicknames.begin(); it != m_nicknames.end(); it++)
    {
        if (it->empty())
            return it - m_nicknames.begin();
    }
    return -1;
}