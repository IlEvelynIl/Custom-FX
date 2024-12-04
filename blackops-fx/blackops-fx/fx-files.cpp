#include "pch.h"

#include "fx-files.hpp"

namespace fx {
	namespace fs = std::filesystem;

	int GetAmountOfFxFiles()
	{
		int fx_files = 0;
		for (const auto& entry : fs::recursive_directory_iterator(FX_FILES_DIR)) {
			if (entry.is_regular_file() && entry.path().extension() == FX_FILE_EXT) {
				++fx_files;
			}
		}

		return fx_files;
	}

	bool DoNonFxFilesExist()
	{
		for (const auto& entry : fs::recursive_directory_iterator(FX_FILES_DIR)) {
			if (entry.is_regular_file() && entry.path().extension() != FX_FILE_EXT) {
				return true;
			}
		}

		return false;
	}

	std::string hashFxFile()
	{
		std::ifstream file("zone\\Common\\custom_fx.ff", std::ios::binary);

		if (!file) {
			return "";
		}

		file.seekg(0, std::ios::end);
		long length = file.tellg();
		file.seekg(0, std::ios::beg);

		if (length <= 0) {
			return "";
		}

		std::vector<char> fileData(length);
		file.read(fileData.data(), length);

		if (!file) {
			return "";
		}

		std::string hash = md5(fileData.data(), length);
		return hash.c_str();
	}
}