#include "pch.h"

#include "ceg.hpp"
#include "memory.hpp"

// taken directly from game mod
namespace ceg {
	void Patch_CEG()
	{
        // Kill Steam DRM IPC creation
        memory::PatchMemory(0x00662F20, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x0046C9A0, (PBYTE)"\xCC", 1);
		memory::PatchMemory(0x005F3290, (PBYTE)"\xCC", 1);

        // Registry key checks
        memory::PatchMemory(0x4DFD60, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
        memory::PatchMemory(0x53F880, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
        memory::PatchMemory(0x5A5360, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
        memory::PatchMemory(0x4DFD60, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
        memory::PatchMemory(0x5A5360, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);

        // Single function, 32bit hash check
        memory::PatchMemory(0x64F6A0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
        memory::PatchMemory(0x5614A0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
        memory::PatchMemory(0x417360, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
        memory::PatchMemory(0x56AB40, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
        memory::PatchMemory(0x59BEB0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);

        // Direct ExitProcess() check
        memory::PatchMemory(0x676740, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
        memory::PatchMemory(0x5DB020, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
        memory::PatchMemory(0x4F02C0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
        memory::PatchMemory(0x572DF0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
        memory::PatchMemory(0x679B40, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
        memory::PatchMemory(0x4BFB50, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
        memory::PatchMemory(0x4D4B80, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
        memory::PatchMemory(0x501080, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
        memory::PatchMemory(0x5CAB50, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
        memory::PatchMemory(0x4C0DE0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);

		// Wrapper ExitProcess() check, executes
		// on certain days of the week
		memory::PatchMemory(0x0041CEB0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x0041CF50, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x00427E00, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x00437350, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x00444E80, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x00449C30, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x004545A0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x0045C550, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x00462B60, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x004682B0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x00487D80, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x0048C7B0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x004A9970, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x004C3360, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x004D9650, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x004E3860, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x00515B20, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x005268E0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x00527200, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x005474A0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x0054F280, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x00561410, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x0059D820, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x005A8800, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x005B4330, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x005D3F20, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x005EF2A0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x006099E0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x00610A60, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x00625500, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x00625980, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x0064FFB0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x00662EC0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x00662F80, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x00671860, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x0067B3B0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x0067D830, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x006857B0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x0068D300, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x0068E8F0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);

		// Wrapper ExitProcess() check with HWBP detection,
		// executes on certain days of the week
		memory::PatchMemory(0x9A23B0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x9A23F0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x9A2430, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x9A2470, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x9A24B0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x9A24F0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x9A2530, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x9A2570, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x9A25B0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x9A25F0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x9A2630, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x9A2670, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x9A26B0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x9A26F0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x9A2730, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x9A2770, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);

		// Direct HWBP check
		memory::PatchMemory(0x9A2980, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x9A29B0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);
		memory::PatchMemory(0x9A29E0, (PBYTE)"\xB8\x01\x00\x00\x00\xC3", 6);

		Detours::X86::DetourFunction((uintptr_t)0x8EE640, (uintptr_t)&sub_8EE640);

		memory::FixupFunction(0x0060CC10, 0x004F20F0);		// CEGObfuscate<LiveStats_Init> => LiveStats_Init
		memory::FixupFunction(0x0063DCC0, 0x0062DD40);		// CEGObfuscate<LiveStats_ResetStats> => LiveStats_ResetStats
		memory::FixupFunction(0x00580460, 0x0079E6D0);		// CEGObfuscate<Con_Restricted_SetLists> => Con_Restricted_SetLists
	}

	void* sub_8EE640(void* Nullptr1, void* Nullptr2)
	{
		__debugbreak();

		if (Nullptr1 != nullptr || Nullptr2 != nullptr)
			__debugbreak();

		*(void**)0xBA1C24 = Nullptr2;
		return (void*)0xBA1C24;
	}
}