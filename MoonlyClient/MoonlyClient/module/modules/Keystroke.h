#pragma once

#include "../Module.h"
#include "../../data/GameData.h"
#include "../../utils/Utils.h"
#include "../../sdk/LocalPlayer.h"
#include "../../sdk/Color.h"

class Keystroke : public Module {
public:
	Keystroke() : Module::Module("Keystroke", "Visuals", "Keystroke") {
		this->isEnabled = true;
	};
	void onRender();
};