#pragma once

#include "../Module.h"
#include "../../data/GameData.h"
#include "../../sdk/LocalPlayer.h"

class Zoom : public Module {
public:
	Zoom() : Module::Module("Zoom", "Visual", "Zoom", 0x43) {
		this->isEnabled = false;
	};
	void onEnable();
	void onDisable();
	void onLoop();
};