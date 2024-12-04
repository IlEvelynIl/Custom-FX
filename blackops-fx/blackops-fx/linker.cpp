#include "pch.h"

#include "linker.hpp"
#include "process.hpp"
#include "debug.hpp"

namespace linker {
	namespace fs = std::filesystem;
    std::string custom_fx_hash;

    bool PrepModCSV()
    {
        std::string fx_files_dir = FX_DIR;
        std::string linker_dir = LINKER_DIR;
        std::string zone_source = ZONE_SOURCE_DIR;
        std::string mod_dir = linker_dir + "\\mods\\custom_fx";

        // Ensure directories exist
        fs::create_directories(zone_source);
        fs::create_directories(mod_dir);

        std::string mod_csv_path = mod_dir + "\\mod.csv";

        std::ofstream mod_csv(mod_csv_path);
        if (!mod_csv.is_open()) {
            return false;
        }

        try {
            // Recursively iterate through `fx_files_dir/fx` for all files
            for (const auto& entry : fs::recursive_directory_iterator(fx_files_dir)) {
                if (entry.is_regular_file()) {
                    std::string file_path = entry.path().string();

                    // use "/" instead of "\\"
                    std::replace(file_path.begin(), file_path.end(), '\\', '/');

                    std::string relative_path = file_path.substr(fx_files_dir.length() + 1);

                    if (relative_path.compare(0, 3, "fx/") == 0) { // Check if the first 3 characters are "fx/"
                        relative_path = relative_path.substr(3);
                    }

                    // Remove `.efx`
                    if (relative_path.size() > 4 && relative_path.substr(relative_path.size() - 4) == ".efx") {
                        relative_path = relative_path.substr(0, relative_path.size() - 4);
                    }

                    mod_csv << "fx," << relative_path << "\n";
                }
            }
        }
        catch (std::exception& e) {
            std::thread{ debug::Log, "Failed to generate custom fx csv" }.detach();
            return false;
        }

        mod_csv.close();

        std::string zone_source_csv_path = zone_source + "\\mod.csv";

        // Copy `mod.csv` to `zone_source`
        try {
            fs::copy(mod_csv_path, zone_source_csv_path, fs::copy_options::overwrite_existing);
        }
        catch (std::exception& e) {
            std::thread{ debug::Log, "Failed to copy custom fx csv to zone_source" }.detach();
            return false;
        }

        return true;
    }
	
	// builds the custom_fx.ff file using linker_pc.exe
    bool LinkCustomFX()
    {
        std::string fx_files_dir = FX_FILES_DIR;
        std::string mod_dir = "custom_fx\\linker\\mods\\custom_fx";

        // Copy files over

        if (fs::exists(fx_files_dir + "/fx"))
        {
            try {
                fs::copy(fx_files_dir + "/fx", mod_dir + "/fx", fs::copy_options::recursive | fs::copy_options::overwrite_existing);
            }
            catch (std::exception& e) {
                std::thread{ debug::Log, "Failed to copy fx folder" }.detach();
            }
        }

        if (fs::exists(fx_files_dir + "/images"))
        {
            try {
                fs::copy(fx_files_dir + "/images", "custom_fx/linker/raw/images", fs::copy_options::recursive | fs::copy_options::overwrite_existing);
            }
            catch (std::exception& e) {
                std::thread{ debug::Log, "Failed to copy images folder" }.detach();
            }
        }

        // "custom_fx/linker/bin/launcher_ldr.exe" "custom_fx/linker/bin/linker_pc.dll" "custom_fx/linker/bin/linker_pc.exe" -nopause -language english -moddir custom_fx mod
        std::string cmd = "\"custom_fx/linker/bin/launcher_ldr.exe\" \"custom_fx/linker/bin/linker_pc.dll\" \"custom_fx/linker/bin/linker_pc.exe\" -nopause -language english -moddir custom_fx mod";
        return process::LaunchProcess(cmd);
    }

    void MoveCustomFXFastFile()
    {
        std::string source_path = "custom_fx\\linker\\zone\\english\\mod.ff";
        std::string destination_path = "zone\\Common\\custom_fx.ff";

        // remove an already existing custom_fx.ff
        if (fs::exists(destination_path))
        {
            fs::remove(destination_path);
        }

        fs::rename(source_path, destination_path);
    }
} // linker