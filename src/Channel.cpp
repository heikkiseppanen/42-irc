/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:11:27 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/05 17:28:54 by jole             ###   ########.fr       */
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

int Channel::join_channel(unsigned int user_id, std::string const& password)
{
    if (!is_invited(user_id))
    {
        std::cout << "User is not invited\n";
        //TODO return ERR_not_invited
        return -1;
    }

    if (!is_valid_password(password))
    {
        std::cout << "Is not valid password\n";
        //TODO return ERR_bad_password
        return -1;
    }

    if (!is_not_full())
    {
        std::cout << "Channel is full\n";
        //TODO return ERR_channel_full
        return -1;
    }

    if (std::find(m_users.begin(), m_users.end(), user_id) != m_users.end())
    {
        std::cout << "User already on channel\n";
        //TODO ERR_already_on_channel
        return -1;
    }
    //TODO remove from invite list ?_?

    m_users.push_back(user_id);
    //TODO return RPL_user_joined_channel
    return 0;
}

int Channel::change_topic(unsigned int user_id, std::string const& topic)
{
    if (m_has_op_topic && !is_operator(user_id))
    {
        //TODO return ERR_op_topic
        return -1;
    }
    m_topic = topic;
    //TODO return RPL_TOPIC
    return 0;
}

int Channel::leave_channel(unsigned int leave_id)
{
    std::vector<unsigned int>::iterator it = std::find(m_users.begin(), m_users.end(), leave_id);
    if (it == m_users.end())
    {
        //TODO ERR_user_not_found
        return -1;
    }
    m_users.erase(it);

    it = std::find(m_operators.begin(), m_operators.end(), leave_id);
    if (it != m_operators.end())
    {
        m_operators.erase(it);
    }
    //TODO return RPL_user_left
    //TODO remove channel if empty
    return m_users.size();
}

int Channel::kick(unsigned int op_id, unsigned int kick_id)
{
    if (!is_operator(op_id))
    {
        //TODO return ERR_not_op
        return -1;
    }

    std::vector<unsigned int>::iterator it = std::find(m_users.begin(), m_users.end(), kick_id);
    if (it == m_users.end())
    {
        //TODO ERR_user_not_found
        return -1;
    }
    m_users.erase(it);

    it = std::find(m_operators.begin(), m_operators.end(), kick_id);
    if (it != m_operators.end())
    {
        m_operators.erase(it);
    }
    //TODO return RPL_user_left
    //TODO remove channel if empty
    return m_users.size();
}

int Channel::invite(unsigned int user_id, unsigned int invite_id)
{
    if (!is_operator(user_id))
    {
        //TODO return ERR_not_op
        return -1;
    }

    std::vector<unsigned int>::iterator it = std::find(m_invited.begin(), m_invited.end(), invite_id);
    if (it == m_invited.end())
    {
        m_invited.push_back(invite_id);
    }
    else
    {
        //TODO return ERR_already_invited
    }
    //TODO return RPL_invited
    return 0;
}

int Channel::set_invite_only(unsigned int op_id, bool mode)
{
    if (!is_operator(op_id))
    {
        //TODO return ERR_not_op
        return -1;
    }
    m_has_invite_only = mode;
    //TODO return RPL_mode
    return 0;
}

int Channel::set_op_topic(unsigned int op_id, bool mode)
{
    if (!is_operator(op_id))
    {
        //TODO return ERR_not_op
        return -1;
    }
    m_has_op_topic = mode;
    //TODO return RPL_mode
    return 0;
}

int Channel::set_password(unsigned int op_id, bool mode, std::string const& pass)
{
    if (!is_operator(op_id))
    {
        //TODO return ERR_not_op
        return -1;
    }

    m_has_password = mode;
    if (mode == ADD)
    {
        m_password = pass;
    }
    else
    {
        m_password.clear();
    }
    return 0;
}

int Channel::set_op(unsigned int op_id, bool mode, unsigned int affect_id)
{
    if (!is_operator(op_id))
    {
        //TODO return ERR_not_op
        return -1;
    }

    if (!is_subscribed(affect_id))
    {
        //TODO ERR_user_not_found
        return -1;
    }

    std::vector<unsigned int>::iterator it = std::find(m_operators.begin(), m_operators.end(), affect_id);
    if (mode == ADD)
    {
        if (it == m_operators.end())
        {
            m_operators.push_back(affect_id);
        }
        else
        {
            //TODO ERR_user_already_op
            return -1;
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
            //TODO ERR_user_already_not_op
        }
    }
    //TODO RPL_name_list
    return 0;
}

int Channel::set_user_limit(unsigned int op_id, bool mode, unsigned int user_limit)
{
    if (!is_operator(op_id))
    {
        //TODO ERR_not_op
        return -1;
    }

    if (mode == ADD)
    {
        m_user_limit = user_limit;
    }
    else
    {
        m_user_limit = 0;
    }
    //TODO RPL_mode
    return 0;
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

bool Channel::if_channel_topic_empty() const
{
    if (m_topic.empty())
    {
        return true;
    }
    return false;
}