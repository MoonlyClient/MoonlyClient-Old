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

DWORD WINAPI countThread(LPVOID lpParam) {
    while (Utils::running) {
        Sleep(1000);

        gData.fps = gData.frameCount;
        gData.frameCount = 0;
        gData.cpsLeft = gData.leftclickCount;
        gData.leftclickCount = 0;
        gData.cpsRight = gData.rightclickCount;
        gData.rightclickCount = 0;
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