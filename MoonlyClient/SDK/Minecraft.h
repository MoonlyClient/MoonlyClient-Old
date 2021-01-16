#pragma once
#include "../Other/Utils.h"

#include "Classes/ClientInstance.h"
#include "Classes/RakNetInstance.h"
#include "Classes/GuiData.h"

class Minecraft {
public:
	static int frameCount;
	static int fps;
	static int cpsLeft;
	static int leftclickCount;
	static int cpsRight;
	static int rightclickCount;
private:
	static ClientInstance* CachedInstance;
	static C_GuiData* CachedGuiData;
	static GameMode* CachedGameMode;
	static RakNetInstance* CachedRakNetInstance;
public:
	static UINT64 ModuleBase() {
		return (UINT64)GetModuleHandle(NULL);
	}

	static void SetClientInstance(ClientInstance* obj) {
		if (obj != nullptr) CachedInstance = obj;
	}

	static ClientInstance* ClientInstance() {
		return CachedInstance;
	}

	static void SetGuiData(C_GuiData* obj) {
		if (obj != nullptr) CachedGuiData = obj;
	}

	static C_GuiData* GuiData() {
		return CachedGuiData;
	}

	static void SetGamemode(GameMode* GM) {
		if (GM != nullptr) CachedGameMode = GM;
	}

	static GameMode* GameMode() {
		return CachedGameMode;
	}

	static void SetRakNetInstance(RakNetInstance* RI) {
		CachedRakNetInstance = RI;
	}

	static RakNetInstance* RakNetInstance() {
		return CachedRakNetInstance;
	}
};