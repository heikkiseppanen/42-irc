#include "Server.hpp"

#include "EventHandler.hpp"

#include <iostream>

Server::Server() : m_eventloop() {}

Server::~Server() {}

void Server::run()
{
    EventHandler handler(m_clients, m_channels);

    while (1)
    {
        m_eventloop.handle(handler);
    }
}
