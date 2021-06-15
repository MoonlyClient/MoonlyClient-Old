#pragma once

#include "../Hook.h"
#include "../../data/GameData.h"
#include "../../module/ModuleManager.h"
#include "../../sdk/ClientInstance.h"

class ClientInstanceHook : public Hook {
public:
	void install();
};

typedef void(__stdcall* ClientInstance_tick)(ClientInstance* _this, void* a1);
ClientInstance_tick _ClientInstance_tick;

void tick_callback(ClientInstance* _this, void* a1) {
	gData.setClientInstance(_this);

	_ClientInstance_tick(_this, a1);
}

typedef float(__stdcall* getGamme)(uintptr_t*);
getGamme _getGamma;

float getGamma_callback(uintptr_t* a1) {
	Module* nightvision = moduleMgr.getModuleByName("NightVision");

	if (nightvision != nullptr && nightvision->isEnabled) {
		return 25.f;
	}

	return _getGamma(a1);
}

typedef void(_stdcall* Actor_attack)(Actor*, Actor&);
Actor_attack _Actor_attack;

void Actor_attack_callback(Actor* _this, Actor& actor) {
	Utils::DebugLogOutput("Actor::attack called");

	gData.lastReach = _this->getPos()->distance(*actor.getPos());

	return _Actor_attack(_this, actor);
}

typedef float(_stdcall* LevelRendererPlayer_getFov)(__int64, float, bool);
LevelRendererPlayer_getFov _LevelRendererPlayer_getFov;

float LevelRendererPlayer_getFov_callback(__int64 _this, float a2, bool a3) {
	Module* zoom = moduleMgr.getModuleByName("Zoom");
	
	if (zoom != nullptr && zoom->isEnabled) {
		return 15.f;
	}
		
	return _LevelRendererPlayer_getFov(_this, a2, a3);
}

void ClientInstanceHook::install() {
	this->hookSig("ClientInstance::tick", xorstr_("48 89 5C 24 ?? 48 89 74 24 ?? 57 48 83 EC ?? 48 8B F9 48 8B 01"), &tick_callback, reinterpret_cast<LPVOID*>(&_ClientInstance_tick));

	this->hookSig("getGamma", xorstr_("48 83 EC ? 80 B9 ? ? ? ? ? 48 8D 54 24 ? 74 ? 41 B8 ? ? ? ? E8 ? ? ? ? 48 8B 10 48 85 D2 74 ? 48 8B 42 ? 48 8B 88 ? ? ? ? 48 85 C9 74 ? E8 ? ? ? ? 48 83 C4 ? C3 F3 0F 10 42"), &getGamma_callback, reinterpret_cast<LPVOID*>(&_getGamma));

	this->hookSig("LevelRendererPlayer::getFov", xorstr_("40 53 48 83 EC 70 0F 29 7C 24 ? 44 0F 29 4C 24 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? F3 0F 10 3D ? ? ? ? 44 0F"), &LevelRendererPlayer_getFov_callback, reinterpret_cast<LPVOID*>(&_LevelRendererPlayer_getFov));
	
	// LocalPlayer::attack offset : 109
}
