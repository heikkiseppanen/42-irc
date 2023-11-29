/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:07:46 by hseppane          #+#    #+#             */
/*   Updated: 2023/11/29 18:42:07 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unistd.h>

#include <sys/socket.h>

struct Socket
{
    int file_descriptor;

    inline Socket() : file_descriptor(-1) {};
    inline Socket(int file_descriptor) : file_descriptor(file_descriptor) {};

    Socket(char const* ip, char const* port);

    inline void close() { if (file_descriptor != -1) { ::close(file_descriptor); }}

    inline bool is_valid() { return file_descriptor != -1; }

    inline int get_file_descriptor() { return file_descriptor; }

    inline ssize_t send(void* data, size_t size) { return ::send(file_descriptor, data, size, 0); }
    inline ssize_t send(void const* data, size_t size) { return ::send(file_descriptor, data, size, 0); }

    inline ssize_t receive(void* destination, size_t size) { return ::recv(file_descriptor, destination, size, 0); }

    Socket accept();
};
