#pragma once

#include <string>

#include "Memory.h"
#include "BlockLegacy.h"

namespace VanillaBlockConversion {
	int getBlockTypeLegacyIdFromName(std::string const&);
	Block* tryGetLegacyState(unsigned int, unsigned int);
};
