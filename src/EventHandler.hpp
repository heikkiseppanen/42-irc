/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:17:19 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/29 12:30:48 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Socket.hpp"
#include <map>

class EventHandler
{
    public:

        void on_client_connected(Socket client);
        void on_client_readable(Socket client);
        void on_client_writeable(Socket client);

    private:

        std::map<int, unsigned int> socket_client_table;
};