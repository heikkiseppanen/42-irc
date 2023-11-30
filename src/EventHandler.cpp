/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:43:21 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/30 13:03:42 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventHandler.hpp"

void EventHandler::on_client_connected(Socket socket)
{
    m_socket_client_table[socket.file_descriptor] = m_clients.add_client();
}

void EventHandler::on_client_readable(Socket socket)
{
    unsigned int id = m_socket_client_table[socket.file_descriptor];
    Client client = m_clients.get_client(id);

    char buf[m_buffer_size + 1];
    unsigned int received = socket.receive(buf, m_buffer_size);
    if (received == -1)
    {
        return;
    }
    else if (received == 0)
    {
        m_socket_client_table.erase(socket.file_descriptor);
        m_clients.remove_client(id);
        m_channels.remove_user(id);
        return;
    }
    buf[received] = '\0';

    client.add_to_buffer(buf);
    std::string const& buffer = client.get_buffer();
    for (std::string::const_iterator it = buffer.begin(); it != buffer.end() - 1; it++)
    {
        if (*it == m_end[0] && *(it + 1) == m_end[1])
        {
            it += 2;
            //TODO interpreter called here
            client.remove_from_buffer(it - buffer.begin());
            break;
        }
    }
}

void EventHandler::on_client_writeable(Socket socket)
{
    Client client = m_clients.get_client(m_socket_client_table[socket.file_descriptor]);
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