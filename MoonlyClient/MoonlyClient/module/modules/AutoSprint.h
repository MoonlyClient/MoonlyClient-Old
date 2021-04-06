#pragma once

#include "../Module.h"
#include "../../data/GameData.h"
#include "../../utils/Utils.h"
#include "../../sdk/LocalPlayer.h"

class AutoSprint : public Module {
public:
	AutoSprint() : Module::Module("AutoSprint", "Movement", "Automatically sprint forward") {
		this->isEnabled = true;
	};
	void onGmTick();
};