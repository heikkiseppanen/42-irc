/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:43:21 by emajuri           #+#    #+#             */
/*   Updated: 2023/12/15 16:14:14 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventHandler.hpp"

#include <iostream>

void EventHandler::on_client_connected(Socket socket)
{
    m_socket_client_table[socket.get_file_descriptor()] = m_clients.add_client();
}

bool find_command(std::string& command, Client& client)
{
    std::string const& buffer = client.get_buffer();
    for (std::string::const_iterator it = buffer.begin(); it != buffer.end() - 1; it++)
    {
        if (it - buffer.begin() > 510)
        {
            client.remove_from_buffer(it - buffer.begin());
            return false;
        }
        if (*it == MSG_END[0] && *(it + 1) == MSG_END[1])
        {
            it += 2;
            command = buffer.substr(0, it - buffer.begin());
            client.remove_from_buffer(it - buffer.begin());
            return true;
        }
    }
    return false;
}

void EventHandler::on_client_readable(Socket socket)
{
    unsigned int id = m_socket_client_table[socket.get_file_descriptor()];
    Client client = m_clients.get_client(id);

    char buf[INPUT_BUFFER_SIZE + 1];
    ssize_t received = socket.receive(buf, INPUT_BUFFER_SIZE - client.get_buffer().length());
    buf[received] = '\0';

    if (received == 0)
    {
        m_socket_client_table.erase(socket.get_file_descriptor());
        m_clients.remove_client(id);
        m_channels.remove_user(id);
        socket.close();
        return;
    }

    client.add_to_buffer(buf);
    std::string command;
    while (find_command(command, client))
    {
            //TODO interpreter called here
    }
}

void EventHandler::on_client_writeable(Socket socket)
{
    Client client = m_clients.get_client(m_socket_client_table[socket.get_file_descriptor()]);
    if (client.has_message())
    {
        std::string msg = client.get_message();
        unsigned int sent_count = client.get_sent_count();
        sent_count += socket.send(msg.c_str() + sent_count, msg.length() - sent_count);
        if (sent_count == msg.length())
            sent_count = 0;
        client.set_sent_count(sent_count);
    }
}
