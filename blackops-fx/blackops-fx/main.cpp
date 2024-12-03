#include "pch.h"

#define DEBUG 1
#define CUSTOM_FX_DIR "custom_fx"

void CustomFX_Init(int game)
{
#if DEBUG
    std::thread{ MessageBoxA, NULL, "Welcome to Custom-FX!", "blackops-fx", MB_OK }.detach();
#endif

    // Make sure we're on BlackOps.exe and not BlackOpsMP.exe
    if (game != 1)
    {
        return;
    }

    if (!std::filesystem::exists(CUSTOM_FX_DIR))
    {
        std::filesystem::create_directory(CUSTOM_FX_DIR);
    }

    // gather up the fx files, ignore all scripts, put it into a zone project

    // compile the fx files into custom_fx.ff, store the size of it in bytes

    // patch the bo1 memory and make it load custom_fx.ff but only if it's size in bytes matches the previously stored size.
}

extern "C" __declspec(dllexport) int Patchbgt5external(int game) {
    CustomFX_Init(game);
    return 1;
}