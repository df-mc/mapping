#pragma once

#include <vector>
#include "HashedString.h"
#include "ItemInstance.h"
#include "RecipeIngredient.h"

struct Recipe {
public:
    static const int SIZE_2X2;

    static const int SIZE_3X3;

protected:
    char filler[152];

private:
    HashedString mTag;

    typedef std::vector<RecipeIngredient, std::allocator<RecipeIngredient>> Ingredients;

    typedef std::vector<ItemInstance, std::allocator<ItemInstance>> ResultList;

public:
    const Ingredients &getIngredients(void) const;

    int getPriority() const;

    int getWidth() const;

    int getHeight() const;

    virtual const ResultList &getResultItem(void) const;

    virtual bool isShapeless(void) const;

    static bool isAnyAuxValue(const ItemDescriptor &);

};
