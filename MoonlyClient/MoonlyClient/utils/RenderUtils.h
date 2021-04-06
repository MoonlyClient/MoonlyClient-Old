#pragma once

#include <string>

#include "MathUtils.h"
#include "../sdk/Color.h"

class RenderUtils {
private:
	static class MinecraftUIRenderContext* cachedContext;
	static class BitmapFont* cachedFont;
public:
	static void setContext(class MinecraftUIRenderContext* Context, class BitmapFont* Font);
	static void flushText();
	static float getTextWidth(std::string text, float textSize);
	static void renderText(std::string text, Vec2 textPos, Color color, float textSize, float alpha);
	static void drawCenteredText(Vec2 pos, std::string text, Color color, float size, float textOpacity = 1);
	static void drawKeystroke(char key, Vec2 pos);
	static void fillRectangle(Vec4 position, Color color, float alpha);
	static void drawRectangle(Vec4 position, Color color, float alpha, float lineWidth);
};
