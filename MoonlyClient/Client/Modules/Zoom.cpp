#include "Zoom.h"

void Zoom::onEnable() {

}

void Zoom::onDisable() {

}

void Zoom::onLoop() {
	LocalPlayer* Player = Minecraft::ClientInstance()->LocalPlayer();
	MinecraftGame* mcGame = Minecraft::ClientInstance()->MinecraftGame();

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