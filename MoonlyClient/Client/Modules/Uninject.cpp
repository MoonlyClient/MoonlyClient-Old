#include "Uninject.h"

void Uninject::onEnable() {
	MH_DisableHook(MH_ALL_HOOKS);
	Sleep(100);
	MH_Uninitialize();
	FreeLibraryAndExitThread(Utils::hModule, 1);
}