#include "../ClientManager.h"
#include "../../Other/Utils.h"
#include "Compass.h"
#include "../../Other/MathUtils.h"

void Compass::onRender() {
	LocalPlayer* player = Minecraft::ClientInstance()->LocalPlayer();

	if (player == nullptr || !Minecraft::ClientInstance()->MinecraftGame()->canUseKeys()) return;

	auto extraPoints = std::multimap<int, std::string>{};
	std::vector<Vec2> stacking{};

	const int deg = (int)(player->bodyRot.y + 180);
	const float degSubOffset = 0;
	const float sCenter = Minecraft::GuiData()->widthGame / 2;

	for (int off = -range; off <= range; off++) {
		int oDeg = (deg + off) % 360;
		if (oDeg < 0) oDeg += 360;

		const float xOff = sCenter + off + degSubOffset;
		constexpr float fadeOutPos = 0.25f;
		constexpr float centerCutoff = 5, centerFadeout = 10;
		float majorOpacity = this->opacity;
		float minorOpacity = majorOpacity;

		{
			if ((range - abs(off)) < range * fadeOutPos)  // Far from center
				minorOpacity = majorOpacity = lerp(0, opacity, (range - abs(off)) / (range * fadeOutPos));
			else if (abs(off) < centerFadeout)  // Close to center
				minorOpacity = lerp(0, opacity, (abs(off) - centerCutoff) / (centerFadeout - centerCutoff));
		}

		switch (oDeg) {
		case 0:
			drawCenteredText(Vec2(xOff, 30.f), "N", 1, majorOpacity);
			break;
		case 45:
			drawCenteredText(Vec2(xOff, 30.f), "NE", 1, majorOpacity);
			break;
		case 90:
			drawCenteredText(Vec2(xOff, 30.f), "E", 1, majorOpacity);
			break;
		case 135:
			drawCenteredText(Vec2(xOff, 30.f), "SE", 1, majorOpacity);
			break;
		case 180:
			drawCenteredText(Vec2(xOff, 30.f), "S", 1, majorOpacity);
			break;
		case 225:
			drawCenteredText(Vec2(xOff, 30.f), "SW", 1, majorOpacity);
			break;
		case 270:
			drawCenteredText(Vec2(xOff, 30.f), "W", 1, majorOpacity);
			break;
		case 315:
			drawCenteredText(Vec2(xOff, 30.f), "NW", 1, majorOpacity);
			break;
		}

		auto result = extraPoints.equal_range(oDeg);

		for (auto it = result.first; it != result.second; it++) {
			std::string pName = it->second;
			std::transform(pName.begin(), pName.end(), pName.begin(), ::toupper);

			Vec2 pos = Vec2(xOff, 31.f);

			int overlapping = 0;
			const float tSize = 0.75f;
			const float tWidth = RenderUtils::GetTextWidth(pName, tSize);
			pos.x -= tWidth / 2;
			const Vec2 myTextRange = Vec2(pos.x, pos.x + tWidth);

			for (const Vec2 otherTextRange : stacking) {
				// Check if other text overlaps us
				if (myTextRange.x < otherTextRange.y && otherTextRange.x < myTextRange.y) {
					overlapping++;
				}
			}
			stacking.push_back(myTextRange);
			pos.y += 5 * (overlapping + 1);
			RenderUtils::RenderText(pName, pos, MC_Colour(255, 255, 255), tSize, majorOpacity);
		}

		if (off != 0 && minorOpacity > 0) {
			if ((oDeg % 15) != 0) {
				if ((oDeg % 5) == 0) {
					RenderUtils::FillRectangle(Vec4(xOff - 0.25f, 16, xOff + 0.25f, 19), MC_Colour(255, 255, 255), minorOpacity);
				}
				continue;
			}

			// Bigger line with degree displayed
			RenderUtils::FillRectangle(Vec4(xOff - 0.5f, 15, xOff + 0.5f, 20), MC_Colour(255, 255, 255), minorOpacity);
			drawCenteredText(Vec2(xOff, 20.f), std::to_string(oDeg), 0.75f, minorOpacity);
		}
	}

	// Center line
	RenderUtils::FillRectangle(Vec4(sCenter - 0.5f, 15, sCenter + 0.5f, 25), MC_Colour(255, 255, 255), opacity);
	drawCenteredText(Vec2(sCenter, 25.f), std::to_string(deg), 0.75f, opacity);
	RenderUtils::FlushText();
}

void Compass::drawCenteredText(Vec2 pos, std::string text, float size, float textOpacity) {
	pos.x -= RenderUtils::GetTextWidth(text, size) / 2;
	RenderUtils::RenderText(text, pos, MC_Colour(255, 255, 255), size, textOpacity);
}