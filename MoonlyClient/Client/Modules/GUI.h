#pragma once
#include "../../Other/Module.h"

class GUI : public Module {
public:
	GUI() : Module::Module("GUI", "Visuals", "GUI") {
		this->isEnabled = true;
	};
	void onRender();
private:
	int currentCategory = 0, currentModule = 0;
	bool selectedCategory = false, selectedModule = 0;
};