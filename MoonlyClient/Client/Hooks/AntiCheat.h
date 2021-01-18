#pragma once
#include "../../Other/Module.h"

class AntiCheat : public Hook {
public:
	void Install();
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

void AntiCheat::Install() {
	if (MH_CreateHook(&LoadLibraryA, &LoadLibraryACallback, (LPVOID*)(&_LoadLibraryA)) == MH_OK) {
		Utils::DebugLogOutput("Successfully created LoadLibraryA Hook, Installing Hook now...");
		MH_EnableHook(&LoadLibraryA);
	} else {
		Utils::DebugLogOutput("Failed to create LoadLibraryA Hook!");
	}

	if (MH_CreateHook(&LoadLibraryExA, &LoadLibraryExACallback, (LPVOID*)(&_LoadLibraryExA)) == MH_OK) {
		Utils::DebugLogOutput("Successfully created LoadLibraryExA Hook, Installing Hook now...");
		MH_EnableHook(&LoadLibraryExA);
	} else {
		Utils::DebugLogOutput("Failed to create LoadLibraryExA Hook!");
	}

	// ToDo : Block all methods used to inject dll
}