#pragma once
#include "../../Other/Module.h"

class ClientInstance_Hook : public Hook {
public:
	void Install();
};

typedef void(__fastcall* C_Hook)(ClientInstance* a1, void* a2);
C_Hook _C_Hook;

void Callback(ClientInstance* a1, void* a2) {
	Minecraft::SetClientInstance(a1);
	_C_Hook(a1, a2);
}

void ClientInstance_Hook::Install() {
	uintptr_t sigAddr = Utils::FindSig("48 89 5C 24 ?? 48 89 74 24 ?? 57 48 83 EC ?? 48 8B F9 48 8B 01");
	if (sigAddr) {
		Utils::DebugLogOutput("Found address needed for the ClientInstance Hook, Preparing Hook install now...");
		if (MH_CreateHook((void*)sigAddr, &Callback, reinterpret_cast<LPVOID*>(&_C_Hook)) == MH_OK) {
			Utils::DebugLogOutput("Successfully created ClientInstance Hook, Installing Hook now...");
			MH_EnableHook((void*)sigAddr);
		}
		else {
			Utils::DebugLogOutput("Failed to create ClientInstance Hook!");
		}
	}
	else {
		Utils::DebugLogOutput("Failed to find address needed for the ClientInstance Hook!");
	}
}