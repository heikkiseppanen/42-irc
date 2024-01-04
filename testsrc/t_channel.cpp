/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_channel.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:36:49 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/04 21:57:36 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"
#include "Channel.hpp"

void test1_channel()
{
    Channel c(0);

    if (!c.is_subscribed(0))
        TEST_ERROR("Constructor failed");
    ok();
}

void test2_channel()
{
    Channel c;

    for (unsigned int i = 0; i < 10; i++)
    {
        c.join_channel(i, "");
        if (!c.is_subscribed(i))
            TEST_ERROR("Joining failed");
    }
    ok();
}

void test3_channel()
{
    Channel c(0);

    for (unsigned int i = 1; i < 10; i++)
    {
        c.join_channel(i, "");
        if (!c.is_subscribed(i))
            TEST_ERROR("Joining failed");
        c.kick(0, i);
        if (c.is_subscribed(i))
            TEST_ERROR("Kicking failed");
    }
    ok();
}

void test4_channel()
{
    Channel c(0);

    c.set_invite_only(0, ADD);
    for (unsigned int i = 1; i < 6; i++)
    {
        c.invite(0, i);
        if (!c.is_invited(i))
            TEST_ERROR("Invite failed");
        c.join_channel(i, "");
        if (!c.is_subscribed(i))
            TEST_ERROR("Joining failed");
    }
    for (unsigned int i = 6; i < 10; i++)
    {
        if (c.is_invited(i))
            TEST_ERROR("Invited without invite");
        c.join_channel(i, "");
        if (c.is_subscribed(i))
            TEST_ERROR("Joining without invite");
    }
    ok();
}

void test5_channel()
{
    Channel c(0);

    c.change_topic(0, "Hello");
    if (c.get_topic() != "Hello")
        TEST_ERROR("Failed to set/get topic");
    c.change_topic(0, "World");
    if (c.get_topic() != "World")
        TEST_ERROR("Failed to set/get topic");
    c.change_topic(1, "topic");
    if (c.get_topic() != "topic")
        TEST_ERROR("Failed to set/get topic");
    c.set_op_topic(0, ADD);
    c.change_topic(1, "good");
    if (c.get_topic() == "good")
        TEST_ERROR("Set topic without op");
    ok();
}

void test_channel()
{
    std::cout << "Channel:\n";

    test1_channel();
    test2_channel();
    test3_channel();
    test4_channel();
    test5_channel();
}