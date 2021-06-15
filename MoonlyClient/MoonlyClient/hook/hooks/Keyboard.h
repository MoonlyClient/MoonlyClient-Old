#pragma once

#include "../Hook.h"
#include "../../data/GameData.h"
#include "../../module/ModuleManager.h"

class KeyboardHook : public Hook {
public:
	void install();
};

typedef void(WINAPI* AVKeyItem)(uint64_t key, bool isDown);
AVKeyItem _AVKeyItem;

void KeyItem_callback(uint64_t key, bool isDown) {
	Utils::KeyMapping[key] = isDown;

		for (auto Module : moduleMgr.modules) {
			if (isDown) {
				if ((int)key == (int)Module->key) {
					Module->isEnabled = !Module->isEnabled;

					if (Module->isEnabled)
						Module->onEnable();
					else
						Module->onDisable();
				}
			}

			if (Module->isEnabled)
				Module->onKey(key, isDown);
		}

		// ToDo : Menu
	
	_AVKeyItem(key, isDown);
}

void KeyboardHook::install() {
	this->hookSig("AVKeyItem", xorstr_("48 89 5C 24 ?? ?? 48 83 EC ?? 8B 05 ?? ?? ?? ?? 8B DA"), &KeyItem_callback, reinterpret_cast<LPVOID*>(&_AVKeyItem));
}