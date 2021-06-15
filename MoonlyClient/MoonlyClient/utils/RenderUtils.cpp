#pragma once

#include "RenderUtils.h"
#include "Utils.h"
#include "../data/GameData.h"
#include "../sdk/ClientInstance.h"

class MinecraftUIRenderContext* RenderUtils::cachedContext = nullptr;
class BitmapFont* RenderUtils::cachedFont = nullptr;

void RenderUtils::setContext(class MinecraftUIRenderContext* Context, class BitmapFont* Font) {
	cachedContext = Context;
	cachedFont = Font;
}

void RenderUtils::flushText() {
	if (cachedContext != nullptr)
		cachedContext->flushText(0);
}

float RenderUtils::getTextWidth(std::string text, float textSize) {
	if (cachedContext != nullptr) {
		TextHolder myText(text);

		return cachedContext->getLineLength(cachedFont, &myText, textSize, false);
	}
}

void RenderUtils::renderText(std::string textStr, Vec2 pos, Color color, float textSize, float alpha) {
	if (cachedContext != nullptr) {
		TextHolder text(textStr);
		static uintptr_t caretMeasureData = 0xFFFFFFFF;

		pos.y -= 1;

		float posF[4];
		posF[0] = pos.x;
		posF[1] = pos.x + 1000;
		posF[2] = pos.y;
		posF[3] = pos.y + 1000;

		TextMeasureData textMeasure{};
		memset(&textMeasure, 0, sizeof(TextMeasureData));
		textMeasure.textSize = textSize;

		cachedContext->drawText(cachedFont, posF, &text, color.arr, alpha, 0, &textMeasure, &caretMeasureData);
	}
};

void RenderUtils::drawCenteredText(Vec2 pos, std::string text, Color color, float size, float textOpacity) {
	pos.x -= RenderUtils::getTextWidth(text, size) / 2;

	RenderUtils::renderText(text, pos, color, size, textOpacity);
}

void RenderUtils::drawKeystroke(char key, Vec2 pos) {
	if (cachedContext != nullptr) {
		std::string keyString = Utils::getKeybindName(key);
		GameSettingsInput* input = gData.getClientInstance()->getGameSettingsInput();

		Vec4 rectPos(pos.x, pos.y, pos.x + ((key == *input->spaceBarKey) ? 64.f : 20.f), pos.y + 20.f);
		Vec2 textPos((rectPos.x + 3.5 + (rectPos.z - rectPos.x) / 2) - (getTextWidth(keyString, 1) / 1.f), rectPos.y + 12.f - cachedFont->getLineHeight() / 2.f);

		if (key == *input->spaceBarKey) {
			fillRectangle(rectPos, Utils::isKeyDown(key) ? Color(255, 255, 255) : Color(0, 0, 0), .15f);
			fillRectangle(Vec4(
				rectPos.x + 20,
				rectPos.y + 9.f,
				rectPos.x + 20 + 25,
				(rectPos.y + 9.f + 2.f)), Color(255, 255, 255), 1.f);

			return;
		}

		fillRectangle(rectPos, Utils::isKeyDown(key) ? Color(255, 255, 255) : Color(0, 0, 0), .15f);
		renderText(keyString, textPos, Color(255, 255, 255), 1.f, 1.f);
	}
}

void RenderUtils::fillRectangle(Vec4 position, Color color, float alpha) {
	if (cachedContext != nullptr) {
		cachedContext->fillRectangle(Vec4(position.x, position.z, position.y, position.w), color, alpha);
	}
}

void RenderUtils::drawRectangle(Vec4 position, Color colour, float alpha, float lineWidth) {
	if (cachedContext != nullptr) {
		lineWidth /= 2;

		fillRectangle(Vec4(position.x - lineWidth, position.y - lineWidth, position.z + lineWidth, position.y + lineWidth), colour, alpha);
		fillRectangle(Vec4(position.x - lineWidth, position.y, position.x + lineWidth, position.w), colour, alpha);
		fillRectangle(Vec4(position.z - lineWidth, position.y, position.z + lineWidth, position.w), colour, alpha);
		fillRectangle(Vec4(position.x - lineWidth, position.w - lineWidth, position.z + lineWidth, position.w + lineWidth), colour, alpha);
	}
}