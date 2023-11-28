/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:07:46 by hseppane          #+#    #+#             */
/*   Updated: 2023/11/28 14:36:24 by hseppane         ###   ########.fr       */
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

    template<typename T>
    inline ssize_t send(T* data, size_t count) { return ::send(file_descriptor, data, count * sizeof(T), 0); }

    template<typename T>
    inline ssize_t receive(T* destination, size_t count) { return ::recv(file_descriptor, destination, count * sizeof(T), 0); }

    Socket accept();
};
