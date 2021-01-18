#pragma once
#include "../../Other/Module.h"

class CPS : public Module {
public:
	CPS() : Module::Module("CPS", "Visuals", "CPS") {
		this->isEnabled = true;
	};
	void onRender();
};