# Custom-FX
Allows custom FX files to be loaded into BO1 without modifying base game files.

FX files define how certain things appear in the game, such as the Thundergun ammo lights.

## Installing
1. Head to [Releases](https://github.com/IlEvelynIl/Custom-FX/releases) and grab the latest version's `custom-fx.zip` file.

1. Navigate to your Black Ops (or BGamer) folder, rename `steam_api.dll` to `o_steam_api.dll`, it must be spelled exactly like that.

1. Extract `custom-fx.zip` into the root of your Black Ops folder.

## Installing Custom FX files
Custom fx files can be found in places such as [Reealithy's Patch Station](https://www.youtube.com/watch?v=da5s8PwkGZM).

Once you have found the fx files you want, simply drag them into your `custom_fx/your_fx_files` folder, and now they should appear ingame.

- These must still be in their original folder structure, meaning `fx` would be the top one.
- Most custom fx files will require extra files, you can place the extra files in `custom_fx/linker/raw`, and can obtain them from [the official Black Ops mod tools](https://github.com/Mythical-Github/black_ops_mod_tools_installer/releases/tag/v2.0.0). You can use `debug-fx.bat` to figure out which files you need.
    - Because of this, fx camo packs would be ideal.
