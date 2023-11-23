/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:07:46 by hseppane          #+#    #+#             */
/*   Updated: 2023/11/23 14:21:05 by hseppane         ###   ########.fr       */
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

    static Socket listen(char const* address, char const* port);

    Socket accept(struct sockaddr_storage* address);

    inline void close()  { if (file_descriptor != -1) { ::close(file_descriptor); }}
};
