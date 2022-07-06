#pragma once

#include <string>

struct Item {
    char padding[552];

    bool isValidAuxValue(int) const;

    std::string buildDescriptionName(class ItemStackBase const &) const;

    const std::string &getFullItemName(void) const;

    short getId() const;
};
