#pragma once

#include "../../include/xorstr.hpp"

#include "TextHolder.h"
#include "MinecraftUIRenderContext.h"
#include "Actor.h"
#include "LocalPlayer.h"
#include "GameMode.h"
#include "GuiData.h"
#include "GameSettingsInput.h"
#include "LoopbackPacketSender.h"

class MinecraftGame {
public:
	BitmapFont* getFont() {
		return *(BitmapFont**)((uintptr_t)(this) + 0x108);
	};

	bool canUseKeys() {
		return *(bool*)((uintptr_t)(this) + 0x300);
	}
};

struct PtrToGameSettings3 {

	char pad_0x0000[0x18];

	GameSettingsInput* settingsInput;
};

struct PtrToGameSettings2 {

	char pad_0x0000[0x148];

	PtrToGameSettings3* ptr;
};

struct PtrToGameSettings1 {

	char pad_0x0000[0x18];

	PtrToGameSettings2* ptr;
};

class ClientInstance {
public:
	char firstPad[0x90];  //0x0008

	MinecraftGame* minecraftGame;  //0x0098

	MinecraftGame* N0000080C;  //0x00A0

	MinecraftGame* N0000080D;  //0x00A8

	__int64* minecraft;  //0x00B0

	char pad_0x0068[0x8];  //0x00B8

	__int64* levelRenderer;  //0x00C0

	char pad_0x0078[0x8];  //0x00C8

	LoopbackPacketSender* loopbackPacketSender;  //0x00D0

	char pad_0x0088[0x18];  //0x00D8

	PtrToGameSettings1* ptr;  //0x00F0

	inline void grabMouse() {
		using GrabMouse = void* (__thiscall*) (ClientInstance*);
		static auto _GrabMouse = (GrabMouse)nullptr;

		if (_GrabMouse == nullptr) {
			_GrabMouse = (GrabMouse)(Utils::getVtable(this)[271]);
		}

		_GrabMouse(this);
	};

	inline void releaseMouse() {
		using ReleaseMouse = void* (__thiscall*) (ClientInstance*);
		static auto _ReleaseMouse = (ReleaseMouse)nullptr;

		if (_ReleaseMouse == nullptr)
			if (_ReleaseMouse == nullptr) {
				_ReleaseMouse = (ReleaseMouse)(Utils::getVtable(this)[272]);
			}

		_ReleaseMouse(this);
	};

	inline class LocalPlayer* LocalPlayer() {
		if (this != nullptr) {
			return *(class LocalPlayer**)((uintptr_t)(this) + 0x148);
		}
		else {
			return nullptr;
		}
	}

	inline class C_GuiData* getGuiData() {
		return *(class C_GuiData**)((uintptr_t)(this) + 0x4D0);
	}

	inline class MinecraftGame* MinecraftGame() {
		if (this != nullptr) {
			return *(class MinecraftGame**)((uintptr_t)(this) + 0xA8);
		}
		else {
			return nullptr;
		}
	}

	Vec2* getMousePos() {
		return *(Vec2**)((uintptr_t)(this) + 0x448);
	}

	inline GameSettingsInput* getGameSettingsInput() { return this->ptr->ptr->ptr->settingsInput; };
};