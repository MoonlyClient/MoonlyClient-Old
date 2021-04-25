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
GmTick _SmTick;

void GmTick_callback(GameMode* GM) {
	Utils::DebugLogOutput("GameMode::tick called lmao");

	LocalPlayer* Player = gData.getClientInstance()->LocalPlayer();

	if (GM != nullptr && GM->Player != nullptr && Player != nullptr) {
		C_GuiData* guiData = gData.getClientInstance()->getGuiData();

		if (guiData != nullptr) {
			gData.setGuiData(guiData);
		}

		if (Player == GM->Player) {
			gData.setGamemode(GM);

			for (auto Module : moduleMgr.modules) {
				if (Module->isEnabled)
					Module->onGmTick();
			}
		}
	}

	_GmTick(GM);
}

void SmTick_callback(GameMode* GM) {
	Utils::DebugLogOutput("SurvivalGameMode::tick called lmao");

	LocalPlayer* Player = gData.getClientInstance()->LocalPlayer();

	if (GM != nullptr && GM->Player != nullptr && Player != nullptr) {
		C_GuiData* guiData = gData.getClientInstance()->getGuiData();

		if (guiData != nullptr) {
			gData.setGuiData(guiData);
		}

		if (Player == GM->Player) {
			gData.setGamemode(GM);

			for (auto Module : moduleMgr.modules) {
				if (Module->isEnabled)
					Module->onGmTick();
			}
		}
	}

	_SmTick(GM);
}

void GameModeHook::install() {
	this->hookSig("GameMode::tick", "40 53 48 83 EC 20 48 8B D9 48 8B 89 ? ? ? ? 48 8B 01 FF 50 ? 8B 43 ?", &GmTick_callback, reinterpret_cast<LPVOID*>(&_GmTick));

	//this->hookSig("SurvivalMode::tick", "48 89 5C 24 ?? 48 89 74 24 ?? 55 57 41 56 48 8D 6C 24 B9 48 81 ?? ?? ?? ?? ?? 48 8B 05 0F F3 8A 01", &SmTick_callback, reinterpret_cast<LPVOID*>(&_SmTick));
}