#pragma once

#include <variant>
#include <cstdint>
#include "Tag.h"
#include "ByteTag.h"
#include "IntTag.h"
#include "StringTag.h"

class CompoundTagVariant {
    char filler[0x30];

public:
    Tag::Type getTagType() const {
        return *(Tag::Type*)(((uintptr_t)this) + 40);
    }
    Tag* asTag() {
        return (Tag*)this;
    }
    ByteTag * asByteTag() const {
        return (ByteTag*)this;
    }
    IntTag* asIntTag() const {
        return (IntTag*)this;
    }
    StringTag* asStringTag() const {
        return (StringTag*)this;
    }

};
