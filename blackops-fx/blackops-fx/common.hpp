namespace common {
	void Com_LoadLevelFastFiles(const char* mapName);
	void Com_GetLevelSharedFastFiles(const char* mapName);
	void Com_LoadCommonFastFile();
	bool Com_IsMenuLevel(const char* name);
	bool Com_IsSpecopLevel(const char* name);
	bool DB_IsZoneLoaded(const char* name);
	void DB_RemoveLevelDependency(const char* dependency);
}