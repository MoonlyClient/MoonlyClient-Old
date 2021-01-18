#pragma once
#include "../../Other/Module.h"

class Keystroke : public Module {
public:
	Keystroke() : Module::Module("Keystroke", "Visuals", "Keystroke") {
		this->isEnabled = true;
	};
	void onRender();
};