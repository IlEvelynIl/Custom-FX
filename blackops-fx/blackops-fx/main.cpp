#include "pch.h"

#include "debug.hpp"
#include "fx-files.hpp"

void CustomFX_Init(int game)
{
    // Make sure we're on BlackOps.exe and not BlackOpsMP.exe
    if (game != 1)
    {
#if DEBUG
        std::thread{ debug::Msg, "Custom-FX only works on SP/ZM." }.detach();
#endif
        return;
    }

    // if the custom fx folder doesnt exist already, create it
    if (!std::filesystem::exists(CUSTOM_FX_DIR))
    {
        std::filesystem::create_directory(CUSTOM_FX_DIR);
    }

    int amount_of_fx = fx::GetAmountOfFxFiles();

    // log the amount of fx files to the logfile
    std::string fx_count_msg = "Total fx files: " + std::to_string(amount_of_fx);
    std::thread{ debug::Log, fx_count_msg.c_str() }.detach();

    // premature checks so we don't do extra work
    if (amount_of_fx == 0)
    {
        return;
    }

    if (fx::DoNonFxFilesExist())
    {
        return;
    }

    // gather up the fx files and compile them into custom_fx.ff, store the size of custom_fx.ff in bytes

    // patch the bo1 memory and make it load custom_fx.ff but only if it's size in bytes matches the previously stored size.
}

extern "C" __declspec(dllexport) int Patchbgt5external(int game) {
    CustomFX_Init(game);
    return 1;
}