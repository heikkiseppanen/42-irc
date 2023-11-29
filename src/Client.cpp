/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:54:18 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/29 13:42:38 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <iostream>

void Client::print_messages() const
{
    for (std::vector<SharedPointer<std::string> >::const_iterator msg = message_queue.begin(); msg != message_queue.end(); msg++)
    {
        std::cout << **msg << " | ";
    }
    std::cout << "\n";
}