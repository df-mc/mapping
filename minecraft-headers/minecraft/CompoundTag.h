#pragma once

#include <string>
#include <memory>
#include <map>
#include "Tag.h"
#include "CompoundTagVariant.h"

class CompoundTag : public Tag {
public:
    std::map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, CompoundTagVariant, std::less<void>, std::allocator<std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const, CompoundTagVariant> > > mTags;

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
