#pragma once

#include <string>

#include "Block.h"

struct BlockPalette {
	BlockLegacy *getBlockLegacy(std::string const &) const;

	const Block *getBlock(BlockSerializationId const &) const;
	const Block *getBlock(const unsigned int & blockRuntimeId) const;

	size_t getNumBlockRuntimeIds() const;
};
