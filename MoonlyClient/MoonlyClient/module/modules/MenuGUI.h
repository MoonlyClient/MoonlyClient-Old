#pragma once

#include "../Module.h"
#include "../ModuleManager.h"
#include "../../data/GameData.h"
#include "../../utils/Utils.h"
#include "../../sdk/LocalPlayer.h"
#include "../../sdk/Color.h"

class MenuGUI : public Module {
public:
	MenuGUI() : Module::Module("MenuGUI", "Visuals", "MenuGUI", 0x46) {
		this->isEnabled = false;
	};
	void onEnable();
	void onDisable();
	void onRender();
	void onMouseClickUpdate(int, bool);
};