# Technical Details
The technical details on exactly how this tool works. This can be used by the community to determine of this tool should be allowed or not.

1. This tool uses what is known as a DLL proxy, we proxy all of the `steam_api.dll` functions to their original ones with `o_steam_api.dll`, except when the initialize function is called, the custom fx tool will start.

2. On launch, the tool will check for a custom fastfile called `custom_fx.ff`, if it exists then the tool will remove it. The tool gathers up the files from the `custom_fx/your_fx_files` folder, and uses the mod tools linker to compile them a new `custom_fx.ff` file, the hash of this file is saved for future use as soon as it is compiled, then the tool moves the file to `zone/Common`.
    - This will ONLY accept `.efx` files so that we don't have people doing fishy shit with scripts, this does NOT change the game mechanics in any way, just changes how some things appear in game, such as Thundergun lights. It will be up for people to decide which FX files are legit to change or not.

3. The game is then told to load `custom_fx.ff` last after the base game files. However, it will not load the file if the hash does not match the previously saved amount, this would prevent people from just dropping in another patch.

### Voilà! You've entered the new era of custom camos on BO1.
