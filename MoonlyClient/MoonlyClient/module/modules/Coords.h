#pragma once

#include "../Module.h"
#include "../../data/GameData.h"
#include "../../utils/Utils.h"
#include "../../sdk/LocalPlayer.h"
#include "../../sdk/Color.h"

class Coords : public Module {
public:
	Coords() : Module::Module("Coords", "Visuals", "FPS") {
		this->isEnabled = true;
	};
	void onRender();
};