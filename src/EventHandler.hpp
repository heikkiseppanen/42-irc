/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:17:19 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/30 12:50:16 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Socket.hpp"
#include "ClientDatabase.hpp"
#include "ChannelDatabase.hpp"
#include <map>
#include <string>

class EventHandler
{
    public:

        EventHandler(ClientDatabase& clients, ChannelDatabase& channels) : m_clients(clients), m_channels(channels) {}

        void on_client_connected(Socket socket);
        void on_client_readable(Socket socket);
        void on_client_writeable(Socket socket);

    private:
        const int m_buffer_size = 512;
        const std::string m_end = "\r\n";

        std::map<int, unsigned int> m_socket_client_table;
        ClientDatabase& m_clients;
        ChannelDatabase& m_channels;
};