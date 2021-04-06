#include "AutoSprint.h"

void AutoSprint::onGmTick() {
	LocalPlayer* Player = gData.getClientInstance()->LocalPlayer();

	if (Player != nullptr) {
		GameSettingsInput* input = gData.getClientInstance()->getGameSettingsInput();

		if (Player->velocity.magnitudexz() > 0.05f) {
			if (!Utils::isKeyDown((char)*input->sneakKey)) {
				if (Utils::isKeyDown((char)*input->forwardKey)) {
					Player->setSprinting(true);
				}
			}
		}
	}
}