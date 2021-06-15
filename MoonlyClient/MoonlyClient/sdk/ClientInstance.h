#pragma once

#include "TextHolder.h"
#include "MinecraftUIRenderContext.h"
#include "Actor.h"
#include "LocalPlayer.h"
#include "GameMode.h"
#include "GuiData.h"
#include "GameSettingsInput.h"
#include "LoopbackPacketSender.h"

class C_Player;

class C_Minecraft {
public:
	char pad_0x0000[0xB0];  //0x0000

	float* timer;  //0x00B0
};

class BlockTessellator;

class ResourceLocation {
public:
	char pad[0x28];
	__int64 hashCode; // 0x28
	char pad2[8];
};

namespace mce {
	class TextureGroup;
	class MaterialPtr;
	class Mesh {
	public:
		void renderMesh(__int64 screenContext, mce::MaterialPtr* material, size_t numTextures, __int64** textureArray);

		template <size_t numTextures>
		void renderMesh(__int64 screenContext, mce::MaterialPtr* material, std::array<__int64*, numTextures> textures) {
			this->renderMesh(screenContext, material, numTextures, &textures[0]);
		}
	};
	class TexturePtr {
	public:
		__int64* clientTexture;
		char pad[0x8];
		ResourceLocation resourceLocation; // 0x10

	
		__int64* getClientTexture() {
			return this->clientTexture;
		}
	};
	class MaterialPtr {
	public:
		std::shared_ptr<void> materialPtr;

	
		MaterialPtr(const std::string& materialName);
	};
};


class LevelRenderer {
public:
	char pad_0x0000[0x58];  //0x0000

	mce::TextureGroup* textureGroup; // 0x0058

	char pad_0x0060[0xE0];  //0x0060

	mce::TexturePtr atlasTexture; // 0x140

	char pad_0x0188[0x150];  //0x0188

	BlockTessellator* blockTessellator; // 0x02D8

	char pad_0x02F0[0x5EC];  //0x02E0

	Vec3 origin;  //0x0890

	__int64 getLevelRendererPlayer() {
		return reinterpret_cast<__int64>(this) + 0x310;
	}
};

struct FontEntry {
public:
	BitmapFont* font;

private:
	void* sharedFontPtr;
};

struct FontList {
public:
	FontEntry fontEntries[9];
};

struct FontRepository {
private:
	uintptr_t* font_repository_vtable;  // 0x0000
	__int64 pad;                        // 0x0008
	void* ptrToSelf;                    // 0x0010
	void* ptrToSelfSharedPtr;           // 0x0018
	__int64 pad2;                       // 0x0020
public:
	FontList* fontList;   //0x0028
};

class MinecraftGame {
public:
	FontRepository* getFontRepository() {
		return *reinterpret_cast<FontRepository**>(reinterpret_cast<__int64>(this) + 0x100);
	}

	BitmapFont* getWtfFont() {
		return this->getFontRepository()->fontList->fontEntries[0].font;
	};

	BitmapFont* getCleanFont() {
		return this->getFontRepository()->fontList->fontEntries[7].font;
	};

	BitmapFont* getCrashFont() {
		return this->getFontRepository()->fontList->fontEntries[6].font;
	}

	BitmapFont* getMinecraftiaFont() {
		return this->getFontRepository()->fontList->fontEntries[3].font;
	}

	bool canUseKeys() {
		return *(bool*)(reinterpret_cast<uintptr_t>(this) + 0x2F8);
	}
};

struct PtrToGameSettings3 {

	char pad_0x0000[0x18];

	GameSettingsInput* settingsInput;
};

struct PtrToGameSettings2 {

	char pad_0x0000[0x148];

	PtrToGameSettings3* ptr;
};

struct PtrToGameSettings1 {

	char pad_0x0000[0x18];

	PtrToGameSettings2* ptr;
};

class ClientInstance {
public:
	char firstPad[0x90];  //0x0008

	MinecraftGame* minecraftGame;  //0x0098

	MinecraftGame* N0000080C;  //0x00A0

	MinecraftGame* N0000080D;  //0x00A8

	C_Minecraft* minecraft;  //0x00B0

	char pad_0x0068[0x8];  //0x00B8

	LevelRenderer* levelRenderer;  //0x00C0

	char pad_0x0078[0x8];  //0x00C8

	LoopbackPacketSender* loopbackPacketSender;  //0x00D0

	char pad_0x0088[0x18];  //0x00D8

	PtrToGameSettings1* ptr;  //0x00F0

	class LocalPlayer* LocalPlayer() {
		if (this != nullptr) {
			return *reinterpret_cast<class LocalPlayer**>(reinterpret_cast<__int64>(this) + 0x138);
		}
		else {
			return nullptr;
		}
	}

	class C_GuiData* getGuiData() {
		return *reinterpret_cast<class C_GuiData**>((uintptr_t)(this) + 0x4D8);
	}

	class MinecraftGame* MinecraftGame() {
		if (this != nullptr) {
			return *reinterpret_cast<class MinecraftGame**>(reinterpret_cast<__int64>(this) + 0x98);
		}
		else {
			return nullptr;
		}
	}

	void displayClientMessage(std::string* a2) {
		using displayClientMessage = void(__thiscall*)(void*, TextHolder&);
		static displayClientMessage displayMessageFunc = reinterpret_cast<displayClientMessage>(Utils::FindSig("48 89 5C 24 ?? 55 48 8D 6C 24 ?? 48 81 EC ?? ?? ?? ?? 48 C7 45 4F ?? ?? ?? ?? 33 DB 48 89 5D ?? 88 5D"));

		TextHolder text = TextHolder(*a2);

		if (displayMessageFunc != nullptr)
			displayMessageFunc(this, text);
	}

	Vec2* getMousePos() {
		uintptr_t _this = reinterpret_cast<uintptr_t>(this);
		return reinterpret_cast<Vec2*>(_this + 0x448);
	}

	inline GameSettingsInput* getGameSettingsInput() { return this->ptr->ptr->ptr->settingsInput; };
};
