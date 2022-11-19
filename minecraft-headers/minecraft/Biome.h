#pragma once

#include "HashedString.h"

struct Biome {
    HashedString name;
    char filler[80];
    unsigned int biomeId;

    virtual ~Biome(void);

    float getDefaultBiomeTemperature() const;

    float getDownfall() const;
};

static_assert(sizeof(std::string) == 32);
