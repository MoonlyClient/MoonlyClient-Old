#pragma once
#include "../../Other/Module.h"
#include "../../SDK/Classes/RakNetInstance.h"
#include "../ClientManager.h"

struct SkinData {
public:
	char pad_0x0000[0x4];     //0x0000
	unsigned int SkinWidth;   //0x0004
	unsigned int SkinHeight;  //0x0008
	char pad_0x000C[0x4];     //0x000C
	void* skinData;           //0x0010
	size_t skinSize;          //0x0018
};

struct CoolSkinData {
	TextHolder unknown;
	TextHolder unknown2;
	TextHolder skinResourcePatch;  // 0x040
	TextHolder geometryName; // 0x060 "geometry.humanoid.custom"
	unsigned char gap2[0x40];      // 0x080
	void* startAnimatedFrames;     // 0x0C0
	void* endAnimatedFrames;       // 0x0C8
	unsigned char gap3[0x8];      // 0x0D0
	TextHolder geometryData;		// 0x0D8
	TextHolder skinAnimationData;  // 0x0F8
	unsigned char gap4[0x20];      // 0x118
	bool isPremiumSkin;            // 0x138
	bool isPersonaSkin;
	bool isCapeOnClassicSkin;
	void* startPersonaPieces;
	void* endPersonaPieces;
	unsigned char gap5[0x8];  // 0x150
	TextHolder armSize;       // 0x158
	unsigned char gap6[0x8];  // 0x178
	void* startPieces;
};

class RakNetInstance_Hook : public Hook {
public:
	void Install();
};

typedef void(__stdcall* RakNetInstance_tick)(RakNetInstance* _this, __int64 a2, __int64 a3);
RakNetInstance_tick _RakNetInstance_tick;

void RakNetInstance_tick_Callback(RakNetInstance* _this, __int64 a2, __int64 a3) {
	Minecraft::SetRakNetInstance(_this);
	_RakNetInstance_tick(_this, a2, a3);
}

typedef __int64(__stdcall* ConnectionRequest_create)(__int64, __int64, void*, TextHolder*, TextHolder*, __int64, TextHolder*, SkinData*, __int64, CoolSkinData*, TextHolder*, int, int, int, TextHolder*, bool, TextHolder*, __int64, TextHolder*, TextHolder*, bool, TextHolder*, TextHolder*, TextHolder*);
ConnectionRequest_create _ConnectionRequest_create;

__int64 ConnectionRequest_createCallback(__int64 _this, __int64 privateKeyManager, void* a3, TextHolder* selfSignedId, TextHolder* serverAddress, __int64 clientRandomId, TextHolder* skinId, SkinData* skinData, __int64 capeData, CoolSkinData* coolSkinStuff, TextHolder* deviceId, int inputMode, int uiProfile, int guiScale, TextHolder* languageCode, bool sendEduModeParams, TextHolder* tenantId, __int64 unused, TextHolder* platformUserId, TextHolder* thirdPartyName, bool thirdPartyNameOnly, TextHolder* platformOnlineId, TextHolder* platformOfflineId, TextHolder* capeId) {
	Utils::DebugLogOutput("Got ConnectionRequest call, serverAddress : " + *serverAddress->getText());

	return _ConnectionRequest_create(_this, privateKeyManager, a3, selfSignedId, serverAddress, clientRandomId, skinId, skinData, capeData, coolSkinStuff, deviceId, inputMode, uiProfile, guiScale, languageCode, sendEduModeParams, tenantId, unused, platformUserId, thirdPartyName, thirdPartyNameOnly, platformOnlineId, platformOfflineId, capeId);
}

void RakNetInstance_Hook::Install() {
	uintptr_t sigAddr = Utils::FindSig("48 89 5C 24 10 48 89 74 24 18 55 57 41 54 41 56 41 57 48 8D ?? 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 48 8B F9 45 33 E4 4C");
	if (sigAddr) {
		Utils::DebugLogOutput("Successfully found address needed for the RakNetInstance_tick Hook, Preparing Hook install now...");
		if (MH_CreateHook((void*)sigAddr, &RakNetInstance_tick_Callback, reinterpret_cast<LPVOID*>(&_RakNetInstance_tick)) == MH_OK) {
			Utils::DebugLogOutput("Successfully created RakNetInstance_tick Hook, Installing hook now...");
			MH_EnableHook((void*)sigAddr);
		}
		else {
			Utils::DebugLogOutput("Failed to create RakNetInstance_tick Hook!");
		}
	}
	else {
		Utils::DebugLogOutput("Failed to find address needed for the RakNetInstance_tick Hook!");
	}

	uintptr_t sigAddr2 = Utils::FindSig("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 C7 45 ?? FE FF FF FF 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 49 8B D9 4D 8B F8");
	if (sigAddr2) {
		Utils::DebugLogOutput("Successfully found address needed for the ConnectionRequest_create Hook, Preparing Hook install now...");
		if (MH_CreateHook((void*)sigAddr2, &ConnectionRequest_createCallback, reinterpret_cast<LPVOID*>(&_ConnectionRequest_create)) == MH_OK) {
			Utils::DebugLogOutput("Successfully created ConnectionRequest_create Hook, Installing hook now...");
			MH_EnableHook((void*)sigAddr2);
		}
		else {
			Utils::DebugLogOutput("Failed to create ConnectionRequest_create Hook!");
		}
	}
	else {
		Utils::DebugLogOutput("Failed to find address needed for the ConnectionRequest_create Hook!");
	}
}