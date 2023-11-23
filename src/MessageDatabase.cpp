/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageDatabase.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:04:51 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/23 13:04:03 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MessageDatabase.hpp"
#include <algorithm>

void    MessageDatabase::message_add(std::string const& message, unsigned int reference_count)
{
    m_messages.push_back(Message(message, reference_count));
}

void    MessageDatabase::message_remove_reference(std::string const& message)
{
    std::vector<Message>::iterator it = std::find_if(m_messages.begin(), m_messages.end(), find_id(message));
    if (--it->reference_count == 0)
    {
        m_messages.erase(it);
    }
}
