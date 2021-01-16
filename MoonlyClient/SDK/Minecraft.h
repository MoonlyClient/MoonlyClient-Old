#pragma once
#include "../Other/Utils.h"

#include "Classes/ClientInstance.h"
#include "Classes/RakNetInstance.h"

class Minecraft {
private:
	static ClientInstance* CachedInstance;
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