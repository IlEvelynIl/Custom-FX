#include "pch.h"

#include "fx-files.hpp"
#include "common.hpp"
#include "linker.hpp"
#include "debug.hpp"

namespace fs = std::filesystem;

void CustomFX_Init(int game)
{
    // Make sure we're on BlackOps.exe and not BlackOpsMP.exe
    if (game != 1)
    {
        MessageBoxA(NULL, "Custom-FX only works on SP/ZM.", "Custom-FX", MB_OK);
        return;
    }

    // remove old custom-fx.log
    if (fs::exists(FX_LOGFILE))
    {
        fs::remove(FX_LOGFILE);
    }

    // remove old custom_fx.ff
    if (fs::exists("zone\\Common\\custom_fx.ff"))
    {
        fs::remove("zone\\Common\\custom_fx.ff");
    }

    // the folder doesnt exist anymore
    if (!fs::exists(CUSTOM_FX_DIR))
    {
        std::thread{ debug::Log, "\"custom_fx\" doesnt exist, aborting." }.detach();
        return;
    }

    // if raw doesnt exist we can't compile the fx files
    if (!fs::exists(LINKER_RAW))
    {
        std::thread{ debug::Log, "\"raw\" doesnt exist, aborting." }.detach();
        return;
    }

    if (!fs::exists(FX_FILES_DIR))
    {
        fs::create_directories(FX_FILES_DIR);
    }

    if (!fs::exists(FX_DIR))
    {
        fs::create_directories(FX_DIR);
    }

    if (!fs::exists(IMAGES_DIR))
    {
        fs::create_directories(IMAGES_DIR);
    }

    // check the amount of fx files so we don't do extra work
    int amount_of_fx = fx::GetAmountOfFxFiles();
    std::string amountMsg = "Total FX files: " + std::to_string(amount_of_fx);
    std::thread{ debug::Log, amountMsg.c_str() }.detach();
    if (amount_of_fx == 0)
    {
        return;
    }

    if (!linker::PrepModCSV())
    {
        std::thread{ debug::Log, "An error occurred with linking custom fx (1)" }.detach();
        return;
    }

    if (!linker::LinkCustomFX())
    {
        std::thread{ debug::Log, "An error occurred with linking custom fx (2)" }.detach();
        return;
    }
    std::thread{ debug::Log, "Linked custom fx" }.detach();

    linker::MoveCustomFXFastFile();
    std::thread{ debug::Log, "Moved custom fx to zone/Common" }.detach();

    linker::custom_fx_hash = fx::hashFxFile();

    if (linker::custom_fx_hash == "") {
        std::thread{ debug::Log, "custom_fx.ff didnt exist" }.detach();
        return;
    }
    std::thread{ debug::Log, "Hashed custom fx" }.detach();
    
    // patch the bo1 memory and make it load custom_fx.ff but only if it's size in bytes matches the previously stored size.
    Detours::X86::DetourFunction((uintptr_t)0x004C8890, (uintptr_t)&common::Com_LoadLevelFastFiles);
}

// entry point for the dll
extern "C" __declspec(dllexport) int Patchbgt5external(int game) {
    CustomFX_Init(game);
    return 1;
}