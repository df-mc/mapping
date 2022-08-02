#pragma once

#include "BlockLegacy.h"
#include "CompoundTag.h"
#include "HashedString.h"

typedef CompoundTag BlockSerializationId;

struct Block {
    float getDestroySpeed() const;

    float getExplosionResistance(class Actor *) const;

    virtual ~Block() {}

    unsigned short data;
    BlockLegacy *blockLegacy;

    char filler2[80];
    BlockSerializationId tag;
};
