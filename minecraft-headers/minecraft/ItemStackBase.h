#pragma once

#include "Item.h"
#include "Block.h"
#include "CompoundTag.h"

class ItemStackBase {
public:
    char mCount;
    char padding[135];

    ItemStackBase(class ItemStackBase const &);

    ItemStackBase();

    Item const *getItem() const;

    CompoundTag const *getUserData() const;

    bool hasUserData() const;

    bool isBlock() const;

    Block const *getBlock() const;

    short getAuxValue() const;

};
