#pragma once

#include <iostream>
#include <exception>
#include <sys/errno.h>

#define IRC_ASSERT_THROW(COND, MSG) do { if (COND) { throw std::runtime_error(MSG); }} while(0);
