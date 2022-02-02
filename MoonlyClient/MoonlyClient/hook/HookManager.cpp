#include "HookManager.h"
#include "../../include/MinHook.h"

#include "hooks/AntiCheat.h"
#include "hooks/ChatScreenController.h"
#include "hooks/ClientInstance.h"
#include "hooks/GameMode.h"
#include "hooks/Keyboard.h"
#include "hooks/Mouse.h"
#include "hooks/RakNetInstance.h"
#include "hooks/RenderContext.h"

HookManager hookMgr;

void HookManager::init() {
	if (MH_Initialize() != MH_OK) {
		return;
	}

	hooks.push_back(new RenderContextHook());
	hooks.push_back(new AntiCheat());
	//hooks.push_back(new ChatScreenControllerHook());
	hooks.push_back(new ClientInstanceHook());
	hooks.push_back(new GameModeHook());
	hooks.push_back(new KeyboardHook());
	hooks.push_back(new MouseHook());
	//hooks.push_back(new RakNetInstanceHook());

	for (int i = 0; i < hooks.size(); i++) {
		hooks.at(i)->install();
	}
}