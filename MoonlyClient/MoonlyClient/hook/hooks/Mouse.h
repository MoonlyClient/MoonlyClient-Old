#pragma once

#include "../Hook.h"
#include "../../data/GameData.h"
#include "../../module/ModuleManager.h"
#include "../../sdk/HIDController.h"

class MouseHook : public Hook {
public:
	void install();
};

typedef void(__stdcall* Mouse)(HIDController*, void*, void*);
Mouse _Mouse;

void Mouse_callback(HIDController* _this, void* a2, void* a3) {
	gData.setHIDController(_this);

	return _Mouse(_this, a2, a3);
}

typedef void(__stdcall* Click)(__int64, char, char, __int16, __int16, __int16, __int16, char);
Click _Click;
void Click_callback(__int64 a1, char mouseButton, char isDown, __int16 mouseX, __int16 mouseY, __int16 relativeMovementX, __int16 relativeMovementY, char a8) {
	Module* menu = moduleMgr.getModuleByName("MenuGUI");

	if (menu == nullptr) {
		return;
	}

	if (menu->isEnabled) {
		if (mouseButton != 0)
			return;
	}

	// ToDo : Menu

	if (isDown)
		if (mouseButton == 1)
			gData.leftclickCount++;
		else if (mouseButton == 2)
			gData.rightclickCount++;

	return _Click(a1, mouseButton, isDown, mouseX, mouseY, relativeMovementX, relativeMovementY, a8);
}

void MouseHook::install() {
	this->hookSig("Mouse", "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 81 EC ? ? ? ? 0F 29 74 24 ? 0F 29 7C 24 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F0", &Mouse_callback, reinterpret_cast<LPVOID*>(&_Mouse));

	this->hookSig("Click", "48 89 5C 24 ?? ?? 48 83 EC ?? 8B 05 ?? ?? ?? ?? 8B DA", &Click_callback, reinterpret_cast<LPVOID*>(&_Click));
}