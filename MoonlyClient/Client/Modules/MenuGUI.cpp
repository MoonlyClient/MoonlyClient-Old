#include "../ClientManager.h"
#include "../../Other/Utils.h"
#include "MenuGUI.h"

void MenuGUI::onEnable() {
	//Minecraft::ClientInstance()->releaseMouse();
}

void MenuGUI::onDisable() {
	//Minecraft::ClientInstance()->grabMouse();
}

void MenuGUI::onRender() {
	LocalPlayer* player = Minecraft::ClientInstance()->LocalPlayer();

	if (player == nullptr || !Minecraft::ClientInstance()->MinecraftGame()->canUseKeys()) return;

	//Minecraft::ClientInstance()->releaseMouse();
}