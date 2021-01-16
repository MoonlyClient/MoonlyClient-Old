#pragma once
#include "../../Other/Module.h"

class GUI : public Module {
public:
	GUI() : Module::Module("GUI", "Visuals", "GUI", VK_TAB) {
		this->isEnabled = true;
	};
	void onRender();
	void onKey(uint64_t key, bool isDown, bool* cancel);
private:
	int currentCategory = 0, currentModule = 0;
	bool selectedCategory = false, selectedModule = 0;
};