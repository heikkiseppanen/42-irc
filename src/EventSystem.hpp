/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventSystem.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:17:49 by hseppane          #+#    #+#             */
/*   Updated: 2023/12/15 15:46:40 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Socket.hpp"

#include <vector>
#include <sys/event.h>
#include "EventHandler.hpp"

#define EVENT_BUFFER_SIZE 128

class EventSystem
{
    public:
        EventSystem();
        ~EventSystem();

        void handle(EventHandler& handler);

    private:
        int m_kqueue;

        Socket m_listener;
        
        std::vector<struct kevent> m_changelist;
        std::vector<struct kevent> m_eventbuffer;
};
