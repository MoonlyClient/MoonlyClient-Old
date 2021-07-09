#pragma once

#include "../Hook.h"
#include "../../data/GameData.h"
#include "../../module/ModuleManager.h"
#include "../../module/modules/MenuGUI.h"
#include "../../sdk/HIDController.h"

#pragma comment(lib, "user32.lib" )

HHOOK hHook = NULL;

class MouseHook : public Hook {
public:
	void install();
};

typedef void(__stdcall* Mouse)(HIDController*, void*, void*);
Mouse _Mouse;

void hMouse(HIDController* _this, void* a2, void* a3) {
	gData.setHIDController(_this);

	return _Mouse(_this, a2, a3);
}

typedef void(__stdcall* Click)(__int64, char, char, __int16, __int16, __int16, __int16, char);
Click _Click;

void hClick(__int64 a1, char mouseButton, char isDown, __int16 mouseX, __int16 mouseY, __int16 relativeMovementX, __int16 relativeMovementY, char a8) {
    MenuGUI* menu = (MenuGUI*)moduleMgr.getModuleByName("MenuGUI");

    if (menu != nullptr && menu->isEnabled) {
        menu->onMouseClickUpdate((int)mouseButton, isDown);
    }
    
    if (isDown)
        if (mouseButton == 1)
            gData.leftClickCount++;
        else if (mouseButton == 2)
            gData.rightClickCount++;

    return _Click(a1, mouseButton, isDown, mouseX, mouseY, relativeMovementX, relativeMovementY, a8);
}

void MouseHook::install() {
	this->hookSig("Mouse", xorstr_("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 81 EC ? ? ? ? 0F 29 74 24 ? 0F 29 7C 24 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F0"), &hMouse, (LPVOID*)&_Mouse);
    this->hookSig("Click", xorstr_("48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 44 0F B7 BC 24 ? ? ? ? 48 8B D9"), &hClick, (LPVOID*)&_Click);
}