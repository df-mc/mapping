#pragma once

#include "BlockLegacy.h"
#include "CompoundTag.h"
#include "HashedString.h"

typedef CompoundTag BlockSerializationId;

struct Block {
    float getDestroySpeed() const;

    int getFlameOdds(void) const;

    int getBurnOdds(void) const;

    float getTranslucency(void) const;

    float getExplosionResistance(class Actor *) const;

    virtual ~Block() {}

    unsigned short data;
    BlockLegacy *blockLegacy;

    char filler2[128];
    BlockSerializationId tag;
};
