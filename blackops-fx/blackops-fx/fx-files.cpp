#include "pch.h"

#include "fx-files.hpp"

namespace fx {
	namespace fs = std::filesystem;

	int GetAmountOfFxFiles()
	{
		int fx_files = 0;
		for (const auto& entry : fs::recursive_directory_iterator(CUSTOM_FX_DIR)) {
			if (entry.is_regular_file() && entry.path().extension() == FX_FILE_EXT) {
				++fx_files;
			}
		}

		return fx_files;
	}

	bool DoNonFxFilesExist()
	{
		for (const auto& entry : fs::recursive_directory_iterator(CUSTOM_FX_DIR)) {
			if (entry.is_regular_file() && entry.path().extension() != FX_FILE_EXT) {
				return true;
			}
		}

		return false;
	}
}