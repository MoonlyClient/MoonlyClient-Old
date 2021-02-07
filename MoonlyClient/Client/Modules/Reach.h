#pragma once
#include "../../Other/Module.h"

class Reach : public Module {
public:
	Reach() : Module::Module("Reach", "Visuals", "Reach") {
		this->isEnabled = true;
	};
	void onRender();
};