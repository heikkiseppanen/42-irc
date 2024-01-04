/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:01:04 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/04 14:59:35 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

#define TEST_ERROR(msg) do { ko(); std::cout << msg << " "; return; } while(0);

void test_client();
void test_clientDB();
void ok();
void ko();