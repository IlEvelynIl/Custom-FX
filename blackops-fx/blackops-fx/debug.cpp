#include "pch.h"

#include "debug.hpp"

namespace debug {
	void Log(const char* msg)
	{
		std::ofstream logFile(FX_LOGFILE, std::ios::app);
		if (logFile.is_open()) {
			logFile << msg << '\n';
		}
	}

	void Msg(const char* msg)
	{
		MessageBoxA(NULL, msg, "blackops-fx", MB_OK);
	}
}