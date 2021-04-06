#include "ReachDisplay.h"

void ReachDisplay::onRender() {
	LocalPlayer* player = gData.getClientInstance()->LocalPlayer();

	if (player == nullptr || !gData.getClientInstance()->MinecraftGame()->canUseKeys()) return;

	char str[40];
	sprintf(str, "%.2f", gData.lastReach);
	auto reachText = "Reach: " + (std::string) str;

	float boxWidth = RenderUtils::getTextWidth(reachText, 1.f) + 8;
	float Ymodifier = 70;
	Vec4 boxPos = Vec4(5, Ymodifier, boxWidth, 10 + Ymodifier);

	RenderUtils::renderText(reachText, Vec2(7, Ymodifier + 2), Color(255, 255, 255), 1.f, 1.f);

	RenderUtils::fillRectangle(boxPos, Color(0, 0, 0), .15f);
	RenderUtils::flushText();
}