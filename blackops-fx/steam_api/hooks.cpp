#include "pch.h"

LPVOID _SteamAPI_RegisterCallResult,
_SteamAPI_Shutdown,
_SteamAPI_UnregisterCallback,
_SteamAPI_UnregisterCallResult,
_SteamAPI_RunCallbacks,
_SteamAPI_RestartAppIfNecessary,
_SteamAPI_Init,
_SteamApps,
_SteamGameServer,
_SteamGameServer_RunCallbacks,
_SteamMasterServerUpdater,
_SteamGameServer_Init,
_SteamGameServer_Shutdown,
_SteamNetworking,
_SteamUserStats,
_SteamAPI_RegisterCallback,
_SteamUtils,
_SteamUser,
_SteamFriends;

extern "C" {
    __declspec(dllexport, naked) void SteamAPI_RegisterCallResult(int, int)
    {
        _asm jmp _SteamAPI_RegisterCallResult
    }

    __declspec(dllexport, naked) void SteamAPI_Shutdown()
    {
        _asm jmp _SteamAPI_Shutdown
    }

    __declspec(dllexport, naked) void SteamAPI_UnregisterCallback()
    {
        _asm jmp _SteamAPI_UnregisterCallback
    }

    __declspec(dllexport, naked) void SteamAPI_UnregisterCallResult(int, int)
    {
        _asm jmp _SteamAPI_UnregisterCallResult
    }

    __declspec(dllexport, naked) int SteamAPI_RunCallbacks()
    {
        _asm jmp _SteamAPI_RunCallbacks
    }

    __declspec(dllexport, naked) int SteamAPI_RestartAppIfNecessary(int)
    {
        _asm jmp _SteamAPI_RestartAppIfNecessary
    }

    __declspec(dllexport, naked) __int8 SteamAPI_Init(void*)
    {
        static HMODULE customFx = LoadLibraryA("blackops-fx.dll");
        if (!customFx) {
            MessageBoxA(NULL, "Could not find blackops-fx.dll", "Custom-FX", MB_OK | MB_ICONERROR);
        }

        _asm jmp _SteamAPI_Init
    }

    __declspec(dllexport, naked) int SteamApps()
    {
        _asm jmp _SteamApps
    }

    __declspec(dllexport, naked) int SteamGameServer()
    {
        _asm jmp _SteamGameServer
    }

    __declspec(dllexport, naked) void SteamGameServer_RunCallbacks()
    {
        _asm jmp _SteamGameServer_RunCallbacks
    }

    __declspec(dllexport, naked) int SteamMasterServerUpdater()
    {
        _asm jmp _SteamMasterServerUpdater
    }

    __declspec(dllexport, naked) int SteamGameServer_Init(int, int, int, int, int, int, const char*, const char*)
    {
        _asm jmp _SteamGameServer_Init
    }

    __declspec(dllexport, naked) int SteamGameServer_Shutdown()
    {
        _asm jmp _SteamGameServer_Shutdown
    }

    __declspec(dllexport, naked) int SteamNetworking()
    {
        _asm jmp _SteamNetworking
    }

    __declspec(dllexport, naked) int SteamUserStats()
    {
        _asm jmp _SteamUserStats
    }

    __declspec(dllexport, naked) void SteamAPI_RegisterCallback(int, int)
    {
        _asm jmp _SteamAPI_RegisterCallback
    }

    __declspec(dllexport, naked) int SteamUtils()
    {
        _asm jmp _SteamUtils
    }

    __declspec(dllexport, naked) int SteamUser()
    {
        _asm jmp _SteamUser
    }

    __declspec(dllexport, naked) int SteamFriends()
    {
        _asm jmp _SteamFriends
    }
}

namespace hooks {
	BOOL init()
	{
        HMODULE o_steam_api = LoadLibrary(L"o_steam_api.dll");

        if (o_steam_api)
        {
            _SteamAPI_RegisterCallResult = GetProcAddress(o_steam_api, "SteamAPI_RegisterCallResult");
            _SteamAPI_Shutdown = GetProcAddress(o_steam_api, "SteamAPI_Shutdown");
            _SteamAPI_UnregisterCallback = GetProcAddress(o_steam_api, "SteamAPI_UnregisterCallback");
            _SteamAPI_UnregisterCallResult = GetProcAddress(o_steam_api, "SteamAPI_UnregisterCallResult");
            _SteamAPI_RunCallbacks = GetProcAddress(o_steam_api, "SteamAPI_RunCallbacks");
            _SteamAPI_RestartAppIfNecessary = GetProcAddress(o_steam_api, "SteamAPI_RestartAppIfNecessary");
            _SteamAPI_Init = GetProcAddress(o_steam_api, "SteamAPI_Init");
            _SteamApps = GetProcAddress(o_steam_api, "SteamApps");
            _SteamGameServer = GetProcAddress(o_steam_api, "SteamGameServer");
            _SteamGameServer_RunCallbacks = GetProcAddress(o_steam_api, "SteamGameServer_RunCallbacks");
            _SteamMasterServerUpdater = GetProcAddress(o_steam_api, "SteamMasterServerUpdater");
            _SteamGameServer_Init = GetProcAddress(o_steam_api, "SteamGameServer_Init");
            _SteamGameServer_Shutdown = GetProcAddress(o_steam_api, "SteamGameServer_Shutdown");
            _SteamNetworking = GetProcAddress(o_steam_api, "SteamNetworking");
            _SteamUserStats = GetProcAddress(o_steam_api, "SteamUserStats");
            _SteamAPI_RegisterCallback = GetProcAddress(o_steam_api, "SteamAPI_RegisterCallback");
            _SteamUtils = GetProcAddress(o_steam_api, "SteamUtils");
            _SteamUser = GetProcAddress(o_steam_api, "SteamUser");
            _SteamFriends = GetProcAddress(o_steam_api, "SteamFriends");

            return TRUE;
        }

        return FALSE;
	}
}