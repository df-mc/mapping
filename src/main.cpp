/*
 * Heavily based around https://github.com/pmmp/mapping by dktapps and Frago9876543210.
 * Improved upon to generate more relevant data for Dragonfly.
 */

#include <minecraft/BinaryStream.h>
#include <minecraft/BlockPalette.h>
#include <minecraft/CompoundTag.h>
#include <minecraft/Item.h>
#include <minecraft/ItemRegistry.h>
#include <minecraft/Level.h>
#include <minecraft/Minecraft.h>
#include <minecraft/ServerInstance.h>
#include <minecraft/Biome.h>
#include <minecraft/BiomeRegistry.h>
#include <minecraft/CreativeItemRegistry.h>

#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <json.hpp>
#include "minecraft/Recipes.h"
#include "minecraft/ListTag.h"
#include "minecraft/I18n.h"
#include "minecraft/ItemStack.h"
#include "minecraft/BlockTypeRegistry.h"

/**
 * Generates the vanilla block states and saves them in network little endian NBT.
 * @param server
 */
void generate_block_states(ServerInstance *server) {
    auto palette = server->getMinecraft()->getLevel()->getBlockPalette();
    auto stream = new BinaryStream();
    for (unsigned int i = 0; i < palette->getNumBlockRuntimeIds(); i++) {
        auto state = palette->getBlock(i);
        stream->writeType(state->tag);
    }

    std::ofstream output("mapping_files/block_states.nbt");
    output << stream->buffer;
    output.close();

    delete stream;

    std::cout << "Generated block states!" << std::endl;
}

/**
 * Generates the vanilla item runtime IDs and saves them in network little endian NBT.
 */
static void generate_item_runtime_ids() {
    CompoundTag out;
    for (auto item: ItemRegistry::mItemRegistry) {
        out.putInt(item->getFullItemName(), item->getId());
    }

    auto stream = new BinaryStream();
    stream->writeType(out);

    std::ofstream output("mapping_files/item_runtime_ids.nbt");
    output << stream->buffer;
    output.close();

    delete stream;
    std::cout << "Generated item runtime IDs!" << std::endl;
}

/**
 * Generates the vanilla creative items and saves them in network little endian NBT.
 */
void generate_creative_items() {
    auto stream = new BinaryStream();
    CreativeItemRegistry::forEachCreativeItemInstance([&stream](ItemInstance &item) -> bool {
        CompoundTag tag;
        tag.putString("name", item.getItem()->getFullItemName());
        tag.putShort("meta", item.getAuxValue());
        if (item.hasUserData()) {
            tag.putCompound("nbt", item.getUserData()->clone());
        }
        if (item.isBlock()) {
            tag.putCompound("block", item.getBlock()->tag.clone());
        }
        stream->writeType(tag);
        return true;
    });

    std::ofstream output("mapping_files/creative_items.nbt");
    output << stream->buffer;
    output.close();

    delete stream;

    std::cout << "Generated creative items!" << std::endl;
}

/**
 * Generates name+meta to display name mappings for each language supported by Minecraft.
 */
void generate_item_names() {
    for (const auto &localization: I18n::mLanguages) {
        std::string code = localization->getFullLanguageCode();
        I18n::chooseLanguage(code);

        auto entries = nlohmann::json::array();
        for (auto item: ItemRegistry::mItemRegistry) {
            auto id = item->getFullItemName();
            std::string lastName;
            for (int aux = 0; aux < 255; aux++) {
                if (!item->isValidAuxValue(aux)) {
                    break;
                }

                // Aux validation checks because Mojang can't do them properly!
                if (id == "minecraft:arrow" && aux == 44) {
                    break;
                }
                if (id.find("potion") != std::string::npos && aux == 43) {
                    break;
                }

                auto stack = new ItemStack(*item, 1, aux);
                auto name = item->buildDescriptionName(*stack);
                if (name.length() == 0 || name.find('.') != std::string::npos) {
                    continue;
                }
                if (id.find("potion") == std::string::npos && id != "minecraft:arrow" && lastName == name) {
                    continue;
                }

                auto object = nlohmann::json::object();
                object["id"] = id;
                object["name"] = name;
                if (aux > 0) {
                    if (id == "minecraft:anvil") {
                        if (aux > 8) {
                            continue;
                        }
                        aux /= 4;
                    }
                    object["meta"] = aux;
                }
                entries.push_back(object);

                lastName = name;
            }
        }

        std::replace(code.begin(), code.end(), '_', '-');

        std::ofstream output("mapping_files/lang/" + code + ".json");
        output << entries << std::endl;
        output.close();

        std::cout << "Generated item names for " << code << "!" << std::endl;
    }
}

/**
 * Generates block attributes for each block type, containing information for friction values, flame and burn odds,
 * destruction speeds, and more. This isn't used in Dragonfly, but is helpful for implementing blocks.
 * @param server
 */
void generate_block_attributes(ServerInstance *server) {
    auto stream = new BinaryStream();
    auto palette = server->getMinecraft()->getLevel()->getBlockPalette();
    for (unsigned int i = 0; i < palette->getNumBlockRuntimeIds(); i++) {
        auto state = palette->getBlock(i);
        stream->writeType(state->tag);
        stream->writeFloat(state->getDestroySpeed());
        stream->writeSignedInt(state->getFlameOdds());
        stream->writeSignedInt(state->getBurnOdds());
        stream->writeFloat(state->getTranslucency());
        stream->writeFloat(state->getExplosionResistance(nullptr));
    }

    std::ofstream output("mapping_files/extra/block_attributes.nbt");
    output << stream->buffer;
    output.close();

    delete stream;

    std::cout << "Generated block attributes!" << std::endl;
}

/**
 * Generates biome mappings from string ID to biome information, including biome temperature, rainfall, and legacy IDs.
 * This isn't used in Dragonfly, but is helpful for implementing newer biomes.
 * @param server
 */
void generate_biomes(ServerInstance *server) {
    auto map = nlohmann::json::object();
    server->getMinecraft()->getLevel()->getBiomeRegistry()->forEachBiome([&map](Biome &biome) {
        auto object = nlohmann::json::object();
        object["id"] = biome.biomeId;
        object["temperature"] = biome.getDefaultBiomeTemperature();
        object["rainfall"] = biome.getDownfall();

        map[biome.name] = object;
    });

    std::ofstream result("mapping_files/extra/biomes.json");
    result << std::setw(4) << map << std::endl;
    result.close();

    std::cout << "Generated biomes!" << std::endl;
}

void generate_item_tags(ServerInstance *server) {
    auto map = nlohmann::json::object();
    for (const auto &pair: ItemRegistry::mTagToItemsMap) {
        auto items = nlohmann::json::array();
        for (const auto &item: pair.second) {
            items.push_back(item->getFullItemName());
        }
        map[pair.first.str] = items;
    }

    std::ofstream result("mapping_files/extra/item_tags.json");
    result << std::setw(4) << map << std::endl;
    result.close();

    std::cout << "Generated item tags!" << std::endl;
}

/**
 * Generates command parameter IDs, used to describe a parameter's type in commands. This is used for Gophertunnel
 * command parameter updates.
 * @param server
 */
void generate_command_parameter_ids(ServerInstance *server) {
    auto map = nlohmann::json::object();
    auto registry = server->getMinecraft()->getCommands().getRegistry();

    for (int id = 0; id < 1000; id++) { //TODO: we can probably use CommandRegistry::forEachSymbol() for this instead
        int symbol = id | 0x100000;
        if (registry.isValid(symbol)) {
            auto name = registry.describe(symbol);
            if (name != "undefined") {
                map[name] = id;
            }
        }
    }

    std::ofstream result("mapping_files/command_parameter_ids.json");
    result << std::setw(4) << map << std::endl;
    result.close();

    std::cout << "Generated command parameter IDs!" << std::endl;
}

/**
 * Generates relevant data from BDS to mapping files for use in Dragonfly.
 * @param serverInstance
 */
extern "C" void modloader_on_server_start(ServerInstance *server) {
    std::filesystem::create_directory("mapping_files");

    std::cout << "Building data..." << std::endl;
//    generate_block_states(server);
//    generate_item_runtime_ids();
//    generate_creative_items();
//    generate_item_names();
    // TODO: Fix Recipe header (breaks on virtual functions?)
    generate_block_attributes(server);
    generate_item_tags(server);
//    generate_biomes(server);
//    generate_command_parameter_ids(server);
}
