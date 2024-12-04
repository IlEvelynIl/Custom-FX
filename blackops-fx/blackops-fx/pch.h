// pch.h: This is a precompiled header file
#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#define DEBUG 1
#define FX_LOGFILE "custom-fx.log"
#define FX_FILE_EXT ".efx"

#define CUSTOM_FX_DIR "custom_fx"
#define FX_FILES_DIR "custom_fx\\your_fx_files"
#define LINKER_DIR "custom_fx\\linker"
#define ZONE_SOURCE_DIR "custom_fx\\linker\\zone_source"

#include <windows.h>
#include <filesystem>
#include <thread>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <iostream>

#include "md5.h"

#include "structs.h"
#include "functions.h"

#pragma comment(lib, "detours.lib")
#include "Detours.h"

#endif //PCH_H