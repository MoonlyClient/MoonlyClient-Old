#include "../ClientManager.h"
#include "../../Other/Utils.h"
#include "../../Other/Menu.h"
#include "MenuGUI.h"

void MenuGUI::onEnable() {
	if (!Minecraft::ClientInstance()->MinecraftGame()->canUseKeys()) {
		this->isEnabled = false;
		return;
	}

	Minecraft::ClientInstance()->releaseMouse();
}

void MenuGUI::onDisable() {
	Minecraft::ClientInstance()->grabMouse();
}

void MenuGUI::onRender() {
	LocalPlayer* player = Minecraft::ClientInstance()->LocalPlayer();

	if (player == nullptr) return;
	
	Minecraft::ClientInstance()->releaseMouse();

	Menu::render();
}