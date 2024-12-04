# Technical Stuff
The nerdy details on how exactly this tool works.

1. By default, BGamer tries to load a file called `bgcustom.dll`, this is what makes it easy to install.

2. On launch, the tool gathers up the files from the `custom_fx/your_fx_files` folder, and uses the mod tools linker to compile them into a fastfile called `custom_fx.ff` which is placed inside of `zone/Common`, the hash of this file is saved for future use.
    - This will ONLY accept fx files, so that we don't have people doing fishy shit with scripts, this does NOT change the game mechanics in any way, just changes how some things appear in game, such as Thundergun lights. This will be up for people to decide which FX files are legit to change or not.
    - On launch, this file is checked for and deleted if it exists.

3. The game is then told to load `custom_fx.ff` last after the base game files. However, it will not load the file if the hash does not match the previously saved amount, this would prevent people from just dropping in another patch.

### Voilà! You've entered the new era of custom camos on BO1.