#include "Menu.h"
#include "Utils.h"
#include "../SDK/Minecraft.h"
#include "../Client/ClientManager.h"

#include <Windows.h>
#include "Module.h"
#include "../SDK/Classes/GuiData.h"

bool wasLeftClickDown = false;
bool isLeftClickDown = false;
bool isRightClickDown = false;
bool shouldToggleLeftClick = false;
bool shouldToggleRightClick = false;

void Menu::DrawAll() {
	auto guiData = Minecraft::GuiData();

	if (guiData == nullptr) return;

	Vec2 mousePos = *Minecraft::ClientInstance()->getMousePos();

	// Convert mouse pos
	{
		Vec2 windowSize = guiData->windowSize;
		Vec2 windowSizeReal = guiData->windowSizeReal;

		mousePos = mousePos.div(windowSizeReal);
		mousePos = mousePos.mult(windowSize);
	}

	float Xmodifier = guiData->widthGame / 6;
	float Ymodifier = 50;

	for (Module* module : ClientManager::Modules) {
		if (module->name == "MenuGUI" || module->name == "GUI" || module->name == "DiscordRPC") continue;

		if (Ymodifier >= guiData->heightGame - (guiData->heightGame / 6)) {
			Ymodifier = 50;
			Xmodifier += 120;
		}

		float boxWidth = RenderUtils::GetTextWidth(module->name, 1.f) + 8;
		Vec4 boxPos = Vec4(Xmodifier, Ymodifier, Xmodifier + boxWidth, Ymodifier + 20);

		if (!wasLeftClickDown && isLeftClickDown && boxPos.contains(mousePos)) {
			module->isEnabled = !module->isEnabled;
		}

		RenderUtils::RenderText(module->name, Vec2(boxPos.x + 7, boxPos.y + 7), module->isEnabled ? MC_Colour(0, 255, 0) : MC_Colour(255, 0, 0), 1.f, boxPos.contains(mousePos) ? .5f : 1.f);
		RenderUtils::FillRectangle(boxPos, MC_Colour(0, 0, 0), 0);

		Ymodifier += 60;
	}

	RenderUtils::FlushText();
}

void Menu::render() {

	RenderUtils::FillRectangle(Vec4(
		0,
		0,
		Minecraft::ClientInstance()->getGuiData()->widthGame,
		Minecraft::ClientInstance()->getGuiData()->heightGame),
		MC_Colour(0, 0, 0), 0.5f);

	Menu::DrawAll();

	shouldToggleLeftClick = false;
	shouldToggleRightClick = false;

	RenderUtils::FlushText();
}

void Menu::onMouseClickUpdate(int key, bool isDown) {
	switch (key) {
	case 0:  // Left Click
		if (wasLeftClickDown && !isDown)
			wasLeftClickDown = true;
		else if (!wasLeftClickDown && isDown)
			wasLeftClickDown = false;

		isLeftClickDown = isDown;
		shouldToggleLeftClick = isDown;
		break;
	case 1:  // Right Click
		isRightClickDown = isDown;
		shouldToggleRightClick = isDown;
		break;
	}
}

void Menu::onKeyUpdate(int key, bool isDown) {
	Module* menu = ClientManager::GetModuleByName("MenuGUI");

	if (menu == nullptr) {
		return;
	}

	if (!isDown)
		return;

	if (!menu->isEnabled) {
		return;
	}

	switch (key) {
	case VK_ESCAPE:
		menu->isEnabled = false;
		return;
	}
}

void Menu::onLoadConfig(void* confVoid) {
	// ToDo
}

void Menu::onSaveConfig(void* confVoid) {
	// ToDo
}
