#include "HookManager.h"
#include "../../include/MinHook.h"

HookManager hookMgr;

void HookManager::init() {
	if (MH_Initialize() != MH_OK) {
		return;
	}

	// ToDo : Add hooks

	for (int i = 0; i < hooks.size(); i++) {
		hooks.at(i)->install();
	}
}