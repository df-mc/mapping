#pragma once

#include "Block.h"

struct ItemDescriptor {
    char padding[72];

    std::string const &getFullName() const;

    short getAuxValue() const;
};
