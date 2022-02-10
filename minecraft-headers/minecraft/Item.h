#pragma once

#include <string>

struct Item {
	char padding[552];

//	virtual ~Item() {}
	const std::string & getFullItemName(void) const;
};
