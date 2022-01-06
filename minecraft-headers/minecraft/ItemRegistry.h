#pragma once

#include <string>
#include "HashedString.h"

struct ItemRegistry{
	static void* mItemRegistry;

	std::pair<HashedString, int>& getNameFromAlias(HashedString const & name, int metadata);
};
