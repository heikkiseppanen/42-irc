/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:21:52 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/08 21:16:52 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reply.hpp"

Reply::Reply(ClientDatabase& clients, ChannelDatabase& channels) : clients(clients), channels(channels)
{
    Replies[RPL_WELCOME] = "Welcome to the Internet Relay Network <nick>!<user>@<host>";
}