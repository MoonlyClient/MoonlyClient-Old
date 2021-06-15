#include <thread>
#include <Windows.h>

#include "include/MinHook.h"

#if defined _M_X64
#pragma comment(lib, "MinHook.x64.lib")
#endif

#include "MoonlyClient/hook/HookManager.h"
#include "MoonlyClient/module/ModuleManager.h"
#include "MoonlyClient/data/GameData.h"
#include "MoonlyClient/utils/Utils.h"

std::string lol = "Not gonna try to skid Moonly, don't forget signatures are stripped lol gl.";

DWORD WINAPI countThread(LPVOID lpParam) {
    Utils::DebugLogOutput("idk created lol");

    while (Utils::running) {
        Sleep(1000);

        gData.fps = gData.frameCount;
        Utils::DebugLogOutput(std::to_string(gData.fps));
        gData.frameCount = 0;
        gData.cpsLeft = gData.leftClickCount;
        gData.leftClickCount = 0;
        gData.cpsRight = gData.rightClickCount;
        gData.rightClickCount = 0;
    }

    MH_DisableHook(MH_ALL_HOOKS);

    Sleep(200);

    MH_Uninitialize();

    Sleep(100);

    FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), 1);  // Uninject
}

void Init(LPVOID lpParam) {
    Utils::hModule = (HMODULE)lpParam;

    Utils::DeletePath("MoonlyClient/logs.txt");
    Utils::DebugLogOutput("Injected...");

	Utils::running = true;

    hookMgr.init();
    moduleMgr.init();

    DWORD countThreadId;
    CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)countThread, lpParam, NULL, &countThreadId);
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