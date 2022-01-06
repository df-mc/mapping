#include <minecraft/BinaryStream.h>
#include <minecraft/Block.h>
#include <minecraft/BlockLegacy.h>
#include <minecraft/BlockPalette.h>
#include <minecraft/CompoundTag.h>
#include <minecraft/ItemRegistry.h>
#include <minecraft/Level.h>
#include <minecraft/LevelSoundEventMap.h>
#include <minecraft/Minecraft.h>
#include <minecraft/ServerInstance.h>
#include <minecraft/Biome.h>
#include <minecraft/BiomeRegistry.h>

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <json.hpp>

void generate_legacy_block_map(ServerInstance *serverInstance) {
	auto palette = serverInstance->getMinecraft()->getLevel()->getBlockPalette();

	std::ifstream input("required_block_states.json");

	auto stream = new BinaryStream();

	auto json = nlohmann::json::object();
	input >> json;

	for (auto &object : json["minecraft"].items()) {
		const auto &name = "minecraft:" + object.key();
		auto blockLegacy = palette->getBlockLegacy(name);
		for (auto &it : object.value()) {
			auto state = it.get<unsigned short>();

			if (name == "minecraft:cocoa" && state >= 12) {
				continue;
			}

			auto block = blockLegacy->getStateFromLegacyData(state);

			stream->writeUnsignedVarInt(name.length());
			stream->write(name.c_str(), name.length());
			stream->writeUnsignedShort(state);
			stream->writeType(block->tag);
		}
	}

	std::ofstream output("mapping_files/r12_to_current_block_map.bin");
	output << *stream->buffer;
	output.close();
	delete stream;
	std::cout << "Generated R12 block state mapping table" << std::endl;
}

void generate_palette(ServerInstance *serverInstance) {
	auto palette = serverInstance->getMinecraft()->getLevel()->getBlockPalette();
	unsigned int numStates = palette->getNumBlockRuntimeIds();
	std::cout << "Number of blockstates: " << numStates << std::endl;

	auto paletteStream = new BinaryStream();
	for (unsigned int i = 0; i < numStates; i++) {
		auto state = palette->getBlock(i);
		paletteStream->writeType(state->tag);
	}

	std::ofstream paletteOutput("mapping_files/canonical_block_states.nbt");
	paletteOutput << *paletteStream->buffer;
	paletteOutput.close();
	delete paletteStream;
	std::cout << "Generated block palette" << std::endl;
}

void generate_item_mapping() {
	auto registry = static_cast<ItemRegistry*>(ItemRegistry::mItemRegistry);

	auto list = nlohmann::json::object();
	std::ifstream listFile("item_id_map.json");

	listFile >> list;

	auto simple = nlohmann::json::object();
	auto complex = nlohmann::json::object();

	for(auto it = list.begin(); it != list.end(); it++){
		auto key = it.key();
		auto firstMapped = registry->getNameFromAlias(key, 0);
		std::cout << firstMapped.first.str << ":" << std::to_string(firstMapped.second) << std::endl;

		auto metaMap = nlohmann::json::object();
		for(auto meta = 1; meta < 300; meta++){
			auto mapped = registry->getNameFromAlias(key, meta);
			if(key != mapped.first.str && mapped.first.str != firstMapped.first.str){
				metaMap[std::to_string(meta)] = mapped.first.str;
				std::cout << mapped.first.str << ":" << std::to_string(firstMapped.second) << std::endl;
				assert(mapped.second == 0);
			}
		}
		if(metaMap.size() > 0){
			if(key != firstMapped.first.str){
				metaMap["0"] = firstMapped.first.str;
			}
			complex[key] = metaMap;
		}else if(key != firstMapped.first.str){
			simple[key] = firstMapped.first.str;
		}
	}

	auto generated = nlohmann::json::object();
	generated["simple"] = simple;
	generated["complex"] = complex;
	std::ofstream result("mapping_files/r16_to_current_item_map.json");
	result << std::setw(4) << generated << std::endl;
	result.close();
	std::cout << "Generated R16U1 item mapping table" << std::endl;
}

void generate_biome_mapping(ServerInstance *server) {
	auto registry = server->getMinecraft()->getLevel()->getBiomeRegistry();

	auto map = nlohmann::json::object();

	registry->forEachBiome([&map] (Biome &biome) {
		auto id = biome.biomeId;
		map[biome.name] = id;
	});

	std::ofstream result("mapping_files/biome_id_map.json");
	result << std::setw(4) << map << std::endl;
	result.close();
	std::cout << "Generated biome ID mapping table" << std::endl;
}

static void generate_level_sound_mapping() {
	auto map = nlohmann::json::object();

	bool found_113 = false;
	for(int i = 0; i < 1000; i++) {
		auto name = LevelSoundEventMap::getName((LevelSoundEvent) i);
		if (name != "undefined") {
			map[name] = i;
			if (i == 113) {
				found_113 = true;
				std::cout << "WARNING: STOP_RECORD(113) has changed, and it won't appear in the output!" << std::endl;
			}
		}
	}
	if (!found_113) {
		map["stop_record"] = 113;
	}

	std::ofstream result("mapping_files/level_sound_id_map.json");
	result << std::setw(4) << map << std::endl;
	result.close();
	std::cout << "Generated LevelSoundEvent mapping table" << std::endl;
}

extern "C" void modloader_on_server_start(ServerInstance *serverInstance) {
	std::filesystem::create_directory("mapping_files");
	generate_item_mapping();
	generate_legacy_block_map(serverInstance);
	generate_palette(serverInstance);
	generate_biome_mapping(serverInstance);
	generate_level_sound_mapping();
}
