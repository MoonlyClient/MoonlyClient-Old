#pragma once
#include "../../Other/Module.h"

class NightVision : public Module {
public:
	NightVision() : Module::Module("NightVision", "Visual", "NightVision") {
		this->isEnabled = true;
	};
	void onEnable();
	void onDisable();
};