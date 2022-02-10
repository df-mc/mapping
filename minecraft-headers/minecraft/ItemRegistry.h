#pragma once

#include <string>
#include <unordered_map>
#include "HashedString.h"
#include "Memory.h"

struct ItemRegistry{
	static void* mItemRegistry;

	struct ItemAlias{
		HashedString alias;
		char padding[120];
	};

	static std::unordered_map<HashedString, ItemAlias> mItemAliasLookupMap;

	static std::pair<HashedString, int> getNameFromAlias(HashedString const & name, int metadata);

	static WeakPtr<Item> getItem(const Block &);
};
