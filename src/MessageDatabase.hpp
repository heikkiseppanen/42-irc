/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageDatabase.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:59:29 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/22 17:56:30 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>

struct Message
{
    std::string message;
    unsigned int reference_count;
    
    Message(std::string const& message, unsigned int reference_count) : message(message), reference_count(reference_count) {}
};

class MessageDatabase
{
    public:

        
        void    message_add(std::string const& message, unsigned int reference_count);
        void    message_remove_reference(std::string const& message);
    
    private:
        std::vector<Message>    m_messages;

    struct find_id
    {
        find_id(std::string const& msg) : msg(msg) {}
        bool operator()(Message const& message) { return message.message == msg; }
        std::string const& msg;
    };
};