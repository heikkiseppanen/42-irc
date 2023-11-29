/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:43:21 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/29 16:10:31 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventHandler.hpp"

void EventHandler::on_client_connected(Socket client)
{
    (void)client;
}

void EventHandler::on_client_readable(Socket client)
{
    (void)client;
}

void EventHandler::on_client_writeable(Socket client)
{
    (void)client;
}