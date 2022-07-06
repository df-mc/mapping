#pragma once

#include <functional>
#include "ItemInstance.h"

struct CreativeItemRegistry {
    static void forEachCreativeItemInstance(std::function<bool(ItemInstance &)>);
};
