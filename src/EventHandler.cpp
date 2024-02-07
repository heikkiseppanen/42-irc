/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:43:21 by emajuri           #+#    #+#             */
/*   Updated: 2024/02/07 17:03:10 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventHandler.hpp"
#include "Debug.hpp"

#include <iostream>

void EventHandler::on_client_connected(const Socket& socket)
{
    auto it = m_socket_client_table.find(socket.get_file_descriptor());
    IRC_ASSERT_THROW(it != m_socket_client_table.end(), "Trying to override existing client with new connection");
    m_socket_client_table.insert( {socket.get_file_descriptor(), m_clients.add_client()} );
}

void EventHandler::on_client_disconnected(Socket const& socket)
{
    auto it = m_socket_client_table.find(socket.get_file_descriptor());
    IRC_ASSERT_THROW(it == m_socket_client_table.end(), "No client for disconnecting socket found");
    unsigned int id = it->second;

    m_socket_client_table.erase(socket.get_file_descriptor());
    m_channels.remove_user(id, ":Connection timeout", m_clients);
    m_clients.remove_client(id);
}

bool find_command(std::string& command, Client& client)
{
    std::string const& buffer = client.get_buffer();
    for (std::string::const_iterator it = buffer.begin(); it != buffer.end(); it++)
    {
        if (it - buffer.begin() > 510)
        {
            client.remove_from_buffer(it + 1 - buffer.begin());
            return false;
        }
        if (*it == MSG_END[0] && *(it + 1) == MSG_END[1])
        {
            command = buffer.substr(0, it - buffer.begin());
            it += 2;
            client.remove_from_buffer(it - buffer.begin());
            return true;
        }
    }
    return false;
}

void EventHandler::on_client_readable(Socket const& socket)
{
    auto it = m_socket_client_table.find(socket.get_file_descriptor());
    IRC_ASSERT_THROW(it == m_socket_client_table.end(), "No client for readable socket found");
    unsigned int id = it->second;

    Client& client = m_clients.get_client(id);

    char buf[INPUT_BUFFER_SIZE + 1];
    ssize_t received = socket.receive(buf, INPUT_BUFFER_SIZE - client.get_buffer().length());
    buf[received] = '\0';

    if (received == 0)
    {
        return;
    }

    client.add_to_buffer(buf);
    std::string command;
    while (find_command(command, client))
    {
        m_parser.parser(command, id);
    }
}

void EventHandler::on_client_writeable(Socket const& socket)
{
    auto it = m_socket_client_table.find(socket.get_file_descriptor());
    IRC_ASSERT_THROW(it == m_socket_client_table.end(), "No client for writeable socket found");
    unsigned int id = it->second;

    Client& client = m_clients.get_client(id);
    if (client.has_message())
    {
        std::string const& msg = client.get_message();
        unsigned int sent_count = client.get_sent_count();
        sent_count += socket.send(msg.c_str() + sent_count, msg.length() - sent_count);
        if (sent_count == msg.length())
        {
            sent_count = 0;
            client.remove_message();
            if (client.is_quitting())
                m_clients.add_to_cleanup(socket.get_file_descriptor());
        }
        client.set_sent_count(sent_count);
    }
}

void EventHandler::cleanup()
{
    for (int socket_id : m_clients.get_cleanup())
    {
        m_clients.remove_client(m_socket_client_table[socket_id]);
        m_socket_client_table.erase(socket_id);
        Socket(socket_id).close();
    }
    m_clients.empty_cleanup();
}
