#pragma once
#include "../../Other/Module.h"
#include "../../SDK/Classes/HIDController.h"

class Mouse_Hook : public Hook {
public:
	void Install();
};

typedef void(__fastcall* Mouse)(HIDController*, void*, void*);
Mouse _Mouse;
void MouseCallback(HIDController* _this, void* a2, void* a3) {
	Minecraft::SetHIDController(_this);
	_Mouse(_this, a2, a3);
}

void Mouse_Hook::Install() {
	uintptr_t sigAddr = Utils::FindSig("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC ? 0F 29 74 24 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 E0 49 8B F0 48 8B F9");
	if (sigAddr) {
		Utils::DebugLogOutput("Found address needed for the Mouse Hook, Preparing Hook install now...");
		if (MH_CreateHook((void*)sigAddr, &MouseCallback, reinterpret_cast<LPVOID*>(&_Mouse)) == MH_OK) {
			Utils::DebugLogOutput("Successfully created Mouse Hook, Installing Hook now...");
			MH_EnableHook((void*)sigAddr);
		}
		else {
			Utils::DebugLogOutput("Failed to create Mouse Hook!");
		}
	}
	else {
		Utils::DebugLogOutput("Failed to find address needed for the Mouse Hook!");
	}
}