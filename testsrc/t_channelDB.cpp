/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_channelDB.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:24:01 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/04 19:34:20 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"
#include "ChannelDatabase.hpp"

//adding and removing
void test1_channeldb()
{
    ChannelDatabase db;

    db.add_channel("channel1", 0);
    db.add_channel("channel2", 0);
    db.add_channel("channel3", 0);

    if (!db.is_channel("channel1"))
        TEST_ERROR("Error adding channel1");
    if (!db.is_channel("channel2"))
        TEST_ERROR("Error adding channel2");
    if (!db.is_channel("channel3"))
        TEST_ERROR("Error adding channel3");

    db.remove_channel("channel1");
    db.remove_channel("channel2");
    db.remove_channel("channel3");

    if (db.is_channel("channel1"))
        TEST_ERROR("Error removing channel1");
    if (db.is_channel("channel2"))
        TEST_ERROR("Error removing channel2");
    if (db.is_channel("channel3"))
        TEST_ERROR("Error removing channel3");

    ok();
}

//test remove_user
void test2_channeldb()
{
    ChannelDatabase db;

    db.add_channel("channel1", 0);
    db.add_channel("channel2", 0);
    db.add_channel("channel3", 0);
    db.add_channel("channel4", 1);
    db.add_channel("channel5", 0);

    if (!db.is_channel("channel1"))
        TEST_ERROR("Error adding channel1");
    if (!db.is_channel("channel2"))
        TEST_ERROR("Error adding channel2");
    if (!db.is_channel("channel3"))
        TEST_ERROR("Error adding channel3");
    if (!db.is_channel("channel4"))
        TEST_ERROR("Error adding channel4");
    if (!db.is_channel("channel5"))
        TEST_ERROR("Error adding channel5");

    db.get_channel("channel4").join_channel(0, "");

    if (!db.is_user_on_channel("channel1", 0))
        TEST_ERROR("User not on channel1");
    if (!db.is_user_on_channel("channel2", 0))
        TEST_ERROR("User not on channel2");
    if (!db.is_user_on_channel("channel3", 0))
        TEST_ERROR("User not on channel3");
    if (!db.is_user_on_channel("channel4", 0))
        TEST_ERROR("User not on channel4");
    if (!db.is_user_on_channel("channel5", 0))
        TEST_ERROR("User not on channel5");

    db.remove_user(0);

    if (db.is_channel("channel1"))
        TEST_ERROR("User is on channel1");
    if (db.is_channel("channel2"))
        TEST_ERROR("User is on channel2");
    if (db.is_channel("channel3"))
        TEST_ERROR("User is on channel3");
    if (db.is_user_on_channel("channel4", 0))
        TEST_ERROR("User is on channel4");
    if (db.is_channel("channel5"))
        TEST_ERROR("User is on channel5");

    ok();
}

void test_channelDB()
{
    std::cout << "ChannelDB:\n";

    test1_channeldb();
    test2_channeldb();
}