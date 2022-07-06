#pragma once

#include <string>

struct Biome {
	void *vtable;
	std::string name;
	void *filler[10];
	unsigned int biomeId;

	float getDefaultBiomeTemperature() const;
	float getDownfall() const;
};

static_assert(sizeof(std::string) == 32);
