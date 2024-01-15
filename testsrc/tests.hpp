/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:01:04 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/15 17:09:20 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

#define TEST_ERROR(msg) do { ko(); std::cout << msg << " "; return; } while(0);

void test_client();
void test_clientDB();
void test_channelDB();
void test_channel();
void test_eventhandler();
void ok();
void ko();