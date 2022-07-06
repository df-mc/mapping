#pragma once

#include "ItemDescriptorCount.h"

struct RecipeIngredient : public ItemDescriptorCount {
public:
    RecipeIngredient(void);

    RecipeIngredient(const ItemDescriptor &, uint16_t);

    RecipeIngredient(const Block &, uint16_t);

    RecipeIngredient(const BlockLegacy &, uint16_t);

    RecipeIngredient(const Item &, int, uint16_t);
};
