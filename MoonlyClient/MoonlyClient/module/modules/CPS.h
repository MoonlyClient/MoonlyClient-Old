#pragma once

#include "../Module.h"
#include "../../data/GameData.h"
#include "../../utils/Utils.h"
#include "../../sdk/LocalPlayer.h"
#include "../../sdk/Color.h"

class CPS : public Module {
public:
	CPS() : Module::Module("CPS", "Visuals", "CPS") {
		this->isEnabled = true;
	};
	void onRender();
};