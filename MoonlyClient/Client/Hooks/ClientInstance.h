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

typedef float(__stdcall* GetGamma)(uintptr_t*);
GetGamma _GetGamma;

float GetGammaCallback(uintptr_t* a1) {
	Module* nightvision = ClientManager::GetModuleByName("NightVision");

	if (nightvision != nullptr && nightvision->isEnabled) {
		return 25.f;
	}

	return _GetGamma(a1);
}

typedef void(_stdcall* Actor_hurt)(Actor*, Actor&);
Actor_hurt _Actor_hurt;

void ActorHurtCallback(Actor* _this, Actor& actor) {
	Minecraft::lastReach = _this->getPos()->distance(*actor.getPos());

	return _Actor_hurt(_this, actor);
}

typedef float(_stdcall* LevelRendererPlayer_getFov)(__int64, float, bool);
LevelRendererPlayer_getFov _LevelRendererPlayer_getFov;

float LevelRendererPlayerGetFovCallback(__int64 _this, float a2, bool a3) {
	Module* zoom = ClientManager::GetModuleByName("Zoom");
	
	if (zoom != nullptr && zoom->isEnabled) {
		return 15.f;
	}
		
	return _LevelRendererPlayer_getFov(_this, a2, a3);
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

	// getGamma
	sigAddr = Utils::FindSig("48 83 EC 28 80 B9 ?? ?? ?? ?? 00 48 8D 54 24 30 74 36 41 B8 ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8B 10 48 85 D2 74 3C 48 8B 8A ?? ?? ?? ?? 48 85 C9 74 0A E8 ?? ?? ?? ?? 48 83 C4 28 C3");
	if (sigAddr) {
		Utils::DebugLogOutput("Found address needed for the getGamma Hook, Preparing Hook install now...");
		if (MH_CreateHook((void*)sigAddr, &GetGammaCallback, reinterpret_cast<LPVOID*>(&_GetGamma)) == MH_OK) {
			Utils::DebugLogOutput("Successfully created getGamma Hook, Installing Hook now...");
			MH_EnableHook((void*)sigAddr);
		}
		else {
			Utils::DebugLogOutput("Failed to create getGamma Hook!");
		}
	}
	else {
		Utils::DebugLogOutput("Failed to find address needed for the GetGamma Hook!");
	}

	// getFov
	sigAddr = Utils::FindSig("40 53 48 83 EC 70 0F 29 7C 24 ? 44 0F 29 4C 24 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? F3 0F 10 3D ? ? ? ? 44 0F");
	if (sigAddr) {
		Utils::DebugLogOutput("Found address needed for the getFov Hook, Preparing Hook install now...");
		if (MH_CreateHook((void*)sigAddr, &LevelRendererPlayerGetFovCallback, reinterpret_cast<LPVOID*>(&_LevelRendererPlayer_getFov)) == MH_OK) {
			Utils::DebugLogOutput("Successfully created getFov Hook, Installing Hook now...");
			MH_EnableHook((void*)sigAddr);
		}
		else {
			Utils::DebugLogOutput("Failed to create getFov Hook!");
		}
	}
	else {
		Utils::DebugLogOutput("Failed to find address needed for the getFov Hook!");
	}

	uintptr_t sigOffset = Utils::FindSig("48 8D 05 ?? ?? ?? ?? 48 89 07 48 8D 8F ?? ?? ?? ?? 48 8B 87");

	int offset = *reinterpret_cast<int*>(sigOffset + 3);
	uintptr_t** localPlayerVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + 7);

	if (localPlayerVtable == 0x0 || sigOffset == 0x0)
		Utils::DebugLogOutput("LocalPlayer vtable not found");
	else {
		// Actor::hurt
		if (MH_CreateHook((void*)localPlayerVtable[107], &ActorHurtCallback, reinterpret_cast<LPVOID*>(&_Actor_hurt)) == MH_OK) {
			Utils::DebugLogOutput("Successfully created Actor::hurt Hook, Installing Hook now...");
			MH_EnableHook((void*)localPlayerVtable[107]);
		}
	}
}