#pragma once
#include "../../Other/Module.h"

class Zoom : public Module {
public:
	Zoom() : Module::Module("Zoom", "Visual", "Zoom") {
		this->isEnabled = true;
	};
	void onEnable();
	void onDisable();
};