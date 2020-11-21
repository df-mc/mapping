#pragma once

#include <string>

struct HashedString{
	unsigned long long hash;
	std::string str;

	HashedString(std::string const & input);
	HashedString(char const * input);
};
