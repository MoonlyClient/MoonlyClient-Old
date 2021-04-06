#pragma once
#include "../../Other/Module.h"

class Compass : public Module {
private:
	float opacity = 0.5;
	int range = 90;
public:
	Compass() : Module::Module("Compass", "Visuals", "Compass") {
		this->isEnabled = true;
	};
	void onRender();
};