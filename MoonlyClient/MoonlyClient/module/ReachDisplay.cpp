#include "../ClientManager.h"
#include "../../Other/Utils.h"
#include "ReachDisplay.h"

void Reach::onRender() {
	LocalPlayer* player = Minecraft::ClientInstance()->LocalPlayer();

	if (player == nullptr || !Minecraft::ClientInstance()->MinecraftGame()->canUseKeys()) return;

	char str[40];
	sprintf(str, "%.2f", Minecraft::lastReach);
	auto reachText = "Reach: " + (std::string) str;

	float boxWidth = RenderUtils::GetTextWidth(reachText, 1.f) + 8;
	float Ymodifier = 70;
	Vec4 boxPos = Vec4(5, Ymodifier, boxWidth, 10 + Ymodifier);

	RenderUtils::RenderText(reachText, Vec2(7, Ymodifier + 2), MC_Colour(255, 255, 255), 1.f, 1.f);

	RenderUtils::FillRectangle(boxPos, MC_Colour(0, 0, 0), .15f);
	RenderUtils::FlushText();
}