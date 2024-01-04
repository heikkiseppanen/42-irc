/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:52:35 by emajuri           #+#    #+#             */
/*   Updated: 2024/01/04 13:35:16 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "tests.hpp"

void ok()
{
    std::cout << "\033[1;32m" << "[OK] " << "\033[0m";
}

void ko()
{
    std::cout << "\033[1;31m" << "[KO] " << "\033[0m";
}

//ok on true
void print(bool a)
{
    if (a)
        ok();
    else
        ko();
}

int main()
{
    test_client();
    std::cout << "\n\n";
    test_clientDB();
    std::cout << "\n";
}