#pragma once

struct Recipes;
struct BlockPalette;
struct BiomeRegistry;

struct Level {
    Recipes &getRecipes() const;

    BlockPalette *getBlockPalette() const;

    BiomeRegistry *getBiomeRegistry() const;
};
