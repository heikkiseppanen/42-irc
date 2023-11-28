/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:17:49 by hseppane          #+#    #+#             */
/*   Updated: 2023/11/28 12:38:46 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Socket.hpp"

#include <vector>
#include <sys/event.h>

class EventSystem
{
    public:
        EventSystem();
        ~EventSystem() { close(m_kqueue); }

        void handle(/* EventHandler? */);

    private:
        int m_kqueue;

        Socket m_listener;
        
        std::vector<struct kevent> m_changelist;
        std::vector<struct kevent> m_eventbuffer;
};
