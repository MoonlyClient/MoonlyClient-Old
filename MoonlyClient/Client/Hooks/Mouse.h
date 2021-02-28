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
	return _Mouse(_this, a2, a3);
}

typedef void(__fastcall* Click)(__int64, char, char, __int16, __int16, __int16, __int16, char);
Click _Click;
void ClickCallback(__int64 a1, char mouseButton, char isDown, __int16 mouseX, __int16 mouseY, __int16 relativeMovementX, __int16 relativeMovementY, char a8) {
	Module* menu = ClientManager::GetModuleByName("MenuGUI");

	if (menu == nullptr) {
		return;
	}

	if (menu->isEnabled) {
		if (mouseButton != 0)
			return;
	}

	if (isDown)
		if (mouseButton == 1)
			Minecraft::leftclickCount++;
		else if (mouseButton == 2)
			Minecraft::rightclickCount++;

	return _Click(a1, mouseButton, isDown, mouseX, mouseY, relativeMovementX, relativeMovementY, a8);
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

	uintptr_t sigAddr2 = Utils::FindSig("48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 44 0F B7 BC 24 ? ? ? ? 48 8B D9");
	if (sigAddr2) {
		Utils::DebugLogOutput("Found address needed for the Click Hook, Preparing Hook install now...");
		if (MH_CreateHook((void*)sigAddr2, &ClickCallback, reinterpret_cast<LPVOID*>(&_Click)) == MH_OK) {
			Utils::DebugLogOutput("Successfully created Click Hook, Installing Hook now...");
			MH_EnableHook((void*)sigAddr2);
		}
		else {
			Utils::DebugLogOutput("Failed to create Click Hook!");
		}
	}
	else {
		Utils::DebugLogOutput("Failed to find address needed for the Click Hook!");
	}
}