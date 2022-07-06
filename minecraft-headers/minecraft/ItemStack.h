#pragma once

#include "ItemStackBase.h"

class ItemStack : public ItemStackBase {

    char padding[24];

public:
    ItemStack(class ItemStack const &);

    ItemStack(class Item const &, int, int);

    ItemStack();
};
