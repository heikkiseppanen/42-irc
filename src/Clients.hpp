/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Clients.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:40:24 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/15 20:45:35 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTS_HPP
# define CLIENTS_HPP

#include <vector>
#include <string>

class Clients
{
    public:

        void    add_user(std::string const& nick);
        inline void    remove_user(int id) { m_nicknames[id].clear(); }
        void    print_users();

    private:
        std::vector<std::string>    m_nicknames;

        int find_next_id();
};

#endif