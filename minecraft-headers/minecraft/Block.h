#pragma once

#include "BlockLegacy.h"
#include "CompoundTag.h"
#include "HashedString.h"

typedef CompoundTag BlockSerializationId;

struct Block {
    int getBurnOdds() const;

    float getDestroySpeed() const;

    int getFlameOdds() const;

    float getFriction() const;

    virtual ~Block() {}

    unsigned short data;
    BlockLegacy *blockLegacy;

    char filler2[80];
    BlockSerializationId tag;
};
