#pragma once

class C_GuiData {
public:
	char pad_0x0000[0x20]; //0x0000
	Vec2 res; //0x0020
	Vec2 scaledRes; //0x0028

	float getGuiScale() {
		return *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(this) + 0x34);
	};

	uint16_t getMouseX() {
		return *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(this) + 0x52);
	};

	uint16_t getMouseY() {
		return *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(this) + 0x54);
	};
};