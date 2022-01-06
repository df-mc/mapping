#pragma once

#include <string>

struct Biome {
	void *vtable;
	std::string name;
	void *filler[10];
	unsigned int biomeId;
};
static_assert(sizeof(std::string) == 32);
