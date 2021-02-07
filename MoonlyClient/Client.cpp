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


DWORD WINAPI keyThread(LPVOID lpParam) {
	bool* keyMap = static_cast<bool*>(malloc(0xFF * 4 + 0x4));
	if (keyMap == nullptr)
		throw std::exception("Keymap not allocated");

	auto clickMap = reinterpret_cast<uintptr_t>(malloc(5));
	if (clickMap == 0)
		throw std::exception("Clickmap not allocated");

	bool* keyMapAddr = nullptr;
	uintptr_t sigOffset = Utils::FindSig("48 8D 0D ?? ?? ?? ?? 89 1C B9");

	if (sigOffset != 0x0) {
		int offset = *reinterpret_cast<int*>((sigOffset + 3));
		keyMapAddr = reinterpret_cast<bool*>(sigOffset + offset + 7);
	}
	else {
		throw std::exception("Keymap not located");
	}

	HIDController** hidController = Minecraft::HIDController();

	while (Utils::running) {
		if (*hidController != nullptr) {
			for (uintptr_t key = 0; key < 5; key++) {
				bool newKey = (*hidController)->clickMap[key];
				bool* oldKey = reinterpret_cast<bool*>(clickMap + key);

				if (newKey != *oldKey) {
					Menu::onMouseClickUpdate((int)key, newKey);

					if (newKey) {
						if ((int)key == 0)
							Minecraft::leftclickCount++;
						else if ((int)key == 1)
							Minecraft::rightclickCount++;
					}
				}
			}

			memcpy(reinterpret_cast<void*>(clickMap), &(*hidController)->leftClickDown, 5);
		}

		memcpy_s(keyMap, 0xFF * 4, keyMapAddr, 0xFF * 4);

		Sleep(2);
	}

	MH_DisableHook(MH_ALL_HOOKS);

	Sleep(200);

	MH_Uninitialize();

	Sleep(100);

	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), 1);  // Uninject
}

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

	DWORD keyThreadId;
	CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)keyThread, lpParam, NULL, &keyThreadId); 

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