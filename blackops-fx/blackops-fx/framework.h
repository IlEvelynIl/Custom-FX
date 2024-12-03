#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#define DEBUG 1
#define FX_LOGFILE "custom-fx.log"
#define CUSTOM_FX_DIR "custom_fx"
#define FX_FILE_EXT ".efx"

#include <windows.h>
#include <filesystem>
#include <thread>
#include <fstream>
#include <string>