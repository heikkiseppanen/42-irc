/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:54:18 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/29 16:24:00 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <iostream>

void Client::print_messages() const
{
    for (std::vector<SharedPointer<std::string> >::const_iterator msg = m_message_queue.begin(); msg != m_message_queue.end(); msg++)
    {
        std::cout << **msg << " | ";
    }
    std::cout << "\n";
}