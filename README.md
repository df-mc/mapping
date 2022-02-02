# mapping
This is a BDS (Bedrock Dedicated Server) mod which allows generating a mapping of legacy blockIDs and their metadata values to modern Minecraft Bedrock blockstates.
It also allows generating a palette for newer versions of the game which don't send it over the wire.

## Usage
Set up a BDS using [modloader-helper](https://github.com/Frago9876543210/modloader-helper).
Once you've done this, clone this repository into the `code` subdirectory, run `helper.sh build mapping`
Then, run the server using the `run.sh` script. The output files will be produced on server start.

## Input files
Input files should be placed in `input_files`. The following files are used by this mod:

| File name | Description |
|:----------|:------------|
| `r12_block_states.json` | JSON table of 1.12 block states as seen [here](https://github.com/pmmp/BedrockData/blob/bd75689119b20b13671d1ab73a91c177451b3082/r12_block_states.json). Used to generate `r12_to_current_block_map.bin`. |
| `item_id_map.json` | JSON table of string ID to their legacy counterparts from pre-1.16.100, as seen [here](https://github.com/pmmp/BedrockData/blob/master/item_id_map.json). Used to generate `r16_to_current_item_map.json`. |
| `old_palettes/*.nbt` | Old blockstate tables in the same format as seen [here](https://github.com/pmmp/BedrockData/blob/master/canonical_block_states.nbt). Used to generate blockstate mapping tables of old blockstates -> current version. |

## Output files
Output files are placed in the `mapping_files` directory.

| File name | Description |
|:----------|:------------|
| `biome_id_map` | Map of biome string ID -> legacy numeric ID. |
| `canonical_block_states.nbt` | Ordered list of blockstates required by the chosen version, in varint NBT format. Read TAG_Compounds until the end of file. |
| `hardness_table.json` | Map of block string ID -> hardness value. |
| `level_sound_id_map.json` | Map of string LevelSoundEvent name -> numeric ID. **NOTE: This is not complete since the game itself doesn't map all of them to strings.** |
| `old_palette_mappings/*_to_current_block_map.bin` | Map of old version's blockstates -> current version.<br>The files are an array of TAG_Compound, where the 0th, 2nd, 4th etc. indexes are the old NBT, and the 1st, 3rd, 5th etc. indexes are the new NBT. Only the versions provides in `input_files/old_palettes` are generated.<br>NOTE: These files contain mappings even for states that haven't changed.<br>You may wish to post-process them to remove unchanged states and reduce their size. |
| `particle_id_map.json` | Map of string particle name -> LevelEvent ID (without the 0x4000 flag). |
| `r12_to_current_block_map.bin` | Map of legacy 1.12 block ID+metadata -> blockstate NBT for the current version. |
| `r16_to_current_item_map.json` | Map of 1.16.0 item ID+meta -> current version IDs (where changed). |
