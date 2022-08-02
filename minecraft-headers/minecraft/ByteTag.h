#pragma once

#include <cstdint>
#include "Tag.h"

class ByteTag : public Tag {
public:
    uint8_t data;
};
