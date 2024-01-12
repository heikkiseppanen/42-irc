/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:07:46 by hseppane          #+#    #+#             */
/*   Updated: 2024/01/12 12:35:14 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unistd.h>
#include <sys/socket.h>

constexpr int SOCKET_LISTEN_BACKLOG_SIZE = 32;

class Socket
{
    public:

        inline Socket() : m_file_descriptor(-1) {};
        inline Socket(int file_descriptor) : m_file_descriptor(file_descriptor) {};

        Socket(char const* ip, char const* port);

        inline void close() { if (m_file_descriptor != -1) { ::close(m_file_descriptor); }}

        inline bool is_valid() const { return m_file_descriptor != -1; }

        inline int get_file_descriptor() const { return m_file_descriptor; }

        ssize_t send(void const* source, size_t size) const;

        ssize_t receive(void* destination, size_t size) const; 

        Socket accept() const;

        inline bool operator == (const Socket rhs) { return m_file_descriptor == rhs.get_file_descriptor(); };

    private:
        int m_file_descriptor;
};
