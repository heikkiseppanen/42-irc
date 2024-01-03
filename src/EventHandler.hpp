/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:17:19 by emajuri           #+#    #+#             */
/*   Updated: 2023/12/01 13:06:10 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Socket.hpp"
#include "ClientDatabase.hpp"
#include "ChannelDatabase.hpp"
#include <map>
#include <string>

#define INPUT_BUFFER_SIZE 512
#define MSG_END "\r\n"

class EventHandler
{
    public:
        EventHandler(ClientDatabase& clients, ChannelDatabase& channels) : m_clients(clients), m_channels(channels) {}

        void on_client_connected(Socket socket);
        void on_client_readable(Socket socket);
        void on_client_writeable(Socket socket);

    private:
        std::map<int, unsigned int> m_socket_client_table;
        ClientDatabase& m_clients;
        ChannelDatabase& m_channels;
};