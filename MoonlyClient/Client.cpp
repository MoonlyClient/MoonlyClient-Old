#include "SDK/Minecraft.h"
#include "Other/Utils.h"
#include "Client/ClientManager.h"

#if defined _M_X64
#pragma comment(lib, "MinHook.x64.lib")
#endif
#include <thread>

void Init(LPVOID lpParam) {
    Utils::hModule = (HMODULE)lpParam;

    Utils::DeletePath("Client/Output.txt");
    Utils::DebugLogOutput("Injected...");

    ClientManager::InitHooks();
    ClientManager::InitModules();

    std::thread countThread([] {
        while (true) {
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