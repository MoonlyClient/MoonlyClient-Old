#pragma once
#include "../../Other/Module.h"

class MenuGUI : public Module {
public:
	MenuGUI() : Module::Module("MenuGUI", "Visuals", "MenuGUI", 0x46) {
		this->isEnabled = false;
	};
	void onEnable();
	void onDisable();
	void onRender();
};