#include "MenuGUI.h"

void MenuGUI::onEnable() {
	if (!gData.getClientInstance()->MinecraftGame()->canUseKeys()) {
		this->isEnabled = false;
		return;
	}

	//gData.getClientInstance()->releaseMouse();
}

void MenuGUI::onDisable() {
	//gData.getClientInstance()->grabMouse();
}

void MenuGUI::onRender() {
	LocalPlayer* player = gData.getClientInstance()->LocalPlayer();

	if (player == nullptr) return;
	
	//gData.getClientInstance()->releaseMouse();

	// ToDo : Make it cleaner
}