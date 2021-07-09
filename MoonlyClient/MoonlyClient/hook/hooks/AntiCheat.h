#pragma once

#include "../Hook.h"

class AntiCheat : public Hook {
public:
	void install();
};

typedef HMODULE(WINAPI* TYPE_LoadLibraryA)(LPCSTR);
TYPE_LoadLibraryA _LoadLibraryA = NULL;
HMODULE WINAPI LoadLibraryACallback(LPCSTR lpFileName)
{
	return NULL;
}

typedef HMODULE(WINAPI* TYPE_LoadLibraryExA)(LPCSTR, HANDLE, DWORD);
TYPE_LoadLibraryExA _LoadLibraryExA = NULL;
HMODULE WINAPI LoadLibraryExACallback(LPCSTR lpLibFileName, _In_ HANDLE hFile, _In_ DWORD  dwFlags)
{
	return NULL;
}

void AntiCheat::install() {
	if (MH_CreateHook(&LoadLibraryA, &LoadLibraryACallback, (LPVOID*)(&_LoadLibraryA)) == MH_OK) {
		Utils::DebugLogOutput("[HookManager] Successfully created LoadLibraryA hook, installing...");
		MH_EnableHook(&LoadLibraryA);
	} else {
		Utils::DebugLogOutput("[HookManager] Failed to create LoadLibraryA hook!");
	}

	if (MH_CreateHook(&LoadLibraryExA, &LoadLibraryExACallback, (LPVOID*)(&_LoadLibraryExA)) == MH_OK) {
		Utils::DebugLogOutput("[HookManager] Successfully created LoadLibraryExA hook, enabling...");
		MH_EnableHook(&LoadLibraryExA);
	} else {
		Utils::DebugLogOutput("[HookManager] Failed to create LoadLibraryExA hook!");
	}

	// ToDo : Block all methods used to inject dll
}