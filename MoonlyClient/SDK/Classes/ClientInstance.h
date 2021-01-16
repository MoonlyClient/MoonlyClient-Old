#pragma once
#include "TextHolder.h"
#include "MinecraftUIRenderContext.h"
#include "Actor.h"
#include "LocalPlayer.h"
#include "GameMode.h"

class ClientInstance {
public:
	class LocalPlayer* LocalPlayer() {
		if (this != nullptr) {
			return *reinterpret_cast<class LocalPlayer**>(reinterpret_cast<__int64>(this) + 0x138);
		}
		else {
			return nullptr;
		}
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

	bool isValidTarget(class Actor* Entity) {
		if (Entity == nullptr) {
			return false;
		}

		if (Entity->isInvisible() || !Entity->isAlive() || Entity->isImmobile()) {
			return false;
		}

		if (Entity->getEntityTypeId() > 60 && Entity->getEntityTypeId() < 104 && Entity->getEntityTypeId() != 63) {
			return false;
		}

		if (Entity->getFormattedNameTag().length() <= 1) {
			return false;
		}

		if (!(this->LocalPlayer()->canAttack(Entity, false))) {
			return false;
		}

		return true;
	}
};

class MinecraftGame {
public:
	class BitmapFont* MCFont() {
		return *reinterpret_cast<class BitmapFont**>(reinterpret_cast<__int64>(this) + 0xD8);
	}

	bool canUseKeys() {
		return *(bool*)(reinterpret_cast<uintptr_t>(this) + 0x260);
	}
};