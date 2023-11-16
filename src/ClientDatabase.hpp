/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientDatabase.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:47:27 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/16 13:53:51 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>
#include <stack>

struct ClientInfo
{
    inline ClientInfo(std::string const& nick) : nickname(nick) {}

    std::string nickname;
};

class ClientDatabase
{
    public:

        int     add_client(std::string const& nick);
        void    remove_client(int id);
        void    print_clients() const;

        std::string const& get_nickname(int id);

    private:
        std::vector<ClientInfo> m_clients;
        std::stack<int>         m_free_ids;

        void    empty_client(ClientInfo& info);
};
