/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:54:10 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/29 13:42:31 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "SharedPointer.hpp"
#include <vector>
#include <string>

class Client
{
    public:
        inline Client(std::string const& nick) : nickname(nick) {}

        inline bool is_empty() const { return nickname.empty(); }

        inline std::string const& get_nickname() const { return nickname; }
        inline void set_nickname(std::string const& nick) { nickname = nick; }

        //messages
        inline void add_message(SharedPointer<std::string> const& msg) { message_queue.push_back(msg); }
        inline std::string const& get_message() const { return *message_queue[0].get(); }
        inline void remove_message() { message_queue.erase(message_queue.begin()); }
        inline bool has_message() const { return message_queue.size() != 0; }

        inline void empty_client() { nickname.clear(); message_queue.clear(); }

        void print_messages() const;

    private:
        std::string nickname;
        std::vector<SharedPointer<std::string> > message_queue;
};