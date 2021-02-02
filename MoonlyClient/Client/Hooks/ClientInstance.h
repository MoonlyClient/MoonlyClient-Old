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

typedef float(__stdcall* GetGamma)(uintptr_t* a1);
GetGamma _GetGamma;

float GetGammaCallback(uintptr_t* a1) {
	Module* nightvision = ClientManager::GetModuleByName("NightVision");

	if (nightvision != nullptr && nightvision->isEnabled) {
		return 25.f;
	}

	return *((float*)*(a1 + 0x27) + 0x7A);
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

	uintptr_t sigAddr2 = Utils::FindSig("48 83 EC 28 80 B9 ?? ?? ?? ?? 00 48 8D 54 24 30 74 36 41 B8 ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8B 10 48 85 D2 74 3C 48 8B 8A ?? ?? ?? ?? 48 85 C9 74 0A E8 ?? ?? ?? ?? 48 83 C4 28 C3");
	if (sigAddr2) {
		Utils::DebugLogOutput("Found address needed for the GetGamma Hook, Preparing Hook install now...");
		if (MH_CreateHook((void*)sigAddr2, &GetGammaCallback, reinterpret_cast<LPVOID*>(&_GetGamma)) == MH_OK) {
			Utils::DebugLogOutput("Successfully created GetGamma Hook, Installing Hook now...");
			MH_EnableHook((void*)sigAddr2);
		}
		else {
			Utils::DebugLogOutput("Failed to create GetGamma Hook!");
		}
	}
	else {
		Utils::DebugLogOutput("Failed to find address needed for the GetGamma Hook!");
	}
}