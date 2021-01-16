#pragma once
#include "../../Other/Module.h"

class DiscordRPC : public Module {
public:
	DiscordRPC() : Module::Module("DiscordRPC", "Other", "DiscordRPC") {
		this->isEnabled = true;
	};
	void onLoop();
};