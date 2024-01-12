/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventSystem.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:33:23 by hseppane          #+#    #+#             */
/*   Updated: 2024/01/12 12:29:09 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventSystem.hpp"
#include "Debug.hpp"

#include <string>
#include <iostream>
#include <array>

EventSystem::EventSystem()
    : m_kqueue(kqueue())
    , m_listener(NULL, "6667")
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
    static struct timespec const timeout = {0, 10000};

    int events_polled = kevent(m_kqueue,
            m_changelist.data(), m_changelist.size(),
            m_eventbuffer.data(), m_eventbuffer.size(),
            &timeout
    );

    IRC_ASSERT_THROW(events_polled < 0, std::string("kevent error: ") + std::strerror(errno));

    std::cout << "EVENT COUNT: " << events_polled << '\n';

    m_changelist.clear();

    auto end = m_eventbuffer.begin() + events_polled;
    for (auto it = m_eventbuffer.begin(); it != end; ++it)
    {
        try
        {
            Socket client(it->ident);

            if (it->flags & EV_EOF)
            {
                std::cout << "Disconnect\n";
                client.close();
                continue;
            }

            switch (it->filter)
            {
                case EVFILT_READ:
                {
                    std::cout << "Socket read " << client.get_file_descriptor() << '\n';

                    if (client == m_listener)
                    {
                        for (auto connection_count = it->data; connection_count > 0; --connection_count)
                        {
                            Socket new_client = m_listener.accept();

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
                    std::cout << client.get_file_descriptor() << " ready to recv: " << it->data << " bytes\n";


                    handler.on_client_writeable(client);
                    break;
                }
                default: std::cerr << "WARNING: Unhandled event: " << it->filter << '\n';
            }
        }
        catch (std::exception& e)
        {
            std::cerr << "ircserv: " << e.what() << '\n';
        }
    }

    std::cin.ignore();

}
