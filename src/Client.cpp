/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:54:18 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/04 15:13:45 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <iostream>

void Client::print_messages() const
{
    for (auto& msg : m_message_queue)
    {
        std::cout << *msg << " | ";
    }
    std::cout << "\n";
}