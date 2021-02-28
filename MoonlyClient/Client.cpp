#include <thread>

#include "SDK/Minecraft.h"
#include "SDK/Classes/HIDController.h"
#include "Other/Utils.h"
#include "Other/Menu.h"
#include "Other/Module.h"
#include "Client/ClientManager.h"
#include "Other/Menu.h"
#include "Other/Authentification.h"

#if defined _M_X64
#pragma comment(lib, "MinHook.x64.lib")
#endif

DWORD WINAPI authThread(LPVOID lpParam) {
	Utils::DebugLogOutput("Auth thread started");

	// ToDo

	return 0;
}

void Init(LPVOID lpParam) {
    Utils::hModule = (HMODULE)lpParam;

    Utils::DeletePath("MoonlyClient/Output.txt");
    Utils::DebugLogOutput("Injected...");

	Utils::running = true;

    ClientManager::InitHooks();
    ClientManager::InitModules();

	DWORD authThreadId;
	CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)authThread, lpParam, NULL, &authThreadId);

    std::thread countThread([] {
        while (Utils::running) {
            Sleep(1000);

            Minecraft::fps = Minecraft::frameCount;
            Minecraft::frameCount = 0;
            Minecraft::cpsLeft = Minecraft::leftclickCount;
            Minecraft::leftclickCount = 0;
            Minecraft::cpsRight = Minecraft::rightclickCount;
            Minecraft::rightclickCount = 0;
        }
    });

    countThread.detach();

    Utils::DebugLogOutput("Count thread started");

    ExitThread(0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Init, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}