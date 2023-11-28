/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:56:39 by hseppane          #+#    #+#             */
/*   Updated: 2023/11/28 13:07:30 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "EventSystem.hpp"

class Server
{
    public:
        Server();
        ~Server();

        void run();

    private:
        Server(Server const& other);
        Server& operator = (Server const& other);

        EventSystem m_eventloop;
};
