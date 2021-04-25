#include "AutoSprint.h"

void AutoSprint::onLoop() {
	LocalPlayer* player = gData.getClientInstance()->LocalPlayer();

	if (player != nullptr) {
		GameSettingsInput* input = gData.getClientInstance()->getGameSettingsInput();

		if (player->velocity.magnitudexz() > 0.05f) {
			if (!Utils::isKeyDown((char)*input->sneakKey)) {
				if (Utils::isKeyDown((char)*input->forwardKey)) {
					player->setSprinting(true);
				}
			}
		}
	}
}