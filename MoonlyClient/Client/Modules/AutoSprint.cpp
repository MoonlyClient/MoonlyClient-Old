#include "AutoSprint.h"

void AutoSprint::onGmTick() {
	LocalPlayer* Player = Minecraft::ClientInstance()->LocalPlayer();

	if (Player != nullptr) {
		GameSettingsInput* input = Minecraft::ClientInstance()->getGameSettingsInput();

		if (Player->velocity.magnitudexz() > 0.05f) {
			if (Utils::isKeyDown((char)*input->forwardKey)) {
				Player->setSprinting(true);
			}
		}
	}
}