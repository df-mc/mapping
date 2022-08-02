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

    char padding[120];
    char unknown;
    char opacity;
    char brightness;
    int flameEncouragement;
    int flammability;
    float hardness;
    float blastResistance;
    char padding2[16];
    float friction;

    std::string getFullName() const {
        return fullName.str;
    }

    Block *getStateFromLegacyData(unsigned short) const;

    const NewBlockID getBlockID() const;

    float getDestroySpeed() const;

    virtual ~BlockLegacy();
};
