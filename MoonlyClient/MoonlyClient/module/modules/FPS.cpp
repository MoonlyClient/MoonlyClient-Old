#include "FPS.h"

void FPS::onRender() {
	LocalPlayer* player = gData.getClientInstance()->LocalPlayer();

	if (player == nullptr || !gData.getClientInstance()->MinecraftGame()->canUseKeys()) return;

	auto fpsText = "FPS: " + std::to_string(gData.fps);
	float boxWidth = RenderUtils::getTextWidth(fpsText, 1.f) + 8;
	float Ymodifier = 50;
	Vec4 boxPos = Vec4(5, Ymodifier, boxWidth, 10 + Ymodifier);

	RenderUtils::renderText(fpsText, Vec2(7, Ymodifier + 2), Color(255, 255, 255), 1.f, 1.f);

	RenderUtils::fillRectangle(boxPos, Color(0, 0, 0), .15f);
	RenderUtils::flushText();
}