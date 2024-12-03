#pragma once

typedef void(__cdecl* DB_ResetZoneSize_t)(int trackLoadProgress);
static DB_ResetZoneSize_t DB_ResetZoneSize = (DB_ResetZoneSize_t)0x00621530;

typedef void(__cdecl* UI_SetLoadingScreenMaterial_t)(const char* name);
static UI_SetLoadingScreenMaterial_t UI_SetLoadingScreenMaterial = (UI_SetLoadingScreenMaterial_t)0x005C6F70;

typedef const char* (__cdecl* Com_LoadInfoString_t)(const char* fileName, const char* fileDesc, const char* ident, char* loadBuffer);
static Com_LoadInfoString_t Com_LoadInfoString = (Com_LoadInfoString_t)0x005A5F10;

typedef void(__cdecl* Com_SetCSV_t)(int csv);
static Com_SetCSV_t Com_SetCSV = (Com_SetCSV_t)0x00403200;

typedef const char* (__cdecl* Com_Parse_t)(const char** data_p);
static Com_Parse_t Com_Parse = (Com_Parse_t)0x00566B30;

typedef const char* (__cdecl* Com_ParseRestOfLine_t)(const char** data_p);
static Com_ParseRestOfLine_t Com_ParseRestOfLine = (Com_ParseRestOfLine_t)0x005D4F10;

typedef void(__cdecl* Com_BeginParseSession_t)(const char* filename);
static Com_BeginParseSession_t Com_BeginParseSession = (Com_BeginParseSession_t)0x00509BE0;

typedef void* ParseThreadInfo;

typedef ParseThreadInfo* (__cdecl* Com_EndParseSession_t)();
static Com_EndParseSession_t Com_EndParseSession = (Com_EndParseSession_t)0x005C11C0;

typedef int(__cdecl* I_strcmp_t)(const char* s0, const char* s1);
static I_strcmp_t I_strcmp = (I_strcmp_t)0x0063E630;

typedef int(__cdecl* I_strncmp_t)(const char* s0, const char* s1, int n);
static I_strncmp_t I_strncmp = (I_strncmp_t)0x005ED6F0;

typedef int(__cdecl* I_strnicmp_t)(const char* s0, const char* s1, int n);
static I_strnicmp_t I_strnicmp = (I_strnicmp_t)0x0052F790;

typedef const char* (__cdecl* I_stristr_t)(const char* s0, const char* substr);
static I_stristr_t I_stristr = (I_stristr_t)0x0062F110;

typedef void(__cdecl* I_strncpyz_t)(char* dest, const char* src, int destsize);
static I_strncpyz_t I_strncpyz = (I_strncpyz_t)0x005D4D60;

typedef void __cdecl Dvar_SetBool_t(dvar_s* dvar, bool value);
static Dvar_SetBool_t* Dvar_SetBool = (Dvar_SetBool_t*)0x004B0C10;

typedef void(__cdecl* Com_Printf_t)(int channel, const char* fmt, ...);
static Com_Printf_t Com_Printf = (Com_Printf_t)0x0043BF30;
static Com_Printf_t Com_PrintWarning = (Com_Printf_t)0x0051CE50;
static Com_Printf_t Com_PrintError = (Com_Printf_t)0x005DFC40;
static Com_Printf_t Com_Error = (Com_Printf_t)0x00651D90;

typedef void(__cdecl* R_BeginRemoteScreenUpdate_t)();
static R_BeginRemoteScreenUpdate_t R_BeginRemoteScreenUpdate = (R_BeginRemoteScreenUpdate_t)0x006D7E60;

typedef void(__cdecl* R_EndRemoteScreenUpdate_t)(void(__cdecl* pumpfunc)());
static R_EndRemoteScreenUpdate_t R_EndRemoteScreenUpdate = (R_EndRemoteScreenUpdate_t)0x006D7EC0;

typedef void(__cdecl* DB_LoadXAssets_t)(XZoneInfo* zoneInfo, unsigned int zoneCount, int sync);
static DB_LoadXAssets_t DB_LoadXAssets = (DB_LoadXAssets_t)0x00631B10;

typedef int(__cdecl* DB_ReleaseXAssets_t)();
static DB_ReleaseXAssets_t DB_ReleaseXAssets = (DB_ReleaseXAssets_t)0x0062C260;