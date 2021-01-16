#include "../ClientManager.h"
#include "../../Other/Utils.h"
#include "../../Other/MathUtils.h"
#include "FPS.h"

void FPS::onRender() {
	LocalPlayer* player = Minecraft::ClientInstance()->LocalPlayer();

	if (player == nullptr || !Minecraft::ClientInstance()->MinecraftGame()->canUseKeys()) return;

	auto fpsText = "FPS: " + std::to_string(Minecraft::fps);
	float boxWidth = RenderUtils::GetTextWidth(fpsText, 1.f) + 8;
	float Ymodifier = 50;
	Vec4 boxPos = Vec4(5, Ymodifier, boxWidth, 10 + Ymodifier);

	RenderUtils::RenderText(fpsText, Vec2(7, Ymodifier + 2), MC_Colour(255, 255, 255), 1.f, 1.f);

	RenderUtils::FillRectangle(boxPos, MC_Colour(0, 0, 0), .15f);
	RenderUtils::FlushText();
}