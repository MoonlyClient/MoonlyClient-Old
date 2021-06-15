#include "Keystroke.h"

void Keystroke::onRender() {
	LocalPlayer* player = gData.getClientInstance()->LocalPlayer();

	if (player == nullptr || !gData.getClientInstance()->MinecraftGame()->canUseKeys()) return;

	Vec2 windowSize = gData.getClientInstance()->getGuiData()->scaledRes;

	GameSettingsInput* input = gData.getClientInstance()->getGameSettingsInput();
	RenderUtils::drawKeystroke(*input->forwardKey, Vec2(32.f, windowSize.y - 74));
	RenderUtils::drawKeystroke(*input->leftKey, Vec2(10.f, windowSize.y - 52));
	RenderUtils::drawKeystroke(*input->backKey, Vec2(32.f, windowSize.y - 52));
	RenderUtils::drawKeystroke(*input->rightKey, Vec2(54.f, windowSize.y - 52));
	RenderUtils::drawKeystroke(*input->spaceBarKey, Vec2(10.f, windowSize.y - 30));

	RenderUtils::flushText();
}