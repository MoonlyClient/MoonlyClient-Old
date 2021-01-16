#pragma once
#include "../../Other/Module.h"

class Coords : public Module {
public:
	Coords() : Module::Module("Coords", "Visuals", "Info") {
		this->isEnabled = true;
	};
	void onRender();
};