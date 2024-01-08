/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_channel.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:36:49 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/08 20:34:28 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"
#include "Channel.hpp"
#include "Reply.hpp"

//constructor
void test1_channel()
{
    Channel c(0);

    if (!c.is_subscribed(0))
        TEST_ERROR("Constructor failed");
    if (!c.is_operator(0))
        TEST_ERROR("Constructor failed");
    ok();
}

//Joining
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

//Kicking
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

//Invite
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

//Topic
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
    c.set_op_topic(0, REMOVE);
    c.change_topic(1, "good");
    if (c.get_topic() != "good")
        TEST_ERROR("Removing op only topic failed");
    ok();
}

void test6_channel()
{
    Channel c(0);

    c.set_password(0, ADD, "pass123");
    c.join_channel(1, "");
    if (c.is_subscribed(1))
        TEST_ERROR("Joining without password");
    c.join_channel(1, "pass123");
    if (!c.is_subscribed(1))
        TEST_ERROR("Failed to join with password");
    c.set_password(0, REMOVE, "");
    c.join_channel(2, "123");
    if (!c.is_subscribed(2))
        TEST_ERROR("Failed to remove password");
    ok();
}

//addop
void test7_channel()
{
    Channel c(0);

    c.set_op(0, ADD, 1);
    if (c.is_operator(1))
        TEST_ERROR("Op without being on channel");
    c.join_channel(1, "");
    c.set_op(0, ADD, 1);
    if (!c.is_operator(1))
        TEST_ERROR("Couldn't add operator");
    c.set_op(0, REMOVE, 1);
    if (c.is_operator(1))
        TEST_ERROR("Couldn't remove operator");
    ok();
}

//user limit
void test8_channel()
{
    Channel c(0);

    c.set_user_limit(0, ADD, 2);
    c.join_channel(1, "");
    c.join_channel(2, "");
    c.join_channel(3, "");
    if (!c.is_subscribed(1))
        TEST_ERROR("Cannot join when space on channel");
    if (c.is_subscribed(2))
        TEST_ERROR("Joined with limit full");
    if (c.is_subscribed(3))
        TEST_ERROR("Joined with limit full");
    c.set_user_limit(0, REMOVE, 0);
    c.join_channel(2, "");
    c.join_channel(3, "");
    if (!c.is_subscribed(2))
        TEST_ERROR("Limit remove failed");
    if (!c.is_subscribed(3))
        TEST_ERROR("Limit remove failed");
    ok();
}

void test9_channel()
{
    Channel c(0);

    c.join_channel(1, "");
    if (!c.is_subscribed(0))
        TEST_ERROR("Not on channel");
    if (!c.is_subscribed(1))
        TEST_ERROR("Not on channel");

    c.leave_channel(0);
    c.leave_channel(1);

    if (c.is_subscribed(0))
        TEST_ERROR("On channel after leave");
    if (c.is_subscribed(1))
        TEST_ERROR("On channel after leave");
    ok();
}

void test10_channel()
{
    Channel c(0);

    if (c.join_channel(1, "") != RPL_NAMREPLY)
        TEST_ERROR("Return fail on success");
    c.set_invite_only(0, ADD);
    if (c.join_channel(2, "") != ERR_INVITEONLYCHAN)
        TEST_ERROR("Return fail on not invited");
    c.set_invite_only(0, REMOVE);
    c.set_password(0, ADD, "pass");
    if (c.join_channel(2, "") != ERR_BADCHANNELKEY)
        TEST_ERROR("Return fail on wrong pass");
    c.set_password(0, REMOVE, "");
    c.set_user_limit(0, ADD, 2);
    if (c.join_channel(2, "") != ERR_CHANNELISFULL)
        TEST_ERROR("Return fail on full channel");
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
    test6_channel();
    test7_channel();
    test8_channel();
    test9_channel();
    test10_channel();
}