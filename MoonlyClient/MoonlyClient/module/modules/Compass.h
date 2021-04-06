#pragma once

#include "../Module.h"
#include "../../data/GameData.h"
#include "../../utils/Utils.h"
#include "../../sdk/LocalPlayer.h"
#include "../../sdk/Color.h"

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