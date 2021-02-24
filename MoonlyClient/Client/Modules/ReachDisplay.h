#pragma once
#include "../../Other/Module.h"

class Reach : public Module {
public:
	Reach() : Module::Module("ReachDisplay", "Visuals", "ReachDisplay") {
		this->isEnabled = true;
	};
	void onRender();
};