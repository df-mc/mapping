#pragma once

#include "HashedString.h"
#include "mce.h"

struct Block;

struct NewBlockID {
    NewBlockID(const NewBlockID &);

    unsigned short value;
};

struct BlockLegacy {

    std::string descriptionId;
    HashedString baseName;
    std::string namespaceName;
    HashedString fullName;

    std::string getFullName() const {
        return fullName.str;
    }

    Block *getStateFromLegacyData(unsigned short) const;

    const NewBlockID getBlockID() const;

    virtual ~BlockLegacy();
};
