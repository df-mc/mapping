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
| `r12_block_states.json` | JSON table of 1.12 block states as seen [here](https://github.com/pmmp/BedrockData/blob/bd75689119b20b13671d1ab73a91c177451b3082/r12_block_states.json). Used to generate [`r12_to_current_block_map.bin`](https://github.com/pmmp/BedrockData/blob/master/r12_to_current_block_map.bin). |
| `item_id_map.json` | JSON table of string ID to their legacy counterparts from pre-1.16.100, as seen [here](https://github.com/pmmp/BedrockData/blob/master/item_id_map.json). Used to generate [`r16_to_current_item_map.json`](https://github.com/pmmp/BedrockData/blob/master/r16_to_current_item_map.json). |
| `old_palettes/*.nbt` | Old blockstate tables in the same format as seen [here](https://github.com/pmmp/BedrockData/blob/master/canonical_block_states.nbt). Used to generate blockstate mapping tables of old blockstates -> current version. |
