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
	ClientInstance* cachedInstance;
	C_GuiData* cachedGuiData;
	HIDController* cachedHIDController;
	GameMode* cachedGameMode;
	RakNetInstance* cachedRakNetInstance;

public:
	UINT64 getModuleBase() {
		return (UINT64)GetModuleHandle(NULL);
	}

	void setClientInstance(ClientInstance* obj) {
		if (obj != nullptr) cachedInstance = obj;
	}

	ClientInstance* getClientInstance() {
		return cachedInstance;
	}

	void setHIDController(HIDController* obj) {
		if (obj != nullptr) cachedHIDController = obj;
	}

	HIDController** getHIDController() {
		return &cachedHIDController;
	}

	void setGuiData(C_GuiData* obj) {
		if (obj != nullptr) cachedGuiData = obj;
	}

	C_GuiData* getGuiData() {
		return cachedGuiData;
	}

	void setGamemode(GameMode* GM) {
		if (GM != nullptr) cachedGameMode = GM;
	}

	GameMode* getGameMode() {
		return cachedGameMode;
	}

	void setRakNetInstance(RakNetInstance* RI) {
		cachedRakNetInstance = RI;
	}

	RakNetInstance* getRakNetInstance() {
		return cachedRakNetInstance;
	}
};

extern GameData gData;