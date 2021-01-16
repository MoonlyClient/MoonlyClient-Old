#pragma once

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
private:
	float _[140];

public:
	virtual void Constructor(void);
	virtual float getLineLength(class BitmapFont* font, class TextHolder* text, float textSize, bool unknown);
	virtual float getTextAlpha();
	virtual void setTextAlpha(float alpha);
	virtual __int64 drawDebugText(const float* pos, class TextHolder* text, float* color, float alpha, unsigned int textAlignment, const float* textMeasureData, const void* caretMeasureData);
	virtual __int64 drawText(BitmapFont* font, const float* pos, TextHolder* text, float* color, float alpha, unsigned int textAlignment, const TextMeasureData* textMeasureData, const uintptr_t* caretMeasureData);
	virtual void flushText(float timeSinceLastFlush);
	virtual __int64 drawImageNOTIMPLEMENTED();
	virtual __int64 drawNinesliceNOTIMPLEMENTED();
	virtual __int64 flushImagesNOTIMPLEMENTED();
	virtual __int64 beginSharedMeshBatchNOTIMPLEMENTED();
	virtual __int64 endSharedMeshBatchNOTIMPLEMENTED();
	virtual void drawRectangle(struct Vec4 position, MC_Colour colour, float alpha, int lineWidth);
	virtual void fillRectangle(struct Vec4 position, MC_Colour colour, float alpha);
};