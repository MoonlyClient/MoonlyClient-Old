#pragma once
#include "../../Other/Module.h"
#include "../../SDK/Classes/RakNetInstance.h"
#include "../ClientManager.h"

class RakNetInstance_Hook : public Hook {
public:
	void Install();
};

typedef void(__stdcall* RakNetInstance_tick)(RakNetInstance* _this, __int64 a2, __int64 a3);
RakNetInstance_tick _RakNetInstance_tick;

void RakNetInstance_tick_Callback(RakNetInstance* _this, __int64 a2, __int64 a3) {
	Minecraft::SetRakNetInstance(_this);
	_RakNetInstance_tick(_this, a2, a3);
}

void RakNetInstance_Hook::Install() {
	uintptr_t sigAddr = Utils::FindSig("48 89 5C 24 10 48 89 74 24 18 55 57 41 54 41 56 41 57 48 8D ?? 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 48 8B F9 45 33 E4 4C");
	if (sigAddr) {
		Utils::DebugLogOutput("Successfully found address needed for the RakNetInstance_tick Hook, Preparing Hook install now...");
		if (MH_CreateHook((void*)sigAddr, &RakNetInstance_tick_Callback, reinterpret_cast<LPVOID*>(&_RakNetInstance_tick)) == MH_OK) {
			Utils::DebugLogOutput("Successfully created RakNetInstance_tick Hook, Installing hook now...");
			MH_EnableHook((void*)sigAddr);
		}
		else {
			Utils::DebugLogOutput("Failed to create RakNetInstance_tick Hook!");
		}
	}
	else {
		Utils::DebugLogOutput("Failed to find address needed for the RakNetInstance_tick Hook!");
	}
}