#pragma once

#include "../Hook.h"
#include "../../data/GameData.h"
#include "../../sdk/RakNetInstance.h"

class RakNetInstanceHook : public Hook {
public:
	void install();
};

typedef void(__stdcall* RakNetInstance_tick)(RakNetInstance* _this, __int64 a2, __int64 a3);
RakNetInstance_tick _RakNetInstance_tick;

void RakNetInstance_tick_callback(RakNetInstance* _this, __int64 a2, __int64 a3) {
	gData.setRakNetInstance(_this);

	_RakNetInstance_tick(_this, a2, a3);
}

void RakNetInstanceHook::install() {
	this->hookSig("RakNetInstance::tick", "48 89 5C 24 10 48 89 74 24 18 55 57 41 54 41 56 41 57 48 8D ?? 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 48 8B F9 45 33 E4 4C", &RakNetInstance_tick_callback, reinterpret_cast<LPVOID*>(&_RakNetInstance_tick));
}