#pragma once
#include "../../Other/Module.h"
#include "../../Other/Menu.h"
#include "../ClientManager.h"
#include "../Modules/MenuGUI.h"

class Keyboard_Hook : public Hook {
public:
	void Install();
};

typedef void(WINAPI* AVKeyItem)(uint64_t key, bool isDown);
AVKeyItem _AVKeyItem;

void KeyItemCallback(uint64_t key, bool isDown) {
	Utils::KeyMapping[key] = isDown;

		for (auto Module : ClientManager::Modules) {
			if (isDown) {
				if ((int)key == (int)Module->key) {
					Module->isEnabled = !Module->isEnabled;

					if (Module->isEnabled)
						Module->onEnable();
					else
						Module->onDisable();
				}
			}

			if (Module->isEnabled) Module->onKey(key, isDown);
		}

		Menu::onKeyUpdate(key, isDown);
	
	_AVKeyItem(key, isDown);
}

void Keyboard_Hook::Install() {
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