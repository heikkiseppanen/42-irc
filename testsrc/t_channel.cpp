/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_channel.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:36:49 by emajuri           #+#    #+#             */
/*   Updated: 2024/02/07 13:30:20 by emajuri          ###   ########.fr       */
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
        c.join_channel(i);
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
        c.join_channel(i);
        if (!c.is_subscribed(i))
            TEST_ERROR("Joining failed");
        c.remove_user_from_channel(i);
        if (c.is_subscribed(i))
            TEST_ERROR("Kicking failed");
    }
    ok();
}

//Invite
void test4_channel()
{
    Channel c(0);

    c.set_invite_only(ADD);
    for (unsigned int i = 1; i < 6; i++)
    {
        c.invite(0, i);
        if (!c.is_invited(i))
            TEST_ERROR("Invite failed");
        if (c.is_invited(i))
            c.join_channel(i);
        if (!c.is_subscribed(i))
            TEST_ERROR("Joining failed");
    }
    for (unsigned int i = 6; i < 10; i++)
    {
        if (c.is_invited(i))
            TEST_ERROR("Invited without invite");
        if (c.is_invited(i))
            c.join_channel(i);
        if (c.is_subscribed(i))
            TEST_ERROR("Joining without invite");
    }
    ok();
}

//Topic
void test5_channel()
{
    Channel c(0);

    c.topic_change("Hello");
    if (c.get_topic() != "Hello")
        TEST_ERROR("Failed to set/get topic");
    c.topic_change("World");
    if (c.get_topic() != "World")
        TEST_ERROR("Failed to set/get topic");
    c.topic_change("topic");
    if (c.get_topic() != "topic")
        TEST_ERROR("Failed to set/get topic");
    c.set_op_topic(ADD);
    if (c.is_operator(1))
        c.topic_change("good");
    if (c.get_topic() == "good")
        TEST_ERROR("Set topic without op");
    c.set_op_topic(REMOVE);
    c.topic_change("good");
    if (c.get_topic() != "good")
        TEST_ERROR("Removing op only topic failed");
    ok();
}

void test6_channel()
{
    Channel c(0);

    c.set_password(ADD, "pass123");
    if (c.is_valid_password(""))
        c.join_channel(1);
    if (c.is_subscribed(1))
        TEST_ERROR("Joining without password");
    if (c.is_valid_password("pass123"))
        c.join_channel(1);
    if (!c.is_subscribed(1))
        TEST_ERROR("Failed to join with password");
    c.set_password(REMOVE, "");
    if (c.is_valid_password("123"))
        c.join_channel(2);
    if (!c.is_subscribed(2))
        TEST_ERROR("Failed to remove password");
    ok();
}

//addop
void test7_channel()
{
    Channel c(0);

    if (c.is_subscribed(1))
        c.set_op(ADD, 1);
    if (c.is_operator(1))
        TEST_ERROR("Op without being on channel");
    c.join_channel(1);
    if (c.is_subscribed(1))
        c.set_op(ADD, 1);
    if (!c.is_operator(1))
        TEST_ERROR("Couldn't add operator");
    c.set_op(REMOVE, 1);
    if (c.is_operator(1))
        TEST_ERROR("Couldn't remove operator");
    ok();
}

//user limit
void test8_channel()
{
    Channel c(0);

    c.set_user_limit(ADD, 2);
    c.join_channel(1);
    if (c.is_not_full())
        c.join_channel(2);
    if (c.is_not_full())
        c.join_channel(3);
    if (!c.is_subscribed(1))
        TEST_ERROR("Cannot join when space on channel");
    if (c.is_subscribed(2))
        TEST_ERROR("Joined with limit full");
    if (c.is_subscribed(3))
        TEST_ERROR("Joined with limit full");
    c.set_user_limit(REMOVE, 0);
    if (c.is_not_full())
        c.join_channel(2);
    if (c.is_not_full())
        c.join_channel(3);
    if (!c.is_subscribed(2))
        TEST_ERROR("Limit remove failed");
    if (!c.is_subscribed(3))
        TEST_ERROR("Limit remove failed");
    ok();
}

void test9_channel()
{
    Channel c(0);

    c.join_channel(1);
    if (!c.is_subscribed(0))
        TEST_ERROR("Not on channel");
    if (!c.is_subscribed(1))
        TEST_ERROR("Not on channel");

    c.remove_user_from_channel(0);
    c.remove_user_from_channel(1);

    if (c.is_subscribed(0))
        TEST_ERROR("On channel after leave");
    if (c.is_subscribed(1))
        TEST_ERROR("On channel after leave");
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
}