/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:56:39 by hseppane          #+#    #+#             */
/*   Updated: 2023/11/17 12:57:55 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>

#include <sys/socket.h>
#include <sys/poll.h>

typedef struct pollfd Socket;

class Server
{
    public:
        Server();
        ~Server();

        void run();

    private:
        Server(Server const& other);
        Server& operator = (Server const& other);

        std::vector<Socket> m_socket_list;
};
