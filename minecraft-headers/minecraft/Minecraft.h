#pragma once

#include <memory>
#include "MinecraftCommands.h"

struct Level;

struct Minecraft {
	Level *getLevel() const;

	MinecraftCommands& getCommands();
};
