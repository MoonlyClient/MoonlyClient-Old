#pragma once
#include "../../Other/Module.h"

class KeyItem : public Hook {
public:
	void Install();
};

typedef void(WINAPI* AVKeyItem)(uint64_t key, bool isDown);
AVKeyItem _AVKeyItem;

void KeyItemCallback(uint64_t key, bool isDown) {
	Utils::KeyMapping[key] = isDown;
	bool cancel = false;
	for (auto Module : ClientManager::Modules) {
		if (Module->isEnabled) Module->onKey(key, isDown, &cancel);
	}
	if(!cancel) _AVKeyItem(key, isDown);
}

void KeyItem::Install() {
	uintptr_t sigAddr = Utils::FindSig("48 89 5C 24 ?? ?? 48 83 EC ?? 8B 05 ?? ?? ?? ?? 8B DA");
	if (sigAddr) {
		Utils::DebugLogOutput("Found address needed for the KeyItem Hook, Preparing Hook install now...");
		if (MH_CreateHook((void*)sigAddr, &KeyItemCallback, reinterpret_cast<LPVOID*>(&_AVKeyItem)) == MH_OK) {
			Utils::DebugLogOutput("Successfully created KeyItem Hook, Installing Hook now...");
			MH_EnableHook((void*)sigAddr);
		}
		else {
			Utils::DebugLogOutput("Failed to create KeyItem Hook!");
		}
	}
	else {
		Utils::DebugLogOutput("Failed to find address needed for the KeyItem Hook!");
	}
}