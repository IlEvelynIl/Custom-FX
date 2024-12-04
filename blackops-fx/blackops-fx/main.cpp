#include "pch.h"

#include "debug.hpp"
#include "fx-files.hpp"
#include "common.hpp"
#include "linker.hpp"

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

    // if they've deleted the fx folder, just return, since theres no files there
    if (!std::filesystem::exists(CUSTOM_FX_DIR))
    {
        std::filesystem::create_directories(CUSTOM_FX_DIR);
        std::thread{ debug::Log, "Created CUSTOM_FX_DIR" }.detach();
    }

    // same for linker
    if (!std::filesystem::exists(LINKER_DIR))
    {
        std::filesystem::create_directories(LINKER_DIR);
        std::thread{ debug::Log, "Created LINKER_DIR" }.detach();
    }

    // now if the custom fx files dir doesnt exist, create it
    if (!std::filesystem::exists(FX_FILES_DIR))
    {
        std::filesystem::create_directories(FX_FILES_DIR);
        std::thread{ debug::Log, "Created FX_FILES_DIR" }.detach();
    }

    // log the amount of fx files to the logfile
    int amount_of_fx = fx::GetAmountOfFxFiles();
    std::string fx_count_msg = "Total fx files: " + std::to_string(amount_of_fx);
    std::thread{ debug::Log, fx_count_msg.c_str() }.detach();

    // premature checks so we don't do extra work
    if (amount_of_fx == 0)
    {
        return;
    }

    if (!linker::PrepModCSV())
    {
        std::thread{ debug::Log, "An error occurred with linking the custom fx (1)" }.detach();
        return;
    }

    if (!linker::LinkCustomFX())
    {
        std::thread{ debug::Log, "An error occurred with linking the custom fx (2)" }.detach();
        return;
    }

    linker::MoveCustomFXFastFile();
    std::thread{ debug::Log, "Moved custom_fx.ff to zone/Common" }.detach();

    linker::custom_fx_hash = fx::hashFxFile();
    std::thread{ debug::Log, "Hashed custom_fx.ff" }.detach();
    
    // patch the bo1 memory and make it load custom_fx.ff but only if it's size in bytes matches the previously stored size.
    Detours::X86::DetourFunction((uintptr_t)0x004C8890, (uintptr_t)&common::Com_LoadLevelFastFiles);
}

extern "C" __declspec(dllexport) int Patchbgt5external(int game) {
    CustomFX_Init(game);
    return 1;
}