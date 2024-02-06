/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_channelDB.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:24:01 by emajuri           #+#    #+#             */
/*   Updated: 2024/02/06 13:07:54 by emajuri          ###   ########.fr       */
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

void test_channelDB()
{
    std::cout << "ChannelDB:\n";

    test1_channeldb();
}