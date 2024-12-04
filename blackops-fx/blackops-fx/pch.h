// pch.h: This is a precompiled header file
#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#define FX_FILE_EXT ".efx"
#define FX_LOGFILE "custom-fx.log"

#define CUSTOM_FX_DIR "custom_fx"
#define FX_FILES_DIR "custom_fx\\your_fx_files"
#define FX_DIR "custom_fx\\your_fx_files\\fx"
#define IMAGES_DIR "custom_fx\\your_fx_files\\images"
#define LINKER_DIR "custom_fx\\linker"
#define LINKER_RAW "custom_fx\\linker\\raw"
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