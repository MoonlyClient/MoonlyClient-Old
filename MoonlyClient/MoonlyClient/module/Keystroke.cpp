#include "../ClientManager.h"
#include "../../Other/Utils.h"
#include "Keystroke.h"

void Keystroke::onRender() {
	LocalPlayer* player = Minecraft::ClientInstance()->LocalPlayer();

	if (player == nullptr || !Minecraft::ClientInstance()->MinecraftGame()->canUseKeys()) return;

	Vec2 windowSize = Minecraft::ClientInstance()->getGuiData()->windowSize;

	GameSettingsInput* input = Minecraft::ClientInstance()->getGameSettingsInput();
	RenderUtils::DrawKeystroke(*input->forwardKey, Vec2(32.f, windowSize.y - 74));
	RenderUtils::DrawKeystroke(*input->leftKey, Vec2(10.f, windowSize.y - 52));
	RenderUtils::DrawKeystroke(*input->backKey, Vec2(32.f, windowSize.y - 52));
	RenderUtils::DrawKeystroke(*input->rightKey, Vec2(54.f, windowSize.y - 52));
	RenderUtils::DrawKeystroke(*input->spaceBarKey, Vec2(10.f, windowSize.y - 30));

	RenderUtils::FlushText();
}