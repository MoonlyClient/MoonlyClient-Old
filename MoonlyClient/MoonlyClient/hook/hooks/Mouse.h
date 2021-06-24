#pragma once

#include "../Hook.h"
#include "../../data/GameData.h"
#include "../../module/ModuleManager.h"
#include "../../sdk/HIDController.h"

#pragma comment( lib, "user32.lib" )

HHOOK hHook = NULL;

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

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        if (wParam == WM_RBUTTONDOWN)
            gData.rightClickCount++;
        else if (wParam == WM_LBUTTONDOWN)
            gData.leftClickCount++;
    }

    return nCode < 0 ? CallNextHookEx(hHook, nCode, wParam, lParam) : 0;
}

void MouseHook::install() {
	this->hookSig("Mouse", xorstr_("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 81 EC ? ? ? ? 0F 29 74 24 ? 0F 29 7C 24 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F0"), &Mouse_callback, reinterpret_cast<LPVOID*>(&_Mouse));

	hHook = SetWindowsHookEx(WH_MOUSE, HookProc, Utils::hModule, 0);
}