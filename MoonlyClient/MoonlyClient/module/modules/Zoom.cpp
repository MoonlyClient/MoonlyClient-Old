#include "Zoom.h"

void Zoom::onEnable() {

}

void Zoom::onDisable() {

}

void Zoom::onLoop() {
	LocalPlayer* Player = gData.getClientInstance()->LocalPlayer();
	MinecraftGame* mcGame = gData.getClientInstance()->MinecraftGame();

	if (Utils::isKeyDown(this->key)) {
		if (Player != nullptr && mcGame != nullptr && mcGame->canUseKeys()) {
			this->isEnabled = true;
		}
		else {
			if (this->isEnabled)
				this->isEnabled = false;
		}
	}
	else {
		if (this->isEnabled)
			this->isEnabled = false;
	}
}