#pragma once

#include "../Hook.h"
#include "../../data/GameData.h"
#include "../../module/ModuleManager.h"
#include "../../sdk/MinecraftUIRenderContext.h"

class RenderContextHook : public Hook {
public:
	void install();
};

typedef void(__stdcall* RenderUIContext_render)(__int64 _this, MinecraftUIRenderContext* ctx);
RenderUIContext_render _RenderUIContext_render;

void RenderUIContext_render_callback(__int64 _this, MinecraftUIRenderContext* ctx) {
	ClientInstance* Curr = gData.getClientInstance();
	MinecraftGame* mcGame = Curr->MinecraftGame();

	if (Curr != nullptr && mcGame != nullptr && mcGame->getCleanFont() != nullptr) {
		RenderUtils::setContext(ctx, mcGame->getMinecraftiaFont());

		gData.frameCount++;

		for (auto module : moduleMgr.modules) {
			if (module->isEnabled)
				module->onRender();
		}

		RenderUtils::flushText();
	}

	_RenderUIContext_render(_this, ctx);
}

void RenderContextHook::install() {
	this->hookSig("MinecraftUIRenderContext::render", xorstr_("48 8B C4 48 89 58 ?? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 0F 29 70 ?? 0F 29 78 ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 4C 8B"), &RenderUIContext_render_callback, reinterpret_cast<LPVOID*>(&_RenderUIContext_render));
}