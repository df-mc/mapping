#pragma once

#include "Tag.h"

class ListTag : public Tag {
public:
    char filler[32];

    ListTag();

    void add(std::unique_ptr<Tag>);

    std::unique_ptr<ListTag> copyList() const;
};
