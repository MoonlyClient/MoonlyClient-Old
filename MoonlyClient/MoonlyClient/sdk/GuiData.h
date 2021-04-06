#pragma once
#include "../../Other/Utils.h"

class C_GuiData {
private:
	char pad_0x0000[0x18];  //0x0000
public:
	union {
		struct {
			float widthReal;   //0x0018
			float heightReal;  //0x001C
		};
		Vec2 windowSizeReal;  //0x0018
	};

	float widthReal2;   //0x0020
	float heightReal2;  //0x0024
	union {
		struct {
			float widthGame;   //0x0028
			float heightGame;  //0x002C
		};
		Vec2 windowSize;  //0x0028
	};

	void displayClientMessage(std::string a2) {
		using displayClientMessageF = void(__thiscall*)(void*, TextHolder&);
		static displayClientMessageF displayMessageFunc = reinterpret_cast<displayClientMessageF>(Utils::FindSig("48 89 5C 24 ?? 55 48 8D 6C 24 ?? 48 81 EC ?? ?? ?? ?? 48 C7 45 4F ?? ?? ?? ?? 33 DB 48 89 5D ?? 88 5D"));

		TextHolder text = TextHolder(a2);

		if (displayMessageFunc != nullptr)
			displayMessageFunc(this, text);
	}
};