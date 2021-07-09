#include "MenuGUI.h"

bool isLeftClickDown = false;
bool shouldToggleLeftClick = false;

void MenuGUI::onEnable() {
	if (!gData.getClientInstance()->MinecraftGame()->canUseKeys()) {
		this->isEnabled = false;
		return;
	}

	gData.getClientInstance()->releaseMouse();
}

void MenuGUI::onDisable() {
	gData.getClientInstance()->grabMouse();
}

void MenuGUI::onMouseClickUpdate(int key, bool isDown) {
	switch (key) {
	case 1:
		isLeftClickDown = isDown;
		if (isDown)
			shouldToggleLeftClick = true;
		break;
	}
}

void MenuGUI::onRender() {
	LocalPlayer* player = gData.getClientInstance()->LocalPlayer();

	if (player == nullptr) return;
	
	gData.getClientInstance()->releaseMouse();

	RenderUtils::fillRectangle(Vec4(
		0,
		0,
		gData.getClientInstance()->getGuiData()->scaledRes.x,
		gData.getClientInstance()->getGuiData()->scaledRes.y),
		Color(0, 0, 0), 0.5f);

	auto guiData = gData.getClientInstance()->getGuiData1();

	if (guiData == nullptr) return;

	Vec2 mousePos = *gData.getClientInstance()->getMousePos();

	// Convert mouse pos
	{
		Vec2 windowSize = guiData->windowSize;
		Vec2 windowSizeReal = guiData->windowSizeReal;

		mousePos = mousePos.div(windowSizeReal);
		mousePos = mousePos.mult(windowSize);
	}

	float Xmodifier = guiData->widthGame / 6;
	float Ymodifier = 50;

	for (Module* module : moduleMgr.modules) {
		if (module->name == "MenuGUI" || module->name == "GUI" || module->name == "Zoom") continue;

		if (Ymodifier >= guiData->heightGame - (guiData->heightGame / 6)) {
			Ymodifier = 50;
			Xmodifier += 120;
		}

		float boxWidth = RenderUtils::getTextWidth(module->name, 1.f) + 8;
		Vec4 boxPos = Vec4(Xmodifier, Ymodifier, Xmodifier + boxWidth, Ymodifier + 20);

		if (boxPos.contains(mousePos) && shouldToggleLeftClick) {
			shouldToggleLeftClick = false;
			module->isEnabled = !module->isEnabled;
		}

		RenderUtils::renderText(module->name, Vec2(boxPos.x + 7, boxPos.y + 7), module->isEnabled ? Color(0, 255, 0) : Color(255, 0, 0), 1.f, boxPos.contains(mousePos) ? .5f : 1.f);
		RenderUtils::fillRectangle(boxPos, Color(0, 0, 0), 0);

		Ymodifier += 60;
	}
}