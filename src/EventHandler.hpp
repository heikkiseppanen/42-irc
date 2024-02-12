/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:17:19 by emajuri           #+#    #+#             */
/*   Updated: 2024/02/12 13:04:42 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Socket.hpp"
#include "ClientDatabase.hpp"
#include "ChannelDatabase.hpp"
#include "CommandParser.hpp"

#include <map>
#include <string>

#define INPUT_BUFFER_SIZE 512
#define MSG_END "\r\n"

class EventHandler
{
    public:
        inline EventHandler(ClientDatabase& clients, ChannelDatabase& channels, std::string const& start_time, std::string const& password)
            : m_parser(clients, channels, start_time, password),
              m_clients(clients),
              m_channels(channels)
        {}

        void on_client_connected(Socket const& socket, std::string const& address);
        void on_client_disconnected(Socket const& socket);
        void on_client_readable(Socket const& socket);
        void on_client_writeable(Socket const& socket);
        void cleanup();

    private:
        std::map<int, unsigned int> m_socket_client_table;

        CommandParser m_parser;

        ClientDatabase& m_clients;
        ChannelDatabase& m_channels;
};
