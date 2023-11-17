/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageDatabase.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:59:29 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/16 14:13:36 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>

struct Message
{
    std::string message;
    int         reference_count;
    int         id;
};

class MessageDatabase
{
    public:

        void    message_remove_reference(int id);
    
    private:
        std::vector<Message>    m_messages;

        inline bool    compare(Message message) { return message.id; }

};