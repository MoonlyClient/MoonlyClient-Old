#pragma once

#include "Color.h"
#include "../utils/Utils.h"

class TexturePtr {
private:
	char pad_0x0[0x18];  //0x0000

public:
	TextHolder filePath;  //0x0018

private:
	char pad_0x0038[0x20];  //0x0038
};

class BitmapFont {
private:
	virtual void destructorFont();
	virtual void unk1();
	virtual void unk2();
	virtual void unk3();
	virtual void unk4();
	virtual void unk5();

public:
	virtual float getLineLength(TextHolder* str, float textSize, bool unknown);
	virtual float getLineHeight();
};

struct TextMeasureData {
	float textSize;
	int idk;
	bool bool1;
	bool bool2;
};

class MinecraftUIRenderContext {
public:
	virtual void Constructor(void);
	virtual float getLineLength(class BitmapFont* font, class TextHolder* text, float textSize, bool unknown);
	virtual float getTextAlpha();
	virtual void setTextAlpha(float alpha);
	virtual __int64 drawDebugText(const float* pos, class TextHolder* text, float* color, float alpha, unsigned int textAlignment, const float* textMeasureData, const void* caretMeasureData);
	virtual __int64 drawText(BitmapFont* font, const float* pos, TextHolder* text, float* color, float alpha, unsigned int textAlignment, const TextMeasureData* textMeasureData, const uintptr_t* caretMeasureData);
	virtual void flushText(float timeSinceLastFlush);
	virtual __int64 drawImage(TexturePtr* texturePtr, Vec2& ImagePos, Vec2& ImageDimension, __int64& a4, Vec2& idk);
	virtual __int64 __func1(); // idk
	virtual __int64 __func2(); // flushImages
	virtual __int64 __func3(); // beginSharedMeshBatch
	virtual __int64 __func4(); // endSharedMeshBatch
	virtual void drawRectangle(struct Vec4 position, Color colour, float alpha, int lineWidth);
	virtual void fillRectangle(struct Vec4 position, Color colour, float alpha);
};