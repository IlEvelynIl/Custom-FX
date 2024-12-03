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

	std::string hashFxFile()
	{
		std::ifstream file("zone\\Common\\custom_fx.ff", std::ios::binary);

		if (!file)
		{
			throw std::runtime_error("Could not open file.");
		}

		std::size_t basis = 0xCBF29CE484222325;
		std::size_t prime = 0x100000001B3;

		std::size_t hash = basis;
		char buffer[8192];

		while (file.read(buffer, sizeof(buffer))) {
			for (std::streamsize i = 0; i < file.gcount(); ++i) {
				hash ^= static_cast<unsigned char>(buffer[i]);
				hash *= prime;
			}
		}

		for (std::streamsize i = 0; i < file.gcount(); ++i) {
			hash ^= static_cast<unsigned char>(buffer[i]);
			hash *= prime;
		}

		std::ostringstream oss;
		oss << std::hex << std::setw(16) << std::setfill('0') << hash;
		return oss.str();
	}
}