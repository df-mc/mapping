#pragma once

#include "ItemDescriptor.h"

struct ItemDescriptorCount : public ItemDescriptor {
private:
    uint16_t mStackSize;
    char padding[6];

public:
    ItemDescriptorCount(void);

    ItemDescriptorCount(const ItemDescriptor &, uint16_t);

    ItemDescriptorCount(const Block &, uint16_t);

    ItemDescriptorCount(const BlockLegacy &, uint16_t);

    short getStackSize(void) const;

    void setStackSize(short);

};
