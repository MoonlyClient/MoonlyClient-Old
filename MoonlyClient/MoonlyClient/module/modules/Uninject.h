#pragma once

#include "../Module.h"

class Uninject : public Module {
public:
	Uninject() : Module::Module("Uninject", "Other", "Uninject the Client from the Game") {};
	void onEnable();
};