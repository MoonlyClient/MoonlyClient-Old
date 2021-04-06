#include "CPS.h"

void CPS::onRender() {
	LocalPlayer* player = gData.getClientInstance()->LocalPlayer();

	if (player == nullptr || !gData.getClientInstance()->MinecraftGame()->canUseKeys()) return;

	auto cpsText = "CPS: " + std::to_string(gData.cpsLeft) + " | " + std::to_string(gData.cpsRight);
	float boxWidth = RenderUtils::getTextWidth(cpsText, 1.f) + 8;
	float Ymodifier = 60;
	Vec4 boxPos = Vec4(5, Ymodifier, boxWidth, 10 + Ymodifier);

	RenderUtils::renderText(cpsText, Vec2(7, Ymodifier + 2), Color(255, 255, 255), 1.f, 1.f);

	RenderUtils::fillRectangle(boxPos, Color(0, 0, 0), .15f);
	RenderUtils::flushText();
}