#pragma once

#include "../Hook.h"
#include "../../data/GameData.h"
#include "../../module/ModuleManager.h"
#include "../../sdk/GameMode.h"

class GameModeHook : public Hook {
public:
	void install();
};

typedef void(__stdcall* GmTick)(GameMode* GM);
GmTick _GmTick;

void GmTick_callback(GameMode* GM) {
	LocalPlayer* player = gData.getClientInstance()->LocalPlayer();

	if (GM != nullptr && GM->Player != nullptr && player != nullptr) {
		C_GuiData* guiData = gData.getClientInstance()->getGuiData();

		if (guiData != nullptr) {
			gData.setGuiData(guiData);
		}

		if (player == GM->Player) {
			gData.setGamemode(GM);

			for (auto Module : moduleMgr.modules) {
				if (Module->isEnabled)
					Module->onGmTick();
			}
		}
	}

	_GmTick(GM);
}

typedef void(_stdcall* GameMode_attack)(GameMode*, Actor*);
GameMode_attack _GameMode_attack;

void GameMode_attack_callback(GameMode* _this, Actor* actor) {
	Utils::DebugLogOutput("Actor::attack called");

	gData.lastReach = _this->Player->getPos()->distance(*actor->getPos());

	return _GameMode_attack(_this, actor);
}

void GameModeHook::install() {
	uintptr_t sigAddr = Utils::FindSig(xorstr_("48 8D 05 ? ? ? ? 48 8B D9 48 89 01 8B FA 48 8B 89 ? ? ? ? 48 85 C9 74 ? 48 8B 01 BA ? ? ? ? FF 10 48 8B 8B"));

	if (!sigAddr)
		return;

	int offset = *reinterpret_cast<int*>(sigAddr + 3);
	uintptr_t** vtable = reinterpret_cast<uintptr_t**>(sigAddr + offset + 7);

	this->hookAddr("GameMode::tick", (void*)vtable[10], &GmTick_callback, (LPVOID*)&_GmTick);
	this->hookAddr("GameMode::attack", (void*)vtable[14], &GameMode_attack_callback, (LPVOID*)&_GameMode_attack);
}