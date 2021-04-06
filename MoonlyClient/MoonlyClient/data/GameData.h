#pragma once

#include<Windows.h>

#include "../sdk/ClientInstance.h"
#include "../sdk/RakNetInstance.h"
#include "../sdk/GuiData.h"
#include "../sdk/HIDController.h"

class GameData {
public:
	int frameCount;
	int fps;
	int cpsLeft;
	int leftclickCount;
	int cpsRight;
	int rightclickCount;
	float lastReach;
private:
	ClientInstance* CachedInstance;
	C_GuiData* CachedGuiData;
	HIDController* CachedHIDController;
	GameMode* CachedGameMode;
	RakNetInstance* CachedRakNetInstance;
public:
	UINT64 ModuleBase() {
		return (UINT64)GetModuleHandle(NULL);
	}

	void SetClientInstance(ClientInstance* obj) {
		if (obj != nullptr) CachedInstance = obj;
	}

	ClientInstance* ClientInstance() {
		return CachedInstance;
	}

	void SetHIDController(HIDController* obj) {
		if (obj != nullptr) CachedHIDController = obj;
	}

	HIDController** HIDController() {
		return &CachedHIDController;
	}

	void SetGuiData(C_GuiData* obj) {
		if (obj != nullptr) CachedGuiData = obj;
	}

	C_GuiData* GuiData() {
		return CachedGuiData;
	}

	void SetGamemode(GameMode* GM) {
		if (GM != nullptr) CachedGameMode = GM;
	}

	GameMode* GameMode() {
		return CachedGameMode;
	}

	void SetRakNetInstance(RakNetInstance* RI) {
		CachedRakNetInstance = RI;
	}

	RakNetInstance* RakNetInstance() {
		return CachedRakNetInstance;
	}
};

extern GameData gData;