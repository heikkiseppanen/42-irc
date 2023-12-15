/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:56:39 by hseppane          #+#    #+#             */
/*   Updated: 2023/12/15 15:22:28 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "EventSystem.hpp"
#include "ClientDatabase.hpp"
#include "ChannelDatabase.hpp"

class Server
{
    public:
        Server();
        ~Server();

        void run();

    private:
        Server(Server const& other);
        Server& operator = (Server const& other);

        EventSystem m_eventloop;

        ClientDatabase m_clients;
        ChannelDatabase m_channels; 
};
