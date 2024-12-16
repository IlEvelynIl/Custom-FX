# Custom-FX
Allows custom FX files to be loaded into BO1 without modifying base game files.

FX files define how certain things appear in the game, such as the Thundergun ammo lights.

## Installing
1. Head to [Releases](https://github.com/IlEvelynIl/Custom-FX/releases) and grab the latest version's `custom-fx.zip` file.

1. Navigate to your Black Ops (or BGamer) folder, rename `steam_api.dll` to `o_steam_api.dll`.

1. Extract `custom-fx.zip` into the root of your Black Ops folder.

## Creating your own FX Camos
You will need to install [the official Black Ops mod tools](https://github.com/Mythical-Github/black_ops_mod_tools_installer/releases/tag/v2.0.0), as this is where you'd find the FX files and the files they depend on as well. You can use the included `debug-fx.bat` to figure out which files you need, be sure you've run the game with no FX camos installed before using the debug script.

- FX files must be in their original folder structure. the tool will automatically create the `custom_fx/your_fx_files/fx` folder.
    - Do not place these in `custom_fx/linker/raw`, they're automatically copied over by the tool.

- You'll want to put the files that your FX files depend on (from your mod tools' raw folder) in their original folder structure in `custom_fx/linker/raw`, typically they will come from these folders:
- `raw/images`
- `raw/materials`
- `raw/pimp/techniques`
- `raw/pimp/techsets`
- `raw/shadercache_mods`
- `raw/statemaps`
