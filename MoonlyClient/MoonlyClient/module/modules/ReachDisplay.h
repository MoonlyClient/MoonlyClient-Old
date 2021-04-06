#pragma once

#include "../Module.h"
#include "../../data/GameData.h"
#include "../../utils/Utils.h"
#include "../../sdk/LocalPlayer.h"
#include "../../sdk/Color.h"

class ReachDisplay : public Module {
public:
	ReachDisplay() : Module::Module("ReachDisplay", "Visuals", "ReachDisplay") {
		this->isEnabled = true;
	};
	void onRender();
};