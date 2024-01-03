/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:54:18 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/03 14:31:58 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <iostream>

void Client::print_messages() const
{
    for (std::vector<std::shared_ptr<std::string> >::const_iterator msg = m_message_queue.begin(); msg != m_message_queue.end(); msg++)
    {
        std::cout << **msg << " | ";
    }
    std::cout << "\n";
}