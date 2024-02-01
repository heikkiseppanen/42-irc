/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventSystem.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:33:23 by hseppane          #+#    #+#             */
/*   Updated: 2024/02/08 12:40:48 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventSystem.hpp"
#include "Debug.hpp"

#include <string>
#include <iostream>
#include <array>
#include <algorithm>

EventSystem::EventSystem(const char* port)
    : m_kqueue(kqueue())
    , m_listener(NULL, port)
    , m_changelist()
    , m_eventbuffer(EVENT_BUFFER_SIZE)
{
    IRC_ASSERT_THROW(m_kqueue < 0, std::string("Failed to create kqueue: ") + std::strerror(errno))

    struct kevent listener_event;
    EV_SET(&listener_event, m_listener.get_file_descriptor(), EVFILT_READ, EV_ADD | EV_CLEAR, 0, 0, 0);
    m_changelist.push_back(listener_event);
}

EventSystem::~EventSystem() { close(m_kqueue); }

void EventSystem::handle(EventHandler& handler)
{
    static struct timespec constexpr timeout = {0, 10000};

    int events_polled = kevent(m_kqueue,
            m_changelist.data(), m_changelist.size(),
            m_eventbuffer.data(), m_eventbuffer.size(),
            &timeout
    );

    IRC_ASSERT_THROW(events_polled < 0, std::string("kevent error: ") + std::strerror(errno));

    m_changelist.clear();

    std::vector<unsigned int> disconnect_list;
    auto end = m_eventbuffer.begin() + events_polled;
    
    for (auto it = m_eventbuffer.begin(); it != end; ++it)
    {
        if (std::find(disconnect_list.begin(), disconnect_list.end(), it->ident) != disconnect_list.end())
            continue;
        try
        {
            Socket client{ static_cast<int>(it->ident) };

            if (it->flags & EV_EOF)
            {
                disconnect_list.push_back(it->ident);
                handler.on_client_disconnected(client);
                client.close();
                continue;
            }

            switch (it->filter)
            {
                case EVFILT_READ:
                {
                    if (client == m_listener)
                    {
                        for (auto connection_count = it->data; connection_count > 0; --connection_count)
                        {
                            std::string address;
                            Socket new_client = m_listener.accept(address);

                            struct kevent client_event = {};

                            EV_SET(&client_event, new_client.get_file_descriptor(), EVFILT_READ, EV_ADD, 0, 0, 0);
                            m_changelist.push_back(client_event);

                            EV_SET(&client_event, new_client.get_file_descriptor(), EVFILT_WRITE, EV_ADD, 0, 0, 0);
                            m_changelist.push_back(client_event);

                            handler.on_client_connected(new_client);
                        }
                    }
                    else
                    {
                        handler.on_client_readable(client);
                    }
                    break;
                }
                case EVFILT_WRITE:
                {
                    handler.on_client_writeable(client);
                    break;
                }
                default: throw std::runtime_error("WARNING: Unhandled event type " + std::to_string(it->filter));
            }
        }
        catch (std::exception& e)
        {
            std::cerr << "ircserv: " << e.what() << '\n';
        }
    }
    disconnect_list.clear();
    handler.cleanup();
}
