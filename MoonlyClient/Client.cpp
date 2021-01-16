#include "Other/Utils.h"
#include "Client/ClientManager.h"

#if defined _M_X64
#pragma comment(lib, "MinHook.x64.lib")
#endif

void Init(LPVOID lpParam) {
    Utils::hModule = (HMODULE)lpParam;

    Utils::DeletePath("Client/Output.txt");
    Utils::DebugLogOutput("Injected...");

    ClientManager::InitHooks();
    ClientManager::InitModules();
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