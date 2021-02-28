#pragma once
#include "../../Other/Module.h"

class Zoom : public Module {
public:
	Zoom() : Module::Module("Zoom", "Visual", "Zoom", 0x43) {
		this->isEnabled = false;
	};
	void onEnable();
	void onDisable();
	void onLoop();
};