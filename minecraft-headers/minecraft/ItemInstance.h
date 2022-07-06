#pragma once

#include "ItemStackBase.h"

struct ItemInstance : public ItemStackBase {
    class ItemInstance clone() const;
};
