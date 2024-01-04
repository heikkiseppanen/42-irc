/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:01:04 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/04 13:31:53 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

#define TEST_ERROR(msg) do { print(false); std::cout << msg << " "; return; } while(0);

void test_client();
void test_clientDB();
void print(bool a);