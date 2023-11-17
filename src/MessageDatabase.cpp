/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageDatabase.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:04:51 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/16 14:13:43 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MessageDatabase.hpp"
#include "algorithm"

void    MessageDatabase::message_remove_reference(int id)
{
    std::find_if(m_messages.begin(), m_messages.end(), compare);
}