#include "../ClientManager.h"
#include "../../Other/Utils.h"
#include "../../Other/MathUtils.h"
#include "Coords.h"

void Coords::onRender() {
	LocalPlayer* player = Minecraft::ClientInstance()->LocalPlayer();

	if (player == nullptr || !Minecraft::ClientInstance()->MinecraftGame()->canUseKeys()) return;

	int x = (int)player->getPos()->x;
	int y = (int)player->getPos()->y;
	int z = (int)player->getPos()->z;

	float boxWidth = 80;
	float Ymodifier = 20;
	Vec4 boxPos = Vec4(5, Ymodifier, boxWidth,  30 + Ymodifier);

	RenderUtils::RenderText("X: " + std::to_string(x), Vec2(7, Ymodifier + 2), MC_Colour(255, 255, 255), 1.f, 1.f);
	RenderUtils::RenderText("Y: " + std::to_string(y), Vec2(7, Ymodifier + 2 + 10), MC_Colour(255, 255, 255), 1.f, 1.f);
	RenderUtils::RenderText("Z: " + std::to_string(z), Vec2(7, Ymodifier + 2 + 10 + 10), MC_Colour(255, 255, 255), 1.f, 1.f);

	RenderUtils::DrawCenteredText(Vec2(7 + 55, Ymodifier + 2 + 8), getDirection(player->bodyRot.y - 90), MC_Colour(255, 255, 255), 1.5f, 1.f);

	RenderUtils::FillRectangle(boxPos, MC_Colour(0, 0, 0), .15f);
	RenderUtils::FlushText();
}