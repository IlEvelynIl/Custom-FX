#include "pch.h"

#include "hooks.hpp"

BOOL WINAPI DllMain(HINSTANCE module, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        if (!hooks::init())
        {
            MessageBoxA(NULL, "Failed to initialize (make sure you renamed your original steam_api.dll to o_steam_api.dll)", "Custom-FX", MB_OK | MB_ICONERROR);
            return FALSE;
        }
    }
    return TRUE;
}