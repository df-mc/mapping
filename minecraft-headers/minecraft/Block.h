#pragma once

#include "BlockLegacy.h"
#include "CompoundTag.h"

struct Block {
	const BlockLegacy* getLegacyBlock() const;
	
	char filler[96];
	CompoundTag tag;
};
