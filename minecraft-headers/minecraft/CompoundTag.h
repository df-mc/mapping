#pragma once

#include <string>
#include <memory>
#include "Tag.h"

class CompoundTag : public Tag {
public:
    char filler[48];

    CompoundTag(void);

    CompoundTag(const CompoundTag &);

    CompoundTag(CompoundTag &&);

    Tag *put(std::string, std::unique_ptr<Tag>);

    CompoundTag *putCompound(std::string name, std::unique_ptr<CompoundTag> tag);

    std::string &putString(std::string, std::string);

    short &putShort(std::string, short);

    int &putInt(std::string name, int value);

    std::unique_ptr<CompoundTag> clone(void) const;

    virtual ~CompoundTag(void);
};
