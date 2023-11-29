/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventSystem.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:17:49 by hseppane          #+#    #+#             */
/*   Updated: 2023/11/29 16:07:09 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Socket.hpp"

#include <vector>
#include <sys/event.h>
#include "EventHandler.hpp"

class EventSystem
{
    public:
        EventSystem();
        ~EventSystem() { close(m_kqueue); }

        void handle(/*EventHandler& handler*/);

    private:
        int m_kqueue;

        Socket m_listener;
        
        std::vector<struct kevent> m_changelist;
        std::vector<struct kevent> m_eventbuffer;
};
