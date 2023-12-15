/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventSystem.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:33:23 by hseppane          #+#    #+#             */
/*   Updated: 2023/12/15 16:13:56 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventSystem.hpp"
#include "Debug.hpp"

#include <string>
#include <iostream>

EventSystem::EventSystem()
    : m_kqueue(kqueue())
    , m_listener(NULL, "6667")
    , m_changelist()
    , m_eventbuffer()
{
    IRC_ASSERT_THROW(m_kqueue < 0, std::string("Failed to create kqueue: ") + std::strerror(errno))

    struct kevent listener_event;

    EV_SET(&listener_event, m_listener.get_file_descriptor(), EVFILT_READ, EV_ADD, 0, 0, 0);

    m_changelist.push_back(listener_event);
    m_eventbuffer.resize(EVENT_BUFFER_SIZE);
}

EventSystem::~EventSystem() { close(m_kqueue); }

void EventSystem::handle(EventHandler& handler)
{
    static struct timespec const timeout = {0, 1000};

    int events_polled = kevent(m_kqueue, m_changelist.data(), m_changelist.size(), m_eventbuffer.data(), m_eventbuffer.size(), &timeout);

    IRC_ASSERT_THROW(events_polled < 0, std::string("kevent error: ") + std::strerror(errno));

    m_changelist.clear();

    for (std::vector<struct kevent>::const_iterator event = m_eventbuffer.begin(); events_polled != 0; --events_polled)
    {
        Socket client(event->ident);

        switch (event->filter)
        {
            case EVFILT_READ:
            {
                if (client == m_listener)
                {
                    Socket new_client = m_listener.accept();

                    struct kevent client_event = {};

                    EV_SET(&client_event, new_client.get_file_descriptor(), EVFILT_READ, EV_ADD, 0, 0, 0);
                    m_changelist.push_back(client_event);

                    client_event.filter = EVFILT_WRITE;

                    m_changelist.push_back(client_event);

                    handler.on_client_connected(new_client);
                }
                else
                {
                    handler.on_client_readable(client);
                }
                break;
            }
            case EVFILT_WRITE:
            {
                //std::cout << "WRITE\n";
                handler.on_client_writeable(client);
                break;
            }
            default: std::cout << "Event not implemented\n";
        }
    }
}
