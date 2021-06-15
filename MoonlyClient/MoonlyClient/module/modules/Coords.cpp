#include "Coords.h"

void Coords::onRender() {
	LocalPlayer* player = gData.getClientInstance()->LocalPlayer();

	if (player == nullptr || !gData.getClientInstance()->MinecraftGame()->canUseKeys()) return;

	int x = (int)player->getPos()->x;
	int y = (int)player->getPos()->y;
	int z = (int)player->getPos()->z;

	float boxWidth = 80;
	float Ymodifier = 20;
	Vec4 boxPos = Vec4(5, Ymodifier, boxWidth,  30 + Ymodifier);

	RenderUtils::renderText("X: " + std::to_string(x), Vec2(7, Ymodifier + 2), Color(255, 255, 255), 1.f, 1.f);
	RenderUtils::renderText("Y: " + std::to_string(y), Vec2(7, Ymodifier + 2 + 10), Color(255, 255, 255), 1.f, 1.f);
	RenderUtils::renderText("Z: " + std::to_string(z), Vec2(7, Ymodifier + 2 + 10 + 10), Color(255, 255, 255), 1.f, 1.f);

	RenderUtils::drawCenteredText(Vec2(7 + 55, Ymodifier + 2 + 8), getDirection(player->bodyRot.y - 90), Color(255, 255, 255), 1.5f, 1.f);

	RenderUtils::fillRectangle(boxPos, Color(0, 0, 0), .15f);
	RenderUtils::flushText();
}