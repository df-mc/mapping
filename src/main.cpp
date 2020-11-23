#include <minecraft/BinaryStream.h>
#include <minecraft/Block.h>
#include <minecraft/BlockLegacy.h>
#include <minecraft/BlockPalette.h>
#include <minecraft/CompoundTag.h>
#include <minecraft/ItemRegistry.h>
#include <minecraft/Level.h>
#include <minecraft/Minecraft.h>
#include <minecraft/ServerInstance.h>

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

	std::ofstream output("r12_to_current_block_map.bin");
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

	std::ofstream paletteOutput("canonical_block_states.nbt");
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

		auto metaMap = nlohmann::json::object();
		for(auto meta = 1; meta < 300; meta++){
			auto mapped = registry->getNameFromAlias(key, meta);
			if(key != mapped && mapped != firstMapped){
				metaMap[std::to_string(meta)] = mapped;
			}
		}
		if(metaMap.size() > 0){
			if(key != firstMapped){
				metaMap["0"] = firstMapped;
			}
			complex[key] = metaMap;
		}else if(key != firstMapped){
			simple[key] = firstMapped;
		}
	}

	auto generated = nlohmann::json::object();
	generated["simple"] = simple;
	generated["complex"] = complex;
	std::ofstream result("r16_to_current_item_map.json");
	result << std::setw(4) << generated << std::endl;
	result.close();
	std::cout << "Generated R16U1 item mapping table" << std::endl;
}

extern "C" void modloader_on_server_start(ServerInstance *serverInstance) {
	generate_item_mapping();
	generate_legacy_block_map(serverInstance);
	generate_palette(serverInstance);
}
