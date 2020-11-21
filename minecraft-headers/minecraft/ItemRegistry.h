#pragma once

#include <string>
#include "HashedString.h"

struct ItemRegistry{
	static void* mItemRegistry;

	std::string& getNameFromAlias(HashedString const & name, int metadata);
};
