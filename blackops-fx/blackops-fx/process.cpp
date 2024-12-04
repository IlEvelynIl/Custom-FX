#include "pch.h"
#include "debug.hpp"

namespace process {
	bool LaunchProcess(std::string& cmd)
	{
        STARTUPINFOA si = { 0 };
        PROCESS_INFORMATION pi = { 0 };

        si.cb = sizeof(si);

        // Create a mutable copy of the cmd since CreateProcess modifies it
        char cmdLine[1024];
        strncpy_s(cmdLine, cmd.c_str(), sizeof(cmdLine) - 1);
        cmdLine[sizeof(cmdLine) - 1] = '\0';

        // Create the process
        if (!CreateProcessA(
            nullptr,        // Application name (nullptr because the executable is in the cmd line)
            cmdLine,        // Command line
            nullptr,        // Process handle not inheritable
            nullptr,        // Thread handle not inheritable
            FALSE,          // Set handle inheritance to FALSE
            0,              // No creation flags
            nullptr,        // Use parent's environment block
            nullptr,        // Use parent's starting directory
            &si,            // Pointer to STARTUPINFO structure
            &pi             // Pointer to PROCESS_INFORMATION structure
        )) {
            std::string error = "Failed to start linker process: " + std::to_string(GetLastError());
            std::thread{ debug::Log, error.c_str() }.detach();
            return false;
        }

        // Wait for the process to complete (optional, remove if not needed)
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Close process and thread handles
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return true;
	}
}