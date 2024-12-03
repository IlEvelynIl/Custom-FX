#pragma once

#define VANILLA_DVAR(NAME, ADDRESS) static dvar_s*& NAME = *(dvar_s **)ADDRESS;
#define VANILLA_VALUE(NAME, TYPE, ADDRESS) static TYPE& NAME = *(TYPE*)ADDRESS;

#define STATIC_ASSERT_SIZE(struct, size)				static_assert(sizeof(struct) == size, "Size check")
#define STATIC_ASSERT_OFFSET(struct, member, offset)	static_assert(offsetof(struct, member) == offset, "Offset check")

struct XZoneInfoInternal
{
	char name[64];
	int flags;
};

struct XZoneInfo
{
	const char* name;
	int allocFlags;
	int freeFlags;
};

struct LevelDependency
{
	char base[64];		// Base map
	char required[64];	// FF required for loading the map
};

enum FF_DIR : DWORD
{
	FFD_DEFAULT,
	FFD_MOD_DIR,
	FFD_USER_MAP
};

struct XZoneName
{
	char name[64];
	int flags;
	int fileSize;
	FF_DIR dir;
	bool loaded;
};
STATIC_ASSERT_SIZE(XZoneName, 0x50);

enum XZoneFlags
{
	DB_ZONE_NULL = 0,
	DB_ZONE_CODE = 1,		// 0x1,
	DB_ZONE_CODE_LOC = 1 << 1,	// 0x2,

	DB_ZONE_DEV = 1 << 2,	// 0x4, (IN SP: DB_ZONE_DEV == DB_ZONE_DEV_LOC )
	// DB_ZONE_DEV_LOC			= 1 << 2,	// 0x4,

	DB_ZONE_PATCH = 1 << 3,	// 0x8,
	DB_ZONE_PATCH_LOC = 1 << 4,	// 0x10,
	DB_ZONE_MOD = 1 << 5,	// 0x20,
	DB_ZONE_MOD_LOC = 1 << 6,	// 0x40,
	DB_ZONE_COMMON = 1 << 8,	// 0x100,
	DB_ZONE_COMMON_LOC = 1 << 8,	// 0x100,

#if 0
	// These values need to be validated
	DB_ZONE_FFOTD = 1 << 9,	// 0x200,
	DB_ZONE_FFOTD_LOC = 1 << 10,	// 0x400,
	DB_ZONE_LEVELCOMMON = 1 << 11,	// 0x800,
	DB_ZONE_LEVELCOMMON_LOC = 1 << 12,	// 0x1000,
	DB_ZONE_LEVEL = 1 << 13,	// 0x2000,
	DB_ZONE_LEVEL_LOC = 1 << 14,	// 0x4000,
	DB_ZONE_LEVELOVERLAY = 1 << 15,	// 0x8000,
	DB_ZONE_LEVELOVERLAY_LOC = 1 << 16,	// 0x10000,
#endif

	DB_ZONE_GUMP = 1 << 17,	// 0x20000,
	DB_ZONE_GUMP_LOC = 1 << 18,	// 0x40000,

#if 0
	// These values need to be validated
	DB_ZONE_LOW_MARKER = 1 << 19,	// 0x80000,
	DB_ZONE_MYCHANGES_LOC = 1 << 20,	// 0x100000,
	DB_ZONE_MYCHANGES = 1 << 21,	// 0x200000,

	// Probably not used in SP
	DB_ZONE_UI_VIEWER_LOC = 1 << 22,	// 0x400000,
	DB_ZONE_UI_VIEWER = 1 << 23,	// 0x800000,

	DB_ZONE_FRONTEND_LOC = 1 << 24,	// 0x1000000,
	DB_ZONE_FRONTEND = 1 << 25,	// 0x2000000,
#endif

	DB_ZONE_PATCH_UI = 1 << 26, // 0x4000000,
	DB_ZONE_PATCH_UI_LOC = 1 << 27, // 0x8000000,

#if 0
	// These values need to be validated
	DB_ZONE_HIGH_MARKER = 1 << 26,	// 0x4000000,
	DB_ZONE_LOAD = 1 << 27,	// 0x8000000,
#endif

	DB_FLAG_NULL = 0,
	DB_FLAG_RSTREAM = 1 << 30,	// 0x40000000,
	DB_FLAG_STRICTFREE = 1 << 31,	// 0x80000000,
};

VANILLA_VALUE(g_zoneInfoCount, volatile unsigned int, 0x00E72984);
static XZoneInfoInternal* g_zoneInfo = (XZoneInfoInternal*)0x00C84308;
static XZoneName* g_zoneNames = (XZoneName*)0x010C6608;

static char** g_assetNames = (char**)0x00B73BB0;
VANILLA_VALUE(g_load_filename, char*, 0x00C7934C);

#define DVAR_NOFLAG				0				// 0x0000
#define DVAR_ARCHIVE            (1 << 0)        // 0x0001
#define DVAR_USERINFO           (1 << 1)        // 0x0002
#define DVAR_SERVERINFO         (1 << 2)        // 0x0004
#define DVAR_SYSTEMINFO         (1 << 3)        // 0x0008
#define DVAR_INIT               (1 << 4)        // 0x0010
#define DVAR_LATCH              (1 << 5)        // 0x0020
#define DVAR_ROM                (1 << 6)        // 0x0040
#define DVAR_CHEAT              (1 << 7)        // 0x0080
#define DVAR_DEVELOPER          (1 << 8)        // 0x0100
#define DVAR_SAVED              (1 << 9)        // 0x0200
#define DVAR_NORESTART          (1 << 10)       // 0x0400
#define DVAR_CHANGEABLE_RESET   (1 << 12)       // 0x1000
#define DVAR_EXTERNAL           (1 << 14)       // 0x4000
#define DVAR_AUTOEXEC           (1 << 15)       // 0x8000
#define DVAR_UNRESTRICTED		(1 << 16)		// 0x10000

enum dvarType_t
{
	DVAR_TYPE_BOOL = 0x0,
	DVAR_TYPE_FLOAT = 0x1,
	DVAR_TYPE_FLOAT_2 = 0x2,
	DVAR_TYPE_FLOAT_3 = 0x3,
	DVAR_TYPE_FLOAT_4 = 0x4,
	DVAR_TYPE_INT = 0x5,
	DVAR_TYPE_ENUM = 0x6,
	DVAR_TYPE_STRING = 0x7,
	DVAR_TYPE_COLOR = 0x8,
	DVAR_TYPE_INT64 = 0x9,
	DVAR_TYPE_LINEAR_COLOR_RGB = 0xA,
	DVAR_TYPE_COLOR_XYZ = 0xB,
	DVAR_TYPE_COUNT = 0xC,
};

enum DvarSetSource
{
	DVAR_SOURCE_INTERNAL = 0x0,
	DVAR_SOURCE_EXTERNAL = 0x1,
	DVAR_SOURCE_SCRIPT = 0x2,
	DVAR_SOURCE_DEVGUI = 0x3,
};

union DvarValue
{
	bool enabled;
	int integer;
	unsigned int unsignedInt;
	__int64 integer64;
	unsigned __int64 unsignedInt64;
	float value;
	float vector[4];
	const char* string;
	char color[4];
};

union DvarLimits
{
	struct
	{
		int stringCount;
		const char** strings;
	} enumeration;

	struct
	{
		int min;
		int max;
	} integer;

	struct
	{
		__int64 min;
		__int64 max;
	} integer64;

	struct
	{
		float min;
		float max;
	} value;

	struct
	{
		float min;
		float max;
	} vector;
};

struct dvar_s
{
	const char* name;
	const char* description;
	int hash;
	unsigned int flags;
	dvarType_t type;
	bool modified;
	bool loadedFromSaveGame;
	DvarValue current;
	DvarValue latched;
	DvarValue reset;
	DvarValue saved;
	DvarLimits domain;
	dvar_s* hashNext;
};
STATIC_ASSERT_OFFSET(dvar_s, current, 0x18);

VANILLA_DVAR(sv_mapname, 0x02899CEC);
VANILLA_DVAR(zombietron, 0x0247FDE8);
VANILLA_DVAR(zombiemode, 0x0243FDD4);
VANILLA_DVAR(blackopsmode, 0x0243FD24);
VANILLA_DVAR(useFastFile, 0x0247FEC8);