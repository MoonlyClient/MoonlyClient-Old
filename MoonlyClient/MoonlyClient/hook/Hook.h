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
			Utils::DebugLogOutput("[HookManager] Found " + name + " address, creating...");

			if (MH_CreateHook((void*)sigAddr, pDetour, ppOriginal) == MH_OK) {
				Utils::DebugLogOutput("[HookManager] Successfully created " + name + " hook, enabling...");

				MH_EnableHook((void*)sigAddr);
			}
			else {
				Utils::DebugLogOutput("[HookManager] Failed to create " + name + " hook!");
			}
		}
		else {
			Utils::DebugLogOutput("[HookManager] Failed to find " + name + " address!");
		}
	}
};