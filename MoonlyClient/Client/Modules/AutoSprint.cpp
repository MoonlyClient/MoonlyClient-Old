#include "AutoSprint.h"

void AutoSprint::onGmTick() {
	LocalPlayer* Player = Minecraft::ClientInstance()->LocalPlayer();

	if (Player != nullptr) {
		if (Player->velocity.magnitudexz() > 0.05f) {
			Player->setSprinting(true);
		}
	}
}