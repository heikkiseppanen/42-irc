#include "Server.hpp"

#include "EventHandler.hpp"

#include <iostream>

Server::Server(const char* port, const char* password)
    : m_password(password ? std::make_optional<std::string>(password) : std::nullopt),
      m_eventloop(port)
{
}

Server::~Server() {}

void Server::run()
{
    EventHandler handler(m_clients, m_channels);

    while (1)
    {
        m_eventloop.handle(handler);
    }
}
