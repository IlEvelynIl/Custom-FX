#include "pch.h"

#include "common.hpp"
#include "fx-files.hpp"
#include "linker.hpp"
#include "debug.hpp"

namespace common {
	std::vector<LevelDependency> g_LevelDependencies;

	void Com_LoadLevelFastFiles(const char* mapName)
	{
		int zoneCount = 0;
		XZoneInfo zoneInfo[10];

		DB_ResetZoneSize(0);
		UI_SetLoadingScreenMaterial(mapName);
		Com_GetLevelSharedFastFiles(mapName);

		if (I_stristr(mapName, "zombietron"))
		{
			Dvar_SetBool(zombiemode, true);
			Dvar_SetBool(zombietron, true);
		}

		if (Com_IsMenuLevel(mapName))
		{
			zoneInfo[zoneCount].name = "patch_ui";
			zoneInfo[zoneCount].allocFlags = DB_ZONE_PATCH_UI;
			zoneInfo[zoneCount++].freeFlags = 0;
		}
		else
		{
			// If we aren't on a menu level, load common assets
			Com_LoadCommonFastFile();
		}

		// Enable the use of level_dependencies.csv
		for (auto& dependency : g_LevelDependencies)
		{
			if (DB_IsZoneLoaded(dependency.required))
				continue;

			Com_Printf(1, "Adding level dependency: %s\n", dependency.required);

			// The allocFlags were originally 0x800 - but would cause a free error
			// (these new flags appear to load / unload correctly)
			zoneInfo[zoneCount].name = dependency.required;
			zoneInfo[zoneCount].allocFlags = 0x4000000;
			zoneInfo[zoneCount++].freeFlags = 0;
		}

		char specOpsZoneName[64];
		if (Com_IsSpecopLevel(mapName))
		{
			const char* basename = nullptr;
			for (basename = &mapName[strlen("so_")]; *basename && *basename != '_'; ++basename)
				/* Do nothing */;

			if (!*basename)
				Com_PrintError(1, "Bad specop level name\n");

			sprintf_s(specOpsZoneName, "%s", basename + 1);
			zoneInfo[zoneCount].name = specOpsZoneName;
			zoneInfo[zoneCount].allocFlags = 0x800;
			zoneInfo[zoneCount++].freeFlags = 0;
		}

		int allocFlags = 0;

		if (!Com_IsMenuLevel(mapName))
			allocFlags = Com_IsSpecopLevel(mapName) ? 0x4000 : 0x800;
		else
			allocFlags = 0x2000000;

		zoneInfo[zoneCount].allocFlags = allocFlags;
		zoneInfo[zoneCount].name = mapName;
		zoneInfo[zoneCount++].freeFlags = 0;

		// load custom_fx.ff if its not been modified
		std::string customFxHash = fx::hashFxFile("zone\\Common\\custom_fx.ff");
		if (customFxHash == linker::custom_fx_hash)
		{
			Com_LoadCustomFXFastFile();
		}

		R_BeginRemoteScreenUpdate();
		DB_LoadXAssets(zoneInfo, zoneCount, 0);
		R_EndRemoteScreenUpdate(nullptr);
	}

	void Com_LoadCustomFXFastFile()
	{
		XZoneInfo zoneInfo[2];
		int zoneCount = 0;

		DB_ResetZoneSize(0);

		zoneInfo[zoneCount].name = "custom_fx";
		zoneInfo[zoneCount].allocFlags = 0x4000000;
		zoneInfo[zoneCount++].freeFlags = 0;

		DB_LoadXAssets(zoneInfo, zoneCount, 0);
	}

	void Com_LoadCommonFastFile()
	{
		XZoneInfo zoneInfo[4];
		int zoneCount = 0;

		DB_ResetZoneSize(0);

		if (useFastFile->current.enabled)
			DB_ReleaseXAssets();

		// Zombietron has everything isolated to a single FF
		if (zombietron->current.enabled)
		{
			zoneInfo[zoneCount].name = nullptr;
			zoneInfo[zoneCount].allocFlags = 0;
			zoneInfo[zoneCount++].freeFlags = DB_ZONE_COMMON;

			DB_LoadXAssets(zoneInfo, zoneCount, 0);
			return;
		}

		//
		// blackopsmode requires common_zombie for technique data, and common for scripts
		//
		if (zombiemode->current.enabled || blackopsmode->current.enabled)
		{
			if (DB_IsZoneLoaded("common_zombie"))
				return;

			// common_zombie must be unloaded after common/en_common
			int zoneAllocFlags = (blackopsmode->current.enabled) ? 0x400 : DB_ZONE_COMMON;

			zoneInfo[zoneCount].name = "common_zombie";
			zoneInfo[zoneCount].allocFlags = zoneAllocFlags;
			zoneInfo[zoneCount++].freeFlags = 0;
		}

		if (!zombiemode->current.enabled)
		{
			if (DB_IsZoneLoaded("common"))
				return;

			zoneInfo[zoneCount].name = "common";
			zoneInfo[zoneCount].allocFlags = DB_ZONE_COMMON;
			zoneInfo[zoneCount++].freeFlags = 0;
		}

		if (zoneCount)
		{
			// Don't load map required zones if we already did here
			for (int i = 0; i < zoneCount; i++)
				DB_RemoveLevelDependency(zoneInfo[i].name);

			DB_LoadXAssets(zoneInfo, zoneCount, 0);
		}
	}

	void Com_GetLevelSharedFastFiles(const char* mapName)
	{
		// Reload the list for every map, every time (mod.ff may override level_dependencies.csv)
		static std::vector<LevelDependency> allDependencies;
		{
			char loadBuffer[16384];
			const char* buffer = Com_LoadInfoString("level_dependencies.csv", "level_dependency_info", "", loadBuffer);

			Com_BeginParseSession("level_dependencies.csv");
			Com_SetCSV(true);

			while (true)
			{
				const char* token = Com_Parse(&buffer);

				if (!*token)
					break;

				if (*token != '/')
				{
					LevelDependency m;
					memset(&m, 0, sizeof(m));

					strcpy_s(m.base, token);
					token = Com_Parse(&buffer);
					strcpy_s(m.required, token);

					allDependencies.push_back(m);
				}
				else
				{
					// Skip the rest of the line if the token was a comment
					Com_ParseRestOfLine(&buffer);
				}
			}

			Com_EndParseSession();
		}

		// Now return each entry for this map name
		std::vector<LevelDependency> returnedMaps;

		for (auto& dependency : allDependencies)
		{
			if (!_stricmp(dependency.base, mapName))
				returnedMaps.push_back(dependency);
		}

		// Will be empty if there's nothing to load
		g_LevelDependencies = std::move(returnedMaps);
	}

	bool Com_IsMenuLevel(const char* name)
	{
		if (!name)
			name = sv_mapname->current.string;

		return !I_strnicmp(name, "menu_", 5) || !I_strcmp(name, "frontend");
	}

	bool Com_IsSpecopLevel(const char* name)
	{
		if (!name)
			name = sv_mapname->current.string;

		return !I_strnicmp(name, "so_", 3);
	}

	bool DB_IsZoneLoaded(const char* name)
	{
		for (int i = 1; i < 33; ++i)
		{
			if (g_zoneNames[i].name[0] && !_stricmp(g_zoneNames[i].name, name))
				return g_zoneNames[i].loaded;
		}

		return false;
	}

	void DB_RemoveLevelDependency(const char* dependency)
	{
		for (auto itr = g_LevelDependencies.begin(); itr != g_LevelDependencies.end();)
		{
			if (!_stricmp(itr->required, dependency))
				itr = g_LevelDependencies.erase(itr);
			else
				itr++;
		}
	}
}