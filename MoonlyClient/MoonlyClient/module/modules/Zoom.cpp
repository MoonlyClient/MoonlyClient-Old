#include "Zoom.h"

void Zoom::onEnable() {
	LocalPlayer* player = gData.getClientInstance()->LocalPlayer();

	if (player == nullptr)
		return;

	player->setFieldOfViewModifier(0.3f);
}

void Zoom::onDisable() {
	LocalPlayer* player = gData.getClientInstance()->LocalPlayer();

	if (player == nullptr)
		return;

	player->setFieldOfViewModifier(1);
}

void Zoom::onLoop() {
	LocalPlayer* player = gData.getClientInstance()->LocalPlayer();
	MinecraftGame* mcGame = gData.getClientInstance()->MinecraftGame();

	if (Utils::isKeyDown(this->key)) {
		if (player != nullptr && mcGame != nullptr && mcGame->canUseKeys()) {
			this->isEnabled = true;
			this->onEnable();
		}
		else {
			if (this->isEnabled) {
				this->isEnabled = false;
				this->onDisable();
			}
		}
	}
	else {
		if (this->isEnabled) {
			this->isEnabled = false;
			this->onDisable();
		}
	}
}