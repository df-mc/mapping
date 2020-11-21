#pragma once

#include "BlockLegacy.h"
#include "CompoundTag.h"

struct Block {
	const BlockLegacy* getLegacyBlock() const;
	
	char filler[24];
	CompoundTag tag;
};
