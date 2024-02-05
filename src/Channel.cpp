/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:11:27 by emajuri           #+#    #+#             */
/*   Updated: 2024/02/05 17:43:56 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <iostream>

Channel::Channel(unsigned int user_id)
{
    m_users.push_back(user_id);
    m_operators.push_back(user_id);
    m_user_limit = 0;
    m_has_invite_only = false;
    m_has_op_topic = false;
    m_has_password = false;
}

void Channel::join_channel(unsigned int user_id)
{
    remove_invite(user_id);
    m_users.push_back(user_id);
}

int Channel::leave_channel(unsigned int leave_id)
{
    std::vector<unsigned int>::iterator it = std::find(m_users.begin(), m_users.end(), leave_id);
    m_users.erase(it);

    it = std::find(m_operators.begin(), m_operators.end(), leave_id);
    if (it != m_operators.end())
        m_operators.erase(it);
    //TODO return RPL_NAMREPLY
    return m_users.size();
}

void Channel::remove_invite(unsigned int user_id)
{
    std::vector<unsigned int>::iterator it = std::find(m_invited.begin(), m_invited.end(), user_id);
    if (it != m_invited.end())
    {
        m_invited.erase(it);
    }
}

void Channel::kick(unsigned int kick_id)
{
    std::vector<unsigned int>::iterator it = std::find(m_users.begin(), m_users.end(), kick_id);
    if (it == m_users.end())
        return;

    m_users.erase(it);
    it = std::find(m_operators.begin(), m_operators.end(), kick_id);
    if (it != m_operators.end())
    {
        m_operators.erase(it);
    }
    //TODO return RPL_NAMREPLY?
    //TODO remove channel if empty
}

void Channel::invite(unsigned int invite_id)
{
    std::vector<unsigned int>::iterator it = std::find(m_invited.begin(), m_invited.end(), invite_id);
    if (it == m_invited.end())
    {
        m_invited.push_back(invite_id);
    }
}

void Channel::set_password(bool mode, std::string const& pass)
{
    m_has_password = mode;
    if (mode == ADD)
    {
        m_password = pass;
    }
    else
    {
        m_password.clear();
    }
}

void Channel::set_op(bool mode, unsigned int affect_id)
{
    std::vector<unsigned int>::iterator it = std::find(m_operators.begin(), m_operators.end(), affect_id);
    if (mode == ADD)
    {
        if (it == m_operators.end())
        {
            m_operators.push_back(affect_id);
        }
    }
    else
    {
        if (it != m_operators.end())
        {
            m_operators.erase(it);
        }
    }
}
void Channel::set_user_limit(bool mode, unsigned int user_limit)
{
    if (mode == ADD)
    {
        m_user_limit = user_limit;
    }
    else
    {
        m_user_limit = 0;
    }
}

void Channel::print_channel()
{
    std::cout << "Users: ";
    for (std::vector<unsigned int>::iterator it = m_users.begin(); it != m_users.end(); it++)
    {
        std::cout << *it << ", ";
    }
    std::cout << "\n";

    std::cout << "Operators: ";
    for (std::vector<unsigned int>::iterator it = m_operators.begin(); it != m_operators.end(); it++)
    {
        std::cout << *it << ", ";
    }
    std::cout << "\n";

    std::cout << "invited: ";
    for (std::vector<unsigned int>::iterator it = m_invited.begin(); it != m_invited.end(); it++)
    {
        std::cout << *it << ", ";
    }
    std::cout << "\n";

    std::cout << "Topic: " << m_topic << "\n";

    std::cout << "Modes:\n";
    std::cout << std::boolalpha;
    std::cout << "\tInvite only: " << m_has_invite_only << "\n";
    std::cout << "\tTopic op only: " << m_has_op_topic << "\n";
    std::cout << "\tHas password: " << m_has_password << " | " << m_password << "\n";
    std::cout << "\tUser limit: " << m_user_limit << "\n\n";
}

bool Channel::is_invited(unsigned int user_id) const
{
    if (m_has_invite_only)
    {
        if (std::find(m_invited.begin(), m_invited.end(), user_id) == m_invited.end())
        {
            return false;
        }
    }
    return true;
}

bool Channel::is_valid_password(std::string const& password) const
{
    if (m_has_password)
    {
        if (m_password != password)
        {
            return false;
        }
    }
    return true;
}

bool Channel::is_operator(unsigned int user_id) const
{
    if (std::find(m_operators.begin(), m_operators.end(), user_id) == m_operators.end())
    {
        return false;
    }
    return true;
}

bool Channel::is_not_full() const
{
    if (m_user_limit != 0)
    {
        if (m_users.size() == m_user_limit)
        {
            return false;
        }
    }
    return true;
}

bool Channel::is_subscribed(unsigned int user_id) const
{
    if (std::find(m_users.begin(), m_users.end(), user_id) == m_users.end())
    {
        return false;
    }
    return true;
}