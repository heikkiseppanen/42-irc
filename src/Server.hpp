/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:56:39 by hseppane          #+#    #+#             */
/*   Updated: 2024/01/22 10:36:24 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "EventSystem.hpp"
#include "ClientDatabase.hpp"
#include "ChannelDatabase.hpp"

#include <optional>
#include <string>

class Server
{
    public:
        Server() = delete;
        Server(const char* port, const char* password);

        Server(Server const& other) = delete;
        Server& operator = (Server const& other) = delete;

        ~Server();

        void run();

    private:

        std::optional<std::string> m_password;

        EventSystem m_eventloop;

        ClientDatabase m_clients;
        ChannelDatabase m_channels; 
};
