# mapping
This is a BDS (Bedrock Dedicated Server) mod which allows generating a mapping of legacy blockIDs and their metadata values to modern Minecraft Bedrock blockstates.
It also allows generating a palette for newer versions of the game which don't send it over the wire.

## Usage
Set up a BDS using [modloader-helper](https://github.com/Frago9876543210/modloader-helper).
Once you've done this, clone this repository into the `code` subdirectory, run `helper.sh build mapping`
Then, run the server using the `run.sh` script. The output files will be produced on server start.
