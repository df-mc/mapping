#pragma once

struct BlockPalette;
struct BiomeRegistry;

struct Level {
	BlockPalette *getBlockPalette() const;
	BiomeRegistry *getBiomeRegistry() const;
};
