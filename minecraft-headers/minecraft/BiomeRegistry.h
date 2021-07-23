#pragma once

#include "Biome.h"

struct BiomeRegistry {
	Biome* lookupById(int) const;
};
