#pragma once

#include "../Module.h"
#include "../../data/GameData.h"
#include "../../utils/Utils.h"
#include "../../sdk/LocalPlayer.h"
#include "../../sdk/Color.h"

class FPS : public Module {
public:
	FPS() : Module::Module("FPS", "Visuals", "FPS") {
		this->isEnabled = true;
	};
	void onRender();
};