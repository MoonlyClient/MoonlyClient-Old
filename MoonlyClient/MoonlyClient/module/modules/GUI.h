#pragma once

#include "../Module.h"
#include "../../data/GameData.h"
#include "../../utils/Utils.h"
#include "../../sdk/LocalPlayer.h"
#include "../../sdk/Color.h"

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