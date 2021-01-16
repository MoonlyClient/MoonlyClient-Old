#pragma once
#include "../../Other/Module.h"

class GameMode_Hook : public Hook {
public:
	void Install();
};

typedef void(__fastcall* GmTick)(GameMode* GM);
GmTick _GmTick;
GmTick _SmTick;

void GmTickCallback(GameMode* GM) {
	LocalPlayer* myPlayer = Minecraft::ClientInstance()->LocalPlayer();
	if (GM != nullptr && GM->Player != nullptr && myPlayer != nullptr) {
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
		if (myPlayer == GM->Player) {
			Minecraft::SetGamemode(GM);
			for (auto Module : ClientManager::Modules) {
				if (Module->isEnabled) Module->onGmTick();
			}
		}
	}
	_SmTick(GM);
}

typedef void(__fastcall* StartDestroyBlock)(GameMode*, Vec3_i*, uint8_t, void*, void*);
StartDestroyBlock _StartDestroyBlock;

void DestroyBlockCallback(GameMode* GM, Vec3_i* blockPos, uint8_t blockFace, void* a4, void* a5) {
	for (auto Module : ClientManager::Modules) {
		if (Module->isEnabled) Module->onStartDestroyBlock(GM, blockPos, blockFace);
	}
	_StartDestroyBlock(GM, blockPos, blockFace, a4, a5);
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
		uintptr_t startDestroyBlockAddr = Utils::FindSig("40 55 53 56 57 41 56 41 57 48 8D 6C 24 D1 48 81 EC C8 00 00 00 0F");
		if (startDestroyBlockAddr) {
			Utils::DebugLogOutput("Successfully found address needed for the GameMode::onStartDestroyBlock Hook, Preparing Hook Install...");
			if (MH_CreateHook((void*)startDestroyBlockAddr, &DestroyBlockCallback, reinterpret_cast<LPVOID*>(&_StartDestroyBlock)) == MH_OK) {
				Utils::DebugLogOutput("Successfully created GameMode::onStartDestroyBlock Hook, Enabling Hook...");
				MH_EnableHook((void*)startDestroyBlockAddr);
			}
			else {
				Utils::DebugLogOutput("Failed to create GameMode::onStartDestroyBlock Hook!");
			}
		}
		else {
			Utils::DebugLogOutput("Failed to find address needed for GameMode::onStartDestroyBlock Hook!");
		}
	}
	/* SurvivalMode */
	{
		uintptr_t sigAddr = Utils::FindSig("48 89 5C 24 ?? 48 89 74 24 ?? 55 57 41 56 48 8D 6C 24 B9 48 81 ?? ?? ?? ?? ?? 48 8B 05 0F F3 8A 01");
		if (sigAddr) {
			Utils::DebugLogOutput("Successfully found address needed for SurvivalMode::tick Hook, Preparing Hook Install...");
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