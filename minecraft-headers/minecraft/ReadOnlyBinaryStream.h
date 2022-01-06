#pragma once

#include <string>
#include <memory>
#include "serialize.h"

struct ReadOnlyBinaryStream {
	void *vt;
	unsigned long offset;
	char filler[8]; //unknown field
	std::string ownedBuffer;
	std::string* buffer;

	template<typename T>
	T getType() {
		return std::move(serialize<T>::read(*this));
	}
};

static_assert(offsetof(ReadOnlyBinaryStream, buffer) == 56);
static_assert(sizeof(ReadOnlyBinaryStream) == 64);
