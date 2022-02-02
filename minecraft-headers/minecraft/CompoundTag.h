#pragma once

struct CompoundTag {
	char filler[56];

	CompoundTag(CompoundTag &&);
};
