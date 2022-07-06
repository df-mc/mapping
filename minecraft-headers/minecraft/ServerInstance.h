#pragma once

#include <memory>

struct Minecraft;

struct ServerInstance {
    char filler[120];
    std::unique_ptr<Minecraft> minecraft;

    Minecraft *getMinecraft() {
        return minecraft.get();
    }
};
