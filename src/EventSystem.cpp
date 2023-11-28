/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventSystem.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:33:23 by hseppane          #+#    #+#             */
/*   Updated: 2023/11/28 16:47:40 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventSystem.hpp"
#include "Debug.hpp"

#include <string>
#include <iostream>

EventSystem::EventSystem()
    : m_kqueue(kqueue())
    , m_listener(NULL, "6667")
{
    IRC_ASSERT_THROW(m_kqueue < 0, std::string("Failed to create kqueue: ") + std::strerror(errno))

    struct kevent listener_event;

    EV_SET(&listener_event, m_listener.get_file_descriptor(), EVFILT_READ, EV_ADD, 0, 0, 0);

    m_changelist.push_back(listener_event);
    m_eventbuffer.resize(1);
}

void EventSystem::handle(EventHandler& handler)
{
    static struct timespec const timeout = {0, 1000};

    int events_polled = kevent(m_kqueue, m_changelist.data(), m_changelist.size(), m_eventbuffer.data(), m_eventbuffer.size(), &timeout);

    m_changelist.clear();

    for (std::vector<struct kevent>::const_iterator event = m_eventbuffer.cbegin(); events_polled != 0; --events_polled)
    {
        Socket client = event->ident;

        switch (event->filter)
        {
            case EVFILT_READ:
            {
                if (client.file_descriptor == m_listener.file_descriptor)
                {
                    std::cout << "New incoming connection\n";

                    Socket client = m_listener.accept();

                    struct kevent client_event = {};

                    EV_SET(&client_event, client.file_descriptor, EVFILT_READ, EV_ADD, 0, 0, 0);
                    m_changelist.push_back(client_event);

                    EV_SET(&client_event, client.file_descriptor, EVFILT_WRITE, EV_ADD, 0, 0, 0);
                    m_changelist.push_back(client_event);

                    handler.on_client_connected(client);
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
        }
    }
    
}
