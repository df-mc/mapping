#pragma once

#include <string>
#include <unordered_map>
#include "HashedString.h"

struct ItemRegistry{
	static void* mItemRegistry;

	struct ItemAlias{
		HashedString alias;
		char padding[120];
	};

	static std::unordered_map<HashedString, ItemAlias> mItemAliasLookupMap;

	std::pair<HashedString, int>& getNameFromAlias(HashedString const & name, int metadata);
};
