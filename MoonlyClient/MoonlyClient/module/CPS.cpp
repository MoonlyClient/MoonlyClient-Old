#include "../ClientManager.h"
#include "../../Other/Utils.h"
#include "CPS.h"

void CPS::onRender() {
	LocalPlayer* player = Minecraft::ClientInstance()->LocalPlayer();

	if (player == nullptr || !Minecraft::ClientInstance()->MinecraftGame()->canUseKeys()) return;

	auto cpsText = "CPS: " + std::to_string(Minecraft::cpsLeft) + " | " + std::to_string(Minecraft::cpsRight);
	float boxWidth = RenderUtils::GetTextWidth(cpsText, 1.f) + 8;
	float Ymodifier = 60;
	Vec4 boxPos = Vec4(5, Ymodifier, boxWidth, 10 + Ymodifier);

	RenderUtils::RenderText(cpsText, Vec2(7, Ymodifier + 2), MC_Colour(255, 255, 255), 1.f, 1.f);

	RenderUtils::FillRectangle(boxPos, MC_Colour(0, 0, 0), .15f);
	RenderUtils::FlushText();
}