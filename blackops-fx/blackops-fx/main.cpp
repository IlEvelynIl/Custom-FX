#include "pch.h"

#include "fx-files.hpp"
#include "common.hpp"
#include "linker.hpp"
#include "debug.hpp"
#include "ceg.hpp"

namespace fs = std::filesystem;

BOOL CustomFX_Init()
{
    ceg::Patch_CEG();

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

    if (!fs::exists(CUSTOM_FX_DIR))
    {
        fs::create_directories(CUSTOM_FX_DIR);
    }

    if (!fs::exists(LINKER_RAW))
    {
        fs::create_directories(LINKER_RAW);
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
        return TRUE;
    }

    if (!linker::PrepModCSV())
    {
        std::thread{ debug::Log, "An error occurred with linking custom fx (1)" }.detach();
        return FALSE;
    }

    if (!linker::LinkCustomFX())
    {
        std::thread{ debug::Log, "An error occurred with linking custom fx (2)" }.detach();
        return FALSE;
    }
    std::thread{ debug::Log, "Linked custom fx" }.detach();

    linker::custom_fx_hash = fx::hashFxFile("custom_fx\\linker\\zone\\english\\mod.ff");
    if (linker::custom_fx_hash == "") {
        std::thread{ debug::Log, "custom_fx.ff didnt exist" }.detach();
        return FALSE;
    }

    linker::MoveCustomFXFastFile();
    std::thread{ debug::Log, "Moved custom fx to zone/Common" }.detach();
    
    // patch the bo1 memory and make it load custom_fx.ff but only if it's size in bytes matches the previously stored size.
    Detours::X86::DetourFunction((uintptr_t)0x004C8890, (uintptr_t)&common::Com_LoadLevelFastFiles);

    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE module, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        return CustomFX_Init();
    }
    return TRUE;
}