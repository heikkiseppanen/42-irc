/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:11:27 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/21 16:57:06 by emajuri          ###   ########.fr       */
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
    m_has_topic_op_only = false;
    m_has_password = false;
}

void Channel::join_channel(unsigned int user_id, std::string const& password)
{
    if (!is_invited(user_id))
        return;

    if (!is_password_good(password))
        return;

    if (m_user_limit != 0)
    {
        if (m_users.size() == m_user_limit)
        {
            //TODO handle full channel
            return;
        }
    }

    if (std::find(m_users.begin(), m_users.end(), user_id) != m_users.end())
    {
        //TODO already on channel
        return;
    }
    //TODO remove from invite list ?_?

    //TODO tell everyone that user joined a channel
    m_users.push_back(user_id);
}

void Channel::change_topic(std::string const& topic)
{
    //TODO tell everyone that topic changed
    m_topic = topic;
}

void Channel::kick(unsigned int user_id)
{
    std::vector<unsigned int>::iterator it = std::find(m_users.begin(), m_users.end(), user_id);
    if (it == m_users.end())
    {
        //TODO user not found
        return;
    }
    //TODO tell everyone user was kicked from the channel
    m_users.erase(it);

    it = std::find(m_operators.begin(), m_operators.end(), user_id);
    if (it != m_operators.end())
    {
        m_operators.erase(it);
    }
    //TODO remove channel if empty
}

void Channel::invite(unsigned int user_id)
{
    m_invited.push_back(user_id);
}

void Channel::set_invite_only(bool mode)
{
    m_has_invite_only = mode;
}

void Channel::set_op_topic(bool mode)
{
    m_has_invite_only = mode;
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

void Channel::set_op(bool mode, unsigned int user_id)
{
    std::vector<unsigned int>::iterator it = std::find(m_operators.begin(), m_operators.end(), user_id);
    if (mode == ADD)
    {
        if (it == m_operators.end())
        {
            if (std::find(m_users.begin(), m_users.end(), user_id) != m_users.end())
            {
                m_operators.push_back(user_id);
            }
            else
            {
                //Todo already op
            }
        }
    }
    else
    {
        if (it != m_operators.end())
        {
            m_operators.erase(it);
        }
        else
        {
            //Todo already not op
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
    std::cout << "\tTopic op only: " << m_has_topic_op_only << "\n";
    std::cout << "\tHas password: " << m_has_password << " | " << m_password << "\n";
    std::cout << "\tUser limit: " << m_user_limit << "\n\n";
}

bool Channel::is_invited(unsigned int user_id) const
{
    if (m_has_invite_only)
    {
        if (std::find(m_invited.begin(), m_invited.end(), user_id) == m_invited.end())
        {
            //TODO handle not invited
            return false;
        }
    }
    return true;
}

bool Channel::is_password_good(std::string const& password) const
{
    if (m_has_password)
    {
        if (m_password != password)
        {
            //TODO incorrect password
            return false;
        }
    }
    return true;
}

bool Channel::is_operator(unsigned int user_id) const
{
    if (std::find(m_operators.begin(), m_operators.end(), user_id) == m_operators.end())
    {
        //TODO not operator
        return false;
    }
    return true;
}
