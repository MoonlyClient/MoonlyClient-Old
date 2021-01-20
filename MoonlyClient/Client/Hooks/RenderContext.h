#pragma once
#include "../../Other/Module.h"
#include "../../Client/Modules/MenuGUI.h"

class RenderContext : public Hook {
public:
	void Install();
};

typedef void(__stdcall* RenderUIContext)(__int64 a1, MinecraftUIRenderContext* Ctx);
RenderUIContext _RenderContext;

void RenderCallback(__int64 a1, MinecraftUIRenderContext* Ctx) {
	ClientInstance* Curr = Minecraft::ClientInstance();
	MinecraftGame* mcGame = Curr->MinecraftGame();

	Minecraft::frameCount++;

	if (Curr != nullptr && mcGame != nullptr && mcGame->MCFont() != nullptr) {
		RenderUtils::SetContext(Ctx, mcGame->MCFont());

		for (auto Module : ClientManager::Modules) {
			if (Module->isEnabled) Module->onRender();
		}

		MenuGUI* menu = (MenuGUI*)ClientManager::GetModuleByName("MenuGUI");

		if (menu != nullptr) {
			//Utils::DebugLogOutput("Menu not null");

			if (menu->isEnabled) {
				// ToDo
			}
		}
	}

	_RenderContext(a1, Ctx);
}

void RenderContext::Install() {
	uintptr_t sigAddr = Utils::FindSig("48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 0F 29 70 ?? 0F 29 78 ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 4C 8B F2 48 89 54 24");
	if (sigAddr) {
		Utils::DebugLogOutput("Successfully found address needed for the RenderContext Hook, Preparing Hook install now...");
		if (MH_CreateHook((void*)sigAddr, &RenderCallback, reinterpret_cast<LPVOID*>(&_RenderContext)) == MH_OK) {
			Utils::DebugLogOutput("Successfully created RenderContext Hook, Installing hook now...");
			MH_EnableHook((void*)sigAddr);
		}
		else {
			Utils::DebugLogOutput("Failed to create RenderContext Hook!");
		}
	}
	else {
		Utils::DebugLogOutput("Failed to find address needed for the RenderContext Hook!");
	}
}