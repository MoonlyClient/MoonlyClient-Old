#pragma once
#include "../../Other/Module.h"

class FPS : public Module {
public:
	FPS() : Module::Module("FPS", "Visuals", "FPS") {
		this->isEnabled = true;
	};
	void onRender();
};