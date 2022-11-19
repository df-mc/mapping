#pragma once

#include "ItemStackBase.h"

class ItemStack : public ItemStackBase {

    char padding[24];

public:
    ItemStack(class ItemStack const &);

    ItemStack(const Item &, int, int, const CompoundTag *);

    ItemStack();
};
