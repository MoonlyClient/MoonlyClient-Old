#include "ClientManager.h"
#include "../Other/Module.h"

std::vector<Hook*> ClientManager::Hooks;
std::vector<Module*> ClientManager::Modules;
std::vector<std::string> ClientManager::Categories;

#include "Hooks/ClientInstance.h"
#include "Hooks/RenderContext.h"
#include "Hooks/GameMode.h"
#include "Hooks/RakNetInstance.h"
#include "Hooks/AntiCheat.h"
#include "Hooks/Mouse.h"
#include "Hooks/ChatScreenController.h"
#include "Hooks/Keyboard.h"

int Minecraft::frameCount = 0;
int Minecraft::fps = 0;
int Minecraft::cpsLeft = 0;
int Minecraft::leftclickCount = 0;
int Minecraft::cpsRight = 0;
int Minecraft::rightclickCount = 0;

ClientInstance* Minecraft::CachedInstance = nullptr; //Resolve error on compile
C_GuiData* Minecraft::CachedGuiData = nullptr; //Resolve error on compile
HIDController* Minecraft::CachedHIDController = nullptr; //Resolve error on compile
GameMode* Minecraft::CachedGameMode = nullptr; //Resolve error on compile
RakNetInstance* Minecraft::CachedRakNetInstance = nullptr; //Resolve error on compile
CommandMgr* ClientManager::CmdMgr = nullptr; //Resolve error on compile

void ClientManager::InitHooks() {

	if (MH_Initialize() == MH_OK) {
		Hooks.push_back(new ClientInstance_Hook());
		Hooks.push_back(new RenderContext());
		Hooks.push_back(new GameMode_Hook());
		Hooks.push_back(new RakNetInstance_Hook());
		Hooks.push_back(new AntiCheat());
		Hooks.push_back(new Mouse_Hook());
		Hooks.push_back(new ChatScreenController_Hook());
		Hooks.push_back(new Keyboard_Hook());
	}

	Utils::DebugLogOutput("Initializing Hooks...");

	for (int I = 0; I < Hooks.size(); I++) { //Initialize the hooks
		Hooks.at(I)->Install();
	}
}

#include "Modules/AutoSprint.h"
#include "Modules/GUI.h"
#include "Modules/NightVision.h"
#include "Modules/Compass.h"
#include "Modules/Coords.h"
#include "Modules/FPS.h"
#include "Modules/CPS.h"
#include "Modules/Keystroke.h"
#include "Modules/MenuGUI.h"
#include "Modules/Uninject.h"

void ClientManager::InitModules() {
	ClientManager::CmdMgr = new CommandMgr();
	CmdMgr->Init();

	Modules.push_back(new AutoSprint());
	Modules.push_back(new GUI());
	Modules.push_back(new NightVision());
	Modules.push_back(new Compass());
	Modules.push_back(new Coords());
	Modules.push_back(new FPS());
	Modules.push_back(new CPS());
	Modules.push_back(new Keystroke());
	//Modules.push_back(new MenuGUI());

#ifdef __DEBUG
	Modules.push_back(new Uninject());
#endif

	for (int I = 0; I < Modules.size(); I++) { //Initialize Categories
		bool exists = false;
		for (auto currCategory : Categories) {
			if (currCategory == Modules.at(I)->category) exists = true;
		}
		if (!exists) {
			Categories.push_back(Modules.at(I)->category);
		}
	}
}

class Module* ClientManager::GetModuleByName(std::string name) {
	for (auto Module : Modules) {
		if (Module->name == name) {
			return Module;
		}
	}
}

std::vector<class Module*> ClientManager::GetModulesFromCategory(std::string Category) {
	bool exists = false;
	for (auto Curr : Categories) {
		if (Curr == Category) exists = true;
	}
	if (exists) {
		std::vector<Module*> ModulesArr;
		for (auto Module : Modules) {
			if (Module->category == Category) ModulesArr.push_back(Module);
		}
		return ModulesArr;
	}
	else {
		return std::vector<Module*>();
	}
}