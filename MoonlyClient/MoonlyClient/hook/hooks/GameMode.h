#pragma once
#include "../../Other/Module.h"

class GameMode_Hook : public Hook {
public:
	void Install();
};

typedef void(__stdcall* GmTick)(GameMode* GM);
GmTick _GmTick;
GmTick _SmTick;

void GmTickCallback(GameMode* GM) {
	LocalPlayer* myPlayer = Minecraft::ClientInstance()->LocalPlayer();

	if (GM != nullptr && GM->Player != nullptr && myPlayer != nullptr) {
		C_GuiData* guiData = Minecraft::ClientInstance()->getGuiData();

		if (guiData != nullptr) {
			Minecraft::SetGuiData(guiData);
		}

		if (myPlayer == GM->Player) {
			Minecraft::SetGamemode(GM);

			for (auto Module : ClientManager::Modules) {
				if (Module->isEnabled) Module->onGmTick();
			}
		}
	}

	_GmTick(GM);
}

void SmTickCallback(GameMode* GM) {
	LocalPlayer* myPlayer = Minecraft::ClientInstance()->LocalPlayer();

	if (GM != nullptr && GM->Player != nullptr && myPlayer != nullptr) {
		C_GuiData* guiData = Minecraft::ClientInstance()->getGuiData();

		if (guiData != nullptr) {
			Minecraft::SetGuiData(guiData);
		}

		if (myPlayer == GM->Player) {
			Minecraft::SetGamemode(GM);

			for (auto Module : ClientManager::Modules) {
				if (Module->isEnabled) Module->onGmTick();
			}
		}
	}

	_SmTick(GM);
}

void GameMode_Hook::Install() {
	/* GameMode */
	{
		uintptr_t sigAddr = Utils::FindSig("8B 41 20 89 41 1C C3");
		if (sigAddr) {
			Utils::DebugLogOutput("Found address needed for the GameMode::tick Hook, Preparing Hook Install...");
			if (MH_CreateHook((void*)sigAddr, &GmTickCallback, reinterpret_cast<LPVOID*>(&_GmTick)) == MH_OK) {
				Utils::DebugLogOutput("Successfully created GameMode::tick Hook, Enabling Hook...");
				MH_EnableHook((void*)sigAddr);
			}
			else {
				Utils::DebugLogOutput("Failed to create GameMode::tick Hook!");
			}
		}
		else {
			Utils::DebugLogOutput("Failed to find address needed for the GameMode::tick Hook!");
		}
	}

	/* SurvivalMode */
	{
		uintptr_t sigAddr = Utils::FindSig("48 89 5C 24 ?? 48 89 74 24 ?? 55 57 41 56 48 8D 6C 24 B9 48 81 ?? ?? ?? ?? ?? 48 8B 05 0F F3 8A 01");
		if (sigAddr) {
			Utils::DebugLogOutput("Successfully found address needed for SurvivalMode::tick Hook, Preparing Hook Install...");
			Utils::DebugLogOutput("Address " + Utils::ptrToStr(sigAddr));
			if (MH_CreateHook((void*)sigAddr, &SmTickCallback, reinterpret_cast<LPVOID*>(&_SmTick)) == MH_OK) {
				Utils::DebugLogOutput("Successfully created SurvivalMode::tick Hook, Enabling Hook...");
				MH_EnableHook((void*)sigAddr);
			}
			else {
				Utils::DebugLogOutput("Failed to create SurvivalMode::tick Hook!");
			}
		}
		else {
			Utils::DebugLogOutput("Failed to find address needed for SurvivalMode::tick Hook!");
		}
	}
}