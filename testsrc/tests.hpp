/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:01:04 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/03 19:22:22 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define TEST_ERROR(msg) do { print(false); std::cout << msg << " "; return; } while(0);

void test_clientDB();
void print(bool a);