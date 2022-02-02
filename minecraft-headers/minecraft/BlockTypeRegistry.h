#pragma once
#include <functional>
#include "BlockLegacy.h"

struct BlockTypeRegistry{
	static void forEachBlock(std::function<bool (const BlockLegacy &)>);
};
