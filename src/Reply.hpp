/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:21:48 by emajuri           #+#    #+#             */
/*   Updated: 2023/11/22 12:39:38 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>

enum ReplyEnum
{
    RPL_WELCOME
};

class Reply
{
    public:

        Reply();

    private:

        std::map<ReplyEnum, std::string> Replies;
};
