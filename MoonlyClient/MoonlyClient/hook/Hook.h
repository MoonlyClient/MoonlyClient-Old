#pragma once

#include<Windows.h>
#include <cstdint>

#include "../../include/MinHook.h"
#include "../utils/Utils.h"

class Hook {
public:
	virtual void install() {};
	
	inline void hookSig(std::string name, const char* szSignature, LPVOID pDetour, LPVOID* ppOriginal) {
		uintptr_t sigAddr = Utils::FindSig(szSignature);

		if (sigAddr) {
			Utils::DebugLogOutput("Found " + name + " address, creating...");

			if (MH_CreateHook((void*)sigAddr, pDetour, ppOriginal) == MH_OK) {
				Utils::DebugLogOutput("Successfully created " + name + " hook, enabling...");

				MH_EnableHook((void*)sigAddr);
			}
			else {
				Utils::DebugLogOutput("Failed to create " + name + " hook!");
			}
		}
		else {
			Utils::DebugLogOutput("Failed to find " + name + " address!");
		}
	}
};