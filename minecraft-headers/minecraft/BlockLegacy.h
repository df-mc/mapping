#pragma once

struct Block;

struct NewBlockID {
	NewBlockID(const NewBlockID&);

	unsigned short value;
};

struct BlockLegacy {
	Block *getStateFromLegacyData(unsigned short) const;
	const NewBlockID getBlockID() const;
	const std::string& getFullName() const;
};
