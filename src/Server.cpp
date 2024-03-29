/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:00:57 by hseppane          #+#    #+#             */
/*   Updated: 2024/02/12 15:07:52 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "EventHandler.hpp"

#include <iostream>
#include <chrono>
#include <ctime>

Server::Server(const char* port, const char* password)
    : m_password(password ? std::make_optional<std::string>(password) : std::nullopt),
      m_eventloop(port)
{
}

Server::~Server() {}

static std::string get_start_time()
{
    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    return (std::ctime(&time));
}

void Server::run()
{
    EventHandler handler(m_clients, m_channels, get_start_time(), m_password.has_value() ? m_password.value() : "");

    while (1)
    {
        m_eventloop.handle(handler);
    }
}
